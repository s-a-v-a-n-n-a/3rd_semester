#ifndef DRAWING
#define DRAWING

#include <SFML/Graphics.hpp>

struct Point
{
	double x;
	double y;
};

inline void draw_point(sf::RenderWindow *window, sf::Vertex point)
{
	window->draw(&point, POINT, sf::Points);
}

inline void draw_line(sf::RenderWindow *window, sf::Vertex begin, sf::Vertex end) // redo // redid
{
	sf::Vertex line[] = { begin, end };
	window->draw(line, LINE, sf::Lines); // magic // where
}

#endif // DRAWING
