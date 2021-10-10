#include "Molecula.hpp"

Molecula::Molecula(const char par_type, const Radius_vector &par_centre_position, const Radius_vector &par_velocity, const double par_weight, const Color par_color,
				   const bool par_active, const bool par_just_born) : Shape(par_type, par_centre_position, par_velocity, par_weight, par_color, par_active, par_just_born)
{
	radius = sqrt(par_weight / M_PI);
}

void Molecula::set_weight(const double par_weight)
{
	assert(par_weight > 0);

	Shape::set_weight(par_weight);

	radius = sqrt(par_weight / M_PI);
}

Radius_vector Molecula::count_move(const double delta_time)
{
	return Radius_vector(get_centre_position() + get_velocity() * delta_time);
}

void Molecula::move(const Radius_vector &par_centre_position)
{
	set_centre_position(par_centre_position);
}

void Molecula::draw(Screen_information *screen)
{
	assert(screen);

	screen->draw_circle(get_centre_position() - Radius_vector(radius, radius), get_color(), radius);
}
