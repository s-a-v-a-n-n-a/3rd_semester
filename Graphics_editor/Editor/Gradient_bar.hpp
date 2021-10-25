#ifndef GRADIENT_BAR_H
#define GRADIENT_BAR_H

#include "../GUI/Visual_object_base.hpp"

#include "Color_picker.hpp"

const size_t BAR_DEFAULT_WIDTH = 30;
const size_t DEFAULT_COLORS_AMOUNT = 7;
const Color COLOR_SEQUENCE[] = { BLACK, RED, FUCHSIA, BLUE, CYAN, GREEN, YELLOW };

class Gradient_bar : public Visual_object
{
private:
	Color_picker *to_control;
	Pencil *pencil;

	Color color_array[BAR_DEFAULT_WIDTH * MAX_COLOR_VALUE];
	size_t current_position;

public:
	Gradient_bar(const size_t par_type, const Vector_ll &par_position, Texture *par_texture, Pencil *par_pencil, Color_picker *par_to_control)
	: Visual_object(par_type, par_position, par_texture), pencil(par_pencil), current_position(0), to_control(par_to_control)
	{
		;
	}

	bool on_mouse_click(const bool state, const size_t par_x, const size_t par_y) override
	{
		if (point_inside(par_x, par_y) && state)
		{
			current_position = par_x - get_position().get_x();
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
			
			to_control->set_main_color(first_color);
			to_control->set_pencil_color();
			
			return true;
		}

		return false;
	}

	void draw(Screen_information *screen) override
	{
		Visual_object::draw(screen);

		Vector_ll position(get_position());

		screen->draw_rectangle(position + Vector_ll(current_position, 0), BLACK, 5, BAR_DEFAULT_WIDTH);
	}

};

#endif // GRADIENT_BAR_H
