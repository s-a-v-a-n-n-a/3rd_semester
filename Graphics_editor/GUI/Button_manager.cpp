#include "Button_manager.hpp"

Button_manager::Button_manager(const size_t par_type, const Vector_ll &par_position, Color par_color, double par_width, double par_height)
: Visual_object(par_type, par_position, par_color, par_width, par_height)
{
    size_t button_height = par_height;

    size_t current_button_offset = 0;

    current_end_position = par_position;
}

Button_manager::~Button_manager()
{
	Visual_object **objects = get_objects()->get_array();
	size_t objects_amount = get_objects()->get_length();

	for (size_t i = 0; i < objects_amount; ++i)
	{
		delete objects[i];
	}
}

Button *Button_manager::add_button(Button_delegate *par_delegate, const char *par_text, const Color par_color, const size_t par_width, const size_t par_height)
{
	// size_t button_width = strlen(par_text) * 40 > par_width :  strlen(par_text) * 40 : par_width;

	Button *new_button = new Button((size_t)Vidget_type::BUTTON,
    								current_end_position, 
    								par_color, 
								  	par_width, 
								  	par_height,
								  	par_delegate, 
								  	par_text);

	current_end_position += Vector_ll(par_width, 0.0);

	add_visual_object(new_button);

	return new_button;
}

Button *Button_manager::add_button(Button_delegate *par_delegate, const char *par_text, Texture *par_texture)
{
	// size_t button_width = strlen(par_text) * 40 > par_width :  strlen(par_text) * 40 : par_width;

	Button *new_button = new Button((size_t)Vidget_type::BUTTON,
    								current_end_position, 
    								par_texture,
								  	par_delegate, 
								  	par_text);

	current_end_position += Vector_ll(par_texture->get_width(), 0.0);

	add_visual_object(new_button);

	return new_button;
}

// void Button_manager::draw(Screen_information *screen)
// {
// 	Visual_object **objects_array = get_objects()->get_array();
// 	size_t objects_amount = get_objects()->get_length();

// 	for (size_t i = 0; i < objects_amount; ++i)
// 	{
// 		if (objects_array[i]->get_visible())
// 		{
// 			objects_array[i]->draw(screen);
// 		}
// 	}	
// }
