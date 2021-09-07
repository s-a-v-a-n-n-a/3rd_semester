#ifndef SIMPLE_LIST
#define SIMPLE_LIST

#include <cstddef>
#include <cstdio>

#include "../shapes/shape_base.hpp"

extern const size_t LIST_SIZE;

typedef Shape* list_type;

struct List
{
	list_type *array;

	size_t capacity;
	size_t length;
};

List *list_create(size_t capacity);
void list_construct(List *thus, size_t capacity);
void list_delete(List *thus);
void list_destruct(List *thus);
void list_resize(List *thus);
void list_add_to_end(List *thus, list_type value);

#endif // SIMPLE_LIST
