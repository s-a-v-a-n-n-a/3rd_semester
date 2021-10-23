#include "Tools_vidget.hpp"

Tools_vidget::Tools_vidget(const size_t par_type, const Radius_vector &par_position, const Color &par_color, const size_t par_width, const size_t par_height, Pencil *par_pencil)
: Visual_object(par_type, par_position, par_color, par_width, par_height)
{
	Window_control_panel *control = new Window_control_panel((size_t)Vidget_type::WINDOW_CONTROL_PANEL, 
																par_position, 
																BLUE, 
																par_width, 
																DEFAULT_BUTTON_HEIGHT, 
																this);

	Palette *palette = new Palette((size_t)Vidget_type::PALETTE, par_position + Radius_vector(0, DEFAULT_BUTTON_HEIGHT), WHITE, 300, 300, par_pencil);

	add_visual_object(control);
	add_visual_object(palette);
}
