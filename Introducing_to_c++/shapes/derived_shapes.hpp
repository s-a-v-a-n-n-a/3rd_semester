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
	Point begin_point;

	Point end_point;

	Point left_tail_end;
	Point right_tail_end;

	void init_simple(Point par_begin_point, Point par_end_point);
	void init_relative(System_of_axes where, Point par_begin_point, double par_projection_horizontal, double par_projection_vertical);

	void calculate_arrow_ends(double par_projection_vertical, double par_projection_horizontal);
};

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
