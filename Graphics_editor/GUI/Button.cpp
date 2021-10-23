#include "Button.hpp"

const size_t DEFAULT_BUTTON_HEIGHT = 80;

Button::Button(const size_t par_type, const Radius_vector &par_position, Color par_color, double par_width, double par_height,
			   Button_delegate *par_click, const char *par_text)
			   : Visual_object(par_type, par_position, par_color, par_width, par_height) // const char *par_text = NULL
{
	size_t offset = par_width / (2 + strlen(par_text) / 2);
	while (offset * 3 > par_height && offset > 1)
		offset--;
	Text *text = new Text((size_t)Vidget_type::TEXT, 
							par_text, 
							offset, 
							par_position + Radius_vector(par_width/2.0, par_height/2.0), //par_position + 
							DEFAULT_TEXT_COLOR);
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

bool Button::on_mouse(const Mouse_state state, const size_t par_x, const size_t par_y) // const Mouse_event par_event, 
{
	if (point_inside(par_x, par_y))
	{
		set_active_state(true);
	    if (click)
	    	if (state == Mouse_state::CLICKED)
	    		return click->on_mouse_click(par_x, par_y);
	    	else if (state == Mouse_state::MOVED)
	    		return click->on_mouse_move(par_x, par_y);
	    	else
	    	{
	    		return click->on_mouse_release();
	    	}

	    return true;
	}
	else
	{
		return false;
	}
}
