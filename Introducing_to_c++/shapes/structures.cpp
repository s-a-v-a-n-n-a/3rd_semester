#include "structures.hpp"

Work_field *work_field_create(System_of_axes coordinates, size_t list_size)
{
	Work_field *thus = (Work_field*)calloc(1, sizeof(Work_field));

	if (thus)
		Work_field(coordinates, list_size);

	return thus;
}

void work_field_delete(Work_field *thus)
{
	free(thus);
}

void Work_field::add_shape(Shape *shape)
{
	shapes->add_to_end(shape);
}

void draw_axes(sf::RenderWindow *window, System_of_axes coordinates)
{
	double abs_max = coordinates.get_x_up_bound();
	double abs_min = coordinates.get_x_low_bound();

	double offset_out_of_border_x = (abs_min > 0 ? abs_min : 0);

	double ord_min = coordinates.get_y_low_bound();
	double ord_max = coordinates.get_y_up_bound();

	double offset_out_of_border_y = (ord_max < 0 ? ord_max : 0);

	double offset_x = coordinates.get_left_corner().x - (abs_min > 0 ? abs_min : 0);
	double offset_y = coordinates.get_left_corner().y + (ord_max < 0 ? ord_max : 0);

	if (abs_min > 0)
		abs_min = 0;
	if (ord_max < 0)
		ord_max = 0;

	Vector_w_arrow abscissa_axe({offset_x, fabs(ord_max) + offset_y}, {fabs(abs_max - abs_min) + offset_x + (coordinates.get_x_up_bound() < 0 && coordinates.get_y_up_bound() < 0 ? fabs(coordinates.get_x_up_bound()) : 0), fabs(ord_max) + offset_y});
    
    abscissa_axe.draw_shape(window);

    Vector_w_arrow ordinate_axe({fabs(abs_min) + offset_x, fabs(ord_max - ord_min) + offset_y}, {fabs(abs_min) + offset_x, offset_y + (coordinates.get_x_low_bound() > 0 && coordinates.get_y_low_bound() > 0 ? coordinates.get_y_low_bound() : 0)});
    
    ordinate_axe.draw_shape(window);
}

void Work_field::draw(sf::RenderWindow *window)
{
	coordinates.draw(window);

	draw_axes(window, coordinates);

	size_t shapes_amount = shapes->get_length();
	for (size_t i = 0; i < shapes_amount; ++i)
	{
		(shapes->get_array())[i]->draw_shape(window);
	}
}
