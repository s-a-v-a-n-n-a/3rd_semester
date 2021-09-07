#ifndef DRAWING
#define DRAWING

#include <SFML/Graphics.hpp>

struct Point
{
	double x;
	double y;
};

inline void draw_point_sfml(sf::RenderWindow *window, Point point)
{
	sf::Vertex sfml_point(sf::Vector2f(point.x, point.y), sf::Color(196, 0, 171));

	window->draw(&sfml_point, POINT, sf::Points);
}

inline void draw_line_sfml(sf::RenderWindow *window, Point begin, Point end) // redo // redid
{
	sf::Vertex sfml_begin(sf::Vector2f(begin.x, begin.y), sf::Color(196, 0, 171));
	sf::Vertex sfml_end(sf::Vector2f(end.x, end.y), sf::Color(196, 0, 171));

	sf::Vertex line[] = { sfml_begin, sfml_end };
	window->draw(line, LINE, sf::Lines); // magic // where
}

#endif // DRAWING
