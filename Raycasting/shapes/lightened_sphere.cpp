#include "lightened_sphere.hpp"

const unsigned char EMBEDDING = 10;

Lightened_sphere::Lightened_sphere(Circle other, Point_3d par_lighting_point, Point_3d par_view_point) : Circle(other)
{
	lighting_point = par_lighting_point;
	view_point     = par_view_point;
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
				Point_3d sphere_center = { center_point.x, center_point.y, 0 };

				Vector_3d radius_vector(sphere_center, {(double)x, (double)y, z});
				radius_vector *= 2.0;
				Vector_3d perpendicular_to_the_surface({(double)x, (double)y, z}, radius_vector.get_end_point());
				Vector_3d light_vector({(double)x, (double)y, z}, lighting_point);

				// скалярное произведение
				double cos_angle = perpendicular_to_the_surface.cosine_of_angle_between(light_vector);
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

double Lightened_sphere::angle_for_raycasting(Vector_3d &normal, Vector_3d &light_vector)
{
	double cos_angle = normal.cosine_of_angle_between(light_vector);
	if (cos_angle < 0)
		cos_angle = 0;

	return cos_angle;
}

double Lightened_sphere::angle_for_glare(Vector_3d &normal, Vector_3d &light_vector, Vector_3d &view_vector)
{
	Vector_3d reflected_vector = light_vector.reflect_vector_relative_vector(normal);
	double cos_angle = reflected_vector.cosine_of_angle_between(view_vector);

	return cos_angle;
}

Vector_3d Lightened_sphere::count_normal_to_surface(double x, double y, double z)
{
	Vector_3d radius_vector(sphere_center, Point_3d{x, y, z});
	radius_vector *= 2.0;
	
	return Vector_3d(Point_3d{x, y, z}, radius_vector.get_end_point());
}

void Lightened_sphere::draw_lambert_and_fong(Screen_information *screen)
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
				sphere_center = { center_point.x, center_point.y, 0 };

				Vector_3d perpendicular_to_the_surface(count_normal_to_surface((double)x, (double)y, z));
				Vector_3d light_vector({(double)x, (double)y, z}, lighting_point);
				Vector_3d view_vector ({(double)x, (double)y, z}, view_point);

				double light_angle_cos = angle_for_raycasting(perpendicular_to_the_surface, light_vector);
				double glare_angle_cos = angle_for_glare(perpendicular_to_the_surface, light_vector, view_vector);

				unsigned char grey_color = ((unsigned char)(255.0 * light_angle_cos) + (unsigned char)(255.0 * glare_angle_cos) + EMBEDDING > 255 ? 255 : ((unsigned char)(255.0 * light_angle_cos) + (unsigned char)(255.0 * glare_angle_cos) + EMBEDDING));
				
				screen->set_color(y, x, {255, grey_color, grey_color, grey_color});
			}
			else
			{
				screen->set_color(y, x, {0, 0, 0, 0});
			}
		}
	}
}



// #include "lightened_sphere.hpp"

// const unsigned char EMBEDDING = 10;

// Lightened_sphere::Lightened_sphere(Circle other, Point_3d par_lighting_point, Point_3d par_view_point) : Circle(other)
// {
// 	lighting_point = par_lighting_point;
// 	view_point     = par_view_point;
// }

// double Lightened_sphere::count_z_coordinate(double x, double y)
// {
// 	return sqrt(radius * radius - x * x - y * y);
// }

// void Lightened_sphere::draw_z(Screen_information *screen)
// {
// 	size_t width = screen->get_width();
// 	size_t height = screen->get_height();

// 	for (unsigned x = 0; x < width; ++x)
// 	{
// 		for (unsigned y = 0; y < height; ++y)
// 		{
// 			if ((x - center_point.x) * (x - center_point.x) + (y - center_point.y) * (y - center_point.y) <= radius * radius)
// 			{
// 				double z = count_z_coordinate((double)(x - center_point.x), (double)(y - center_point.y)); //  + center_point.z
// 				double propotion = z / radius;

// 				screen->set_color(y, x, {255, (unsigned char)((double)255 * propotion), (unsigned char)((double)255 * propotion), (unsigned char)((double)255 * propotion) });
// 			}
// 			else
// 			{
// 				screen->set_color(y, x, {0, 0, 0, 0});
// 			}
// 		}
// 	}
// }

