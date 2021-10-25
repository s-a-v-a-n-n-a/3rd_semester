#include "Tab.hpp"

Tab::Tab(const size_t par_type, const Vector_ll &par_position, const Color &par_color, const size_t par_width, const size_t par_height, Visual_object *par_parent)
: Visual_object(par_type, par_position, par_color, par_width, par_height)
{
	parent = par_parent;

	size_t button_width = 150;
    size_t button_height = 80;

    Canvas_keeper *keep = new Canvas_keeper(parent);
    Button *keeper = new Button((size_t)Vidget_type::BUTTON,
    							par_position, // get_position() + Vector_ll(get_objects()->get_length() * 250, 0.0), 
								WHITE, 
								button_width, 
								button_height,
								keep, 
								"Canvas");


    Button *closing = new Button((size_t)Vidget_type::BUTTON,
    							par_position + Vector_ll(button_width, 0.0), // get_position() + Vector_ll(get_objects()->get_length() * 250 + 150, 0.0),
    							WHITE,
    							100,
    							button_height,
    							NULL,
    							"X");
    Close_delegate *close = new Close_delegate(parent);
    closing->set_delegate(close);
   

    add_visual_object(keeper);
    add_visual_object(closing);
}

Tab::Tab(const size_t par_type, const Vector_ll &par_position, Texture *par_texture, Visual_object *par_parent)
: Visual_object(par_type, par_position, par_texture)
{
    parent = par_parent;

    size_t button_width = 200;
    size_t button_height = 80;

    Canvas_keeper *keep = new Canvas_keeper(parent);
    Button *keeper = new Button((size_t)Vidget_type::BUTTON,
                                par_position, // get_position() + Vector_ll(get_objects()->get_length() * 250, 0.0), 
                                TRANSPARENT, 
                                button_width, 
                                button_height,
                                keep, 
                                "Canvas");


    Full_texture *texture = new Full_texture(CLOSE_TEXTURE);
    Button *closing = new Button((size_t)Vidget_type::BUTTON,
                                par_position + Vector_ll(button_width, 0.0), // get_position() + Vector_ll(get_objects()->get_length() * 250 + 150, 0.0),
                                texture,
                                NULL,
                                "");
    Close_delegate *close = new Close_delegate(parent);
    closing->set_delegate(close);
   

    add_visual_object(keeper);
    add_visual_object(closing);
}

