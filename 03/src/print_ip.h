#include <iostream>
#include <type_traits>

#include "traits.h"
#include "utils.h"
#include "assert.h"

/**
 * Prints IP as an integral type, byte by byte
 */
template <
	typename T,
	typename _Is_integral = std::enable_if_t<std::is_integral_v<T>>>
void print_ip(T number)
{
	unsigned char bytes[sizeof(T)];
	auto temp = static_cast<std::make_unsigned_t<T>>(number);
	for (size_t i = 0; i < sizeof(T); ++i)
	{
		bytes[i] = temp & 255;
		temp >>= 8;
	}
	for (auto i = sizeof(T) - 1; i > 0; --i)
	{
		std::cout << int(bytes[i]) << ".";
	}
	std::cout << int(bytes[0]);
}

// template <typename T, typename Fake1 = decltype(T().c_str()), int Fake2 = 0, int Fake3 = 0> // a simpler approach

/**
 * Prints IP passed as a string, as is
 */
template <
	typename T,
	typename _Is_string = std::enable_if_t<is_string<T>::value>,
	int Fake1 = 0>
void print_ip(T str)
{
	std::cout << str;
}

/**
 * Prints IP passed as a container
 */
template <
	typename T,
	/* is_stl_container_like is positive for std::string as well, so need to distinguish */
	typename _Is_container = std::enable_if_t<!is_string<T>::value && is_stl_container_like<T>::value>,
	int Fake1 = 0,
	int Fake2 = 0>
void print_ip(T container)
{
	auto it = container.cbegin();
	if (it == container.cend())
		return;
	std::cout << *it;
	it++;
	while (it != container.cend())
	{
		std::cout << "." << *it;
		it++;
	}
}

/**
 * Prints IP passed as a container, if all items are of the same type
 */
template <
	typename T,
	typename _Is_tuple = std::enable_if_t<is_tuple<T>::value>,
	/* this check is on a different line because compilation would fail if the type is bad */
	typename _Is_homogeneous = std::enable_if_t<is_homogeneous_tuple<T>::value>>
void print_ip(T tuple)
{
	//std::cout << "HOMOGENEOUS TUPLE\n";
	print_tuple(tuple);
}

/**
 * This template is called when a tuple is passed with items of different types
 */
template <
	typename T,
	typename _Is_tuple = std::enable_if_t<is_tuple<T>::value>,
	typename _Is_homogeneous = std::enable_if_t<!is_homogeneous_tuple<T>::value>,
	int Fake = 0> // makes this a different template
void print_ip(T tuple)
{
	//std::cout << "HETEROGENEOUS TUPLE\n";
	throw std::runtime_error("A homogeneous tuple required");
	// or static assert
	//static_assert(false, "A homogeneous tuple required");
	print_tuple(tuple);
}
