#ifndef TOOLS_VIDGET_H
#define TOOLS_VIDGET_H

#include "../GUI/Visual_object_base.hpp"

#include "Window_control_panel.hpp"
#include "Palette.hpp"
#include "Pencil.hpp"

class Tools_vidget : public Visual_object
{
private:

public:
	Tools_vidget(const size_t par_type, const Radius_vector &par_position, const Color &par_color, const size_t par_width, const size_t par_height, Pencil *par_pencil);
	~Tools_vidget() = default;
};

#endif // TOOLS_VIDGET_H
