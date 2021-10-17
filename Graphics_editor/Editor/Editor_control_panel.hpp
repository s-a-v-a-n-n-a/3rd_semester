#ifndef EDITOR_CONTROL_PANEL
#define EDITOR_CONTROL_PANEL

#include "../GUI/Visual_object_base.hpp"
#include "../GUI/Button.hpp"

#include "Editor_delegates.hpp"

class Editor_control_panel : public Visual_object
{
private:

public:
	Editor_control_panel(const Radius_vector &par_position, Color par_color, double par_width, double par_height);
	~Editor_control_panel();

	// void draw(Screen_information *screen);
	// bool on_mouse(const double par_x, const double par_y) override;
};

#endif // EDITOR_CONTROL_PANEL
