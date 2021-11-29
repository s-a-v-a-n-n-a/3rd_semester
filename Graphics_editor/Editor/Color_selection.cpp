#include "Color_selection.hpp"

Color_selection_window::Color_selection_window(const Visual_object::Config &par_base)
: Window(par_base)
{
	Visual_object::Config palette_base = {(size_t)Vidget_type::PALETTE, get_position() + Vector_ll(0, DEFAULT_BUTTON_HEIGHT), nullptr, WHITE, get_width(), get_height() - DEFAULT_BUTTON_HEIGHT};
	Palette *palette = new Palette(palette_base);
	
	add_visual_object(palette);
}

