#include "coordinate_axes.hpp"

void System_of_axes::init(double left_high_corner_x,
					 	  double left_high_corner_y,
					 	  double x_min,
					 	  double x_max,
					 	  double y_min,
					 	  double y_max)
{
	if (x_max < x_min)
	{
		double tmp = x_max;
		x_max = x_min;
		x_min = tmp;
	}

	if (y_max < y_min)
	{
		double tmp = y_max;
		y_max = y_min;
		y_min = tmp;
	}

	this->left_high_corner_x = left_high_corner_x;
	this->left_high_corner_y = left_high_corner_y;
	
	this->x_min = x_min;
	this->x_max = x_max;

	this->y_min = y_min;
	this->y_max = y_max;

	if (x_min <= 0)
		this->zero_point_x = left_high_corner_x + fabs(x_min);
	else
		this->zero_point_x = left_high_corner_x - fabs(x_min);
	
	if (y_max >= 0)
		this->zero_point_y = left_high_corner_y + fabs(y_max);
	else
		this->zero_point_y = left_high_corner_y - fabs(y_max);
}

void System_of_axes::draw(sf::RenderWindow *window)
{
	sf::RectangleShape coordinate_field(sf::Vector2f(this->x_max - this->x_min, this->y_max - this->y_min));
	coordinate_field.setPosition(this->left_high_corner_x, this->left_high_corner_y);

	// sf::Vertex abs_begin(sf::Vector2f(this->left_high_corner_x, this->left_high_corner_y + fabs(y_max)));

	window->draw(coordinate_field);
}
