#include "derived_shapes.hpp"

extern const sf::Color DEFAULT_COLOR = sf::Color(196, 0, 171); 

extern const double ARROW_ANGLE = 45.0 * 180.0 / M_PI;
extern const double ARROW_LEN_PERCENTAGE = 0.3;

extern const double VECTOR_LEN_DEFAULT = 100;
extern const double ARROW_LEN_DEFAULT = VECTOR_LEN_DEFAULT * ARROW_LEN_PERCENTAGE;

extern const size_t POINTS_AMOUNT = 10000;

extern const double COEF_A = 0.5;
extern const double COEF_B = 0.0;
extern const double COEF_C = 0.0;

void Vector::calculate_arrow_ends()
{
	double tmp_arrow_tail_length = length < VECTOR_LEN_DEFAULT? ARROW_LEN_PERCENTAGE * length : ARROW_LEN_DEFAULT; 
	
	Point left_end = rotate_point(Point{ end_point_x, end_point_y}, 
								  Point{ end_point_x - tmp_arrow_tail_length * (double)sin(ARROW_ANGLE), end_point_y - tmp_arrow_tail_length * (double)cos(ARROW_ANGLE)},
								   		 angle);
	
	left_tail_end = sf::Vertex(sf::Vector2f(left_end.x, left_end.y), DEFAULT_COLOR);

	Point right_end = rotate_point(Point{ end_point_x, end_point_y}, 
								   Point{ end_point_x - tmp_arrow_tail_length * (double)sin(ARROW_ANGLE), end_point_y + tmp_arrow_tail_length * (double)cos(ARROW_ANGLE)},
								   		  angle);

	right_tail_end = sf::Vertex(sf::Vector2f(right_end.x, right_end.y), DEFAULT_COLOR);
}

void Vector::init_simple(double par_begin_point_x, double par_begin_point_y, double par_end_point_x, double par_end_point_y)
{
	draw_shape = draw_vector;

	begin_point_x = par_begin_point_x;
	begin_point_y = par_begin_point_y;
	end_point_x = par_end_point_x;
	end_point_y = par_end_point_y;

	begin_point = sf::Vertex(sf::Vector2f(begin_point_x, begin_point_y), DEFAULT_COLOR);
	end_point   = sf::Vertex(sf::Vector2f(end_point_x, end_point_y), DEFAULT_COLOR);

	projection_horizontal = end_point_x - begin_point_x;
	projection_vertical   = end_point_y - begin_point_y;

	length = sqrt(projection_horizontal * projection_horizontal + projection_vertical * projection_vertical);

	calculate_arrow_ends();
	calculate_angle();
}

void Vector::init_relative(System_of_axes coordinates, double par_begin_point_x, double par_begin_point_y, double par_projection_horizontal, double par_projection_vertical)
{
	draw_shape = draw_vector;

	begin_point_x = par_begin_point_x + coordinates.zero_point_x;
	begin_point_y = par_begin_point_y + coordinates.zero_point_y;
	end_point_x = begin_point_x + par_projection_horizontal;
	end_point_y = begin_point_y + par_projection_vertical;

	begin_point = sf::Vertex(sf::Vector2f(begin_point_x, begin_point_y), DEFAULT_COLOR);
	end_point   = sf::Vertex(sf::Vector2f(end_point_x, end_point_y), DEFAULT_COLOR);

	projection_horizontal = par_projection_horizontal;
	projection_vertical   = par_projection_vertical;

	length = sqrt(projection_horizontal * projection_horizontal + projection_vertical * projection_vertical);

	calculate_arrow_ends();
	calculate_angle();
}


void Vector::calculate_angle()
{
	angle = atan(projection_vertical/projection_horizontal);

	if (projection_horizontal < 0)
	{
		angle += M_PI;
	}
}

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

	draw_line(window, this_vector->begin_point, this_vector->end_point);

	double arrow_tail_length = this_vector->length < VECTOR_LEN_DEFAULT? ARROW_LEN_PERCENTAGE * this_vector->length : ARROW_LEN_DEFAULT; 
	
	Point above_end = rotate_point(Point{ this_vector->end_point_x, this_vector->end_point_y}, 
								   Point{ this_vector->end_point_x - arrow_tail_length * (double)sin(ARROW_ANGLE), this_vector->end_point_y - arrow_tail_length * (double)cos(ARROW_ANGLE)},
								   		  this_vector->angle);
	
	Vector above = {};
	above.init_simple(this_vector->end_point_x, this_vector->end_point_y, above_end.x, above_end.y);
	draw_line(window, above.begin_point, above.end_point);

	Point under_end = rotate_point(Point{ this_vector->end_point_x, this_vector->end_point_y}, 
								   Point{ this_vector->end_point_x - arrow_tail_length * (double)sin(ARROW_ANGLE), this_vector->end_point_y + arrow_tail_length * (double)cos(ARROW_ANGLE)},
								   		  this_vector->angle);

	Vector under = {};
	under.init_simple(this_vector->end_point_x, this_vector->end_point_y, under_end.x, under_end.y);
	draw_line(window, under.begin_point, under.end_point);
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
			sf::Vertex tmp_point(sf::Vector2f(i + offset_x, -1 * (ordinate) + offset_y), DEFAULT_COLOR);
			draw_point(window, tmp_point);
		}
	}
}
