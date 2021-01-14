template <typename T, std::size_t N>
custom_allocator<T, N>::custom_allocator()
{
	preallocate_size = N;
	data = nullptr;
	used_size = 0;
	std::cout << "CONSTRUCTOR" << __FUNCSIG__ << "\n";
}

template <typename T, std::size_t N>
custom_allocator<T, N>::~custom_allocator()
{
	std::cout << "DESTRUCTOR" << __FUNCSIG__ << "\n";
}

template <typename T, std::size_t N>
template <typename U>
custom_allocator<T, N>::custom_allocator(const custom_allocator<U, N> &) : custom_allocator()
{
}

template <typename T, std::size_t N>
T *custom_allocator<T, N>::allocate(std::size_t n)
{
	// allocate reserved size on first call
	if (data == nullptr)
	{
		data = reinterpret_cast<T *>(std::malloc(preallocate_size * sizeof(T)));
		std::cout << "PREALLOCATED AT " << data << " : " << __FUNCSIG__ << std::endl;
	}
	if (used_size + n > preallocate_size)
	{
		throw std::bad_alloc();
	}
	auto p = data + used_size;
	std::cout << "ALLOCATED AT " << p << " : " << __FUNCSIG__ << std::endl;
	used_size += n;
	return p;
}

template <typename T, std::size_t N>
void custom_allocator<T, N>::deallocate(T *p, std::size_t n)
{
	std::cout << "DEALLOCATE AT " << p << " : " << __FUNCSIG__ << "\n";
	//std::free(p);
}

template <class T, class U, std::size_t N>
constexpr bool operator==(const custom_allocator<T, N> &, const custom_allocator<U, N> &) noexcept
{
	return false;
}

template <class T, class U, std::size_t N>
constexpr bool operator!=(const custom_allocator<T, N> &, const custom_allocator<U, N> &) noexcept
{
	return true;
}

template <typename T, std::size_t N>
template <typename U, typename... Args>
void custom_allocator<T, N>::construct(U *p, Args &&... args)
{
	std::cout << "Construct " << __FUNCSIG__ << "\n";
	new (p) U(std::forward<Args>(args)...);
}

template <typename T, std::size_t N>
void custom_allocator<T, N>::destroy(T *p)
{
	std::cout << "Destroy " << __FUNCSIG__ << "\n";
	p->~T();
}
