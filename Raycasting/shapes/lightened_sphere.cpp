#include "lightened_sphere.hpp"

const unsigned char EMBEDDING = 50;

Lightened_sphere::Lightened_sphere(Circle other, Point_3d par_lighting_point) : Circle(other)
{
	lighting_point = par_lighting_point;
}

double Lightened_sphere::count_z_coordinate(double x, double y)
{
	return sqrt(radius * radius - x * x - y * y);
}

void Lightened_sphere::draw_z(Screen_information *screen)
{
	size_t width = screen->get_width();
	size_t height = screen->get_height();

	for (unsigned x = 0; x < width; ++x)
	{
		for (unsigned y = 0; y < height; ++y)
		{
			if ((x - center_point.x) * (x - center_point.x) + (y - center_point.y) * (y - center_point.y) <= radius * radius)
			{
				double z = count_z_coordinate((double)(x - center_point.x), (double)(y - center_point.y)); //  + center_point.z
				double propotion = z / radius;

				screen->set_color(y, x, {255, (unsigned char)((double)255 * propotion), (unsigned char)((double)255 * propotion), (unsigned char)((double)255 * propotion) });
			}
			else
			{
				screen->set_color(y, x, {0, 0, 0, 0});
			}
		}
	}
}

void Lightened_sphere::draw_lambert(Screen_information *screen)
{
	size_t width = screen->get_width();
	size_t height = screen->get_height();

	for (unsigned x = 0; x < width; ++x)
	{
		for (unsigned y = 0; y < height; ++y)
		{
			if ((x - center_point.x) * (x - center_point.x) + (y - center_point.y) * (y - center_point.y) <= radius * radius)
			{
				double z = count_z_coordinate((double)(x - center_point.x), (double)(y - center_point.y)); // + center_point.z;
				// double propotion = z / radius;

				Point_3d sphere_center = { center_point.x, center_point.y, 0 };

				Vector_3d radius_vector(sphere_center, {(double)x, (double)y, z});
				Vector_3d light_vector(sphere_center, lighting_point);

				// скалярное произведение
				double cos_angle = radius_vector.cosine_of_angle_between(light_vector);
				if (cos_angle < 0)
					cos_angle = 0;

				unsigned char grey_color = ((unsigned char)((double)255 * cos_angle) + EMBEDDING > 255 ? 255 : (unsigned char)((double)255 * cos_angle) + EMBEDDING);

				screen->set_color(y, x, {255, grey_color, grey_color, grey_color});
			}
			else
			{
				screen->set_color(y, x, {0, 0, 0, 0});
			}
		}
	}
}

