#include "Accelerating_rectangle.hpp"

Accelerating_rectangle::Accelerating_rectangle(const Radius_vector &par_acceleration, 
	                                           const double scale, 
	                                           const char par_type, const Radius_vector &par_centre_position, const Radius_vector &par_velocity, const double par_weight, const Color par_color,
	                                           const bool par_active, const bool par_just_born) : Rectangle(scale, par_type, par_centre_position, par_velocity, par_weight, par_color, par_active, par_just_born)
{
	acceleration = par_acceleration;
}

Radius_vector Accelerating_rectangle::count_move(const double delta_time)
{
	Radius_vector result(get_centre_position() + get_velocity() * delta_time + acceleration * delta_time * delta_time / 2.0);
	set_velocity(acceleration * delta_time + get_velocity());

	return result;
}

void Accelerating_rectangle::move(const Radius_vector &par_centre_position)
{
	set_centre_position(par_centre_position); // неверная формула
}
