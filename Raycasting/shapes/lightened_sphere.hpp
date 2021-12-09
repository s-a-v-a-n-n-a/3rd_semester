#ifndef LIGHTENED_CLASS
#define LIGHTENED_CLASS

#include <cmath>

#include "circle.hpp"
#include "../math_structures/math_functions.hpp"
#include "../lighting/Colored_point.hpp"
#include "../sfml_drawing/screen_functions.hpp"

extern const Radius_vector AMBIENT;
extern const double ROTATE_ANGLE_Y;
extern const double ROTATE_ANGLE_Z;

class Lightened_sphere : public Circle
{
	Radius_vector sphere_center;
	Radius_vector sphere_color;
	
	double material_coefficient;
	Radius_vector ambient;
	
	Colored_point common_lightning;
	Colored_point light; 
	
	Radius_vector view_point;

	Radius_vector count_normal_to_surface(Radius_vector current_surface_point);
	
	double diffuse_angle(Radius_vector &normal, Radius_vector &light_vector);
	double specular_angle(Radius_vector &normal, Radius_vector &light_vector, Radius_vector &view_vector);

	// передавать расстояние до источника и делить сначала на него, а потом на его куб
	Radius_vector result_color(double diffuse_cos, double specular_cos);

public:
	Lightened_sphere(const Circle other, 
		             const Radius_vector par_sphere_color, 
		             const Colored_point &par_light, 
		             const Radius_vector par_view_point);
	Lightened_sphere(const Circle other, 
		             const Radius_vector par_sphere_color, 
		             const Colored_point &par_light, 
		             const Colored_point &par_common_lightning,
		             const Radius_vector par_view_point,
		             const Radius_vector par_ambient,
		             const double par_material_coefficient);

	void set_light_position(const Radius_vector &par_position) { light.set_point(par_position); }

	Radius_vector get_sphere_color()    { return sphere_color; }
	Radius_vector get_sphere_position() { return sphere_center; }

	void set_sphere_color(const Radius_vector &par_color) { sphere_color = par_color; }

	void move_light_in_circle();

	Radius_vector count_current_pixel(double x, double y);
	Radius_vector count_pixel_color(Radius_vector current_pixel);

	double count_z_coordinate    (double x, double y);
	void   draw_z                (Screen_information *screen);
	void   draw_normal           (Screen_information *screen);
	void   draw_lambert_and_fong (Screen_information *screen);

	void   draw_lambert_and_fong_in_color (Screen_information *screen);
};

#endif // LIGHTENED_CLASS

