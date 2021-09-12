#include <SFML/Graphics.hpp>

typedef enum Screen_information_code_errors 
{ 
	SCREEN_OK,
    SCREEN_NULL,
    SCREEN_NO_CONSTRUCT,
    SCREEN_SEGMENT_FAULT
} screen_code;

const char *screen_state_text[]
{
    "EVERYTHING IS OKAY\n",
    "LIST DOES NOT EXIST\n",
    "NO MEMORY FOR CONSTRUCTION\n",
    "SEGMENTATION FAULT\n"
};


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
	Screen_information(const char *file_name)
	{
		sf::Image image;
		image.loadFromFile(file_name);

		sf::Vector2u size = image.getSize();
		screen->width = size.x;
		screen->height = size.y;

		screen->data = (Color*)calloc(screen->width * screen->height, sizeof(Color));
		if (screen->data == NULL)
			return SCREEN_NO_CONSTRUCT;

		for (size_t i = 0; i < screen->height; i++)
			for (size_t j = 0; j < screen->width; j++)
			{
				sf::Color color = image.getPixel(j, i);
				copy_color_from_sfml_color(color, screen, i, j);
			}
	}

	Screen_information(size_t par_width, size_t par_height)
	{
		width  = par_width;
		height = par_height;

		data = (Color*)calloc(width * height, sizeof(Color));
		
		if (data == NULL)
			return;
	}

	~Screen_information()
	{
		if (!data)
			return;

		free(data);
	}
	
	friend void copy_color_from_sfml_color(Screen_information &screen, sf::Color color, size_t line, size_t column);
	friend screen_code screen_load(sf::Image* image, Screen_information &screen);
};
