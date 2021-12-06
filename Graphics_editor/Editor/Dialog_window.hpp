#ifndef DIALOG_WINDOW_H
#define DIALOG_WINDOW_H

#include "Window.hpp"
#include "Color_selection.hpp"
#include "../GUI/Slider.hpp"

class Dialog : public Window
{
public:
	Dialog(const Visual_object::Config &par_base);
	
	void create_slider(const Vector_ll &position, const size_t width, const size_t height, Button_delegate *par_delegate);
	void create_color_picker(const Vector_ll &position, const size_t width, const size_t height, const Color &color = DEFAULT_COLOR);
	// void create_spline();
};

Dialog *create_dialog_window(const size_t width, const size_t height);
void destroy_dialog_window(Dialog *dialog_window);

#endif // DIALOG_WINDOW_H
