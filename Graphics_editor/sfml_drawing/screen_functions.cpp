#include "screen_functions.hpp"

const char *screen_state_text[]
{
    "EVERYTHING IS OKAY\n",
    "LIST DOES NOT EXIST\n",
    "NO MEMORY FOR CONSTRUCTION\n",
    "SEGMENTATION FAULT\n"
};

Screen_information::Screen_information(size_t par_width, size_t par_height) 
: window(sf::VideoMode(par_width, par_height), "It works"), event(), mouse_position(0.0, 0.0)//, textures()
{
	width  = par_width;
	height = par_height;

	data = new Color[width * height];
	
	if (data == NULL)
		return;

	mouse_clicked = false;
}

Screen_information::~Screen_information()
{
	delete [] data;
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

void Screen_information::draw_circle(const Vector_ll &par_position, const Color &par_color, const double par_radius, const Color &par_fill_color)
{
	sf::CircleShape circle(par_radius);

	circle.setPosition(sf::Vector2f(par_position.get_x(), par_position.get_y()));

	sf::Color color(par_color.r, par_color.g, par_color.b, par_color.a);
	sf::Color fill_color(par_fill_color.r, par_fill_color.g, par_fill_color.b, par_fill_color.a);
	circle.setOutlineColor(color);
	circle.setFillColor(fill_color);

	window.draw(circle);
}

void Screen_information::draw_rectangle(const Vector_ll &par_position, const Color &par_color, const double par_width, const double par_height)
{
	sf::RectangleShape rectangle(sf::Vector2f(par_width, par_height));

	rectangle.setPosition(sf::Vector2f(par_position.get_x(), par_position.get_y()));

	sf::Color color(par_color.r, par_color.g, par_color.b, par_color.a);
	rectangle.setFillColor(color);

	window.draw(rectangle);
}

void Screen_information::draw_point(const Vector_ll &par_point, const Color &par_color)
{
	sf::Color color(par_color.r, par_color.g, par_color.b, par_color.a);
	sf::Vertex sfml_point(sf::Vector2f(par_point.get_x(), par_point.get_y()), color);

	window.draw(&sfml_point, 1, sf::Points);
}

void Screen_information::draw_line(const Vector_ll &left, const Vector_ll &right, const Color &par_color)
{
	sf::Color color(par_color.r, par_color.g, par_color.b, par_color.a);
	sf::Vertex sfml_line[] = {  sf::Vertex(sf::Vector2f(left.get_x(), left.get_y()), color), 
								sf::Vertex(sf::Vector2f(right.get_x(), right.get_y()), color) };
	
	window.draw(sfml_line, 2, sf::Lines);
}


void Screen_information::draw_text(const char *par_text, const Vector_ll &par_position, const Color &par_color, const size_t par_text_size)
{
	sf::Font font = {};
	if (!font.loadFromFile("graphical_attributes/Fonts/OpenGostTypeA-Regular.ttf"))
	{
	    printf("No fonts found\n");
	}
	else
	{
		sf::Color color(par_color.r, par_color.g, par_color.b, par_color.a);

		sf::Text drawable_text = {};//(par_text, font, par_text_size);
		drawable_text.setFont(font);
		drawable_text.setString(par_text);
		drawable_text.setCharacterSize(par_text_size);
		drawable_text.setFillColor(color);
		
		drawable_text.setPosition(par_position.get_x() - drawable_text.getGlobalBounds().width / 2, par_position.get_y() - (drawable_text.getGlobalBounds().height));

		window.draw(drawable_text);
	}
}

void Screen_information::draw_image(const Color *array, const Vector_ll &position, const size_t width, const size_t height)
{
	sf::Texture texture;
	texture.create(width, height);

	texture_load(&texture, array, width, height);

	draw_texture(position, &texture, width, height);
}

void Screen_information::draw_texture(const Vector_ll &position, const char *texture_name)
{
	sf::Sprite sprite;
	sf::Texture texture;
	texture.loadFromFile(texture_name);

	sprite.setTexture(texture);

	sprite.setPosition(position.get_x(), position.get_y());

	window.draw(sprite);
}

void Screen_information::draw_texture(const Vector_ll &position, const sf::Texture *texture, const size_t width, const size_t height, const double transperancy)
{
	sf::Sprite sprite;

	// sf::RenderTexture render_texture;
	// render_texture.create(get_width(), get_height());

	size_t texture_width = texture->getSize().x;
	size_t texture_height = texture->getSize().y;

	sprite.setPosition(position.get_x(), position.get_y());

	double scale_x = (double)width / (double)texture_width;
	double scale_y = (double)height / (double)texture_height;

	// render_texture.draw(texture);
	// if (scale_x > 1 || scale_y > 1)
	// {
	// 	render_texture.setSmooth(true);
	// }


	sprite.setTexture(*texture);
	sprite.setScale(scale_x, scale_y);

	// double max_color = (double)MAX_COLOR_VALUE;
	// max_color *= transperancy;
	// // printf("brightness %lg\n", max_color);
	// sprite.setColor(sf::Color(255, 255, 255, (unsigned char)max_color));

	window.draw(sprite);
}

void Screen_information::reset()
{
	window.clear();
}

void Screen_information::sfml_update_mouse_state()
{
	sfml_update_mouse_position();
	sfml_update_mouse_pressed_state();
}

void Screen_information::sfml_update_mouse_position()
{
	sf::Vector2i sfml_position(mouse.getPosition(window));

	mouse_position = Vector_ll(sfml_position.x, sfml_position.y);
}

void Screen_information::sfml_update_mouse_pressed_state()
{
	mouse_clicked = mouse.isButtonPressed(mouse.Left);
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

void Screen_information::image_load(sf::Image *image, const Color *to_draw, const size_t width, const size_t height)
{
	sf::Vector2u image_size = (*image).getSize();
	if (image_size.x < width || image_size.y < height)
		return;

	for (size_t i = 0; i < height; i++) {
		for (size_t j = 0; j < width; j++)
		{
			sf::Color color(to_draw[i * width + j].r, to_draw[i * width + j].g,
				            to_draw[i * width + j].b, to_draw[i * width + j].a);

			image->setPixel(j, i, color);
		}
	}
}

void Screen_information::texture_load(sf::Texture *texture, const Color *to_draw, const size_t width, const size_t height)
{
	sf::Vector2u texture_size = (*texture).getSize();
	if (texture_size.x < width || texture_size.y < height)
		return;

	texture->update((sf::Uint8*)to_draw, width, height, 0, 0);
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

Vector_ll get_image_size(const char *filename)
{
	sf::Image image;
	image.loadFromFile(filename);

	sf::Vector2u size = image.getSize();
	
	return Vector_ll(size.x, size.y);
}
