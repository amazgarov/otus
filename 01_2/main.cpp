#include "ip_filter.h"

#include <iostream>
#include <stdio.h>
#include <fcntl.h>
#include <io.h>

int main(int argc, char const *argv[])
{
	try
	{
		// change stdout from text mode to binary mode to avoid CR+LF line endings
		// https://docs.microsoft.com/ru-ru/cpp/c-runtime-library/reference/setmode?view=msvc-160
		_setmode( _fileno( stdout ), _O_BINARY );
		ip_filter::read_and_process();
	}
	catch (const std::exception &e)
	{
		std::cerr << e.what() << std::endl;
	}

	return 0;
}
