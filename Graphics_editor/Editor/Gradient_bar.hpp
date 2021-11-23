#ifndef GRADIENT_BAR_H
#define GRADIENT_BAR_H

#include "../GUI/Visual_object_base.hpp"
#include "../GUI/Button.hpp"

#include "../GUI/Resource_manager.hpp"

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

	Gradient_bar(const Visual_object::Config &par_base, Pencil *par_pencil, Color_picker *par_to_control);

	Color get_color();

	void set_current_position(const Color &main_color);

	HSV get_hsv(const Color &rgb);

	// HSV_d get_hsv(const Color &rgb);

	Color get_rgb(const HSV &hsv);

	// Color get_rgb(HSV_d &hsv);

	bool on_mouse_click(const bool state, const size_t par_x, const size_t par_y) override;

	bool on_mouse_move(const Vector_ll from, const Vector_ll to) override;

	void draw(Screen_information *screen) override;
	
	void tick(Screen_information *screen, const double delta_time) override;
};

#endif // GRADIENT_BAR_H
