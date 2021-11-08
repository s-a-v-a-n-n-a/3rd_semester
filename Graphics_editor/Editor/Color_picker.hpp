#ifndef COLOR_TABLE_H
#define COLOR_TABLE_H

#include "../GUI/Visual_object_base.hpp"
#include "../GUI/Button.hpp"

#include "Graphical_delegates.hpp"
#include "Pencil.hpp"

extern const size_t DEFAULT_POINTER_RADIUS;

class Color_picker : public Visual_object
{
private:
	Pencil *pencil;

	Button *picker;

	Color color_array[MAX_COLOR_VALUE * MAX_COLOR_VALUE];
	Color main_color;

	Vector_ll current_position;

public:
	Color_picker(const size_t par_type, const Vector_ll &par_position, const Color &par_color, const size_t par_width, const size_t par_height, Pencil *par_pencil);

	void set_main_color(const Color &par_main);

	void set_pencil_color()
	{
		pencil->set_color(color_array[current_position.get_y() * MAX_COLOR_VALUE + current_position.get_x()]);
	}

	bool on_mouse_click(const bool state, const size_t par_x, const size_t par_y) override;
	bool on_mouse_move(const Vector_ll from, const Vector_ll to) override;
	void draw(Screen_information *screen) override;
};

#endif // COLOR_TABLE_H
