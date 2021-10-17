#include "Button.hpp"

Button::Button(const Radius_vector &par_position, Color par_color, double par_width, double par_height,
			   Button_delegate *par_click, const char *par_text)
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

bool Button::on_mouse(const bool clicked, const size_t par_x, const size_t par_y) // const Mouse_event par_event, 
{
	printf("came here\n");

	if (point_inside(par_x, par_y))
	{
		set_active_state(true);
	    if (click)
	    	if (clicked)
	    		click->on_mouse_click();
	    	else
	    		;

	    return true;
	}
	else
	{
		return false;
	}
}
