#include "ip_filter.h"

#include <iostream>

#ifdef _WIN32
#include <stdio.h>
#include <fcntl.h>
#include <io.h>
#endif

int main()
{
	try
	{
#ifdef _WIN32
		// change stdout from text mode to binary mode to avoid CR+LF line endings on windows
		// https://docs.microsoft.com/ru-ru/cpp/c-runtime-library/reference/setmode?view=msvc-160
		_setmode(_fileno(stdout), _O_BINARY);
#endif
		ip_filter::read_and_process();
	}
	catch (const std::exception &e)
	{
		std::cerr << e.what() << std::endl;
	}

	return 0;
}
