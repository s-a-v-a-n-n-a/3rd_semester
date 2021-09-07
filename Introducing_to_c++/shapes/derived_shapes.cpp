#include "derived_shapes.hpp"

const sf::Color DEFAULT_COLOR = sf::Color(196, 0, 171); 

const double ARROW_ANGLE = 45.0 * 180.0 / M_PI;
const double ARROW_LEN_PERCENTAGE = 0.3;

const double VECTOR_LEN_DEFAULT = 100;
const double ARROW_LEN_DEFAULT = VECTOR_LEN_DEFAULT * ARROW_LEN_PERCENTAGE;

const size_t POINTS_AMOUNT = 10000;

const double COEF_A = 0.5;
const double COEF_B = 0.0;
const double COEF_C = 0.0;

void Vector::calculate_arrow_ends(double par_projection_vertical, double par_projection_horizontal)
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

void Vector::init_simple(Point par_begin_point, Point par_end_point)
{
	draw_shape = draw_vector;

	begin_point = par_begin_point;

	end_point = par_end_point;

	double projection_horizontal = end_point.x - begin_point.x;
	double projection_vertical   = end_point.y - begin_point.y;
	calculate_arrow_ends(projection_vertical, projection_horizontal);
}

void Vector::init_relative(System_of_axes coordinates, Point par_begin_point, double par_projection_horizontal, double par_projection_vertical)
{
	draw_shape = draw_vector;

	begin_point = { par_begin_point.x + coordinates.zero_point_x, par_begin_point.y + coordinates.zero_point_y};

	end_point = { begin_point.x + par_projection_horizontal, begin_point.y + par_projection_vertical};

	calculate_arrow_ends(par_projection_vertical, par_projection_horizontal);
}


// double Vector::calculate_angle(double projection_vertical, double projection_horizontal)
// {
// 	return atan2(projection_vertical, projection_horizontal);
// }

// double get_angle(Vector *thus)
// {
// 	double angle = atan(thus->projection_vertical/thus->projection_horizontal);

// 	if (thus->projection_horizontal < 0)
// 	{
// 		angle += M_PI;
// 	}

// 	return angle;
// }

Point rotate_point(Point point_0, Point point, double angle)
{
	return { point_0.x + (point.x - point_0.x) * cos(angle) - (point.y - point_0.y) * sin(angle),
			 point_0.y + (point.x - point_0.x) * sin(angle) + (point.y - point_0.y) * cos(angle) };
}

void draw_vector(Shape *shape, sf::RenderWindow *window)
{
	Vector *this_vector = (Vector*)shape;

	draw_line_sfml(window, this_vector->begin_point, this_vector->end_point);

	draw_line_sfml(window, this_vector->end_point, this_vector->left_tail_end);

	draw_line_sfml(window, this_vector->end_point, this_vector->right_tail_end);
}


void Chart::init(System_of_axes coordinates_field, double (*par_chart_equation)(double abscissa))
{
	draw_shape = draw_chart;

	chart_equation = par_chart_equation;

	field = coordinates_field;
}

double get_ordinate_for_parabola(double abscissa)
{
	return COEF_A * abscissa * abscissa + COEF_B * abscissa + COEF_C;
}

void draw_chart(Shape *shape, sf::RenderWindow *window)
{
	Chart *this_chart = (Chart*)shape;

	double left_border = this_chart->field.x_min;
	double right_border =  this_chart->field.x_max;

	double offset_x = this_chart->field.zero_point_x;
	double offset_y = this_chart->field.zero_point_y;

	double offset = (right_border - left_border)/(double)POINTS_AMOUNT;

	for (double i = left_border; i < right_border; i += offset)
	{
		double ordinate = this_chart->chart_equation(i);
		if (ordinate >= this_chart->field.y_min && ordinate <= this_chart->field.y_max)
		{
			Point tmp_point = {i + offset_x, -1 * (ordinate) + offset_y};
			draw_point_sfml(window, tmp_point);
		}
	}
}
