#include "Shape.hpp"

Shape::Shape()
{
	centre_position = { 0, 0 };

	weight = 1;
	direction = { 0, 0 };
}

Shape::Shape(const Radius_vector &par_centre_position, const Radius_vector &par_direction, const double par_weight, const Color par_color)
{
	centre_position = par_centre_position;
	direction = par_direction;
	weight = par_weight;
	color = par_color;
}
