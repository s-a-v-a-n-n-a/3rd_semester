#include "Rectangle.hpp"

Rectangle::Rectangle(const double par_width, const double par_height, const char par_type, const Radius_vector &par_centre_position, const Radius_vector &par_velocity, const double par_weight, const Color par_color) : Shape(par_type, par_centre_position, par_velocity, par_weight, par_color)
{
	valid = true;
	
	// side = par_side;
	width = par_width;
	height = par_height;
}

// void Rectangle::move(const Radius_vector &par_centre_position)
// {
// 	set_centre_position(par_centre_position);
// }

void Rectangle::draw(Screen_information *screen)
{
	size_t screen_width  = screen->get_width();
	size_t screen_height = screen->get_height();

	for (unsigned x = 0; x < screen_width; ++x)
	{
		for (unsigned y = 0; y < screen_height; ++y)
		{
			double x0 = get_centre_position().get_x();
			double y0 = get_centre_position().get_y();
			// double square_size = (side/2) * (side/2);
			double square_width = (width/2) * (width/2);
			double square_height = (height/2) * (height/2);
			// if ((x - x0) * (x - x0) < square_width && (y - y0) * (y - y0) < square_height)
			if (x <= x0 + width/2.0 && x >= x0 - width/2.0 && y <= y0 + height/2.0 && y >= y0 - height/2.0)
			{
				screen->set_color(y, x, get_color());
			}
		}
	}
}
