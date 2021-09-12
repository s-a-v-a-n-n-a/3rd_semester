#ifndef LIGHTENED_CLASS
#define LIGHTENED_CLASS

#include <cmath>

#include "circle.hpp"
#include "vector.hpp"

extern const unsigned char EMBEDDING;

class Lightened_sphere : public Circle
{
	Point_3d lighting_point;

public:
	Lightened_sphere(Circle other, Point_3d par_lighting_point);

	double count_z_coordinate(double x, double y);
	void draw_z(Screen_information *screen);
	void draw_lambert(Screen_information *screen);
};

#endif // LIGHTENED_CLASS
