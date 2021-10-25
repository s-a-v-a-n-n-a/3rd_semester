#ifndef COLOR_TABLE_H
#define COLOR_TABLE_H

const size_t DEFAULT_POINTER_RADIUS = 5;

class Color_picker : public Visual_object
{
private:
	Pencil *pencil;

	Color color_array[MAX_COLOR_VALUE * MAX_COLOR_VALUE];
	Color main_color;

	Vector_ll current_position;

public:
	Color_picker(const size_t par_type, const Vector_ll &par_position, const Color &par_color, const size_t par_width, const size_t par_height, Pencil *par_pencil)
	: Visual_object(par_type, par_position, par_color, par_width, par_height), pencil(par_pencil), main_color(RED), current_position(0, 0)
	{
		set_main_color(RED);
	}

	void set_main_color(const Color &par_main)
	{
		main_color = par_main;

		int red_component   = main_color.get_r();
		int green_component = main_color.get_g();
		int blue_component  = main_color.get_b();

		for (int i = 0; i < MAX_COLOR_VALUE; ++i)
		{
			for (int j = 0; j < MAX_COLOR_VALUE; ++j)
			{
				color_array[i * MAX_COLOR_VALUE + j] = {MAX_COLOR_VALUE, 
										  (unsigned char)(((MAX_COLOR_VALUE - red_component) * (MAX_COLOR_VALUE - j) / MAX_COLOR_VALUE + red_component) * (MAX_COLOR_VALUE - i) / MAX_COLOR_VALUE),
										  (unsigned char)(((MAX_COLOR_VALUE - green_component) * (MAX_COLOR_VALUE - j) / MAX_COLOR_VALUE + green_component) * (MAX_COLOR_VALUE - i) / MAX_COLOR_VALUE), 
										  (unsigned char)(((MAX_COLOR_VALUE - blue_component) * (MAX_COLOR_VALUE - j) / MAX_COLOR_VALUE + blue_component) * (MAX_COLOR_VALUE - i) / MAX_COLOR_VALUE)};
			}
		}
	}

	void set_pencil_color()
	{
		pencil->set_color(color_array[current_position.get_y() * MAX_COLOR_VALUE + current_position.get_x()]);
	}

	bool on_mouse_click(const bool state, const size_t par_x, const size_t par_y) override
	{
		if (point_inside(par_x, par_y) && state)
		{
			current_position = Vector_ll(par_x, par_y) - get_position();
			set_pencil_color();

			return true;
		}

		return false;
	}

	void draw(Screen_information *screen) override
	{
		size_t width = MAX_COLOR_VALUE;
		size_t height = MAX_COLOR_VALUE;

		Vector_ll position(get_position());

		screen->draw_image(color_array, get_position(), width, height);
		
		screen->draw_texture(position + current_position, PICKING_CIRCLE_TEXTURE);
	}
};

#endif // COLOR_TABLE_H
