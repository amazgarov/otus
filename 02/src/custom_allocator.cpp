template <typename T>
custom_allocator<T>::custom_allocator()
{
}

template <typename T>
template <typename U>
custom_allocator<T>::custom_allocator(const custom_allocator<U> &)
{
}

template <typename T>
T *custom_allocator<T>::allocate(std::size_t n)
{
	auto p = std::malloc(n * sizeof(T));
	if (!p)
		throw std::bad_alloc();
	return reinterpret_cast<T *>(p);
}

template <typename T>
void custom_allocator<T>::deallocate(T *p, std::size_t n)
{
	std::free(p);
}

template <class T, class U>
constexpr bool operator== (const custom_allocator<T>&, const custom_allocator<U>&) noexcept {
	return false;
}

template <class T, class U>
constexpr bool operator!= (const custom_allocator<T>&, const custom_allocator<U>&) noexcept {
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