//rename file to shape cause structure(cluss) has name 'shape'
#ifndef SHAPE
#define SHAPE

#include <SFML/Graphics.hpp>

enum Shapes_types
{
	POINT = 1,
	LINE  = 2
};

struct Shape
{
	void (*draw_shape)(Shape *shape, sf::RenderWindow *window);
};


#endif // SHAPE
