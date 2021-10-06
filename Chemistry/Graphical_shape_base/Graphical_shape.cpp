#include "Graphical_shape.hpp"

Graphical_shape::Graphical_shape() : type(0)
{
	centre_position = { 0, 0 };
	color = WHITE;
}

Graphical_shape::Graphical_shape(const int par_type) : type(par_type)
{
	centre_position = { 0, 0 };
	Color = WHITE;
}

Graphical_shape::Graphical_shape(const Radius_vector &par_centre_position, const Color par_color = WHITE, const int par_type = 0) : type(par_type)
{
	centre_position = par_centre_position;
	color = par_color;
}
