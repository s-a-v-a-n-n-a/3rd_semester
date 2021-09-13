#ifndef LIGHTENED_CLASS
#define LIGHTENED_CLASS

#include <cmath>

#include "circle.hpp"
#include "vector.hpp"
#include "../lighting/light_point.hpp"

extern const unsigned char EMBEDDING;

class Lightened_sphere : public Circle
{
	Point_3d sphere_center;
	Color sphere_color;

	Point_3d lighting_point;
	Light_point light;
	
	Point_3d view_point;

	Vector_3d count_normal_to_surface(double x, double y, double z);
	double angle_for_raycasting(Vector_3d &normal, Vector_3d &light_vector);
	double angle_for_glare(Vector_3d &normal, Vector_3d &light_vector, Vector_3d &view_vector);

	struct Color_double
	{
		double a;
		double r;
		double g;
		double b;
	};

	// передавать расстояние до источника и делить сначала на него, а потом на его куб
	Color result_color(double light_angle_cos, double glare_angle_cos)
	{
		Color_double sphere_color_double = { sphere_color.a / 255.0, sphere_color.r / 255.0, sphere_color.g / 255.0, sphere_color.b / 255.0 };
		Color_double light_color_double = { light.light_color.a / 255.0, light.light_color.r / 255.0, light.light_color.g / 255.0, light.light_color.b / 255.0 };

		// double a = (sphere_color_double.a * light_color_double.a * light_angle_cos + sphere_color_double.a * glare_angle_cos + EMBEDDING/255.0 > 1.0 ? 1.0 : sphere_color_double.a * light_color_double.a * light_angle_cos + sphere_color_double.a * glare_angle_cos + EMBEDDING/255.0);
		double red_color   = sphere_color_double.r * light_color_double.r * light_angle_cos + sphere_color_double.r * glare_angle_cos + EMBEDDING / 255.0;
		if (red_color > 1.0)
			red_color = 1.0;

		double green_color = sphere_color_double.g * light_color_double.g * light_angle_cos + sphere_color_double.g * glare_angle_cos + EMBEDDING / 255.0;
		if (green_color > 1.0)
			green_color = 1.0;

		double blue_color  = sphere_color_double.b * light_color_double.b * light_angle_cos + sphere_color_double.b * glare_angle_cos + EMBEDDING / 255.0;
		if (blue_color > 1.0)
			blue_color = 1.0;

		return Color{ 255, (unsigned char)(red_color * 255.0), (unsigned char)(green_color * 255.0), (unsigned char)(blue_color * 255.0) };
	}

public:
	Lightened_sphere(Circle other, Point_3d par_lighting_point, Point_3d par_view_point);
	Lightened_sphere(Circle other, Color par_sphere_color, Light_point& par_light, Point_3d par_view_point);

	double count_z_coordinate    (double x, double y);
	void   draw_z                (Screen_information *screen);
	void   draw_lambert          (Screen_information *screen);
	void   draw_lambert_and_fong (Screen_information *screen);

	void   draw_lambert_and_fong_in_color (Screen_information *screen);
};

#endif // LIGHTENED_CLASS
