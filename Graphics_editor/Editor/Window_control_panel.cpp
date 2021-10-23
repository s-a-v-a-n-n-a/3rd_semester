#include "Window_control_panel.hpp"

Window_control_panel::Window_control_panel(const size_t par_type, const Radius_vector &par_position, const Color &par_color, const size_t par_width, const size_t par_height, Visual_object *whose)
: Visual_object(par_type, par_position, par_color, par_width, par_height)
{
	// create roll up button 
	// ATTENTION
	// MAGIC
	// ------------------------------------------------------------------------
	Button_manager *panel = new Button_manager((size_t)Vidget_type::BUTTON_MANAGER, par_position, BLUE, par_width, DEFAULT_BUTTON_HEIGHT);

	size_t button_width = par_width / 5;
    size_t button_height = par_height;

    Roll_up_delegate *rolling_up = new Roll_up_delegate(whose);
    panel->add_button(rolling_up, "-", WHITE, button_width);
    
    Drag_and_drop_delegate *drag_and_drop = new Drag_and_drop_delegate(whose);
	panel->add_button(drag_and_drop, " ", GREY, button_width * 3);
    
    Close_delegate *closing = new Close_delegate(whose);
	panel->add_button(closing, "X", WHITE, button_width);

	// add_visual_object(roll_up);
	// add_visual_object(dnd);
	// add_visual_object(close);
	add_visual_object(panel);

	// set_active(close);
}

Window_control_panel::~Window_control_panel()
{
	Visual_object **objects = get_objects()->get_array();
	size_t objects_amount = get_objects()->get_length();

	for (size_t i = 0; i < objects_amount; ++i)
	{
		delete objects[i];
	}
}

// void Window_control_panel::draw(Screen_information *screen)
// {
// 	Visual_object::draw(screen);

// 	Visual_object **objects = get_objects()->get_array();
// 	size_t objects_amount = get_objects()->get_length();

// 	for (size_t i = 0; i < objects_amount; ++i)
// 	{
// 		objects[i]->draw(screen);
// 	}
// }

// bool Window_control_panel::on_mouse(const double par_x, const double par_y)
// {
// 	size_t objects_amount = get_objects()->get_length();

// 	if (point_inside(par_x, par_y))
// 	{
// 		for (size_t i = objects_amount; i >= 0; --i)
// 		{
// 			if ((get_objects()->get_array()[i])->on_mouse(par_x, par_y)) // ??????
// 			{
// 				set_active(get_objects()->get_array()[i]);
				
// 				// slow_delete
// 				slow_delete_visual_object(i);
// 				// push
// 				add_visual_object(get_active());
				
// 				return true;
// 			}
// 		}
// 	}

// 	return false;
// }
