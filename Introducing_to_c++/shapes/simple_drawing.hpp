#ifndef DRAWING
#define DRAWING

#include <SFML/Graphics.hpp>

enum Shapes_types
{
	POINT = 1,
	LINE  = 2
};

class Point
{
public:
	double x;
	double y;

	const Point operator+=(const Point &other)
	{
		return { x += other.x, y += other.y };
	} 
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
