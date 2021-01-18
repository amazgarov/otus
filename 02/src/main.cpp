#include <map>
#include <iostream>

#include "my_allocator.h"
#include "my_list.h"

int fact(int x)
{
	int result = 1;
	for (auto i = x; i > 1; --i)
		result *= i;
	return result;
}

int main()
{
	// 1. создание экземпляра map<int, int>
	std::map<int, int> m;

	// 2. заполнение 10 элементами, где ключ - это число от 0 до 9, а значение - факториал ключа
	for (auto x = 0; x <= 9; ++x)
		m.emplace(x, fact(x));

	// 3. создание экземпляра std::map<int, int> с новым аллокатором, ограниченным 10 элементами
	std::map<int, int, std::less<int>, my_allocator<std::pair<const int, int>, 10>> std_map_my_allocator;

	// 4. заполнение 10 элементами, где ключ - это число от 0 до 9, а значение - факториал ключа
	for (auto x = 0; x <= 9; ++x)
		std_map_my_allocator.emplace(x, fact(x));

	// 5. вывод на экран всех значений (ключ и значение разделены пробелом) хранящихся в контейнере
	for(auto&& it : std_map_my_allocator)
		std::cout << it.first << " " << it.second << std::endl;

	// 6. создание экземпляра своего контейнера для хранения значений типа int
	my_list<int> my_list_std_allocator;

	// 7. заполнение 10 элементами от 0 до 9
	for (auto x = 0; x <= 9; ++x)
		my_list_std_allocator.push_back(x);

	// вывод на экран всех значений, хранящихся в контейнере (в задании нет)
	// for(auto&& it : my_list_std_allocator)
	// 	std::cout << it << std::endl;

	// 8. создание экземпляра своего контейнера для хранения значений типа int с новым аллокатором, ограниченным 10 элементами
	my_list<int, my_allocator<int, 10>> my_list_my_allocator;

	// 9. заполнение 10 элементами от 0 до 9
	for (auto x = 0; x <= 9; ++x)
		my_list_my_allocator.push_back(x);

	// 10. вывод на экран всех значений, хранящихся в контейнере
	for(auto&& it : my_list_my_allocator)
		std::cout << it << std::endl;
}