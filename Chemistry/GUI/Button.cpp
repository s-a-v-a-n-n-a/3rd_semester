#include "Button.hpp"

Button::Button(Button_delegate *par_click, const char *par_text, const Radius_vector &par_position, Color par_color, double par_width, double par_height)
: Visual_object(par_position, par_color, par_width, par_height) // const char *par_text = NULL
{
	size_t offset = par_width / (2 + strlen(par_text) / 2);
	while (offset * 3 > par_height && offset > 1)
		offset--;
	Text *text = new Text(par_text, offset, get_position() + Radius_vector(offset, offset), DEFAULT_TEXT_COLOR);
	add_visual_object(text);

	click = par_click;
}

Button::~Button()
{
	Visual_object **objects = get_objects()->get_array();
	size_t objects_amount = get_objects()->get_length();

	for (size_t i = 0; i < objects_amount; ++i)
	{
		delete objects[i];
	}

	delete click;
}

void Button::draw(Screen_information *screen)
{
	Visual_object::draw(screen);

	size_t objects_amount = get_objects()->get_length();
	for (size_t i = 0; i < objects_amount; ++i)
	{
		(get_objects()->get_array()[i])->draw(screen);
	}
}

bool Button::check_click(double par_x, double par_y)
{
	if (point_inside(par_x, par_y))
	{
		set_active(true);
	    click->click_reaction();

	    return true;
	}
	else
	{
		return false;
	}
}
