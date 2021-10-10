#include "Amounts_graph.hpp"

Amounts_graph::Amounts_graph(Shape_manager *par_manager, const Radius_vector &par_position, const Color &par_color, const double par_width, const double par_height)
: Visual_object(par_position, par_color, par_width, par_height)
{
	manager = par_manager;

	scale = 1.0;

	index_to_begin = 0;	

	for (size_t i = 0; i < shape_types_amount; ++i)
	{
		shapes_colors[i] = WHITE;
	}

	for (size_t i = 0; i < shape_types_amount; ++i)
	{
		shapes_amounts[i] = new size_t[get_width()];

		for (size_t j = 0; j < get_width(); ++j)
		{
			shapes_amounts[i][j] = 0;
		}
	}
}

Amounts_graph::~Amounts_graph()
{
	for (size_t i = 0; i < shape_types_amount; ++i)
	{
		delete [] shapes_amounts[i];
	}
}

void Amounts_graph::draw(Screen_information *screen)
{
	Visual_object::draw(screen);

	double x_offset = get_position().get_x();
	double y_offset = get_position().get_y();

	for (size_t i = 0; i < shape_types_amount; ++i)
	{
		for (size_t j = index_to_begin, k = 0; j < get_width() + index_to_begin; ++j, ++k)
		{
			size_t point = shapes_amounts[i][j % get_width()];

			// screen->set_color(y_offset + get_height() - point, x_offset + k, shapes_colors[i]);
			screen->draw_point(Radius_vector((x_offset + k) * scale, (y_offset + get_height() - point) * scale), shapes_colors[i]);
		}
	}
}

void Amounts_graph::tick(Screen_information *screen, const double delta_time)
{	
	size_t shapes_amount = manager->get_shapes()->get_length();
	Shape **shapes_array = manager->get_shapes()->get_array();

	size_t next_index = (index_to_begin + 1) % get_width();
	for (size_t i = 0; i < shape_types_amount; ++i)
	{
		shapes_amounts[i][next_index] = 0;
	}
	for (size_t i = 0; i < shapes_amount; ++i)
	{
		size_t current_type = shapes_array[i]->get_type();

		shapes_amounts[current_type][next_index]++;
	}
	index_to_begin++;
}
