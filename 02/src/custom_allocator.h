template <typename T, std::size_t N>
struct custom_allocator
{
	using value_type = T;

	custom_allocator();

	~custom_allocator();

	template <typename U>
	custom_allocator(const custom_allocator<U, N> &);

	T *allocate(std::size_t n);

	void deallocate(T *p, std::size_t n);

	template <typename U, typename... Args>
	void construct(U *p, Args &&... args);

	void destroy(T *p);

	template <typename U>
	struct rebind
	{
		using other = custom_allocator<U, N>;
	};

private:
	std::size_t preallocate_size;
	// pointer to the start of the chunk
	T* data;
	std::size_t used_size;
};

#include "custom_allocator.cpp"
