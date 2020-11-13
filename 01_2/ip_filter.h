#include <vector>
#include <string>

namespace ip_filter
{
	typedef unsigned char byte;
	using ip_address_bytes = byte[4];

	struct ip_address
	{
		ip_address(byte _a, byte _b, byte _c, byte _d) : a(_a), b(_b), c(_c), d(_d){}
		ip_address(ip_address_bytes &bytes)
		{
			a = bytes[0];
			b = bytes[1];
			c = bytes[2];
			d = bytes[3];
		}
		byte a, b, c, d;
		static bool validate(const std::vector<std::string> &components, ip_address_bytes &parsed);
		bool filter(byte first_byte);
		bool filter(byte first_byte, byte second_byte);
		bool filter_any(byte any_byte);
	};

	void read_and_process();
} // namespace ip_filter
