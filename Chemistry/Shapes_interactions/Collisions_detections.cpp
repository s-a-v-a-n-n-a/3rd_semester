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
		first = (Molecula*)par_first;
		second = (Rectangle*)par_second;
	}
	else
	{
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
	
	if (fabs(current_distance * collision_line.get_cos_angle(Radius_vector(1.0, 0.0))) <= rect_width/2.0 + first->get_radius() && 
		fabs(current_distance * collision_line.get_cos_angle(Radius_vector(0.0, 1.0))) <= rect_height/2.0 + first->get_radius())
	{
		return true;
	}
	
	return false;
}

bool molecula_molecula_collision_detection(const Shape *par_first, const Shape *par_second)
{
	Molecula *first = (Molecula*)par_first;
	Molecula *second = (Molecula*)par_second;

	double current_distance = Radius_vector(first->get_centre_position() - second->get_centre_position()).length() - first->get_radius() - second->get_radius();
	if (current_distance < 0)
	{
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
	
	if (fabs(current_distance * collision_line.get_cos_angle(Radius_vector(1.0, 0.0))) <= (first_width + second_width)/2.0 && 
		fabs(current_distance * collision_line.get_cos_angle(Radius_vector(0.0, 1.0))) <= (first_height + second_height)/2.0)
	{
		return true;
	}
	
	return false;
}