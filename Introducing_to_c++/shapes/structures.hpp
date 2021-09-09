#ifndef STRUCTURES_DESCRIBTIONS
#define STRUCTURES_DESCRIBTIONS

#include <cmath>

#include "../simple_list/simple_list.hpp"

#include "shape_base.hpp"
#include "derived_shapes.hpp"
#include "coordinate_axes.hpp"

class Work_field
{
public:
	System_of_axes coordinates;
	List *shapes;

	Work_field(System_of_axes &coordinates, size_t list_size = LIST_SIZE) : coordinates(coordinates)
	{
		shapes = new List(list_size);
	}

	~Work_field()
	{
		delete shapes;
	}

	void add_shape(Shape *shape);

	void draw(sf::RenderWindow *window);
	// friend draw_axes(sf::RenderWindow *window, System_of_axes coordinates);
};

Work_field *work_field_create(System_of_axes coordinates, size_t list_size = LIST_SIZE);
void 		work_field_delete(Work_field *thus);

void draw_axes(sf::RenderWindow *window, System_of_axes coordinates);

#endif // STRUCTURES_DESCRIBTIONS
