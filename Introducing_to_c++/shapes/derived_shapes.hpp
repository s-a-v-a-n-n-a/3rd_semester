#ifndef DERIVED
#define DERIVED

#include <cmath>

#include "shape_base.hpp"
#include "coordinate_axes.hpp"

#include "simple_drawing.hpp"

extern const sf::Color DEFAULT_COLOR; 

extern const double ARROW_ANGLE;
extern const double ARROW_LEN_PERCENTAGE;
extern const double ARROW_LEN_DEFAULT;
extern const double VECTOR_LEN_DEFAULT;

extern const size_t POINTS_AMOUNT;

extern const double COEF_A;
extern const double COEF_B;
extern const double COEF_C;

struct Vector : Shape
{
	double begin_point_x;
	double begin_point_y;

	double end_point_x;
	double end_point_y;

	sf::Vertex begin_point;
	sf::Vertex end_point;

	sf::Vertex left_tail_end;
	sf::Vertex right_tail_end;

	double angle;
	double length;

	double projection_horizontal;
	double projection_vertical;

	void init_simple(double par_begin_point_x, double par_begin_point_y, double par_end_point_x, double par_end_point_y);
	void init_relative(System_of_axes where, double par_begin_point_x, double par_begin_point_y, double par_projection_horizontal, double par_projection_vertical);

	void calculate_arrow_ends();
	void calculate_angle();
};

// void draw_point(sf::Vertex point, sf::RenderWindow *window);
// void draw_line(sf::Vertex begin, sf::Vertex end, sf::RenderWindow *window);
void draw_vector(Shape *shape, sf::RenderWindow *window);
Point rotate_point(Point point_0, Point point, double angle);

// double get_angle(Vector *thus);

struct Chart : Shape
{
	double (*chart_equation)(double);

	// double abscissa_min;
	// double abscissa_max;

	// double ordinate_min;
	// double ordinate_max;

	// double offset_x;
	// double offset_y;
	System_of_axes field;

	void init(System_of_axes coordinates_field, double (*chart_equation)(double abscissa));
};

double get_ordinate_for_parabola(double abscissa);
void draw_chart(Shape *shape, sf::RenderWindow *window);

#endif // DERIVED
