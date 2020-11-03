#include "ip_filter.h"

#include <algorithm>
#include <cassert>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>

namespace ip_filter
{
	// ("",  '.') -> [""]
	// ("11", '.') -> ["11"]
	// ("..", '.') -> ["", "", ""]
	// ("11.", '.') -> ["11", ""]
	// (".11", '.') -> ["", "11"]
	// ("11.22", '.') -> ["11", "22"]
	std::vector<std::string> split(const std::string &str, char d)
	{
		std::vector<std::string> r;

		std::string::size_type start = 0;
		std::string::size_type stop = str.find_first_of(d);
		while (stop != std::string::npos)
		{
			r.push_back(str.substr(start, stop - start));

			start = stop + 1;
			stop = str.find_first_of(d, start);
		}

		r.push_back(str.substr(start));

		return r;
	}

	bool ip_address::validate(const std::vector<std::string> &components, ip_address_bytes &parsed)
	{
		if (components.size() != parsed.size())
			return false;
		for (auto i = 0; i < parsed.size(); ++i)
		{
			auto &s = components.at(i);
			auto is_numeric = std::all_of(s.cbegin(), s.cend(), ::isdigit);
			if (!is_numeric)
				return false;
			auto x = atoi(s.c_str());
			if (x < 0 || x > 255)
				return false;
			parsed[i] = x;
		}
		return true;
	}

	bool ip_address::filter(uint8_t first_byte)
	{
		return bytes[0] == first_byte;
	}

	bool ip_address::filter(uint8_t first_byte, uint8_t second_byte)
	{
		return bytes[0] == first_byte && bytes[1] == second_byte;
	}

	bool ip_address::filter_any(uint8_t any_byte)
	{
		return std::any_of(bytes.cbegin(), bytes.cend(), [any_byte](uint8_t component) {
			return component == any_byte;
		});
	}

	void print(const ip_address &ip)
	{
		const auto &b = ip.bytes;
		printf("%d.%d.%d.%d\n", b.at(0), b.at(1), b.at(2), b.at(3));
	}

	void read_and_process()
	{
		std::vector<ip_address> ip_pool;

		ip_address_bytes parsed;
		for (std::string line; std::getline(std::cin, line);)
		{
			auto v = split(line, '\t');
			auto components = split(v.at(0), '.');
			if (ip_address::validate(components, parsed))
			{
				ip_pool.push_back(ip_address(parsed));
			}
		}

		// sorting in reverse lexicographical order
		std::sort(ip_pool.begin(), ip_pool.end(), [](const ip_address &t1, const ip_address &t2) {
			auto i = 0;
			while (i < 4 && t1.bytes[i] == t2.bytes[i])
				++i;
			if (i == 4)
				return false;
			return t1.bytes[i] > t2.bytes[i];
		});

		// 1. print whole sorted set
		for (auto &ip : ip_pool)
		{
			print(ip);
		}

		// 2. filter by first byte and output
		for (auto &ip : ip_pool)
		{
			if (ip.filter(1))
			{
				print(ip);
			}
		}

		// 3. filter by first and second bytes and output
		for (auto &ip : ip_pool)
		{
			if (ip.filter(46, 70))
			{
				print(ip);
			}
		}

		// 4. filter by any byte and output
		for (auto &ip : ip_pool)
		{
			if (ip.filter_any(46))
			{
				print(ip);
			}
		}
	}
} // namespace ip_filter