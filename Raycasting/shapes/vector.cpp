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

virtual void Vector_3d::draw_shape(sf::RenderWindow *window)
{
	draw_line_sfml(window, begin_point.section_along_z(), end_point.section_along_z());
	
	sf::CircleShape circle_end(CIRCLE_RADIUS);
	circle_end.setPosition(sf::Vector2f(end_point.x - CIRCLE_RADIUS, end_point.y - CIRCLE_RADIUS));
	circle_end.setFillColor(DEFAULT_COLOR);
	
	window->draw(circle_end);
}

const Vector_3d operator+=(const Vector_3d &other)
{
	return Vector_3d(begin_point += other.get_begin_point(), end_point += other.get_end_point());
}

const Vector_3d operator*=(const double scale)
{
	Point_3d radius_vector = end_point;

	radius_vector -= begin_point;
	radius_vector *= scale;

	return Vector_3d(begin_point, end_point += radius_vector);
}

const Vector_3d normalize()
{
	Point_3d normalized_vector_begin_point = end_point;

	Point_3d normalized_vector_end_point = rotate_point_on_flat(begin_point, end_point, M_PI); // в какую сторону поворачивать????	
	return Vector_3d(normalized_vector_begin_point, normalized_vector_end_point);		
}

const Vector_3d to_mathematical() const
{
	return Vector_3d({0, 0, 0}, end_point - begin_point);
}

const double scalar_multiplication(const Vector_3d &other)
{
	Vector_3d this_mathematical(to_mathematical());
	Vector_3d other_mathematical(other.to_mathematical());

	return this_mathematical.end_point.x * other_mathematical.end_point.x + 
	       this_mathematical.end_point.y * other_mathematical.end_point.y +
		   this_mathematical.end_point.z * other_mathematical.end_point.z;
}

const double length() const
{
	return sqrt((end_point.x - begin_point.x) * (end_point.x - begin_point.x) +
				(end_point.y - begin_point.y) * (end_point.y - begin_point.y) +
				(end_point.z - begin_point.z) * (end_point.z - begin_point.z));
}

const double cosine_of_angle_between(const Vector_3d &other)
{
	double this_length = this->length();
	double other_length = other.length();

	if (!this_length || !other_length)
		return 0;

	// printf("scalar %lg\n", scalar_multiplication(other));

	return scalar_multiplication(other)/(this_length * other_length);
}



/**
Vector_w_arrow_3d functions:
*/
Vector_w_arrow_3d(Point_3d par_begin_point, Point_3d par_end_point) : Vector_3d(par_begin_point, par_end_point)
{
	calculate_arrow_ends(end_point.y - begin_point.y, end_point.x - begin_point.x, end_point.z - begin_point.z);
}

virtual void draw_shape(sf::RenderWindow *window)
{
	draw_line_sfml(window, begin_point.section_along_z(), end_point.section_along_z());

	draw_line_sfml(window, end_point.section_along_z(), left_tail_end.section_along_z());
	draw_line_sfml(window, end_point.section_along_z(), right_tail_end.section_along_z());
}

const Vector_w_arrow_3d operator+=(const Vector_w_arrow_3d &other)
{
	return Vector_w_arrow_3d(begin_point += other.get_begin_point(), end_point += other.get_end_point());
}

const Vector_w_arrow_3d operator*=(const double scale)
{
	Point_3d radius_vector = end_point;

	radius_vector -= begin_point;
	radius_vector *= scale;
	
	return Vector_w_arrow_3d(begin_point, end_point += radius_vector);
}

const Vector_w_arrow_3d normalize()
{
	Point_3d normalized_vector_begin_point = end_point;

	Point_3d normalized_vector_end_point = rotate_point_on_flat(begin_point, end_point, M_PI); // в какую сторону поворачивать????	
	return Vector_w_arrow_3d(normalized_vector_begin_point, normalized_vector_end_point);		
}

void Vector_w_arrow_3d::calculate_arrow_ends(double par_projection_y, double par_projection_x, double par_projection_z)
{
	double tmp_length = sqrt(par_projection_x * par_projection_x + par_projection_y * par_projection_y + par_projection_z * par_projection_z);
	double tmp_arrow_tail_length = tmp_length < VECTOR_LEN_DEFAULT? ARROW_LEN_PERCENTAGE * tmp_length : ARROW_LEN_DEFAULT; 
	double tmp_angle = atan2(par_projection_y, par_projection_x);

	left_tail_end = rotate_point_on_flat(end_point, 
								         Point_3d{ end_point.x - tmp_arrow_tail_length * (double)sin(ARROW_ANGLE), end_point.y - tmp_arrow_tail_length * (double)cos(ARROW_ANGLE), end_point.z},
								   		 tmp_angle);
	
	right_tail_end = rotate_point_on_flat(end_point, 
								          Point_3d{ end_point.x - tmp_arrow_tail_length * (double)sin(ARROW_ANGLE), end_point.y + tmp_arrow_tail_length * (double)cos(ARROW_ANGLE), end_point.z},
								   		  tmp_angle);
}

void Vector_3d::set_end_point(Point_3d par_end_point)
{
	end_point = par_end_point;
}


void Vector_w_arrow_3d::set_end_point(Point_3d par_end_point)
{
	end_point = par_end_point;

	calculate_arrow_ends(end_point.y - begin_point.y, end_point.x - begin_point.x, end_point.z - begin_point.z);
}


//в плоскости xy
Point_3d rotate_point_on_flat(Point_3d point_0, Point_3d point, double angle)
{
	return { point_0.x + (point.x - point_0.x) * cos(angle) - (point.y - point_0.y) * sin(angle),
			 point_0.y + (point.x - point_0.x) * sin(angle) + (point.y - point_0.y) * cos(angle),
			 point.z };
}

