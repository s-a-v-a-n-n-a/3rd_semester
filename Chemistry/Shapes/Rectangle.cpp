#include "Rectangle.hpp"

Rectangle::Rectangle(const double par_scale, 
					 const char par_type, const Radius_vector &par_centre_position, const Radius_vector &par_velocity, const double par_weight, const Color par_color,
	                 const bool par_active, const bool par_just_born) : Shape(par_type, par_centre_position, par_velocity, par_weight, par_color, par_active, par_just_born)
{
	scale = par_scale;
	
	width = sqrt(par_weight / scale);//par_width;
	height = width * scale;//par_height;
}

void Rectangle::set_weight(const double par_weight)
{
	assert(par_weight > 0);
	assert(scale != 0);

	Shape::set_weight(par_weight);

	width = sqrt(par_weight / scale);//par_width;
	height = width * scale;
}

// void Rectangle::move(const Radius_vector &par_centre_position)
// {
// 	set_centre_position(par_centre_position);
// }

void Rectangle::draw(Screen_information *screen)
{
	assert(screen);

	screen->draw_rectangle(get_centre_position() - Radius_vector(width/2.0, height/2.0), get_color(), width, height);
}
