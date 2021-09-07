#include "simple_list.hpp"

extern const size_t LIST_SIZE = 10;

List *list_create(size_t capacity)
{
	List *thus = (List*)calloc(1, sizeof(List));

	if (thus)
		list_construct(thus, capacity);

	return thus;
}

void list_construct(List *thus, size_t capacity)
{
	thus->array = (list_type*)calloc(capacity, sizeof(list_type));

	if (thus->array)
	{
		thus->capacity = capacity;
		thus->length = 0;
	}
}

void list_delete(List *thus)
{
	list_destruct(thus);

	free(thus);
}

void list_destruct(List *thus)
{
	free(thus->array);
}

void list_resize(List *thus)
{
	size_t new_capacity = thus->capacity * 2;
	list_type *other_array = (list_type*)realloc(thus, 2 * new_capacity * sizeof(list_type));

	thus->array = other_array;
	thus->capacity = new_capacity;
}

void list_add_to_end(List *thus, list_type value)
{
	if (thus->length >= thus->capacity - 1)
		list_resize(thus);

	thus->array[thus->length++] = value;
}
