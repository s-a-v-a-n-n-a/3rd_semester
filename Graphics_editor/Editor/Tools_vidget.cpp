#include "Tools_vidget.hpp"

Tools_vidget::Tools_vidget(const size_t par_type, const Vector_ll &par_position, const Color &par_color, const size_t par_width, const size_t par_height, Pencil *par_pencil)
: Visual_object(par_type, par_position, par_color, par_width, par_height)
{
	// Full_texture
	Window_control_panel *control = new Window_control_panel((size_t)Vidget_type::WINDOW_CONTROL_PANEL, 
																par_position, 
																WHITE, 
																par_width, 
																DEFAULT_BUTTON_HEIGHT, 
																this);

	Palette *palette = new Palette((size_t)Vidget_type::PALETTE, par_position + Vector_ll(0, DEFAULT_BUTTON_HEIGHT), WHITE, 300, 300, par_pencil);
	Thickness_palette *thick_palette = new Thickness_palette((size_t)Vidget_type::PALETTE, par_position + Vector_ll(10, DEFAULT_BUTTON_HEIGHT + 350), TRANSPARENT, 300, 40, par_pencil);

	add_visual_object(control);
	add_visual_object(palette);
	add_visual_object(thick_palette);
}

Tools_vidget::Tools_vidget(const size_t par_type, const Vector_ll &par_position, Texture *par_texture, const size_t par_width, const size_t par_height, Pencil *par_pencil)
: Visual_object(par_type, par_position, par_texture, par_width, par_height)
{
	Full_texture *header = new Full_texture(WINDOW_HEADER);
	Window_control_panel *control = new Window_control_panel((size_t)Vidget_type::WINDOW_CONTROL_PANEL, 
																par_position, 
																header, 
																par_width, 
																DEFAULT_BUTTON_HEIGHT, 
																this);

	Palette *palette = new Palette((size_t)Vidget_type::PALETTE, par_position + Vector_ll(0, DEFAULT_BUTTON_HEIGHT), WHITE, par_width, par_height - DEFAULT_BUTTON_HEIGHT, par_pencil);
	// Thickness_palette *thick_palette = new Thickness_palette((size_t)Vidget_type::PALETTE, par_position + Vector_ll(10, DEFAULT_BUTTON_HEIGHT + 350), TRANSPARENT, 300, 40, par_pencil);

	add_visual_object(control);
	add_visual_object(palette);
	// add_visual_object(thick_palette);
}

