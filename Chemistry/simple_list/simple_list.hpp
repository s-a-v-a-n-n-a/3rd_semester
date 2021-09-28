#ifndef SIMPLE_LIST
#define SIMPLE_LIST

#include <cstdio>
#include <cstddef>
#include <cstdlib>

const size_t LIST_SIZE = 10;

template <typename list_type> class List
{
private:
	
	list_type *array;

	size_t capacity;
	size_t length;

public:

	List(size_t par_capacity)
	{
		array = (list_type*)calloc(par_capacity, sizeof(list_type));

		if (array)
		{
			capacity = par_capacity;
			length = 0;
		}
	}

	~List()
	{
		free(array);
	}

	list_type *get_array() { return array; }
	size_t     get_length() { return length; }

	void resize()
	{
		size_t new_capacity = capacity * 2;
		list_type *other_array = (list_type*)realloc(this->get_array(), 2 * new_capacity * sizeof(list_type));

		array = other_array;
		capacity = new_capacity;
	}

	void add_to_end(list_type value)
	{
		if (length >= capacity - 1)
			resize();

		array[length++] = value;
	}

	void slow_delete(size_t index)
	{
		for (size_t i = index + 1; i < length; ++i)
		{
			array[i - 1] = array[i];
		}

		length--;
	}
};

#endif // SIMPLE_LIST
