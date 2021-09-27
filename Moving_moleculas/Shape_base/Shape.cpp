#include "Shape.hpp"

Shape::Shape(const char par_type) : type(par_type)
{
	centre_position = { 0, 0 };

	weight = 1;
	velocity = { 0, 0 };
}

Shape::Shape(const char par_type, const Radius_vector &par_centre_position, const Radius_vector &par_velocity, const double par_weight, const Color par_color) : type(par_type)
{
	assert(par_weight);

	centre_position = par_centre_position;
	velocity = par_velocity;
	weight = par_weight;
	color = par_color;
}
