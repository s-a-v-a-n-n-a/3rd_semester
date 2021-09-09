#include "derived_shapes.hpp"

const sf::Color DEFAULT_COLOR = sf::Color(196, 0, 171); 

const double ARROW_ANGLE = 45.0 * 180.0 / M_PI;
const double ARROW_LEN_PERCENTAGE = 0.3;

const double VECTOR_LEN_DEFAULT = 100;
const double ARROW_LEN_DEFAULT = VECTOR_LEN_DEFAULT * ARROW_LEN_PERCENTAGE;

const double CIRCLE_RADIUS = 10;

const size_t POINTS_AMOUNT = 10000;

const double COEF_A = 0.5;
const double COEF_B = 0.0;
const double COEF_C = 0.0;

void Vector_w_arrow::calculate_arrow_ends(double par_projection_vertical, double par_projection_horizontal)
{
	double tmp_length = sqrt(par_projection_horizontal * par_projection_horizontal + par_projection_vertical * par_projection_vertical);
	double tmp_arrow_tail_length = tmp_length < VECTOR_LEN_DEFAULT? ARROW_LEN_PERCENTAGE * tmp_length : ARROW_LEN_DEFAULT; 
	double tmp_angle = atan2(par_projection_vertical, par_projection_horizontal);

	left_tail_end = rotate_point(end_point, 
								  Point{ end_point.x - tmp_arrow_tail_length * (double)sin(ARROW_ANGLE), end_point.y - tmp_arrow_tail_length * (double)cos(ARROW_ANGLE)},
								   		 tmp_angle);
	
	right_tail_end = rotate_point(end_point, 
								   Point{ end_point.x - tmp_arrow_tail_length * (double)sin(ARROW_ANGLE), end_point.y + tmp_arrow_tail_length * (double)cos(ARROW_ANGLE)},
								   		  tmp_angle);
}

void Vector::set_end_point(Point par_end_point)
{
	end_point = par_end_point;
}


void Vector_w_arrow::set_end_point(Point par_end_point)
{
	end_point = par_end_point;

	calculate_arrow_ends(end_point.y - begin_point.y, end_point.x - begin_point.x);
}



Point rotate_point(Point point_0, Point point, double angle)
{
	return { point_0.x + (point.x - point_0.x) * cos(angle) - (point.y - point_0.y) * sin(angle),
			 point_0.y + (point.x - point_0.x) * sin(angle) + (point.y - point_0.y) * cos(angle) };
}

double get_ordinate_for_parabola(double abscissa)
{
	return COEF_A * abscissa * abscissa + COEF_B * abscissa + COEF_C;
}
