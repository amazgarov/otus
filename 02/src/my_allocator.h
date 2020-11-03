template <typename T, std::size_t PreallocateSize>
class my_allocator
{
	// pointer to the start of the chunk
	T *data;
	std::size_t used_size;

public:
	using value_type = T;

	using _MyType = my_allocator<T, PreallocateSize>;

	my_allocator()
	{
		data = nullptr;
		used_size = 0;
	}

	template <typename U>
	my_allocator(const my_allocator<U, PreallocateSize> &) : my_allocator()
	{
		// calls default constructor to avoid memberwise copy
	}

	~my_allocator()
	{
		std::free(data);
	}

	T *allocate(std::size_t n)
	{
		// allocate reserved size on first call
		if (data == nullptr)
		{
			auto raw_pointer = std::malloc(PreallocateSize * sizeof(T));
			data = reinterpret_cast<T *>(raw_pointer);
		}
		if (used_size + n > PreallocateSize)
		{
			throw std::bad_alloc();
		}
		auto p = data + used_size;
		used_size += n;
		return p;
	}

	void deallocate(T *, std::size_t)
	{
		// implementing deallocate is not a trivial task, skipped for this educational example
	}

	template <typename U, typename... Args>
	void construct(U *p, Args &&...args)
	{
		new (p) U(std::forward<Args>(args)...);
	}

	void destroy(T *p)
	{
		p->~T();
	}

	template <typename U>
	struct rebind
	{
		using other = my_allocator<U, PreallocateSize>;
	};
};
