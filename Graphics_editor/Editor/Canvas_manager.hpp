#ifndef CANVAS_MANAGER
#define CANVAS_MANAGER

#include "../GUI/Visual_object_base.hpp"

#include "Pencil.hpp"
#include "Window_control_panel.hpp"
#include "Canvas.hpp"

class Canvas_manager : public Visual_object
{
private:

public:
	// поэтому получает информацию о главном
	Canvas_manager(Pencil *par_pencil, const Radius_vector &par_position, const Color &par_color, const size_t par_width, const size_t par_height)
	: Visual_object(par_position, par_color, par_width, par_height)
	{
		size_t button_height = 80;

		// create Canvas
		// ------------------------------------------------------------------------------
		
		// посылает информацию о главном
		Canvas *canvas = new Canvas(par_pencil, par_position + Radius_vector(0.0, 100.0), WHITE, par_width, par_height - button_height);

	    // create Window_control_panel
	    // ------------------------------------------------------------------------------
		Window_control_panel *control = new Window_control_panel(this, par_position, BLUE, par_width, button_height);

		add_visual_object(canvas);
		add_visual_object(control);
	}

	~Canvas_manager()
	{
		Visual_object **objects = get_objects()->get_array();
		size_t objects_amount = get_objects()->get_length();

		for (size_t i = 0; i < objects_amount; ++i)
		{
			delete objects[i];
		}
	}

	// void draw(Screen_information *screen) override
	// {
	// 	Visual_object::draw(screen);

	// 	Visual_object **objects = get_objects()->get_array();
	// 	size_t objects_amount = get_objects()->get_length();

	// 	for (size_t i = 0; i < objects_amount; ++i)
	// 	{
	// 		objects[i]->draw(screen);
	// 	}
	// }
};

#endif // CANVAS_MANAGER
