#ifndef SCREEN_FUNCTIONS
#define SCREEN_FUNCTIONS

#include <SFML/Graphics.hpp>

typedef enum Screen_information_code_errors 
{ 
	SCREEN_OK,
    SCREEN_NULL,
    SCREEN_NO_CONSTRUCT,
    SCREEN_SEGMENT_FAULT
} screen_code;

extern const char *screen_state_text[];


struct Color 
{
	unsigned char a;
	unsigned char r;
	unsigned char g;
	unsigned char b;
};

class Screen_information 
{
private:
	Color *data;
	size_t width;
	size_t height;

public:
	Screen_information(const char *file_name);
	Screen_information(size_t par_width, size_t par_height);
	~Screen_information();

	screen_code set_color(size_t line, size_t column, Color color);

	size_t get_width();
	size_t get_height();
	
	friend void copy_color_from_sfml_color(Screen_information &screen, sf::Color color, size_t line, size_t column);
	friend screen_code screen_load(Screen_information &screen, sf::Image* image);
	friend void draw_shape_sfml(sf::RenderWindow *window, Screen_information &screen);
};

#endif // SCREEN_FUNCTIONS
