#ifndef BRUSHES_VIDGET_H
#define BRUSHES_VIDGET_H

#include "../GUI/Visual_object_base.hpp"

#include "Window_control_panel.hpp"
#include "Thickness_palette.hpp"
#include "Pencil.hpp"

class Brush_size_manager : public Visual_object
{
private:

public:
	// Brush_size_manager(const size_t par_type, const Vector_ll &par_position, const Color &par_color, const size_t par_width, const size_t par_height, Pencil *par_pencil);
	Brush_size_manager(const size_t par_type, const Vector_ll &par_position, Texture *par_texture, Pencil *par_pencil)
	: Visual_object(par_type, par_position, par_texture)
	{
		Window_control_panel *control = new Window_control_panel((size_t)Vidget_type::WINDOW_CONTROL_PANEL, 
																par_position, 
																WHITE, 
																par_texture->get_width(), 
																DEFAULT_BUTTON_HEIGHT, 
																this);

		// Palette *palette = new Palette((size_t)Vidget_type::PALETTE, par_position + Vector_ll(0, DEFAULT_BUTTON_HEIGHT), WHITE, 300, 300, par_pencil);
		Thickness_palette *thick_palette = new Thickness_palette((size_t)Vidget_type::PALETTE, par_position + Vector_ll(0, DEFAULT_BUTTON_HEIGHT), TRANSPARENT, 300, 40, par_pencil);

		add_visual_object(control);
		// add_visual_object(palette);
		add_visual_object(thick_palette);
	}
	~Brush_size_manager() = default;
};

#endif // BRUSHES_VIDGET_H
