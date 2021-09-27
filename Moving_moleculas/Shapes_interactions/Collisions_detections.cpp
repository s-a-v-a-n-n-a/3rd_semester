#include "Collisions_detections.hpp"

bool (*detection_functions[shape_types_amount * shape_types_amount])(const Shape *par_first, const Shape *par_second) =
{
	molecula_molecula_collision_detection, molecula_rectangle_collision_detection,
	molecula_rectangle_collision_detection, rectangle_rectangle_collision_detection
};

bool molecula_rectangle_collision_detection(const Shape *par_first, const Shape *par_second)
{
	// printf("1\n");

	Molecula *first = NULL;
	Rectangle *second = NULL;

	if ((Shape_types)par_first->get_type() == Shape_types::MOLECULA)
	{
		// printf("???\n");

		first = (Molecula*)par_first;
		second = (Rectangle*)par_second;
	}
	else
	{
		// printf("!!!\n");

		first = (Molecula*)par_second;
		second = (Rectangle*)par_first;
	}

	Radius_vector first_centre = first->get_centre_position();
	Radius_vector second_centre = second->get_centre_position();

	double rect_width = second->get_width();
	double rect_height = second->get_height();

	double second_centre_x = second_centre.get_x();
	double second_centre_y = second_centre.get_y();

	Radius_vector collision_line(first->get_centre_position() - second->get_centre_position());

	double current_distance = collision_line.length();
	// if (first_centre.get_y() < second_centre_y + rect_height/2.0 && first_centre.get_y() > second_centre_y - rect_height/2.0)
	// {
	// 	double x_projection = fabs(current_distance * cos(collision_line.get_angle(Radius_vector(rect_width, 0))));
	// 	if (x_projection <= rect_width/2.0 + first->get_radius())
	// 	{
	// 		printf("%lg, %lg\n", current_distance, x_projection);
	// 		return true;
	// 	}
	// }
	// else if (first_centre.get_x() < second_centre_x + rect_width/2.0 && first_centre.get_x() > second_centre_x - rect_width/2.0)
	// {
	// 	double y_projection = fabs(current_distance * cos(collision_line.get_angle(Radius_vector(0, rect_height))));
	// 	if (y_projection <= rect_height/2.0 + first->get_radius())
	// 	{
	// 		printf("%lg : %lg\n", y_projection, rect_height/2.0 + first->get_radius());
	// 		// printf("%lg, %lg\n", current_distance, y_projection);
	// 		return true;
	// 	}
	// }
	if (fabs(current_distance * collision_line.get_cos_angle(Radius_vector(1.0, 0.0))) <= rect_width/2.0 + first->get_radius() && 
		fabs(current_distance * collision_line.get_cos_angle(Radius_vector(0.0, 1.0))) <= rect_height/2.0 + first->get_radius())
	{
		// printf("collision\n");
		return true;
	}
	
	return false;
}

bool molecula_molecula_collision_detection(const Shape *par_first, const Shape *par_second)
{
	// printf("2\n");

	Molecula *first = (Molecula*)par_first;
	Molecula *second = (Molecula*)par_second;

	double current_distance = Radius_vector(first->get_centre_position() - second->get_centre_position()).length() - first->get_radius() - second->get_radius();
	if (current_distance < 0)
	{
		// printf("%lg\n", current_distance);
		return true;
	}

	return false;
}

bool rectangle_rectangle_collision_detection(const Shape *par_first, const Shape *par_second)
{
	// printf("3\n");

	Rectangle *first = (Rectangle*)par_first;
	Rectangle *second = (Rectangle*)par_second;

	Radius_vector first_centre = first->get_centre_position();
	Radius_vector second_centre = second->get_centre_position();

	double first_width = first->get_width();
	double first_height = first->get_height();

	double second_width = second->get_width();
	double second_height = second->get_height();

	double first_centre_x = first_centre.get_x();
	double first_centre_y = first_centre.get_y();

	double second_centre_x = second_centre.get_x();
	double second_centre_y = second_centre.get_y();

	Radius_vector collision_line(first_centre - second_centre);

	double current_distance = collision_line.length();
	// if (first_centre_y < second_centre_y + second_height/2.0 && first_centre_y > second_centre_y - second_height/2)
	// {
	// 	double x_projection = current_distance * collision_line.get_angle(Radius_vector(Radius_vector(second_centre_x + second_width/2, second_centre_y - second_height/2) - Radius_vector(second_centre_x - second_width/2, second_centre_x - second_height/2)));
	// 	if (x_projection <= first_width/2.0 + second_width/2.0)
	// 		return true;
	// }
	// else
	// {
	// 	double y_projection = current_distance * collision_line.get_angle(Radius_vector(Radius_vector(second_centre_x, second_centre_y + second_height/2) - Radius_vector(second_centre_x, second_centre_y - second_height/2)));
	// 	if (y_projection <= first_height/2.0 + second_height/2.0)
	// 		return true;
	// }
	
	if (fabs(current_distance * collision_line.get_cos_angle(Radius_vector(1.0, 0.0))) <= (first_width + second_width)/2.0 && 
		fabs(current_distance * collision_line.get_cos_angle(Radius_vector(0.0, 1.0))) <= (first_height + second_height)/2.0)
	{
		// printf("%lg, %lg\n", fabs(current_distance * collision_line.get_cos_angle(Radius_vector(1.0, 0.0))), fabs(current_distance * collision_line.get_cos_angle(Radius_vector(0.0, 1.0))));
		return true;
	}
	
	return false;
}