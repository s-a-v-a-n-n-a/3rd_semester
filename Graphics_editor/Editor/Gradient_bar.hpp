#ifndef GRADIENT_BAR_H
#define GRADIENT_BAR_H

#include "../GUI/Visual_object_base.hpp"
#include "../GUI/Button.hpp"

#include "Color_picker.hpp"

const size_t BAR_DEFAULT_WIDTH = 30;
const size_t DEFAULT_COLORS_AMOUNT = 7;
const Color COLOR_SEQUENCE[] = { BLACK, RED, FUCHSIA, BLUE, CYAN, GREEN, YELLOW };

class Gradient_bar : public Visual_object
{
private:
	Color_picker *to_control;
	Pencil *pencil;

	Magnetic *picker;

	Color color_array[BAR_DEFAULT_WIDTH * MAX_COLOR_VALUE];
	size_t current_position;

public:
	// Gradient_bar(const size_t par_type, const Vector_ll &par_position, Texture *par_texture, const size_t par_width, const size_t par_height, Pencil *par_pencil, Color_picker *par_to_control)
	// : Visual_object(par_type, par_position, par_texture, par_width, par_height), pencil(par_pencil), current_position(0), to_control(par_to_control)
	// {
	// 	;
	// }

	Gradient_bar(const Visual_object::Config &par_base, Pencil *par_pencil, Color_picker *par_to_control)
	: Visual_object(par_base), pencil(par_pencil), current_position(0), to_control(par_to_control)
	{
		Full_texture *rect = Resources::get_instance()->create_texture(PICKING_RECT_TEXTURE, 5, get_height());// new Full_texture(WINDOW_BACKGROUND, DEFAULT_COLOR_VIDGET_WIDTH, DEFAULT_COLOR_VIDGET_HEIGHT);
		
		Visual_object::Config buttton_base = { (size_t)Vidget_type::BUTTON, get_position(), rect, TRANSPARENT, 5, get_height() };
		picker = new Magnetic(buttton_base, this, get_position(), get_position() + Vector_ll(get_width() - 5, 0), get_height());
	
		add_visual_object(picker);
	}

	Color get_color()
	{
		int gap = current_position / ((int)MAX_COLOR_VALUE / ((int)DEFAULT_COLORS_AMOUNT - 1));
		gap++;
		int res = current_position % ((int)MAX_COLOR_VALUE / ((int)DEFAULT_COLORS_AMOUNT - 1));
		
		Color first_color = COLOR_SEQUENCE[gap];
		gap %= (DEFAULT_COLORS_AMOUNT - 1);
		Color second_color = COLOR_SEQUENCE[gap + 1];

		if (first_color.get_r() != second_color.get_r())
		{
			int r_1 = (int)first_color.get_r();
			int r_2 = (int)second_color.get_r();

			first_color.set_r(r_1 + (r_2 - r_1) * res / ((int)MAX_COLOR_VALUE / ((int)DEFAULT_COLORS_AMOUNT - 1)));
		}
		else if (first_color.get_g() != second_color.get_g())
		{
			int g_1 = (int)first_color.get_g();
			int g_2 = (int)second_color.get_g();

			first_color.set_g(g_1 + (g_2 - g_1) * res / ((int)MAX_COLOR_VALUE / ((int)DEFAULT_COLORS_AMOUNT - 1)));
		}
		else if (first_color.get_b() != second_color.get_b())
		{
			int b_1 = (int)first_color.get_b();
			int b_2 = (int)second_color.get_b();

			first_color.set_b(b_1 + (b_2 - b_1) * res / ((int)MAX_COLOR_VALUE / ((int)DEFAULT_COLORS_AMOUNT - 1)));
		}
		else
			printf("This code is wrong\n");
		
		return first_color;
	}

	bool on_mouse_click(const bool state, const size_t par_x, const size_t par_y) override
	{
		if (point_inside(par_x, par_y) && state)
		{
			current_position = par_x - get_position().get_x();
			Color color = get_color();
			
			to_control->set_main_color(color);
			to_control->set_pencil_color();

			picker->on_mouse_click(state, par_x, par_y);
			
			return true;
		}
		
		picker->on_mouse_click(state, par_x, par_y);

		return false;
	}

	bool on_mouse_move(const Vector_ll from, const Vector_ll to) override
	{
		bool change = picker->on_mouse_move(from, to);

		if (change)
		{
			current_position = to.get_x() - get_position().get_x();
			Color color = get_color();

			to_control->set_main_color(color);
			to_control->set_pencil_color();

			return true;
		}

		return false;
	}

	void draw(Screen_information *screen) override
	{
		Visual_object::draw(screen);

		Vector_ll position(get_position());

		// screen->draw_rectangle(position + Vector_ll(current_position, 0), BLACK, 5, get_height());
		picker->draw(screen);
	}

};

#endif // GRADIENT_BAR_H
