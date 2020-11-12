#include "ip_filter.h"

#include <cassert>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

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
		if (components.size() != 4)
			return false;
		for (auto i = 0; i < 4; ++i)
		{
			auto x = atoi(components.at(i).c_str());
			if (x < 0 || x > 255)
				return false;
			parsed[i] = x;
		}
		return true;
	}

	bool ip_address::filter(byte first_byte)
	{
		return a == first_byte;
	}

	bool ip_address::filter(byte first_byte, byte second_byte)
	{
		return a == first_byte && b == second_byte;
	}

	bool ip_address::filter_any(byte any_byte)
	{
		return (a == any_byte || b == any_byte || c == any_byte || d == any_byte);
	}

	void print(const ip_address &ip)
	{
		printf("%d.%d.%d.%d\n", ip.a, ip.b, ip.c, ip.d);
	}

	void read_and_process()
	{
		std::vector<ip_address> ip_pool;

		ip_address_bytes parsed;
		for (std::string line; std::getline(std::cin, line);)
		{
			std::vector<std::string> v = split(line, '\t');
			auto components = split(v.at(0), '.');
			if (ip_address::validate(components, parsed))
			{
				ip_pool.push_back(ip_address(parsed));
			}
		}

		// sorting in reverse lexicographical order
		std::sort(ip_pool.begin(), ip_pool.end(), [](const ip_address &t1, const ip_address &t2) {
			if (t1.a != t2.a)
				return t1.a > t2.a;
			if (t1.b != t2.b)
				return t1.b > t2.b;
			if (t1.c != t2.c)
				return t1.c > t2.c;
			return t1.d > t2.d;
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