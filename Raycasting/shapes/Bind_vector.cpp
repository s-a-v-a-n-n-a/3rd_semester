#include "Bind_vector.hpp"

Bind_vector::Bind_vector(Radius_vector par_begin, Radius_vector par_end)
{
	begin = par_begin;
	end   = par_end;
}

Bind_vector::Bind_vector(const Bind_vector& other)
{
	begin = other.begin;
	end   = other.end;
}

void Bind_vector::set_length(double par_length)
{
	double scale = par_length / get_length();

	double projection_x = (end.get_x() - begin.get_x()) * scale;
	double projection_y = (end.get_y() - begin.get_y()) * scale;
	double projection_z = (end.get_z() - begin.get_z()) * scale;

	end = Radius_vector(projection_x, projection_y, projection_z);
	end += begin;
}

Bind_vector Bind_vector::reflect_vector_relative_vector(const Bind_vector& normal)
{
	// double scalar = to_radius_vector().scalar_multiplication(normal.to_radius_vector());
	// double cos_angle = cosine_scalar(scalar, get_length(), normal.get_length());
	// if (cos_angle == 0)
	// 	return *this;

	// Bind_vector tmp_normal(normal);
	// // tmp_normal.set_length(cos_angle / fabs(cos_angle));
	// tmp_normal.set_length(1.0);

	// Bind_vector tmp_this(*this);
	// tmp_this.set_length(1.0);///cos_angle);

	// Radius_vector change = tmp_normal.end;
	// change -= tmp_this.end;
	// // change *= -1;

	// Radius_vector reflected_vector_end = normal.end;
	// reflected_vector_end += change;
	// reflected_vector_end += change;

	// return Bind_vector({0, 0, 0}, change);
	//return Bind_vector(begin, reflected_vector_end);

	Bind_vector tmp_normal(normal);
	Bind_vector tmp_this(*this);

	tmp_normal.set_length(1.0);
	double projection = tmp_this.to_radius_vector().scalar_multiplication(normal.to_radius_vector()) * 2.0;

	Radius_vector tmp_this_ok = tmp_this.to_radius_vector();
	Radius_vector double_normal = tmp_normal.to_radius_vector();
	double_normal *= projection;
	tmp_this_ok += double_normal;

	// tmp_this_ok /= tmp_this_ok.length();

	// tmp_this_ok *= 255;

	// tmp_this_ok += tmp_this.begin;

	return Bind_vector(tmp_this.begin, tmp_this_ok);
}

// void Bind_vector::rotate_point(double angle)
// {
// 	set_end_point(Radius_vector(begin.get_x() + (end.get_x() - begin.get_x()) * cos(angle) - (end.get_y() - begin.get_y()) * sin(angle),
// 			 	                begin.get_y() + (end.get_x() - begin.get_x()) * sin(angle) + (end.get_y() - begin.get_y()) * cos(angle),
// 			 	                end.get_z()));

// 	// begin.get_y() + (end.get_y() - begin.get_y()) * cos(angle) - (end.get_z() - begin.get_z()) * sin(angle),
// 	// begin.get_z() + (end.get_y() - begin.get_y()) * sin(angle) + (end.get_z() - begin.get_z()) * cos(angle),
// }



Vector reflect_vector(Vector& normal_vector) {
// this == light

	double length_this = this->get_length_vector();
	double length_normal_vector = normal_vector.get_length_vector();

	double scalar_mult = this->scalar_multiplication(normal_vector);
	double cos_angle = scalar_mult / length_this / length_normal_vector;

	if(cos_angle == 0)
	return *this;

	Vector copy_normal_vector(normal_vector);
	copy_normal_vector *= (1.0 / length_normal_vector);

	Vector copy_this(*this);
	copy_this *= (1.0 / cos_angle / length_this);

	// Vector change(copy_normal_vector);
	// change -= copy_this;
	Point change = copy_normal_vector.get_point_end();
	change -= copy_this.get_point_end();
	// change *= 2;

	// Point copy_change_begin = change.get_point_begin();
	// Point copy_change_end = change.get_point_end();

	// copy_change_end -= copy_change_begin;

	// Vector copy_(Point(0, 0), copy_change_end);
	// copy_ *= 2;

	// this->point_end = copy_.get_point_end();
	this->point_end = copy_normal_vector.get_point_end();
	this->point_end += change;
	// this->point_end += copy_change_begin;

	return *this;
}