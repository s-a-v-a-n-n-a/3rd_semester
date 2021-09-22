#include "Rectangle.hpp"

Rectangle::Rectangle(const double par_side, const Radius_vector &par_centre_position, const Radius_vector &par_direction, const double par_weight, const Color par_color) : Shape(par_centre_position, par_direction, par_weight, par_color)
{
	valid = true;
	side = par_side;
}

void Rectangle::move(const Radius_vector &par_centre_position)
{
	set_centre_position(par_centre_position);
}

void Rectangle::draw(Screen_information *screen)
{
	size_t width  = screen->get_width();
	size_t height = screen->get_height();

	for (unsigned x = 0; x < width; ++x)
	{
		for (unsigned y = 0; y < height; ++y)
		{
			double x0 = get_centre_position().get_x();
			double y0 = get_centre_position().get_y();
			double square_size = (side/2) * (side/2);
			if ((x - x0) * (x - x0) < square_size && (y - y0) * (y - y0) < square_size)
			{
				screen->set_color(y, x, get_color());
			}
		}
	}
}
