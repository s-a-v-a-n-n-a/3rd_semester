#ifndef EDITOR_CONTROL_PANEL_H
#define EDITOR_CONTROL_PANEL_H

#include "../GUI/Visual_object_base.hpp"
#include "../GUI/Button.hpp"

#include "Graphical_editor_main_page.hpp"

#include "Graphical_delegates.hpp"
#include "Editor_delegates.hpp"

class Graphical_editor_main_page;

class Editor_control_panel : public Visual_object
{
private:
	// Graphical_editor_main_page *parent;
	Vector_ll current_end_position;

public:
	Editor_control_panel(const size_t par_type, const Vector_ll &par_position, Color par_color, double par_width, double par_height);
	~Editor_control_panel();

	void add_button(Button_delegate *par_delegate, const char *par_text);

	// void draw(Screen_information *screen);
	// bool on_mouse(const double par_x, const double par_y) override;
};

#endif // EDITOR_CONTROL_PANEL_H
