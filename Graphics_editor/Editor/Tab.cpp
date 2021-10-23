#include "Tab.hpp"

Tab::Tab(const size_t par_type, const Radius_vector &par_position, const Color &par_color, const size_t par_width, const size_t par_height, Visual_object *par_parent)
: Visual_object(par_type, par_position, par_color, par_width, par_height)
{
	parent = par_parent;

	size_t button_width = 150;
    size_t button_height = 80;

    // set_width(current_canvases.get_length() * 250);
    // set_height(button_height);
    printf("Tab position: %lg, %lg\n", par_position.get_x(), par_position.get_y());

    Canvas_keeper *keep = new Canvas_keeper(parent);
    Button *keeper = new Button((size_t)Vidget_type::BUTTON,
    							par_position, // get_position() + Radius_vector(get_objects()->get_length() * 250, 0.0), 
								WHITE, 
								button_width, 
								button_height,
								keep, 
								"Canvas");


    Button *closing = new Button((size_t)Vidget_type::BUTTON,
    							par_position + Radius_vector(button_width, 0.0), // get_position() + Radius_vector(get_objects()->get_length() * 250 + 150, 0.0),
    							WHITE,
    							100,
    							button_height,
    							NULL,
    							"X");
    Close_delegate *close = new Close_delegate(parent);
    closing->set_delegate(close);
   

    add_visual_object(keeper);
    add_visual_object(closing);

    // set_active(keeper);
}
