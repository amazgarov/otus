template <typename T, int N>
struct custom_allocator
{
	using value_type = T;

	custom_allocator();

	template <typename U>
	custom_allocator(const custom_allocator<U, N> &);

	T *allocate(std::size_t n);

	void deallocate(T *p, std::size_t n);

	template <typename U>
	struct rebind
	{
		using other = custom_allocator<U, N>;
	};
};

#include "custom_allocator.cpp"
