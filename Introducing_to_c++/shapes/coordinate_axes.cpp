#include "coordinate_axes.hpp"

void System_of_axes::draw(sf::RenderWindow *window)
{
	sf::RectangleShape coordinate_field(sf::Vector2f(x_max - x_min, y_max - y_min));
	coordinate_field.setPosition(left_corner.x, left_corner.y);
	coordinate_field.setFillColor(sf::Color::White);

	window->draw(coordinate_field);
}
