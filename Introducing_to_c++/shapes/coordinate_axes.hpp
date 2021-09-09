#ifndef AXES_SYS
#define AXES_SYS

#include <SFML/Graphics.hpp>
#include <cmath>

#include "simple_drawing.hpp"

class System_of_axes
{
private:
	Point left_corner;

	double x_min;
	double x_max;

	double y_min;
	double y_max;

	Point zero_point;

	void calculate_zero_point()
	{
		double zero_x = 0;// left_corner.x + (x_min <= 0) ? fabs(x_min) : - fabs(x_min);
		if (x_min <= 0)
			zero_x = left_corner.x + fabs(x_min);
		else
			zero_x = left_corner.x - fabs(x_min);

		double zero_y = 0;// left_corner.y + (y_max >= 0) ? fabs(y_max) : - fabs(y_max);
		if (y_max >= 0)
			zero_y = left_corner.y + fabs(y_max);
		else
			zero_y = left_corner.y - fabs(y_max);

		zero_point = { zero_x, zero_y };
	}

	void check_bounders(double par_x_min = 0, double par_x_max = 0, double par_y_min = 0, double par_y_max = 0)
	{
		if (par_x_max < par_x_min)
		{
			x_max = par_x_min;
			x_min = par_x_max;
		}
		else
		{
			x_max = par_x_max;
			x_min = par_x_min;
		}

		if (par_y_max < par_y_min)
		{
			y_max = par_y_min;
			y_min = par_y_max;
		}
		else
		{
			y_max = par_y_max;
			y_min = par_y_min;
		}
	}

public:
	System_of_axes() = default;

	System_of_axes(Point par_left_point,
			  double par_x_min = 0,
			  double par_x_max = 0,
			  double par_y_min = 0,
			  double par_y_max = 0)
	{
		check_bounders(par_x_min, par_x_max, par_y_min, par_y_max);

		left_corner = par_left_point;

		calculate_zero_point();
	}

	System_of_axes(System_of_axes &par_other)
	{
		left_corner = par_other.get_left_corner();

		x_min = par_other.get_x_low_bound();
		x_max = par_other.get_x_up_bound();
		y_min = par_other.get_y_low_bound();
		y_max = par_other.get_y_up_bound();

		calculate_zero_point();
	}

	void copy(System_of_axes par_other)
	{
		left_corner = par_other.get_left_corner();

		x_min = par_other.get_x_low_bound();
		x_max = par_other.get_x_up_bound();
		y_min = par_other.get_y_low_bound();
		y_max = par_other.get_y_up_bound();

		calculate_zero_point();
	}

	void set_left_corner(Point par_left_corner) { left_corner = par_left_corner; calculate_zero_point(); }

	Point get_left_corner() { return left_corner; }
	Point get_zero_point()  { return zero_point; }

	double get_x_low_bound() { return x_min; }
	double get_x_up_bound()  { return x_max; }
	double get_y_low_bound() { return y_min; }
	double get_y_up_bound()  { return y_max; }

	void draw(sf::RenderWindow *window);
};




#endif // AXES_SYS
