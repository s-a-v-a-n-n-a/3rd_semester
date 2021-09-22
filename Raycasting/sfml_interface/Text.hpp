#ifndef TEXT_CLASS
#define TEXT_CLASS

#include <cstring>

struct Text
{
	char *font_file; // "arial.ttf"
	size_t font_size; // 10

	char text[30];

	double left_corner_x;
	double left_corner_y;

	Text()
	{
		font_file = "arial.ttf";
		font_size = 10;

		memset(text, 0, 30);

		left_corner_x = 0;
		left_corner_y = 0;
	}

	Text(char par_text[30], double par_x, double par_y, char *par_font_file = "arial.ttf", size_t par_font_size = 10)
	{
		font_file = par_font_file;
		font_size = par_font_size;

		set_text(par_text);

		left_corner_x = par_x;
		left_corner_y = par_y;
	}

	void set_text(const char par_text[30])
	{
		strcpy(text, par_text, 30);
	}

	void set_position(const double par_x, const double par_y)
	{
		left_corner_x = par_x;
		left_corner_y = par_y;
	}

	void set_font_size(const size_t par_font_size) { font_size = par_font_size; }
	void set_font_file(const char *par_font_file) { font_file = par_font_file; }

	void draw(sf::RenderWindow *window)
	{
		sf::Font font;
		if (!font.loadFromFile(font_file))
		{
		    printf("No fonts found\n");
		    system.pause();
		}

		sf::Text button_text(text, font, font_size);
		button_text.setPosition(left_corner_x, left_corner_y);

		window->draw(text);
	}
};

#endif // TEXT_CLASS
