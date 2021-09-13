#ifndef LIGHT_POINT
#define LIGHT_POINT

#include "../shapes/simple_drawing.hpp"
#include "../sfml_drawing/screen_functions.hpp"

// do getters and setters
class Light_point
{
public:
	Point_3d light_point;
	Color    light_color;

	Light_point()
	{
		light_point = { 0, 0, 0 };
		light_color = { 255, 255, 255, 255 };
	}

	Light_point(Point_3d par_light_point, Color par_light_color)
	{
		light_point = par_light_point;
		light_color = par_light_color;
	}

	Light_point(const Light_point& par_light_point)
	{
		light_point = par_light_point.light_point;
		light_color = par_light_point.light_color;
	}
};

#endif // LIGHT_POINT
