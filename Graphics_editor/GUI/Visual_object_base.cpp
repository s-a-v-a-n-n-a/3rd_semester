#include "Visual_object_base.hpp"

Visual_object::Visual_object(const Radius_vector &par_position, const Color &par_color, const size_t par_width, const size_t par_height)
: objects()
{
	position = par_position;
	color = par_color;

	width = par_width;
	height = par_height;

	current_active = NULL;
	active = false;
	visible = true;
	reactive = true;
	alive = true;
}

void Visual_object::very_slow_delete_visual_object(Visual_object *par_object)
{
	Visual_object **objects_array = objects.get_array();
	size_t objects_amount = objects.get_length();

	for (size_t i = 0; i < objects_amount; ++i)
	{
		if(objects_array[i] == par_object)
		{
			objects.slow_delete(i);
			break;
		}
	}
}

void Visual_object::draw(Screen_information *screen)
{
	assert(screen);

	screen->draw_rectangle(position, get_color(), width, height);

	Visual_object **objects_array = objects.get_array();
	size_t objects_amount = objects.get_length();

	for (size_t i = 0; i < objects_amount; ++i)
	{
		// printf("%d\n", objects_array[i]->get_visible());

		if (objects_array[i]->get_visible())
			objects_array[i]->draw(screen);
	}
}

bool Visual_object::point_inside(const size_t par_x, const size_t par_y)
{
	if (par_x >= position.get_x() && par_x <= position.get_x() + width &&
		par_y >= position.get_y() && par_y <= position.get_y() + height)
		return true;
	
	return false;
}

bool Visual_object::on_mouse(const bool clicked, const size_t par_x, const size_t par_y) // const Mouse_event par_event, 
{
	if (point_inside(par_x, par_y))
	{
		// set_active_state(true);

		// return true;
		size_t objects_amount = objects.get_length();
		
		for (long long i = (long long)objects_amount - 1; i >= 0; --i)
		{
			if ((get_objects()->get_array()[i])->get_reactive() && (get_objects()->get_array()[i])->on_mouse(clicked, par_x, par_y)) // ??????
			{
				set_active(get_objects()->get_array()[i]);
				
				// slow_delete
				// slow_delete_visual_object(i);
				// // push
				// add_visual_object(get_active());
				
				return true;
			}
		}
	}

	return false;
}

void Visual_object::tick(Screen_information *screen, const double delta_time)
{
	assert(screen);

	Visual_object **objects_array = objects.get_array();
	size_t objects_amount = objects.get_length();

	for (size_t i = 0; i < objects_amount; ++i)
	{
		// printf("%d\n", objects_array[i]->get_visible());
		if (!objects_array[i]->get_alive())
		{
			slow_delete_visual_object(i);
			i--;
			objects_amount--;
			continue;
		}

		objects_array[i]->tick(screen, delta_time);
	}
}
