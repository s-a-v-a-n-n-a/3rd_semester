#include "vector.hpp"

const sf::Color DEFAULT_COLOR = sf::Color(196, 0, 171); 

const double ARROW_ANGLE = 45.0 * 180.0 / M_PI;
const double ARROW_LEN_PERCENTAGE = 0.3;

const double VECTOR_LEN_DEFAULT = 100;
const double ARROW_LEN_DEFAULT = VECTOR_LEN_DEFAULT * ARROW_LEN_PERCENTAGE;

const double CIRCLE_RADIUS = 10;

/**
Vector_3d functions:
*/
Vector_3d::Vector_3d(Point_3d par_begin_point, Point_3d par_end_point)
{
	begin_point = par_begin_point;
	end_point   = par_end_point;
}

Vector_3d::Vector_3d(const Vector_3d &other)
{
	begin_point = other.begin_point;
	end_point = other.end_point;
}

void Vector_3d::draw_shape(sf::RenderWindow *window)
{
	draw_line_sfml(window, begin_point.section_along_z(), end_point.section_along_z());
	
	sf::CircleShape circle_end(CIRCLE_RADIUS);
	circle_end.setPosition(sf::Vector2f(end_point.x - CIRCLE_RADIUS, end_point.y - CIRCLE_RADIUS));
	circle_end.setFillColor(DEFAULT_COLOR);
	
	window->draw(circle_end);
}

const Vector_3d Vector_3d::normalize()
{
	Point_3d normalized_vector_begin_point = end_point;
	Point_3d normalized_vector_end_point = end_point.rotate_point_on_flat(begin_point, M_PI); // в какую сторону поворачивать????	
	
	return Vector_3d(normalized_vector_begin_point, normalized_vector_end_point);		
}

const Vector_3d Vector_3d::to_mathematical() const
{
	Point_3d radius_vector = end_point;
	radius_vector -= begin_point;

	return Vector_3d({0, 0, 0}, radius_vector);
}

const double Vector_3d::scalar_multiplication(const Vector_3d &other) const
{
	Vector_3d this_mathematical(to_mathematical());
	Vector_3d other_mathematical(other.to_mathematical());

	// printf("%lg %lg %lg; %lg %lg %lg\n", this_mathematical.end_point.x, this_mathematical.end_point.y, this_mathematical.end_point.z, 
	// 	                                 other_mathematical.end_point.x, other_mathematical.end_point.y, other_mathematical.end_point.z);

	return this_mathematical.end_point.x * other_mathematical.end_point.x + 
	       this_mathematical.end_point.y * other_mathematical.end_point.y +
		   this_mathematical.end_point.z * other_mathematical.end_point.z;
}

const double Vector_3d::length() const
{
	return sqrt((end_point.x - begin_point.x) * (end_point.x - begin_point.x) +
				(end_point.y - begin_point.y) * (end_point.y - begin_point.y) +
				(end_point.z - begin_point.z) * (end_point.z - begin_point.z));
}

const double Vector_3d::cosine_of_angle_between(const Vector_3d &other)
{
	double this_length = this->length();
	double other_length = other.length();

	if (!this_length || !other_length)
		return 0;

	// printf("scalar %lg\n", scalar_multiplication(other));

	return scalar_multiplication(other)/(this_length * other_length);
}

void Vector_3d::set_length(double par_length)
{
	double length = this->length();
	// printf("len before %lg\n", length);
	double scale = par_length / length;

	(*this) *= scale;
}

Vector_3d Vector_3d::reflect_vector_relative_vector(Vector_3d &vector_0)
{
	double cos_angle = this->cosine_of_angle_between(vector_0);
	if (cos_angle == 0)
	{
		return *this;
	}

	// printf("COSINE %lg\n", cos_angle);
	
	Vector_3d tmp_vector_0(vector_0);
	// if (cos_angle > 0)
	// 	tmp_vector_0.set_length(1.0);
	// else
	// 	tmp_vector_0.set_length(-1.0);
	tmp_vector_0.set_length(cos_angle / fabs(cos_angle));

	Vector_3d tmp_this(*this);
	tmp_this.set_length(1.0/cos_angle);

	// printf("end x %lg\n", tmp_vector_0.end_point.x);
	Point_3d change = tmp_vector_0.end_point;// - this->end_point;
	change -= this->end_point;

	Point_3d reflected_vector_end = vector_0.end_point;// + change;
	reflected_vector_end += change;

	return Vector_3d(this->begin_point, reflected_vector_end);
}



/**
Vector_w_arrow_3d functions:


*/
Vector_w_arrow_3d::Vector_w_arrow_3d(Point_3d par_begin_point, Point_3d par_end_point) : Vector_3d(par_begin_point, par_end_point)
{
	calculate_arrow_ends(end_point.y - begin_point.y, end_point.x - begin_point.x, end_point.z - begin_point.z);
}

void Vector_w_arrow_3d::draw_shape(sf::RenderWindow *window)
{
	draw_line_sfml(window, begin_point.section_along_z(), end_point.section_along_z());

	draw_line_sfml(window, end_point.section_along_z(), left_tail_end.section_along_z());
	draw_line_sfml(window, end_point.section_along_z(), right_tail_end.section_along_z());
}

const Vector_w_arrow_3d Vector_w_arrow_3d::normalize()
{
	Point_3d normalized_vector_begin_point = end_point;

	Point_3d normalized_vector_end_point = end_point.rotate_point_on_flat(begin_point, M_PI); // в какую сторону поворачивать????	
	return Vector_w_arrow_3d(normalized_vector_begin_point, normalized_vector_end_point);		
}

void Vector_w_arrow_3d::calculate_arrow_ends(double par_projection_y, double par_projection_x, double par_projection_z)
{
	double tmp_length = sqrt(par_projection_x * par_projection_x + par_projection_y * par_projection_y + par_projection_z * par_projection_z);
	double tmp_arrow_tail_length = tmp_length < VECTOR_LEN_DEFAULT? ARROW_LEN_PERCENTAGE * tmp_length : ARROW_LEN_DEFAULT; 
	double tmp_angle = atan2(par_projection_y, par_projection_x);

	Point_3d left_point_to_rotate = { end_point.x - tmp_arrow_tail_length * (double)sin(ARROW_ANGLE), end_point.y - tmp_arrow_tail_length * (double)cos(ARROW_ANGLE), end_point.z };
	left_tail_end = left_point_to_rotate.rotate_point_on_flat(end_point, tmp_angle);
	
	Point_3d right_point_to_rotate = { end_point.x - tmp_arrow_tail_length * (double)sin(ARROW_ANGLE), end_point.y + tmp_arrow_tail_length * (double)cos(ARROW_ANGLE), end_point.z };
	right_tail_end = right_point_to_rotate.rotate_point_on_flat(end_point, tmp_angle);
}

void Vector_3d::set_end_point(Point_3d par_end_point)
{
	end_point = par_end_point;
}

void Vector_3d::set_begin_point(Point_3d par_begin_point)
{
	begin_point = par_begin_point;
}


void Vector_w_arrow_3d::set_end_point(Point_3d par_end_point)
{
	end_point = par_end_point;

	calculate_arrow_ends(end_point.y - begin_point.y, end_point.x - begin_point.x, end_point.z - begin_point.z);
}

