#ifndef TEXT_CLASS
#define TEXT_CLASS

#include <cstring>

#include "Visual_object_base.hpp"

class Text : public Visual_object
{
private:
	// char *font_file; // "arial.ttf"
	bool was_drawn;
	size_t font_size; 

	char *text;

public:
	Text(const char *par_text, const size_t par_font_size, const Radius_vector &par_position, const Color &par_color)
	: Visual_object(par_position, par_color, strlen(par_text), par_font_size)
	{
		set_color(par_color);

		font_size = par_font_size;

		text = new char[strlen(par_text) + 1];
		strcpy(text, par_text);
		// set_text(par_text);

		was_drawn = false;
	}

	~Text()
	{
		delete [] text;
	}

	void set_text(const char *par_text)
	{
		strcpy(text, par_text);
	}

	void set_font_size(const size_t par_font_size) { font_size = par_font_size; }
	// void set_font_file(const char *par_font_file)  { font_file = par_font_file; }

	void draw(Screen_information *screen) override
	{
		// ;
		// if (!was_drawn)
		// {
		// 	was_drawn = true;
		// 	screen->add_text(text, get_position(), font_size);
		// }
		screen->draw_text(text, get_position(), get_color(), font_size);
	}
};

#endif // TEXT_CLASS
