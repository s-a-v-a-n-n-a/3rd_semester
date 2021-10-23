#include "Canvases_list.hpp"

void Canvases_list::add_canvas(Canvas_manager *to_add)
{
	current_canvases.add_to_end(to_add);

    size_t button_width = 150;
    size_t button_height = 80;

    set_width(current_canvases.get_length() * 250);
    set_height(button_height);

    Canvas_keeper *keep = new Canvas_keeper(to_add);
    Button *keeper = new Button(Vidget_type::BUTTON,
    							get_position() + Radius_vector(get_objects()->get_length() * 250, 0.0), 
								WHITE, 
								button_width, 
								button_height,
								keep, 
								"Canvas");

    Button *closing = new Button(Vidget_type::BUTTON,
    							get_position() + Radius_vector(get_objects()->get_length() * 250 + 150, 0.0),
    							WHITE,
    							100,
    							button_height,
    							NULL,
    							"X");
    Close_interactive_delegate *close = new Close_interactive_delegate(this, closing);
    closing->set_delegate(close);
   

    add_visual_object(keeper);
    add_visual_object(closing);

    set_active(keeper);
}

void Canvases_list::delete_canvas(Canvas_manager *to_delete)
{
	size_t index = very_slow_delete_visual_object(to_delete);

	slow_delete_visual_object(index);

	Visual_object **objects_array = get_objects()->get_array();
	size_t objects_amount = get_objects()->get_length();
	
	for (size_t i = index; i < objects_amount; ++i)
	{
		objects_array[i]->set_position(objects_array[i]->get_position() - Radius_vector(250.0, 0.0));
	}
}

