#include "Canvas_manager_manager.hpp"

Canvas_manager_manager::Canvas_manager_manager(const size_t par_type, const Vector_ll &par_position, const Color &par_color, const size_t par_width, const size_t par_height, Pencil *par_pencil)
: Visual_object(par_type, par_position, par_color, par_width, par_height), pencil(par_pencil)
{
	// size_t button_height = 80;

	// создаёт Window_control_panel
    // ------------------------------------------------------------------------------
	Window_control_panel *control = new Window_control_panel((size_t)Vidget_type::WINDOW_CONTROL_PANEL, 
															par_position, 
															WHITE, 
															par_width, 
															DEFAULT_BUTTON_HEIGHT, 
															this);


	// создаёт начальный объект
	// ------------------------------------------------------------------------------
	Canvas_manager *canvas = new Canvas_manager((size_t)Vidget_type::CANVAS_MANAGER, 
												par_position + Vector_ll(0.0, DEFAULT_BUTTON_HEIGHT), 
												WHITE, 
												par_width, 
												par_height - DEFAULT_BUTTON_HEIGHT, 
												pencil,
												0);
	add_visual_object(control);
	add_visual_object(canvas);
}

Canvas_manager_manager::Canvas_manager_manager(const size_t par_type, const Vector_ll &par_position, Texture *par_texture, Pencil *par_pencil)
: Visual_object(par_type, par_position, par_texture), pencil(par_pencil)
{
	Window_control_panel *control = new Window_control_panel((size_t)Vidget_type::WINDOW_CONTROL_PANEL, 
															par_position, 
															WHITE, 
															get_width(), 
															DEFAULT_BUTTON_HEIGHT, 
															this);

	Canvas_manager *canvas = new Canvas_manager((size_t)Vidget_type::CANVAS_MANAGER, 
												par_position + Vector_ll(0.0, DEFAULT_BUTTON_HEIGHT), 
												GREY, 
												get_width(), 
												get_height() - DEFAULT_BUTTON_HEIGHT, 
												pencil,
												0);
	
	add_visual_object(control);
	add_visual_object(canvas);
}

void Canvas_manager_manager::add_canvas()
{
	Canvas_manager *canvas = new Canvas_manager((size_t)Vidget_type::CANVAS_MANAGER, 
												get_position() + Vector_ll(0.0, DEFAULT_BUTTON_HEIGHT), 
												WHITE, 
												get_width(), 
												get_height() - DEFAULT_BUTTON_HEIGHT, 
												pencil,
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

			offset_coefficient++;

			slow_delete_visual_object(i);
			i--;
			objects_amount--;
			continue;
		}
		else if (objects_array[i]->get_type() == (size_t)Vidget_type::CANVAS_MANAGER && offset_coefficient)
		{
			((Canvas_manager*)objects_array[i])->set_offset(((Canvas_manager*)objects_array[i])->get_offset() - Vector_ll(DEFAULT_TAB_WIDTH, 0.0) * offset_coefficient);
		}

		objects_array[i]->tick(screen, delta_time);
	}
}

void Canvas_manager_manager::draw(Screen_information *screen)
{
	assert(screen);

	// screen->draw_rectangle(get_position(), get_color(), get_width(), get_height());
	Visual_object::draw(screen);

	if (get_reactive())
	{
		Visual_object **objects_array = get_objects()->get_array();
		size_t objects_amount = get_objects()->get_length();

		for (size_t i = 0; i < objects_amount - 1; ++i)
		{
			if (objects_array[i]->get_visible())
			{
				objects_array[i]->set_active_state(false);
				objects_array[i]->draw(screen);
			}
		}

		objects_array[objects_amount - 1]->set_active_state(true);
		objects_array[objects_amount - 1]->draw(screen);
	}
}

