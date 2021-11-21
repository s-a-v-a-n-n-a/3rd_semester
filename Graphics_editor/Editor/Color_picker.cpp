#include "Color_picker.hpp"

const size_t DEFAULT_POINTER_RADIUS = 5;

Color_picker::Color_picker(const Visual_object::Config &par_base, Pencil *par_pencil)
: Visual_object(par_base), pencil(par_pencil), main_color(RED), current_position(0, get_height())
{
	set_main_color(RED);

	Full_texture *circle = Resources::get_instance()->create_texture(PICKING_CIRCLE_TEXTURE, 18, 18);// new Full_texture(WINDOW_BACKGROUND, DEFAULT_COLOR_VIDGET_WIDTH, DEFAULT_COLOR_VIDGET_HEIGHT);
	
	size_t circle_width = circle->get_width();
	size_t circle_height = circle->get_height();

	Visual_object::Config buttton_base = { (size_t)Vidget_type::BUTTON, get_position() + Vector_ll(0, get_height()) - Vector_ll(0, circle_height), circle, TRANSPARENT, circle_width, circle_height };
	picker = new Magnetic(buttton_base, this, get_position(), get_position() + Vector_ll(get_width(), get_height()) - Vector_ll(circle_width, circle_height));
	
	// Drag_and_drop_delegate *dnd = new Drag_and_drop_delegate(picker);
	// Magnetic *magnit_delegate = new Magnetic(picker, get_position(), get_position() + Vector_ll(get_width(), get_height()));
	// picker->set_delegate(magnit_delegate);

	add_visual_object(picker);
}

void Color_picker::set_main_color(const Color &par_main)
{
	main_color = par_main;

	int red_component   = main_color.get_r();
	int green_component = main_color.get_g();
	int blue_component  = main_color.get_b();

	for (int i = 0; i < MAX_COLOR_VALUE; ++i)
	{
		for (int j = 0; j < MAX_COLOR_VALUE; ++j)
		{
			color_array[i * MAX_COLOR_VALUE + j] = { 
									  (unsigned char)(((MAX_COLOR_VALUE - red_component) * (MAX_COLOR_VALUE - j) / MAX_COLOR_VALUE + red_component) * (MAX_COLOR_VALUE - i) / MAX_COLOR_VALUE),
									  (unsigned char)(((MAX_COLOR_VALUE - green_component) * (MAX_COLOR_VALUE - j) / MAX_COLOR_VALUE + green_component) * (MAX_COLOR_VALUE - i) / MAX_COLOR_VALUE), 
									  (unsigned char)(((MAX_COLOR_VALUE - blue_component) * (MAX_COLOR_VALUE - j) / MAX_COLOR_VALUE + blue_component) * (MAX_COLOR_VALUE - i) / MAX_COLOR_VALUE),
									  MAX_COLOR_VALUE};
		}
	}
}

bool Color_picker::on_mouse_click(const bool state, const size_t par_x, const size_t par_y)
{
	if (point_inside(par_x, par_y))
	{
		if (state)
		{
			Vector_ll last_position = current_position;
			current_position = Vector_ll(par_x, par_y) - get_position();
			
			// picker->set_position(picker->get_position() + current_position - last_position);
			picker->on_mouse_click(state, par_x - picker->get_width()/2, par_y - picker->get_height()/2);
			
			set_pencil_color();

			return true;
		}
		else
			picker->on_mouse_click(state, par_x - picker->get_width()/2, par_y - picker->get_height()/2);

		// picker->on_mouse_click(state, par_x, par_y);
	}

	return false;
}

bool Color_picker::on_mouse_move(const Vector_ll from, const Vector_ll to)
{
	// printf("move picker\n");
	// picker->set_position(picker->get_position() + to - last);

	return picker->on_mouse_move(from, to - Vector_ll(picker->get_width()/2, picker->get_height()/2));
}

void Color_picker::draw(Screen_information *screen)
{
	Vector_ll position(get_position());

	screen->draw_image(color_array, get_position(), get_width(), get_height());
	picker->draw(screen);
	// Full_texture *circle = new Full_texture(PICKING_CIRCLE_TEXTURE, 18, 18);
	// screen->draw_texture(position + current_position - Vector_ll(circle->get_width()/2, circle->get_height()/2), PICKING_CIRCLE_TEXTURE);
	// delete circle;
}
