#ifndef STRUCTURES_DESCRIBTIONS
#define STRUCTURES_DESCRIBTIONS

#include <cmath>

#include "../simple_list/simple_list.hpp"

#include "shape_base.hpp"
#include "derived_shapes.hpp"
#include "coordinate_axes.hpp"

struct Work_field
{
	System_of_axes coordinates;
	List *shapes;

	void construct(System_of_axes coordinates, size_t list_size = LIST_SIZE);
	void destruct();

	void add_shape(Shape *shape);

	void draw(sf::RenderWindow *window);
};

Work_field *work_field_create(System_of_axes coordinates, size_t list_size = LIST_SIZE);
void 		work_field_delete(Work_field *thus);

void draw_axes(sf::RenderWindow *window, System_of_axes coordinates);

#endif // STRUCTURES_DESCRIBTIONS
