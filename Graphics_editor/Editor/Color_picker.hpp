#ifndef COLOR_TABLE_H
#define COLOR_TABLE_H

const size_t DEFAULT_POINTER_RADIUS = 5;

class Color_picker : public Visual_object
{
private:
	Pencil *pencil;

	Button *picker;

	Color color_array[MAX_COLOR_VALUE * MAX_COLOR_VALUE];
	Color main_color;

	Vector_ll current_position;

public:
	Color_picker(const size_t par_type, const Vector_ll &par_position, const Color &par_color, const size_t par_width, const size_t par_height, Pencil *par_pencil)
	: Visual_object(par_type, par_position, par_color, par_width, par_height), pencil(par_pencil), main_color(RED), current_position(0, par_height)
	{
		set_main_color(RED);

		Full_texture *circle = new Full_texture(PICKING_CIRCLE_TEXTURE, 18, 18);
		
		size_t circle_width = circle->get_width();
		size_t circle_height = circle->get_height();

		picker = new Button((size_t)Vidget_type::BUTTON, par_position + Vector_ll(circle_width, circle_height), circle, circle_width, circle_height, nullptr, "");
		Drag_and_drop_delegate *dnd = new Drag_and_drop_delegate(picker);
		picker->set_delegate(dnd);

		add_visual_object(picker);
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
				color_array[i * MAX_COLOR_VALUE + j] = { 
										  (unsigned char)(((MAX_COLOR_VALUE - red_component) * (MAX_COLOR_VALUE - j) / MAX_COLOR_VALUE + red_component) * (MAX_COLOR_VALUE - i) / MAX_COLOR_VALUE),
										  (unsigned char)(((MAX_COLOR_VALUE - green_component) * (MAX_COLOR_VALUE - j) / MAX_COLOR_VALUE + green_component) * (MAX_COLOR_VALUE - i) / MAX_COLOR_VALUE), 
										  (unsigned char)(((MAX_COLOR_VALUE - blue_component) * (MAX_COLOR_VALUE - j) / MAX_COLOR_VALUE + blue_component) * (MAX_COLOR_VALUE - i) / MAX_COLOR_VALUE),
										  MAX_COLOR_VALUE};
			}
		}
	}

	void set_pencil_color()
	{
		pencil->set_color(color_array[current_position.get_y() * MAX_COLOR_VALUE + current_position.get_x()]);
	}

	bool on_mouse_click(const bool state, const size_t par_x, const size_t par_y) override
	{
		if (point_inside(par_x, par_y))
		{
			if (state)
			{
				Vector_ll last_position = current_position;
				current_position = Vector_ll(par_x, par_y) - get_position();
				
				picker->set_position(picker->get_position() + current_position - last_position);
				picker->on_mouse_click(state, par_x, par_y);
				
				set_pencil_color();

				return true;
			}
			else
				picker->on_mouse_click(state, par_x, par_y);
		}

		return false;
	}

	bool on_mouse_move(const Vector_ll from, const Vector_ll to) override
	{
		// printf("move picker\n");
		// picker->set_position(picker->get_position() + to - last);

		return picker->on_mouse_move(from, to);
	}

	void draw(Screen_information *screen) override
	{
		Vector_ll position(get_position());

		screen->draw_image(color_array, get_position(), get_width(), get_height());
		
		Full_texture *circle = new Full_texture(PICKING_CIRCLE_TEXTURE, 18, 18);
		screen->draw_texture(position + current_position - Vector_ll(circle->get_width()/2, circle->get_height()/2), PICKING_CIRCLE_TEXTURE);
		delete circle;
	}
};

#endif // COLOR_TABLE_H
