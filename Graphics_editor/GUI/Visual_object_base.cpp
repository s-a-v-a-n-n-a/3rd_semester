#include "Visual_object_base.hpp"

// const size_t VIDGETS_AMOUNT = 9;
Visual_object::Visual_object(const Visual_object::Config &par_base)
: objects(), base(par_base),
  current_active(nullptr), active(false), visible(true), reactive(true), alive(true)
{
	;
}

void Visual_object::add_visual_object(Visual_object *par_object) 
{ 
	objects.add_to_end(par_object); 
}

void Visual_object::slow_delete_visual_object(size_t index) 
{ 
	objects.slow_delete(index); 
}

long long Visual_object::very_slow_delete_visual_object(Visual_object *par_object)
{
	Visual_object **objects_array = objects.get_array();
	size_t objects_amount = objects.get_length();

	for (size_t i = 0; i < objects_amount; ++i)
	{
		if(objects_array[i] == par_object)
		{
			objects.slow_delete(i);
			
			return i;
		}
	}

	return -1;
}

void Visual_object::set_position(const Vector_ll &par_position)
{
	Vector_ll offset = par_position - get_position();
	base.position = par_position;

	Visual_object **objects_array = objects.get_array();
	size_t objects_amount = objects.get_length();

	for (size_t i = 0; i < objects_amount; ++i)
	{
		objects_array[i]->set_position(objects_array[i]->get_position() + offset);
	}
}

void Visual_object::draw(Screen_information *screen)
{
	assert(screen);

	if (base.texture)
	{
		screen->draw_texture(get_position(), base.texture->get_texture(), get_width(), get_height()); // пока нету такой функции

		// sf::Sprite sprite;

		// size_t texture_width = texture->getSize().x;
		// size_t texture_height = texture->getSize().y;

		// sprite.setPosition(position.get_x(), position.get_y());

		// double scale_x = (double)width / (double)texture_width;
		// double scale_y = (double)height / (double)texture_height;

		// sprite.setTexture(*texture);
		// sprite.setScale(scale_x, scale_y);

		// window.draw(sprite);
	}
	else
	{
		screen->draw_rectangle(get_position(), get_color(), get_width(), get_height());
	}

	// if (get_reactive())
	// {
		Visual_object **objects_array = objects.get_array();
		size_t objects_amount = objects.get_length();

		for (size_t i = 0; i < objects_amount; ++i)
		{
			if (objects_array[i]->get_visible())
			{
				objects_array[i]->draw(screen);
			}
		}
	// }
}

bool Visual_object::point_inside(const size_t par_x, const size_t par_y)
{
	if (par_x >= get_position().get_x() && par_x <= get_position().get_x() + get_width() &&
		par_y >= get_position().get_y() && par_y <= get_position().get_y() + get_height())
		return true;
	
	return false;
}

void Visual_object::move_to_end(Visual_object *child, size_t child_number)
{
	set_active(child);
	child->set_active_state(true);
	
	// slow_delete
	objects.extract(child_number);
	// push
	add_visual_object(child);
}

bool Visual_object::on_mouse_click(const bool state, const size_t par_x, const size_t par_y) // const Mouse_event par_event, 
{
	if (point_inside(par_x, par_y))
	{
		size_t objects_amount = objects.get_length();
		
		for (long long i = (long long)objects_amount - 1; i >= 0; --i)
		{
			if ((get_objects()->get_array()[i])->on_mouse_click(state, par_x, par_y))//(((get_objects()->get_array()[i])->get_reactive() || state == Mouse_state::MOVED) && (get_objects()->get_array()[i])->on_mouse(state, par_x, par_y)) // ??????
			{
				// set_active(get_objects()->get_array()[i]);
				// (get_objects()->get_array()[i])->set_active_state(true);
				
				// // slow_delete
				// objects.extract(i);
				// // push
				// add_visual_object(get_active());
				move_to_end(get_objects()->get_array()[i], i);
				
				return true;
			}

			set_active_state(false);
		}
	}

	return false;
}

bool Visual_object::on_mouse_move(const Vector_ll from, const Vector_ll to)
{
	bool move = false;
	bool tmp_move = false;

	if (get_reactive() && (point_inside(from.get_x(), from.get_y()) || point_inside(to.get_x(), to.get_y())))
	{
		size_t objects_amount = objects.get_length();
		
		for (long long i = (long long)objects_amount - 1; i >= 0; --i)
		{
			tmp_move = (objects.get_array()[i])->on_mouse_move(from, to);
			
			if (tmp_move)
				move = tmp_move;
			// if ((objects.get_array()[i])->on_mouse_move(from, to))//(((get_objects()->get_array()[i])->get_reactive() || state == Mouse_state::MOVED) && (get_objects()->get_array()[i])->on_mouse(state, par_x, par_y)) // ??????
			// {
			// 	// set_active(get_objects()->get_array()[i]);
			// 	// (get_objects()->get_array()[i])->set_active_state(true);
				
			// 	// slow_delete
			// 	// objects.extract(i);
			// 	// // push
			// 	// add_visual_object(get_active());
				
			// 	return true;
			// }
		}
	}

	return move;
}

bool Visual_object::on_key_pressed(const unsigned key_mask)
{
	size_t objects_amount = objects.get_length();
	
	for (long long i = (long long)objects_amount - 1; i >= 0; --i)
	{
		if ((get_objects()->get_array()[i])->get_reactive() && (get_objects()->get_array()[i])->on_key_pressed(key_mask)) // ??????
		{
			// set_active(get_objects()->get_array()[i]);
			
			// // slow_delete
			// objects.extract(i);
			// // push
			// add_visual_object(get_active());
			move_to_end(get_objects()->get_array()[i], i);
			
			return true;
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
