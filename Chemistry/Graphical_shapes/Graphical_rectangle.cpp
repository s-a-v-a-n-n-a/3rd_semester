#include "Graphical_rectangle.hpp"

Graphical_rectangle::Graphical_rectangle(const double par_width, const double par_height, 
	                 const char par_type, const Radius_vector &par_centre_position, const Color par_color) : Graphical_shape(par_type, par_centre_position, par_color)
{
	assert(par_width >= EPSILON);
	assert(par_height >= EPSILON);

	width = par_width;
	height = par_height;
}

void Graphical_rectangle::draw(Screen_information *screen)
{
	assert(screen);

	size_t screen_width  = screen->get_width();
	size_t screen_height = screen->get_height();

	for (unsigned x = 0; x < screen_width; ++x)
	{
		for (unsigned y = 0; y < screen_height; ++y)
		{
			double x0 = get_centre_position().get_x();
			double y0 = get_centre_position().get_y();
			
			double square_width  = (width/2) * (width/2);
			double square_height = (height/2) * (height/2);
			
			if (x <= x0 + width/2.0 && x >= x0 - width/2.0 && y <= y0 + height/2.0 && y >= y0 - height/2.0)
			{
				screen->set_color(y, x, get_color());
			}
		}
	}
}

