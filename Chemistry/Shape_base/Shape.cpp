#include "Shape.hpp"

const double CRITICAL_ENERGY = 50.0;

Shape::Shape(const size_t par_type) : type(par_type)
{
	centre_position = { 0, 0 };

	weight = 1;
	velocity = { 0, 0 };

	active = true;
	just_born = false;
}

Shape::Shape(const size_t par_type, const Radius_vector &par_centre_position, const Radius_vector &par_velocity, const double par_weight, const Color par_color, 
	         const bool par_active, const bool par_just_born) : type(par_type)
{
	assert(par_weight);

	centre_position = par_centre_position;
	velocity = par_velocity;
	weight = par_weight;
	color = par_color;
	
	active = par_active;
	just_born = par_just_born;
}
