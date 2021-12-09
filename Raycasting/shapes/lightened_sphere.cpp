#include "lightened_sphere.hpp"

const Radius_vector AMBIENT = Radius_vector(0.5, 0.035, 0.285);
const double ROTATE_ANGLE_Y = -0.25;
const double ROTATE_ANGLE_Z = 0;

void reduce_color(Colored_point &point)
{
	Radius_vector color = point.get_color();
	color /= 2.0;
	point.set_color(color);
}

Lightened_sphere::Lightened_sphere(const Circle other, 
	                               const Radius_vector par_sphere_color, 
	                               const Colored_point &par_light, 
	                               const Radius_vector par_view_point) : Circle(other)
{
	light = par_light;
	// reduce_color(light);
	common_lightning = Colored_point(Radius_vector(0.5, 0.5, 0.5), Radius_vector(0.0, 0.0, 0.0));

	sphere_color = par_sphere_color;
	while (sphere_color.get_x() > 1.0 || sphere_color.get_y() > 1.0 || sphere_color.get_z() > 1.0)
		sphere_color /= (double)MAX_COLOR_VALUE;

	view_point = par_view_point;

	ambient = sphere_color;
	ambient /= 4;
	material_coefficient = 15;
}

Lightened_sphere::Lightened_sphere(const Circle other, 
		         				   const Radius_vector par_sphere_color, 
		                           const Colored_point& par_light, 
		                           const Colored_point& par_common_lightning,
		                           const Radius_vector par_view_point,
		                           const Radius_vector par_ambient,
		                           const double par_material_coefficient) : Circle(other)
{
	light = par_light;
	common_lightning = par_common_lightning;

	sphere_color = par_sphere_color;
	while (sphere_color.get_x() > 1.0 || sphere_color.get_y() > 1.0 || sphere_color.get_z() > 1.0)
	{
		sphere_color /= (double)MAX_COLOR_VALUE;
	}

	view_point = par_view_point;

	ambient = par_ambient;
	material_coefficient = par_material_coefficient;
}

Radius_vector Lightened_sphere::result_color(double diffuse_cos, double specular_cos)
{
	Radius_vector diffuse_component(sphere_color);
	diffuse_component.componentwise_multiplication(light.get_color());
	diffuse_component *= diffuse_cos;

	Radius_vector specular_component(sphere_color);
	// specular_component.componentwise_multiplication(common_lightning.get_color());
	specular_component *= specular_cos;
	specular_component /= 3;

	Radius_vector ambient_component(ambient);
	ambient_component.componentwise_multiplication(sphere_color);

	Radius_vector result_color(diffuse_component);
	result_color += specular_component;
	result_color += ambient_component;

	if (result_color.get_x() > 1.0)
		result_color.set_x(1.0);
	if (result_color.get_y() > 1.0)
		result_color.set_y(1.0);
	if (result_color.get_z() > 1.0)
		result_color.set_z(1.0);

	result_color *= MAX_COLOR_VALUE;

	return result_color;
}

double Lightened_sphere::count_z_coordinate(double x, double y)
{
	return sqrt(radius * radius - x * x - y * y);
}

Radius_vector Lightened_sphere::count_current_pixel(double x, double y)
{
	double z = count_z_coordinate((x - center_point.x), (y - center_point.y));
	return Radius_vector(x, y, z);
}

void Lightened_sphere::draw_z(Screen_information *screen)
{
	size_t width = screen->get_width();
	size_t height = screen->get_height();

	for (unsigned x = 0; x < width; ++x)
	{
		for (unsigned y = 0; y < height; ++y)
		{
			if (if_point_in_circle((double)x, (double)y))
			{
				double z = count_z_coordinate((double)(x - center_point.x), (double)(y - center_point.y)); 
				double propotion = z / radius;

				screen->set_color(y, x, {MAX_COLOR_VALUE, 
										(unsigned char)(MAX_COLOR_VALUE * propotion), 
										(unsigned char)(MAX_COLOR_VALUE * propotion), 
										(unsigned char)(MAX_COLOR_VALUE * propotion) });
			}
			else
			{
				screen->set_color(y, x, BLACK);
			}
		}
	}
}

