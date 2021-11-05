#include "Window_control_panel.hpp"

Window_control_panel::Window_control_panel(const size_t par_type, const Vector_ll &par_position, const Color &par_color, const size_t par_width, const size_t par_height, Visual_object *whose)
: Visual_object(par_type, par_position, par_color, par_width, par_height)
{
	// create roll up button 
	// ATTENTION
	// MAGIC
	// ------------------------------------------------------------------------
	Button_manager *panel = new Button_manager((size_t)Vidget_type::BUTTON_MANAGER, par_position, WHITE, par_width, DEFAULT_BUTTON_HEIGHT);

	// Full_texture *roll_up_texture = new Full_texture(ROLL_UP_TEXTURE);
	Animating_texture *close_texture = new Animating_texture(CLOSE_TEXTURE, par_height, par_height);
	close_texture->set_move_texture(CLOSE_MOVE_TEXTURE);

	Drag_and_drop_delegate *drag_and_drop = new Drag_and_drop_delegate(whose);


	panel->add_button(drag_and_drop, "", GREY, par_width - par_height, par_height); //  - roll_up_texture->get_width() 

	// Roll_up_delegate *rolling_up = new Roll_up_delegate(whose);
	Button *roll = panel->add_button(nullptr, "", close_texture, par_height, par_height);
	Animating_roll_up_delegate *rolling_up = new Animating_roll_up_delegate(whose, roll);
	roll->set_delegate(rolling_up);
	// panel->add_button(rolling_up, "", roll_up_texture);
	    
	// Close_delegate *closing = new Close_delegate(whose);
	

	add_visual_object(panel);

	// set_active(close);
}

Window_control_panel::Window_control_panel(const size_t par_type, const Vector_ll &par_position, Texture *par_texture, const size_t par_width, const size_t par_height, Visual_object *whose)
: Visual_object(par_type, par_position, par_texture, par_width, par_height)
{
	assert(par_texture);

	Button_manager *panel = new Button_manager((size_t)Vidget_type::BUTTON_MANAGER, par_position, TRANSPARENT, par_width, DEFAULT_BUTTON_HEIGHT);

	// Full_texture *roll_up_texture = new Full_texture(ROLL_UP_TEXTURE);
	Animating_texture *close_texture = new Animating_texture(CLOSE_TEXTURE, par_height, par_height);
	close_texture->set_move_texture(CLOSE_MOVE_TEXTURE);

	Drag_and_drop_delegate *drag_and_drop = new Drag_and_drop_delegate(whose);


	panel->add_button(drag_and_drop, "", TRANSPARENT, par_width - par_height, par_height); //  - roll_up_texture->get_width() 

	// Roll_up_delegate *rolling_up = new Roll_up_delegate(whose);
	Button *roll = panel->add_button(nullptr, "", close_texture, par_height, par_height);
	Animating_roll_up_delegate *rolling_up = new Animating_roll_up_delegate(whose, roll);
	roll->set_delegate(rolling_up);
	// panel->add_button(rolling_up, "", roll_up_texture);
	    
	// Close_delegate *closing = new Close_delegate(whose);
	

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

