#include "ip_filter.h"

#include "gtest/gtest.h"

#include <vector>
#include <string>

using namespace ip_filter;

TEST(ValidateIpAddress, InvalidNumberOfComponents)
{
	std::vector<std::string> input{"1", "2", "3"};
	ip_address_bytes parsed;
	auto result = ip_address::validate(input, parsed);
	EXPECT_FALSE(result);
}

TEST(ValidateIpAddress, ComponentNotInRangeLower)
{
	std::vector<std::string> input{"1", "2", "3", "-1"};
	ip_address_bytes parsed;
	auto result = ip_address::validate(input, parsed);
	EXPECT_FALSE(result);
}

TEST(ValidateIpAddress, ComponentNotInRangeHigher)
{
	std::vector<std::string> input{"1", "2", "3", "256"};
	ip_address_bytes parsed;
	auto result = ip_address::validate(input, parsed);
	EXPECT_FALSE(result);
}

TEST(ValidateIpAddress, ComponentNotANumber)
{
	std::vector<std::string> input{"1", "2", "3", "b"};
	ip_address_bytes parsed;
	auto result = ip_address::validate(input, parsed);
	EXPECT_FALSE(result);
}

TEST(ValidateIpAddress, ValidAddress)
{
	std::vector<std::string> input{"1", "2", "3", "4"};
	ip_address_bytes parsed;
	auto result = ip_address::validate(input, parsed);
	EXPECT_TRUE(result);
}

TEST(FilterByFirstByte, True)
{
	ip_address ip(1,2,3,4);
	EXPECT_TRUE(ip.filter(1));
}

TEST(FilterByFirstByte, False)
{
	ip_address ip(1,2,3,4);
	EXPECT_FALSE(ip.filter(2));
}

TEST(FilterByFirstAndSecondByte, True)
{
	ip_address ip(1,2,3,4);
	EXPECT_TRUE(ip.filter(1, 2));
}

TEST(FilterByFirstAndSecondByte, False)
{
	ip_address ip(1,2,3,4);
	EXPECT_FALSE(ip.filter(1, 3));
}

TEST(FilterByAnyByte, True)
{
	ip_address ip(1,2,3,4);
	EXPECT_TRUE(ip.filter_any(4));
}

TEST(FilterByAnyByte, False)
{
	ip_address ip(1,2,3,4);
	EXPECT_FALSE(ip.filter_any(5));
}

int main(int argc, char **argv)
{
	::testing::InitGoogleTest(&argc, argv);
	int ret = RUN_ALL_TESTS();
	return ret;
}