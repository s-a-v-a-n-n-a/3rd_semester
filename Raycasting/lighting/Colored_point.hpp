#ifndef COLORED_POINT
#define COLORED_POINT

// #include "../shapes/simple_drawing.hpp"
#include "../sfml_drawing/screen_functions.hpp"

#include "../shapes/Radius_vector.hpp"

class Colored_point
{
private:
	Radius_vector point;
	Radius_vector color;

public:
	Colored_point()
	{
		point = { 0.0, 0.0, 0.0 };
		color = { 1.0, 1.0, 1.0 };
	}

	Colored_point(Radius_vector par_point, Radius_vector par_color)
	{
		point = par_point;
		
		color = par_color;
		while (color.get_x() > 1.0 || color.get_y() > 1.0 || color.get_z() > 1.0)
			color *= (1.0 / 255.0);
	}

	Colored_point(const Colored_point& par_point)
	{
		point = par_point.point;
		color = par_point.color;
	}

	const Radius_vector& get_point() const { return point; }
	const Radius_vector& get_color() const { return color; }

	void set_point(const Radius_vector &par_point) { point = par_point; }
	void set_color(const Radius_vector &par_color) { color = par_color; }
};

#endif // COLORED_POINT
