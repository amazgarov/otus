#include "ip_filter.h"

#include "gtest/gtest.h"

TEST(SampleSuite, SampleTest)
{
	// dummy test
	EXPECT_TRUE(true);
}

int main(int argc, char **argv)
{
	::testing::InitGoogleTest(&argc, argv);
	int ret = RUN_ALL_TESTS();
	return ret;
}