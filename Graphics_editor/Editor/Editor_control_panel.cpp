#include "Editor_control_panel.hpp"

Editor_control_panel::Editor_control_panel(const Radius_vector &par_position, Color par_color, double par_width, double par_height)
: Visual_object(par_position, par_color, par_width, par_height)
{
	size_t button_width = 0;
    size_t button_height = par_height;

    size_t current_button_offset = 0;

	// create File button
	// ------------------------------------------------------------------
    // Roll_up_delegate * = new Roll_up_delegate(whose);
    button_width = strlen(" File ") * par_height / 3;

    Button *file_button = new Button(Radius_vector(Radius_vector(0.0, 0.0)), 
								  WHITE, 
								  button_width, 
								  button_height,
								  NULL, 
								  "File");

    current_button_offset += button_width;
    // create new button
    // ------------------------------------------------------------------
    button_width = strlen(" New ") * par_height / 3;

    Create_canvas *canvas_creator = new Create_canvas(Radius_vector(0.0, 0.0), Radius_vector(0.0, 0.0));
    Button *new_button = new Button(Radius_vector(Radius_vector(0.0, 0.0) + Radius_vector(current_button_offset, 0.0)), 
								  WHITE, 
								  button_width, 
								  button_height,
								  canvas_creator, 
								  "New");

	current_button_offset += button_width;

	// create Help button
	// ------------------------------------------------------------------
	// Roll_up_delegate * = new Roll_up_delegate(whose);
    button_width = strlen(" Help ") * par_height / 3;

    Button *help_button = new Button(par_position + Radius_vector(current_button_offset, 0.0), 
								  WHITE, 
								  button_width, 
								  button_height,
								  NULL, 
								  "Help");

    add_visual_object(file_button);
    add_visual_object(new_button);
    add_visual_object(help_button);

    set_active(help_button);
}

Editor_control_panel::~Editor_control_panel()
{
	Visual_object **objects = get_objects()->get_array();
	size_t objects_amount = get_objects()->get_length();

	for (size_t i = 0; i < objects_amount; ++i)
	{
		delete objects[i];
	}
}

// void Editor_control_panel::draw(Screen_information *screen)
// {
// 	Visual_object::draw(screen);

// 	Visual_object **objects = get_objects()->get_array();
// 	size_t objects_amount = get_objects()->get_length();

// 	for (size_t i = 0; i < objects_amount; ++i)
// 	{
// 		objects[i]->draw(screen);
// 	}
// }

// bool Editor_control_panel::on_mouse(const double par_x, const double par_y)
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
