#include "Canvas.hpp"

void Canvas::draw(Screen_information *screen)
{
	Visual_object::draw(screen);

	size_t width = get_width();
	size_t height = get_height();

	Color current_color = get_color();

	Radius_vector position(get_position());

	screen->draw_image(drawing, get_position(), width, height);
	// for (size_t i = 0; i < width; ++i)
	// {
	// 	for (size_t j = 0; j < height; ++j)
	// 	{
	// 		// if (drawing[i * height + j] != current_color)
	// 		// 	screen->draw_point(position + Radius_vector(i, j), drawing[i * height + j]);
	// 	}
	// }
}

bool Canvas::point_inside (const size_t par_x, const size_t par_y)
{
	size_t low_bound_x = get_position().get_x();
	size_t low_bound_y = get_position().get_y();

	if (par_x >= low_bound_x && par_x < low_bound_x + get_width() && par_y >= low_bound_y && par_y <= low_bound_y + get_height())
		return true;

	return false;
}

bool Canvas::on_mouse (const bool clicked, const size_t par_x, const size_t par_y)
{
	if (!point_inside(par_x, par_y))
		return false;

	if (pencil->get_color() != current_drawing_color)
		current_drawing_color = pencil->get_color();

	if (clicked)
	{
		drawing_state = true;
	}
	else
	{
		drawing_state = false;

		return true;
	}

		size_t width = get_width();
		size_t height = get_height();

		size_t position_x = get_position().get_x();
		size_t position_y = get_position().get_y();

		printf("%lu\n", (par_x - position_x) * height + (par_y - position_y));

		size_t begin_x = par_x - position_x > 10 ? par_x - position_x - 10 : par_x - position_x;
		size_t begin_y = par_y - position_y > 10 ? par_y - position_y - 10 : par_y - position_y;

		size_t end_x = par_x - position_x + 10 < width ? par_x - position_x + 10 : par_x - position_x;
		size_t end_y = par_y - position_y + 10 < height ? par_y - position_y + 10 : par_y - position_y;

		for (size_t i = begin_y; i < end_y; ++i)
			for (size_t j = begin_x; j < end_x; ++j)
				drawing[i * width + j] = current_drawing_color;
	// }

	return true;
}
