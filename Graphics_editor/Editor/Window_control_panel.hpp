#ifndef WINDOW_CONTROL_PANEL
#define WINDOW_CONTROL_PANEL

#include "../GUI/Visual_object_base.hpp"
#include "../GUI/Button.hpp"

#include "Editor_delegates.hpp"

class Window_control_panel : public Visual_object
{
private:

public:
	Window_control_panel(Visual_object *whose, const Radius_vector &par_position, const Color &par_color, const size_t par_width, const size_t par_height);
	~Window_control_panel();

	// void draw(Screen_information *screen) override;
	// bool on_mouse(const double par_x, const double par_y) override;
};

#endif // WINDOW_CONTROL_PANEL
