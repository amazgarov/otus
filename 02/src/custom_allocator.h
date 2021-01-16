#define LOG(NAME) std::cout << "[" << this << "] " << NAME << " " << __FUNCSIG__ << std::endl << std::flush;

template <typename T, std::size_t PreallocateSize>
struct custom_allocator
{
	using value_type = T;

	using _MyType = custom_allocator<T, PreallocateSize>;

	custom_allocator()
	{
		LOG("CONSTRUCTOR")
		data = nullptr;
		used_size = 0;
	}

	custom_allocator(const _MyType &) noexcept : custom_allocator()
	{
		LOG("COPY CONSTRUCTOR T->T")
	}

	template <typename U>
	custom_allocator(const custom_allocator<U, PreallocateSize> &) noexcept : custom_allocator()
	{
		LOG("COPY CONSTRUCTOR T->U")
	}

	~custom_allocator()
	{
		std::cout << "\nDESTRUCTOR " << this << " free at: " << data << " : " << __FUNCSIG__ << "\n\n";
		//std::free(data);
		//std::cout << "FREED " << this << " " << data << " : " << __FUNCSIG__ << "\n";
		//data = nullptr;
	}

	T *allocate(std::size_t n)
	{
		LOG("ALLOCATE")
		// allocate reserved size on first call
		if (data == nullptr)
		{
			auto raw_pointer = std::malloc(PreallocateSize * sizeof(T));
			data = reinterpret_cast<T *>(raw_pointer);
			std::cout << "PREALLOCATED AT " << data << std::endl;
		}
		if (used_size + n > PreallocateSize)
		{
			throw std::bad_alloc();
		}
		auto p = data + used_size;
		std::cout << "ALLOCATED AT " << p << std::endl;
		used_size += n;
		LOG("ALLOCATE END")
		return p;
	}

	void deallocate(T *p, std::size_t n)
	{
		LOG("DEALLOCATE");
		std::cout << "AT " << p << "\n";
		// implementing deallocate is not a trivial task, skipped for this educational example
	}

	template <typename U, typename... Args>
	void construct(U *p, Args &&...args)
	{
		std::cout << "Construct " << __FUNCSIG__ << "\n";
		new (p) U(std::forward<Args>(args)...);
	}

	void destroy(T *p)
	{
		std::cout << "Destroy " << __FUNCSIG__ << "\n";
		p->~T();
	}

	template <typename U>
	struct rebind
	{
		using other = custom_allocator<U, PreallocateSize>;
	};

	template <typename U>
	bool operator==(const _MyType &) noexcept
	{
		LOG("operator==U")
		return false;
	}

	template <typename U>
	bool operator!=(const _MyType &) noexcept
	{
		LOG("operator!=U")
		return true;
	}

	bool operator==(const _MyType &) noexcept
	{
		LOG("operator==T")
		return false;
	}

	bool operator!=(const _MyType &) noexcept
	{
		LOG("operator!=T")
		return true;
	}

private:
	// pointer to the start of the chunk
	T *data;
	std::size_t used_size;
};
