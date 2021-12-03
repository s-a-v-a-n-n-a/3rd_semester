#ifndef DIALOG_WINDOW_H
#define DIALOG_WINDOW_H

#include "Window.hpp"

#include "Color_selection.hpp"
#include "../GUI/Slider.hpp"

Dialog *create_dialog_window(const size_t width, const size_t height)
{
	Visual_object *editor = Application::get_app()->get_default();

	Vector_ll main_position = editor->get_position();
	Vector_ll main_window_size = Vector_ll(editor->get_width(), editor->get_height());
	Vector_ll dialog_size = Vector_ll(width, height);

	if (dialog_size.get_x() < main_window_size.get_x())
		dialog_size.get_x() = main_window_size.get_x();
	if (dialog_size.get_y() < main_window_size.get_y())
		dialog_size.get_y() = main_window_size.get_y();
	
	size_t x_pos = main_position.get_x() + rand() % (main_window_size.get_x() - dialog_size.get_x());  
	size_t y_pos = main_position.get_y() + rand() % (main_window_size.get_y() - dialog_size.get_y());  

	Vector_ll position = Vector_ll(x_pos, y_pos);

	Dialog *dialog_window = new Dialog(position, dialog_size.get_x(), dialog_size.get_y(), NULL);
	editor->add_visual_object(dialog_window);

	return dialog_window;
}

void destroy_dialog_window(Dialog *dialog_window)
{
	Visual_object *editor = Application::get_app()->get_default();

	editor->very_slow_delete_visual_object(dialog_window);
}

class Dialog : public Window
{
public:
	Dialog(const Visual_object::Config &par_base)
	: Window(par_base)
	{
		;
	}

	void create_slider(const Vector_ll &position, const size_t width, const size_t height, Button_delegate *par_delegate)
	{
		Slider *slider = new Slider({(size_t)Vidget_type::SLIDER, position, NULL, TRANSPARENT, width, height}, par_delegate, 0, 1, true);

		add_visual_object(slider);
	}

	void create_color_picker(const Vector_ll &position, const size_t width, const size_t height, const Color &color = DEFAULT_COLOR)
	{
		Visual_object::Config picker_base = { (size_t)Vidget_type::COLOR_SELECTION, position, NULL, TRANSPARENT, width, height};

		Color_selection_window *picker = new Color_selection_window(picker_base, color);
		add_visual_object(picker);
	}
	// void create_spline();
};

#endif // DIALOG_WINDOW_H
