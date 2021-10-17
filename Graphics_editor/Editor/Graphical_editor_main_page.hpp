#ifndef GRAPHICAL_EDITOR_MAIN_PAGE
#define GRAPHICAL_EDITOR_MAIN_PAGE

#include "../GUI/Visual_object_base.hpp"

#include "Editor_control_panel.hpp"
#include "Canvas_manager.hpp"
#include "Palette.hpp"

#include "Pencil.hpp"

class Graphical_editor_main_page : public Visual_object
{
private:
	Pencil pencil;

public:
	Graphical_editor_main_page(const Radius_vector &par_position, const Color &par_color, const size_t par_width, const size_t par_height);
	~Graphical_editor_main_page();

	Color get_pencil_color() { return pencil.get_color(); }

	void set_pencil_color(const Color &par_color) { pencil.set_color(par_color); }

	// void draw(Screen_information *screen) override;
	// bool on_mouse(const double par_x, const double par_y) override;
};

#endif // GRAPHICAL_EDITOR_MAIN_PAGE
