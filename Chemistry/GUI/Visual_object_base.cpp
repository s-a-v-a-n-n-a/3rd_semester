#include "Visual_object_base.hpp"

Visual_object::Visual_object(const Radius_vector &par_position, const Color &par_color, const size_t par_width, const size_t par_height)
: objects()
{
	position = par_position;
	color = par_color;

	width = par_width;
	height = par_height;

	active = false;
}

void Visual_object::draw(Screen_information *screen)
{
	assert(screen);

	screen->draw_rectangle(position, get_color(), width, height);
}

bool Visual_object::point_inside(const double par_x, const double par_y)
{
	if (par_x >= position.get_x() && par_x <= position.get_x() + width &&
		par_y >= position.get_y() && par_y <= position.get_y() + height)
		return true;
	
	return false;
}
