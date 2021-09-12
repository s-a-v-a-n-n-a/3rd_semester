#ifndef CIRCLE_SHAPE
#define CIRCLE_SHAPE

#include "sfml_shape.hpp"
#include "simple_drawing.hpp"
#include "../sfml_drawing/screen_functions.hpp"

class Circle : public Sfml_shape
{
protected:
	Point left_corner_point;
	Point center_point;
	double radius;

public:
	Circle(Point par_left_corner = {0, 0}, double par_radius = 0);
	Circle(const Circle &other);

	void draw_shape(Screen_information *screen);
};

#endif // CIRCLE_SHAPE
