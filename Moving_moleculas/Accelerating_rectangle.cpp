#include "Accelerating_rectangle.hpp"

Accelerating_rectangle::Accelerating_rectangle(const Radius_vector &par_acceleration, const double par_side, const Radius_vector &par_centre_position, const Radius_vector &par_direction, const double par_weight, const Color par_color) : Rectangle(par_side, par_centre_position, par_direction, par_weight, par_color)
{
	valid = true;
	side = par_side;
}

void Accelerating_rectangle::move(const Radius_vector &par_centre_position)
{
	set_centre_position(par_centre_position);

	set_direction(acceleration + get_direction());
}
