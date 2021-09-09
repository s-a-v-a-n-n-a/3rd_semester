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

extern const double CIRCLE_RADIUS;

extern const size_t POINTS_AMOUNT;

extern const double COEF_A;
extern const double COEF_B;
extern const double COEF_C;

Point rotate_point(Point point_0, Point point, double angle);

void draw_chart(Shape *shape, sf::RenderWindow *window);
double get_ordinate_for_parabola(double abscissa);

class Vector : public Shape
{

protected:
	Point begin_point;
	Point end_point;

public:
	Vector(Point par_begin_point, Point par_end_point)
	{
		begin_point = par_begin_point;
		end_point = par_end_point;
	}

	Vector(System_of_axes coordinates, Point par_begin_point, double par_projection_horizontal, double par_projection_vertical)
	{
		begin_point = { par_begin_point.x + coordinates.get_zero_point().x, 
						par_begin_point.y + coordinates.get_zero_point().y};
		end_point   = { begin_point.x + par_projection_horizontal, 
						begin_point.y + par_projection_vertical};
	}

	virtual void draw_shape(sf::RenderWindow *window)
	{
		draw_line_sfml(window, begin_point, end_point);
		
		sf::CircleShape circle_end(CIRCLE_RADIUS);
		circle_end.setPosition(sf::Vector2f(end_point.x - CIRCLE_RADIUS, end_point.y - CIRCLE_RADIUS));
		circle_end.setFillColor(DEFAULT_COLOR);
		window->draw(circle_end);
	}

	Point get_begin_point() const { return begin_point; }
	Point get_end_point() const { return end_point; }

	virtual void set_end_point(Point par_end_point);

	const Vector operator+=(const Vector &other)
	{
		return Vector(begin_point += other.get_begin_point(), end_point += other.get_end_point());
	}
};

class Vector_w_arrow : public Vector
{

private:
	Point left_tail_end;
	Point right_tail_end;

	void calculate_arrow_ends(double par_projection_vertical, double par_projection_horizontal);

public:
	Vector_w_arrow(Point par_begin_point, Point par_end_point) : Vector(par_begin_point, par_end_point)
	{
		calculate_arrow_ends(end_point.y - begin_point.y, end_point.x - begin_point.x);
	}
 
	Vector_w_arrow(System_of_axes coordinates, Point par_begin_point, double par_projection_horizontal, double par_projection_vertical) 
	: Vector(coordinates, par_begin_point, par_projection_horizontal, par_projection_vertical)
	{
		calculate_arrow_ends(par_projection_vertical, par_projection_horizontal);
	}

	virtual void draw_shape(sf::RenderWindow *window)
	{
		draw_line_sfml(window, begin_point, end_point);

		draw_line_sfml(window, end_point, left_tail_end);
		draw_line_sfml(window, end_point, right_tail_end);
	}

	virtual void set_end_point(Point par_end_point);

	const Vector_w_arrow operator+=(const Vector_w_arrow &other)
	{
		return Vector_w_arrow(begin_point += other.get_begin_point(), end_point += other.get_end_point());
	}
};


class Chart : Shape
{
public:
	double (*chart_equation)(double);

	System_of_axes field;

	Chart(System_of_axes &coordinates_field, double (*par_chart_equation)(double abscissa)):field(coordinates_field)
	{
		chart_equation = par_chart_equation;
	}

	virtual void draw_shape(sf::RenderWindow *window)
	{
		Chart *this_chart = this;

		double left_border = this_chart->field.get_x_low_bound();
		double right_border =  this_chart->field.get_x_up_bound();

		double offset_x = this_chart->field.get_zero_point().x;
		double offset_y = this_chart->field.get_zero_point().y;

		double offset = (right_border - left_border)/(double)POINTS_AMOUNT;

		for (double i = left_border; i < right_border; i += offset)
		{
			double ordinate = this_chart->chart_equation(i);
			if (ordinate >= this_chart->field.get_y_low_bound() && ordinate <= this_chart->field.get_y_up_bound())
			{
				Point tmp_point = {i + offset_x, -1 * (ordinate) + offset_y};
				draw_point_sfml(window, tmp_point);
			}
		}
	}
};

#endif // DERIVED
