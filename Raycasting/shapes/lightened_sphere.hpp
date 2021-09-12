#ifndef LIGHTENED_CLASS
#define LIGHTENED_CLASS

#include <cmath>

#include "circle.hpp"
#include "vector.hpp"

extern const unsigned char EMBEDDING;

class Lightened_sphere : public Circle
{
	Point_3d sphere_center;

	Point_3d lighting_point;
	Point_3d view_point;

	Vector_3d count_normal_to_surface(double x, double y, double z);
	double angle_for_raycasting(Vector_3d &normal, Vector_3d &light_vector);
	double angle_for_glare(Vector_3d &normal, Vector_3d &light_vector, Vector_3d &view_vector);

public:
	Lightened_sphere(Circle other, Point_3d par_lighting_point, Point_3d par_view_point);

	double count_z_coordinate    (double x, double y);
	void   draw_z                (Screen_information *screen);
	void   draw_lambert          (Screen_information *screen);
	void   draw_lambert_and_fong (Screen_information *screen);
};

#endif // LIGHTENED_CLASS
