#include "Canvas_manager_manager.hpp"

Canvas_manager_manager::Canvas_manager_manager(const size_t par_type, const Radius_vector &par_position, const Color &par_color, const size_t par_width, const size_t par_height, Pencil *par_pencil)
: Visual_object(par_type, par_position, par_color, par_width, par_height), pencil(par_pencil)
{
	// size_t button_height = 80;

	// создаёт Window_control_panel
    // ------------------------------------------------------------------------------
	Window_control_panel *control = new Window_control_panel((size_t)Vidget_type::WINDOW_CONTROL_PANEL, 
															par_position, 
															BLUE, 
															par_width, 
															DEFAULT_BUTTON_HEIGHT, 
															this);


	// создаёт начальный объект
	// ------------------------------------------------------------------------------
	Canvas_manager *canvas = new Canvas_manager((size_t)Vidget_type::CANVAS_MANAGER, 
												par_position + Radius_vector(0.0, DEFAULT_BUTTON_HEIGHT), 
												WHITE, 
												par_width, 
												par_height - DEFAULT_BUTTON_HEIGHT, 
												pencil,
												par_position + Radius_vector(0.0, DEFAULT_BUTTON_HEIGHT),
												0);
	// add_visual_object(drop_and_down_menu);
	add_visual_object(control);
	add_visual_object(canvas);
}

void Canvas_manager_manager::add_canvas()
{
	size_t button_height = 80;

	Canvas_manager *canvas = new Canvas_manager((size_t)Vidget_type::CANVAS_MANAGER, 
												get_position() + Radius_vector(0.0, DEFAULT_BUTTON_HEIGHT), 
												WHITE, 
												get_width(), 
												get_height() - DEFAULT_BUTTON_HEIGHT, 
												pencil,
												get_position() + Radius_vector(0.0, DEFAULT_BUTTON_HEIGHT),
												get_objects()->get_length() - 1);

	add_visual_object(canvas);

	set_active(canvas);
}

void Canvas_manager_manager::tick(Screen_information *screen, const double delta_time)
{
	assert(screen);

	Visual_object **objects_array = get_objects()->get_array();
	size_t objects_amount = get_objects()->get_length();

	size_t offset_coefficient = 0;

	for (size_t i = 0; i < objects_amount; ++i)
	{
		if (!objects_array[i]->get_alive())
		{
			if (objects_array[i]->get_type() != (size_t)Vidget_type::CANVAS_MANAGER)
				continue;

			printf("Manager of canvas managers tries to delete one of canvases: %p\n", objects_array[i]);
			offset_coefficient++;

			slow_delete_visual_object(i);
			i--;
			objects_amount--;
			continue;
		}
		else if (objects_array[i]->get_type() == (size_t)Vidget_type::CANVAS_MANAGER && offset_coefficient)
		{
			((Canvas_manager*)objects_array[i])->set_offset(((Canvas_manager*)objects_array[i])->get_offset() - Radius_vector(DEFAULT_TAB_WIDTH, 0.0) * offset_coefficient);
		}

		objects_array[i]->tick(screen, delta_time);
	}
}

