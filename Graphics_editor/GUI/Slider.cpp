#include "Slider.hpp"

Slider::Slider(const Visual_object::Config &par_base, Button_delegate *par_delegate, const long long par_high_limit, const long long par_low_limit, const bool par_horizontal)
: Visual_object(par_base), delegate(par_delegate), high_limit(par_high_limit), low_limit(par_low_limit), horizontal(par_horizontal)
{
	size_t width = get_width();
	size_t height = get_height();

	size_t line_length = 0;
	if (horizontal)
		line_length = width - 2 * height;
	else
		line_length = height - 2 * width;

	// ползунок
	if (horizontal)
	{
		slider = create_sliding_button(get_position() + Vector_ll(height + 10, 0), 20, height, get_position() + Vector_ll(height + 10, 0), get_position() + Vector_ll(line_length + height - 20, 0), this);
		current_relation = slider->get_x_relation();
	}
	else
	{
		slider = create_sliding_button(get_position() + Vector_ll(0, width), width, 20, get_position() + Vector_ll(0, width + 10), get_position() + Vector_ll(0, line_length + width - 10), this);
		current_relation = slider->get_y_relation();
	}

	// кнопка влево
	// magic !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	Button *left = NULL;
	if (horizontal)
		left = create_control_button(get_position(), height, height, SLIDER_LEFT, -10, true, slider);
	else
		left = create_control_button(get_position(), width, width, SLIDER_DOWN, -10, false, slider);
	
	// кнопка вправо
	// magic !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	Button *right = NULL;
	if (horizontal)
		right = create_control_button(get_position() + Vector_ll(width - height, 0), height, height, SLIDER_RIGHT, 10, true, slider);
	else
		right = create_control_button(get_position() + Vector_ll(height - width, 0), width, width, SLIDER_UP, 10, false, slider);
	
	// полосочка, по которой ездят
	// а кто он и что он будет уметь? Светиться? Фон рисовать?
	Magnet_control *line_delegate = new Magnet_control(slider);
	Full_texture *texture = Resources::get_instance()->create_texture(SLIDER_LINE_HOR, line_length, height);
	Button *line = new Button({(size_t)Vidget_type::BUTTON, get_position() + Vector_ll(height, 0), texture, TRANSPARENT, line_length, height}, line_delegate, "");
	add_visual_object(line);

	move_to_end(slider, 0);
}

Magnetic *Slider::create_sliding_button(const Vector_ll &position, const size_t width, const size_t height, const Vector_ll &left_bound, const Vector_ll &right_bound, Visual_object *parent)
{
	Full_texture *texture = Resources::get_instance()->create_texture(SLIDER, width, height);
	Magnetic *magnet = new Magnetic({(size_t)Vidget_type::BUTTON, position, texture, TRANSPARENT, width, height}, parent, left_bound, right_bound, height); // add delegate
	
	add_visual_object(magnet);

	return magnet;
}

Button *Slider::create_control_button(const Vector_ll &position, const size_t width, const size_t height, const char *texture_name, const long long delta, const bool x_coord, Visual_object *to_control)
{
	Full_texture *texture = Resources::get_instance()->create_texture(texture_name, width, height);

	Change_fixedly *change = new Change_fixedly(to_control, delta, x_coord);
	Button *control = new Button({(size_t)Vidget_type::BUTTON, position, texture, TRANSPARENT, width, height}, change, "");

	add_visual_object(control);

	return control;
}

void Slider::count_intermediate_state() const
{
	size_t new_point = (size_t)(current_relation * (double)((double)high_limit - (double)low_limit) + (double)low_limit);

	if (horizontal)
	{
		printf("calling delegate\n");
		delegate->on_mouse_click(new_point, 0);
	}
	else
		delegate->on_mouse_click(0, new_point);
}

void Slider::check_slider_state()
{
	if (horizontal)
	{
		double x_relation = slider->get_x_relation();
		if (x_relation != current_relation)
		{
			current_relation = x_relation;
		}
	}
	else
	{
		double y_relation = slider->get_y_relation();
		if (y_relation != current_relation)
		{
			current_relation = y_relation;
		}
	}
	count_intermediate_state();
}

bool Slider::on_mouse_click(const bool state, const size_t par_x, const size_t par_y)
{
	bool result = Visual_object::on_mouse_click(state, par_x, par_y);

	if (result)
	{
		check_slider_state();
	}
	// else
	// {
	// 	result = slider->on_mouse_click(state, par_x, par_y);
	// 	if (result)
	// 		check_slider_state();
	// }

	return result;
}

bool Slider::on_mouse_move(const Vector_ll from, const Vector_ll to)
{
	bool result = Visual_object::on_mouse_move(from, to);

	if (result)
	{
		check_slider_state();
	}
	// else
	// {
	// 	result = slider->on_mouse_move(from, to);
	// 	if (result)
	// 		check_slider_state();
	// }

	return result;
}

