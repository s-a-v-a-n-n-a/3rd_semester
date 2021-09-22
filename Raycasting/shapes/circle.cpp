#include "circle.hpp"

Circle::Circle(Point par_left_corner, double par_radius)
{
	left_corner_point = par_left_corner;

	if (par_radius < 0)
		par_radius *= -1;

	radius = par_radius;

	center_point = { left_corner_point.x + par_radius, left_corner_point.y + par_radius }; // bad
}

Circle::Circle(const Circle &other)
{
	left_corner_point = other.left_corner_point;
	center_point 	  = other.center_point;

	radius = other.radius;
}

bool Circle::if_point_in_circle(double x, double y)
{
	return (x - center_point.x) * (x - center_point.x) + (y - center_point.y) * (y - center_point.y) <= radius * radius;
}

void Circle::draw_shape(Screen_information *screen)
{
	size_t width = screen->get_width();
	size_t height = screen->get_height();

	for (unsigned x = 0; x < width; ++x)
	{
		for (unsigned y = 0; y < height; ++y)
		{
			if ((x - center_point.x) * (x - center_point.x) + (y - center_point.y) * (y - center_point.y) < radius * radius)
			{
				screen->set_color(y, x, WHITE);
			}
			else
			{
				screen->set_color(y, x, BLACK);
			}
		}
	}
}