#ifndef TOOLS_VIDGET_H
#define TOOLS_VIDGET_H

#include "../GUI/Visual_object_base.hpp"

#include "Window_control_panel.hpp"
#include "Palette.hpp"
#include "Thickness_palette.hpp"
#include "Pencil.hpp"

class Tools_vidget : public Visual_object
{
private:

public:
	Tools_vidget(const Visual_object::Config &par_base, Pencil *par_pencil);
	// Tools_vidget(const size_t par_type, const Vector_ll &par_position, const Color &par_color, const size_t par_width, const size_t par_height, Pencil *par_pencil);
	// Tools_vidget(const size_t par_type, const Vector_ll &par_position, Texture *par_texture, const size_t par_width, const size_t par_height, Pencil *par_pencil);
	~Tools_vidget() = default;
};

#endif // TOOLS_VIDGET_H
