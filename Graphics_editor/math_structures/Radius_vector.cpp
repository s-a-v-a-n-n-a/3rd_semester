#include "Radius_vector.hpp"

Radius_vector Radius_vector::reflect_vector(const Radius_vector& normal)
{
	Radius_vector tmp_normal(normal);
	Radius_vector tmp_vector(*this);

	tmp_normal /= tmp_normal.length();
	double projection = tmp_vector.scalar_multiplication(tmp_normal) * 2.0;
	if (projection < 0)
		projection *= -1;

	tmp_normal *= projection;
	tmp_vector += tmp_normal;

	return tmp_vector;
}

void Radius_vector::rotate_point(const Radius_vector &other, const double par_angle) 
{
	Radius_vector horizontal(1.0, 0.0);
	Radius_vector vertical(0.0, -1.0);
	Radius_vector relative(*this);
	relative -= other;

	double length = relative.length();

	Radius_vector hor_projection = relative.get_projection(horizontal);
	Radius_vector ver_projection = relative.get_projection(vertical);

	Radius_vector this_parallel(relative);
	this_parallel /= length;
	Radius_vector this_normal(this_parallel.normal());

	this_normal *= length * sin(par_angle);
	this_parallel *= length * (1 - cos(par_angle));

	*this -= this_parallel + this_normal;
}

void Radius_vector::normalization()
{
	*this /= length();
}

