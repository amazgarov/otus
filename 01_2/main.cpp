#include "ip_filter.h"

#include <iostream>

int main(int argc, char const *argv[])
{
	try
	{
		ip_filter::read_and_process();
	}
	catch (const std::exception &e)
	{
		std::cerr << e.what() << std::endl;
	}

	return 0;
}
