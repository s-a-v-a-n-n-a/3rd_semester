#include "Editor_control_panel.hpp"

Editor_control_panel::Editor_control_panel(const size_t par_type, const Vector_ll &par_position, Color par_color, double par_width, double par_height)
: Visual_object(par_type, par_position, par_color, par_width, par_height)
{
    size_t button_height = par_height;

    size_t current_button_offset = 0;

    current_end_position = par_position;

	// create File button
	// ------------------------------------------------------------------
 //    Roll_up_delegate *canvas_roll_up = new Roll_up_delegate(canvas);
 //    button_width = strlen(" Canvas ") * par_height / 3;

 //    Button *canvas_button = new Button(Vidget_type::BUTTON,
 //    								Vector_ll(Vector_ll(0.0, 0.0)), 
	// 							  	WHITE, 
	// 							  	button_width, 
	// 							  	button_height,
	// 							  	canvas_roll_up, 
	// 							  	"Canvas");

 //    current_button_offset += button_width;



 //    // create new button
 //    // ------------------------------------------------------------------
 //    button_width = strlen(" New ") * par_height / 3;

 //    Create_canvas *canvas_creator = new Create_canvas(parent->get_pencil(), canvas, par_position + Vector_ll(800.0, 800.0), Vector_ll(500.0, 500.0));
 //    Button *new_button = new Button(Vidget_type::BUTTON,
 //    								Vector_ll(Vector_ll(0.0, 0.0) + Vector_ll(current_button_offset, 0.0)), 
	// 							  	WHITE, 
	// 							  	button_width, 
	// 							  	button_height,
	// 							  	canvas_creator, 
	// 							  	"New");

	// current_button_offset += button_width;

	// // create Help button
	// // ------------------------------------------------------------------
	// // Roll_up_delegate * = new Roll_up_delegate(whose);
 //    button_width = strlen(" Help ") * par_height / 3;

 //    Button *help_button = new Button(Vidget_type::BUTTON,
 //    								par_position + Vector_ll(current_button_offset, 0.0), 
	// 							  	WHITE, 
	// 							  	button_width, 
	// 							  	button_height,
	// 							  	NULL, 
	// 							  	"Help");

    // add_visual_object(canvas_button);
    // add_visual_object(new_button);
    // add_visual_object(help_button);

    // set_active(help_button);
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

void Editor_control_panel::add_button(Button_delegate *par_delegate, const char *par_text)
{
	// size_t button_width = 80;

	Button *new_button = new Button((size_t)Vidget_type::BUTTON,
    								current_end_position, 
    								WHITE, 
								  	strlen(par_text) * 10, 
								  	DEFAULT_BUTTON_HEIGHT,
								  	par_delegate, 
								  	par_text);

	current_end_position += Vector_ll(strlen(par_text) * 10, 0.0);

	add_visual_object(new_button);
}
