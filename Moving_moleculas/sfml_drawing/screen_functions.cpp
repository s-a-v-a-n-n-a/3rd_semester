#include "screen_functions.hpp"

const char *screen_state_text[]
{
    "EVERYTHING IS OKAY\n",
    "LIST DOES NOT EXIST\n",
    "NO MEMORY FOR CONSTRUCTION\n",
    "SEGMENTATION FAULT\n"
};

// !!!! запретить !!!!
Screen_information::Screen_information(const char *file_name)
{
	sf::Image image;
	image.loadFromFile(file_name);

	sf::Vector2u size = image.getSize();
	width = size.x;
	height = size.y;

	data = (Color*)calloc(width * height, sizeof(Color));
	if (data == NULL)
		return;

	for (size_t i = 0; i < height; i++)
		for (size_t j = 0; j < width; j++)
		{
			sf::Color color = image.getPixel(j, i);
			copy_color_from_sfml_color(*this, color, i, j);
		}
}

Screen_information::Screen_information(size_t par_width, size_t par_height)
{
	width  = par_width;
	height = par_height;

	data = (Color*)calloc(width * height, sizeof(Color));
	
	if (data == NULL)
		return;
}

Screen_information::~Screen_information()
{
	if (!data)
		return;

	free(data);
}


screen_code Screen_information::set_color(size_t line, size_t column, Color color)
{
	if (line > height || column > width)
		return SCREEN_SEGMENT_FAULT;

	data[line * width + column] = color;

	return SCREEN_OK;
}

size_t Screen_information::get_width()
{
	return width;
}

size_t Screen_information::get_height()
{
	return height;
}

void Screen_information::reset()
{
	for (size_t i = 0; i < height; i++)
		for (size_t j = 0; j < width; j++)
		{
			data[i * width + j] = BLACK;
		}
}

void copy_color_from_sfml_color(Screen_information &screen, sf::Color color, size_t line, size_t column)
{
	screen.data[line * screen.width + column].r = color.r;
	screen.data[line * screen.width + column].g = color.g;
	screen.data[line * screen.width + column].b = color.b;
	screen.data[line * screen.width + column].a = color.a;
}

screen_code screen_load(Screen_information &screen, sf::Image *image)
{
	sf::Vector2u image_size = (*image).getSize();
	if (image_size.x < screen.width || image_size.y < screen.height)
		return SCREEN_SEGMENT_FAULT;

	for (size_t i = 0; i < screen.height; i++) {
		for (size_t j = 0; j < screen.width; j++)
		{
			sf::Color color(screen.data[i * screen.width + j].r, screen.data[i * screen.width + j].g,
				            screen.data[i * screen.width + j].b, screen.data[i * screen.width + j].a);

			image->setPixel(j, i, color);
		}
	}

	return SCREEN_OK;
}

void draw_shape_sfml(sf::RenderWindow *window, Screen_information &screen)
{
	sf::Sprite sprite;
	sf::Texture texture;
	texture.create(screen.width, screen.height);

	sprite.setTexture(texture);

	sf::Image image;
	image.create(screen.width, screen.height, sf::Color::Black);

	screen_load(screen, &image);

	texture.update(image);

	window->draw(sprite);
}
