template <typename T>
struct custom_allocator
{
	using value_type = T;

	custom_allocator();

	template <typename U>
	custom_allocator(const custom_allocator<U> &);

	T *allocate(std::size_t n);

	void deallocate(T *p, std::size_t n);
};

#include "custom_allocator.cpp"
