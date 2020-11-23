#include <array>
#include <vector>
#include <string>

namespace ip_filter
{
	using ip_address_bytes = std::array<uint8_t, 4>;

	struct ip_address
	{
		ip_address(const ip_address_bytes &_bytes)
		{
			bytes = _bytes;
		}
		static bool validate(const std::vector<std::string> &components, ip_address_bytes &parsed);
		bool filter(uint8_t first_byte);
		bool filter(uint8_t first_byte, uint8_t second_byte);
		bool filter_any(uint8_t any_byte);
		ip_address_bytes bytes;
	};

	void read_and_process();
} // namespace ip_filter
