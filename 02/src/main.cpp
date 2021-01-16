#include <map>
#include <vector>
#include <iostream>
//#include <memory>

#include "custom_allocator.h"

int fact(int x)
{
	int result = 1;
	for (auto i = x; i > 1; --i)
		result *= i;
	return result;
}

int main()
{
	freopen("output.txt", "w", stdout);
	std::vector<int, custom_allocator<int, 40>> vec;
	std::cout << "Adding elements\n";
	for(int i = 0; i<3; ++i)
		vec.push_back(i);

	std::cout << "\n\t<<< RETURN 0 >>>\n" << std::endl;
	return 0;

	// 1. создание экземпляра map<int, int>
	std::map<int, int> m;

	// 2. заполнение 10 элементами, где ключ - это число от 0 до 9, а значение - факториал ключа
	for (auto x = 0; x <= 9; ++x)
		m.emplace(x, fact(x));

	// 3. создание экземпляра std::map<int, int> с новым аллокатором, ограниченным 10 элементами
	std::map<int, int, std::less<int>, custom_allocator<std::pair<const int, int>, 10>> map_with_custom_alloc;

	// 4. заполнение 10 элементами, где ключ - это число от 0 до 9, а значение - факториал ключа
	for (auto x = 0; x <= 9; ++x)
		map_with_custom_alloc.emplace(x, fact(x));

	// 5. вывод на экран всех значений (ключ и значение разделены пробелом) хранящихся в контейнере
	for(auto&& it : map_with_custom_alloc)
		std::cout << it.first << " " << it.second << std::endl;

	// 6. создание экземпляра своего контейнера для хранения значений типа int
	// 7. заполнение 10 элементами от 0 до 9
	// 8. создание экземпляра своего контейнера для хранения значений типа int с новым аллокатором, ограниченным 10 элементами
	// 9. заполнение 10 элементами от 0 до 9
	// 10. вывод на экран всех значений, хранящихся в контейнере
}