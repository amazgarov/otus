#include <tuple>
#include <type_traits>

/**
 * Metafunction to check if the type is a string
 */
template <typename T>
class is_string
{
	template <typename U>
	static decltype(U().c_str()) test(const U &);

	static int test(...);

public:
	static constexpr bool value = std::is_same_v<const char *, decltype(test(T()))>;
};

/**
 * Metafunction to check if the type is a container
 */
template <typename T>
class is_stl_container_like
{
	template <typename U>
	static constexpr bool test(
		U *pt,
		U const *cpt = nullptr,
		decltype(pt->begin()) * = nullptr,
		decltype(pt->end()) * = nullptr,
		decltype(cpt->begin()) * = nullptr,
		decltype(cpt->end()) * = nullptr,
		typename U::iterator *pi = nullptr,
		typename U::const_iterator *pci = nullptr)
	{
		typedef typename U::iterator iterator;
		typedef typename U::const_iterator const_iterator;
		typedef typename U::value_type value_type;
		return std::is_same_v<decltype(pt->begin()), iterator> &&
			   std::is_same_v<decltype(pt->end()), iterator> &&
			   std::is_same_v<decltype(cpt->begin()), const_iterator> &&
			   std::is_same_v<decltype(cpt->end()), const_iterator> &&
			   std::is_same_v<decltype(**pi), value_type &> &&
			   std::is_same_v<decltype(**pci), value_type const &>;
	}

	template <typename U>
	static constexpr bool test(...)
	{
		return false;
	}

public:
	static constexpr bool value = test<T>(nullptr);
};

/**
 * Checks if a tuple has all items of the same type
 */
template <typename T, int at = std::tuple_size_v<T> - 1>
struct is_homogeneous_tuple
{
	//using type = decltype(std::get<at>(T()));
	using type = std::tuple_element_t<at, T>;
	static const bool value = std::is_same_v<type, typename is_homogeneous_tuple<T, at - 1>::type>;
};

/**
 * Checks if a tuple has all items of the same type, base case
 */
template <typename T>
struct is_homogeneous_tuple<T, 0>
{
	//using type = decltype(std::get<0>(T()));
	using type = std::tuple_element_t<0, T>;
	static const bool value = true;
};

/**
 * Checks if a type is a tuple
 */
template <typename>
struct is_tuple : std::false_type
{
};

/**
 * Checks if a type is a tuple
 */
template <typename... T>
struct is_tuple<std::tuple<T...>> : std::true_type
{
};
