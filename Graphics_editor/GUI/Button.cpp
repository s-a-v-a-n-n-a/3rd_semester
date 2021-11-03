#include "Button.hpp"

const size_t DEFAULT_BUTTON_HEIGHT = 50;
const size_t INCREASED_BUTTON_HEIGHT = 70;

Button::Button(const size_t par_type, const Vector_ll &par_position, const Color &par_color, const size_t par_width, const size_t par_height, Button_delegate *par_click, const char *par_text)
: Visual_object(par_type, par_position, par_color, par_width, par_height) // const char *par_text = NULL
{
	size_t offset = par_height / 2;
	Text *text = new Text((size_t)Vidget_type::TEXT, 
							par_text, 
							offset, 
							par_position + Vector_ll(par_width/2.0, par_height/2.0), //par_position + 
							DEFAULT_TEXT_COLOR);
	add_visual_object(text);

	click = par_click;
}

Button::Button(const size_t par_type, const Vector_ll &par_position, Texture *par_texture, const size_t par_width, const size_t par_height, Button_delegate *par_click, const char *par_text)
: Visual_object(par_type, par_position, par_texture, par_width, par_height) // const char *par_text = NULL
{
	size_t offset = get_height() / 2;
	Text *text = new Text((size_t)Vidget_type::TEXT, 
							par_text, 
							offset, 
							par_position + Vector_ll(get_width()/2.0, get_height()/2.0), //par_position + 
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
	if(get_texture())
	{
		screen->draw_texture(get_position(), get_texture()->get_texture(), get_width(), get_height());
	}
	else	
	{
		Visual_object::draw(screen);
	}

	size_t objects_amount = get_objects()->get_length();
	for (size_t i = 0; i < objects_amount; ++i)
	{
		(get_objects()->get_array()[i])->draw(screen);
	}
}

bool Button::on_mouse_click(const bool state, const size_t par_x, const size_t par_y) // const Mouse_event par_event, 
{
	if (point_inside(par_x, par_y))
	{
		set_active_state(true);
	    if (click)
	    	if (state)
	    	{
	    		// printf("mouse click\n");
	    		return click->on_mouse_click(par_x, par_y);
	    	}
	    	// else if (state == Mouse_state::MOVED)
	    	// 	return click->on_mouse_move(par_x, par_y);
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

bool Button::on_mouse_move(const Vector_ll from, const Vector_ll to)
{
	if (point_inside(from.get_x(), from.get_y()) || point_inside(to.get_x(), to.get_y()))
	{
		set_active_state(true);
		// printf("mouse move\n");
	    return click->on_mouse_move(from, to);
	}
	else
	{
		return false;
	}

	// return click->on_mouse_move(from, to);
}