double Lightened_sphere::diffuse_angle(Radius_vector &normal, Radius_vector &light_vector)
{
	double scalar = normal.scalar_multiplication(light_vector);
	double cos_angle = cosine_scalar(scalar, normal.length(), light_vector.length());
	if (cos_angle < 0)
		cos_angle = 0;

	return cos_angle;
}

double Lightened_sphere::specular_angle(Radius_vector &normal, Radius_vector &light_vector, Radius_vector &view_vector)
{
	Radius_vector reflected_vector = view_vector.reflect_vector(normal); 

	double scalar = reflected_vector.scalar_multiplication(light_vector);
	double cos_angle = cosine_scalar(scalar, reflected_vector.length(), light_vector.length());
	if (cos_angle < 0)
		cos_angle = 0;

	return cos_angle;
}

Radius_vector Lightened_sphere::count_normal_to_surface(Radius_vector current_surface_point)
{
	return Radius_vector((sphere_center - current_surface_point) * 2.0);
}

Radius_vector Lightened_sphere::count_pixel_color(Radius_vector current_pixel)
{
	sphere_center = { center_point.x, center_point.y, 0 };

	Radius_vector perpendicular(count_normal_to_surface(current_pixel));
	Radius_vector light_vector(current_pixel - light.get_point());
	
	if (perpendicular.scalar_multiplication(light_vector) <= 0)
	{
		Radius_vector point_color = result_color(0, 0);
		
		return Radius_vector((unsigned char)point_color.get_x(), (unsigned char)point_color.get_y(), (unsigned char)point_color.get_z());
	}

	Radius_vector view_vector(view_point - current_pixel);

	double diffuse_cos  = diffuse_angle(perpendicular, light_vector);
	double specular_cos = specular_angle(perpendicular, light_vector, view_vector);

	specular_cos = calculate_power(specular_cos, material_coefficient); 

	return result_color(diffuse_cos, specular_cos);
}

void Lightened_sphere::draw_lambert_and_fong_in_color (Screen_information *screen)
{
	size_t width = screen->get_width();
	size_t height = screen->get_height();

	for (unsigned x = 0; x < width; ++x)
	{
		for (unsigned y = 0; y < height; ++y)
		{
			if (if_point_in_circle((double)x, (double)y))
			{
				Radius_vector current_pixel = count_current_pixel((double)x, (double)y);

				Radius_vector point_color = count_pixel_color(current_pixel);

				screen->set_color(y, x, { MAX_COLOR_VALUE, 
					                     (unsigned char)point_color.get_x(), 
					                     (unsigned char)point_color.get_y(), 
					                     (unsigned char)point_color.get_z() });
			}
			else
			{
				screen->set_color(y, x, BLACK);
			}
		}
	}
}

void Lightened_sphere::move_light_in_circle()
{
	Radius_vector tmp_vector(light.get_point() - sphere_center);
	set_light_position(tmp_vector.rotate_point(ROTATE_ANGLE_Y, ROTATE_ANGLE_Z) + sphere_center);
}

/*
// double z = count_z_coordinate((double)(x - center_point.x), (double)(y - center_point.y));
// sphere_center = { center_point.x, center_point.y, 0 };

// Radius_vector perpendicular(count_normal_to_surface((double)x, (double)y, z));
// Radius_vector light_vector(Radius_vector((double)x, (double)y, z) - light.get_point());

// if (perpendicular.scalar_multiplication(light_vector) <= 0)
// {
// 	Radius_vector point_color = result_color(0, 0);
// 	screen->set_color(y, x, {MAX_COLOR_VALUE, (unsigned char)point_color.get_x(), (unsigned char)point_color.get_y(), (unsigned char)point_color.get_z()});

// 	continue;
// }

// Radius_vector view_vector(view_point);
// view_vector -= Radius_vector((double)x, (double)y, z);

// double diffuse_cos = diffuse_angle(perpendicular, light_vector);
// double specular_cos = specular_angle(perpendicular, light_vector, view_vector);

// specular_cos = calculate_power(specular_cos, material_coefficient); 
*/

				