// void Lightened_sphere::draw_lambert(Screen_information *screen)
// {
// 	size_t width = screen->get_width();
// 	size_t height = screen->get_height();

// 	for (unsigned x = 0; x < width; ++x)
// 	{
// 		for (unsigned y = 0; y < height; ++y)
// 		{
// 			if ((x - center_point.x) * (x - center_point.x) + (y - center_point.y) * (y - center_point.y) <= radius * radius)
// 			{
// 				double z = count_z_coordinate((double)(x - center_point.x), (double)(y - center_point.y)); // + center_point.z;
// 				// double propotion = z / radius;

// 				Point_3d sphere_center = { center_point.x, center_point.y, 0 };

// 				Vector_3d radius_vector(sphere_center, {(double)x, (double)y, z});
// 				radius_vector *= 2.0;
// 				Vector_3d perpendicular_to_the_surface({(double)x, (double)y, z}, radius_vector.get_end_point());
// 				Vector_3d light_vector({(double)x, (double)y, z}, lighting_point);

// 				// скалярное произведение
// 				double cos_angle = perpendicular_to_the_surface.cosine_of_angle_between(light_vector);
// 				if (cos_angle < 0)
// 					cos_angle = 0;

// 				unsigned char grey_color = ((unsigned char)((double)255 * cos_angle) + EMBEDDING > 255 ? 255 : (unsigned char)((double)255 * cos_angle) + EMBEDDING);
				
// 				screen->set_color(y, x, {255, grey_color, grey_color, grey_color});
// 			}
// 			else
// 			{
// 				screen->set_color(y, x, {0, 0, 0, 0});
// 			}
// 		}
// 	}
// }

// void Lightened_sphere::draw_lambert_and_fong(Screen_information *screen)
// {
// 	size_t width = screen->get_width();
// 	size_t height = screen->get_height();

// 	for (unsigned x = 0; x < width; ++x)
// 	{
// 		for (unsigned y = 0; y < height; ++y)
// 		{
// 			if ((x - center_point.x) * (x - center_point.x) + (y - center_point.y) * (y - center_point.y) <= radius * radius)
// 			{
// 				double z = count_z_coordinate((double)(x - center_point.x), (double)(y - center_point.y)); // + center_point.z;
// 				// double propotion = z / radius;

// 				sphere_center = { center_point.x, center_point.y, 0 };

				


// 				Vector_3d radius_vector(sphere_center, {(double)x, (double)y, z});
// 				// printf("x=%lg, y=%lg, z=%lg\n", sphere_center.x, sphere_center.y, sphere_center.z);
// 				// printf("before x=%lg, y=%lg, z=%lg\n", (double)x, (double)y, z);
// 				radius_vector *= 2.0;
// 				// printf("after x=%lg, y=%lg, z=%lg\n", radius_vector.get_end_point().x, radius_vector.get_end_point().y, radius_vector.get_end_point().z);
// 				Vector_3d perpendicular_to_the_surface({(double)x, (double)y, z}, radius_vector.get_end_point());
// 				Vector_3d light_vector({(double)x, (double)y, z}, lighting_point);

				



// 				// скалярное произведение
// 				double cos_angle = perpendicular_to_the_surface.cosine_of_angle_between(light_vector);
// 				// printf("%lg\n", cos_angle);
// 				if (cos_angle < 0)
// 					cos_angle = 0;
				







// 				Vector_3d reflected_vector = light_vector.reflect_vector_relative_vector(perpendicular_to_the_surface);
// 				Vector_3d view_vector({(double)x, (double)y, z}, view_point);
// 				double glare_angle_cos = reflected_vector.cosine_of_angle_between(view_vector);

// 				unsigned char grey_color = ((unsigned char)((double)255 * cos_angle) + (unsigned char)((double)255 * glare_angle_cos) + EMBEDDING > 255 ? 255 : (unsigned char)((double)255 * cos_angle) + (unsigned char)((double)255 * glare_angle_cos) + EMBEDDING);
// 				// grey_color = (grey_color + 255 * glare_angle_cos > 255 ? 0 : grey_color + 255 * glare_angle_cos);

// 				screen->set_color(y, x, {255, grey_color, grey_color, grey_color});
// 			}
// 			else
// 			{
// 				screen->set_color(y, x, {0, 0, 0, 0});
// 			}
// 		}
// 	}
// }

