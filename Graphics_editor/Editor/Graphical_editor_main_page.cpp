#include "Graphical_editor_main_page.hpp"

Graphical_editor_main_page::Graphical_editor_main_page(const Radius_vector &par_position, const Color &par_color, const size_t par_width, const size_t par_height)
: Visual_object(par_position, par_color, par_width, par_height), pencil()
{
	// create Edtor_control_panel
	// ----------------------------------------------------------------------
	Editor_control_panel *panel = new Editor_control_panel(par_position, BLUE, par_width, 100);

	// create Canvas_manager
	// ----------------------------------------------------------------------
	
	// + отсылает информацию о себе
	Canvas_manager *canvas = new Canvas_manager(&pencil, par_position + Radius_vector(200.0, 200.0), WHITE, 500, 500);

	// create Palette
	// ----------------------------------------------------------------------
	Palette *palette = new Palette(&pencil, par_position + Radius_vector(0, 100), WHITE, 100, 100);

	add_visual_object(panel);
	add_visual_object(canvas);
	add_visual_object(palette);

	set_active(canvas);
}

Graphical_editor_main_page::~Graphical_editor_main_page()
{
	Visual_object **objects = get_objects()->get_array();
	size_t objects_amount = get_objects()->get_length();

	for (size_t i = 0; i < objects_amount; ++i)
	{
		delete objects[i];
	}
}

// void Graphical_editor_main_page::draw(Screen_information *screen)
// {
// 	Visual_object::draw(screen);

// 	Visual_object **objects = get_objects()->get_array();
// 	size_t objects_amount = get_objects()->get_length();

// 	for (size_t i = 0; i < objects_amount; ++i)
// 	{
// 		if(objects[i]->get_visible())
// 			objects[i]->draw(screen);
// 	}
// }

// bool Graphical_editor_main_page::on_mouse(const double par_x, const double par_y)
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
