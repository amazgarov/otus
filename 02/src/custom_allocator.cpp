template <typename T, int N>
custom_allocator<T, N>::custom_allocator()
{
	std::cout << "I can allocate up to " << N << " elements total.\n";
}

template <typename T, int N>
template <typename U>
custom_allocator<T, N>::custom_allocator(const custom_allocator<U, N> &)
{
	std::cout << "This is a copy constructor" << __FUNCSIG__ << "\n";
}

template <typename T, int N>
T *custom_allocator<T, N>::allocate(std::size_t n)
{
	// TODO use N here
	auto p = std::malloc(n * sizeof(T));
	if (!p)
		throw std::bad_alloc();
	return reinterpret_cast<T *>(p);
}

template <typename T, int N>
void custom_allocator<T, N>::deallocate(T *p, std::size_t n)
{
	std::free(p);
}

template <class T, class U, int N>
constexpr bool operator==(const custom_allocator<T, N> &, const custom_allocator<U, N> &) noexcept
{
	return false;
}

template <class T, class U, int N>
constexpr bool operator!=(const custom_allocator<T, N> &, const custom_allocator<U, N> &) noexcept
{
	return true;
}

// template <typename T>
// template <typename U, typename... Args>
// void custom_allocator<T>::construct(U *p, Args &&... args)
// {
// 	new (p) U(std::forward<Args>(args)...);
// }

// template <typename T>
// void custom_allocator<T>::destroy(T *p)
// {
// 	p->~T();
// }