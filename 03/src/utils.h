/**
 * Helper template to print a tuple
 */
template <typename Tuple, std::size_t Index = std::tuple_size_v<Tuple> - 1>
struct _Tuple_printer
{
	static void print(const Tuple &tuple)
	{
		const std::size_t idx = std::tuple_size_v<Tuple> - 1 - Index;
		std::cout << std::get<idx>(tuple) << ".";
		_Tuple_printer<Tuple, Index - 1>::print(tuple);
	}
};

/**
 * Helper template to print a tuple, base case
 */
template <typename Tuple>
struct _Tuple_printer<Tuple, 0>
{
	static void print(const Tuple &tuple)
	{
		const std::size_t idx = std::tuple_size_v<Tuple> - 1;
		std::cout << std::get<idx>(tuple);
	}
};

/**
 * Prints IP passed as a tuple
 */
template <typename Tuple>
void print_tuple(const Tuple &tuple)
{
	_Tuple_printer<Tuple>::print(tuple);
}
