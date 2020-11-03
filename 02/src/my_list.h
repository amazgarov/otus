template <typename T, typename Allocator = std::allocator<T>>
class my_list
{
	// type declarations
	struct node
	{
		T data;
		node *next = nullptr;
	};
	using node_allocator_type = typename std::allocator_traits<Allocator>::template rebind_alloc<node>;
	using allocator_traits = std::allocator_traits<node_allocator_type>;

	// members
	node *head = nullptr, *tail = nullptr;
	node_allocator_type allocator;

public:
	my_list()
	{
		head = allocator_traits::allocate(allocator, 1);
		// placeholder node, not available from outside
		allocator_traits::construct(allocator, head, node{});
		tail = head;
	}

	~my_list()
	{
		while (head != nullptr)
		{
			auto p = head;
			head = head->next;
			allocator_traits::destroy(allocator, p);
			allocator_traits::deallocate(allocator, p, 1);
		}
	}

	void push_back(const T &value)
	{
		node *newNode = allocator_traits::allocate(allocator, 1);
		allocator_traits::construct(allocator, newNode, node{value, nullptr});
		tail->next = newNode;
		tail = newNode;
	}

	class iterator
	{
		node *ptr_current;

	public:
		iterator(node *ptr) : ptr_current(ptr) {}

		iterator operator++()
		{
			ptr_current = ptr_current->next;
			return *this;
		}
		T &operator*() { return ptr_current->data; }
		bool operator==(const iterator &rhs) { return ptr_current == rhs.ptr_current; }
		bool operator!=(const iterator &rhs) { return ptr_current != rhs.ptr_current; }
	};

	iterator begin() { return iterator(head->next); }
	iterator end() { return iterator(tail->next); }
};
