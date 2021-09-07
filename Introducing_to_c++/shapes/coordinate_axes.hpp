#ifndef AXES_SYS
#define AXES_SYS

#include <SFML/Graphics.hpp>
#include <cmath>

struct System_of_axes
{
	double left_high_corner_x;
	double left_high_corner_y;
	// double right_low_corner;

	double x_min;
	double x_max;

	double y_min;
	double y_max;

	double zero_point_x;
	double zero_point_y;

	void init(double left_corner  = 0,
			  double right_corner = 0,
			  double x_min = 0,
			  double x_max = 0,
			  double y_min = 0,
			  double y_max = 0);

	void draw(sf::RenderWindow *window);
};




#endif // AXES_SYS
