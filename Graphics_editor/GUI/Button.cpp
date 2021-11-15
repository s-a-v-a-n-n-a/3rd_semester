#include "Button.hpp"

const size_t DEFAULT_BUTTON_HEIGHT = 50;
const size_t INCREASED_BUTTON_HEIGHT = 70;

Button::Button(const Visual_object::Config &base, Button_delegate *par_click, const char *par_text)
: Visual_object(base)
{
	size_t offset = get_height() / 2;
	Text *text = new Text((size_t)Vidget_type::TEXT, 
							par_text, 
							offset, 
							get_position() + Vector_ll(get_width()/2.0, get_height()/2.0), //par_position + 
							DEFAULT_TEXT_COLOR);
	add_visual_object(text);

	click = par_click;
}

Button::~Button()
{
	Visual_object **objects = get_objects()->get_array();
	size_t objects_amount = get_objects()->get_length();

	for (size_t i = 0; i < objects_amount; ++i)
	{
		delete objects[i];
	}

	delete click;
}

void Button::draw(Screen_information *screen)
{
	if(get_texture())
	{
		screen->draw_texture(get_position(), get_texture()->get_texture(), get_width(), get_height());
	}
	else	
	{
		Visual_object::draw(screen);
	}

	size_t objects_amount = get_objects()->get_length();
	for (size_t i = 0; i < objects_amount; ++i)
	{
		(get_objects()->get_array()[i])->draw(screen);
	}
}

bool Button::on_mouse_click(const bool state, const size_t par_x, const size_t par_y) // const Mouse_event par_event, 
{
	if (point_inside(par_x, par_y))
	{
		set_active_state(true);
	    if (click)
	    	if (state)
	    	{
	    		// printf("mouse click\n");
	    		return click->on_mouse_click(par_x, par_y);
	    	}
	    	// else if (state == Mouse_state::MOVED)
	    	// 	return click->on_mouse_move(par_x, par_y);
	    	else
	    	{
	    		return click->on_mouse_release();
	    	}

	    return true;
	}
	else
	{
		return false;
	}
}

bool Button::on_mouse_move(const Vector_ll from, const Vector_ll to)
{
	if (point_inside(from.get_x(), from.get_y()))
	{
		set_active_state(true);
		// printf("mouse move\n");
	    return click->on_mouse_move(from, to);
	}
	// else if (!point_inside(to.get_x(), to.get_y()))
	// {
	// 	click->on_mouse_release();
	// 	return false;
	// }
	else
	{
		click->on_mouse_release();
		return false;
	}

	// return click->on_mouse_move(from, to);
}

Magnetic::Magnetic(const Visual_object::Config &par_base, const Vector_ll &par_left_bound, const Vector_ll &par_right_bound, const size_t par_radius)
: Visual_object(par_base), left_bound(par_left_bound), right_bound(par_right_bound), pressed(false), radius(par_radius)
{
	;
}

bool Magnetic::in_x_bounds(const size_t par_x, const size_t par_y)
{
	if (par_x >= left_bound.get_x() && par_x <= right_bound.get_x() && (left_bound.get_y() - (long long)par_y) <= (long long)radius && ((long long)par_y - right_bound.get_y()) <= (long long)radius)
		return true;

	return false;
}

bool Magnetic::in_y_bounds(const size_t par_x, const size_t par_y)
{
	if (par_y >= left_bound.get_y() && par_y <= right_bound.get_y() && (left_bound.get_x() - (long long)par_x) <= (long long)radius && ((long long)par_x - right_bound.get_x()) <= (long long)radius)
	{
		// printf("y: %lu, y1 %lld; y2 %lld\n", par_y, left_bound.get_y(), right_bound.get_y());
		return true;
	}

	return false;
}

bool Magnetic::on_mouse_click(const bool state, const size_t par_x, const size_t par_y)
{
	if (state)
	{
		pressed = true;

		bool in_x = in_x_bounds(par_x, par_y);
		bool in_y = in_y_bounds(par_x, par_y);

		if (in_x && in_y)
		{
			// printf("both\n");
			set_position(Vector_ll(par_x, par_y));

			return true;
		}
		else if (in_x)
		{
			set_position(Vector_ll(par_x, get_position().get_y()));

			return true;
		}
		else if (in_y)
		{
			set_position(Vector_ll(get_position().get_x(), par_y));

			return true;
		}

		pressed = false;
		return false;
	}
	else
	{
		// printf("released\n");
		pressed = false;
	}

	return true;
}

bool Magnetic::on_mouse_move(const Vector_ll from, const Vector_ll to)
{
	// printf("it is moving: %d\n", in);
	if (pressed)
	{
		bool in_x = in_x_bounds(to.get_x(), to.get_y());
		bool in_y = in_y_bounds(to.get_x(), to.get_y());
		
		if (in_x || in_y)
		{
			// set_position(to);
			if (in_x && in_y)
			{
				set_position(to);
			}
			else if (in_x)
			{
				set_position(Vector_ll(to.get_x(), get_position().get_y()));
			}
			else if (in_y)
			{
				set_position(Vector_ll(get_position().get_x(), to.get_y()));
			}

			return true;
		}
		else
			return false;
	}
	else// if (!in_bounds(to.get_x(), to.get_y()))
	{
		pressed = false;

		return false;
	}
	return true;
}
