#include "screen_functions.h"

void Screen_information::copy_color_from_sfml_color(Screen_information screen, sf::Color color, size_t line, size_t column)
{
	screen->data[line * screen->width + column].r = color.r;
	screen->data[line * screen->width + column].g = color.g;
	screen->data[line * screen->width + column].b = color.b;
	screen->data[line * screen->width + column].a = color.a;
}

screen_code screen_load(sf::Image *image, Screen_information &screen)
{
	sf::Vector2u image_size = (*image).getSize();
	if (image_size.x < screen.width || image_size.y < screen.height)
		return SCREEN_SEGMENT_FAULT;

	for (size_t i = 0; i < screen->height; i++) {
		for (size_t j = 0; j < screen->width; j++)
		{
			sf::Color color(screen->data[i * screen->width + j].r, screen->data[i * screen->width + j].g,
				            screen->data[i * screen->width + j].b, screen->data[i * screen->width + j].a);

			image->setPixel(j, i, color);
		}
	}

	return SCREEN_OK;
}
