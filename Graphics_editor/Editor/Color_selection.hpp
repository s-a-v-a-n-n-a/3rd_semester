#ifndef TOOLS_VIDGET_H
#define TOOLS_VIDGET_H

#include "../GUI/Visual_object_base.hpp"

#include "Window_control_panel.hpp"
#include "Palette.hpp"
#include "Thickness_palette.hpp"
#include "Pencil.hpp"

#include "Window.hpp"

class Color_selection_window : public Window
{
public:
	Color_selection_window() = delete;
	Color_selection_window(const Visual_object::Config &par_base, Pencil *par_pencil);
	~Color_selection_window() = default;
};

#endif // TOOLS_VIDGET_H
