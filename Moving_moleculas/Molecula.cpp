#include "Molecula.hpp"

Molecula::Molecula(const double par_radius, const Radius_vector &par_centre_position, const Radius_vector &par_direction, const double par_weight, const Color par_color) : Shape(par_centre_position, par_direction, par_weight, par_color)
{
	valid = true;
	radius = par_radius;
}

void Molecula::move(const Radius_vector &par_centre_position)
{
	set_centre_position(par_centre_position);
}

void Molecula::draw(Screen_information *screen)
{
	size_t width  = screen->get_width();
	size_t height = screen->get_height();

	for (unsigned x = 0; x < width; ++x)
	{
		for (unsigned y = 0; y < height; ++y)
		{
			double x0 = get_centre_position().get_x();
			double y0 = get_centre_position().get_y();
			if ((x - x0) * (x - x0) + (y - y0) * (y - y0) < radius * radius)
			{
				screen->set_color(y, x, get_color());
			}
		}
	}
}
