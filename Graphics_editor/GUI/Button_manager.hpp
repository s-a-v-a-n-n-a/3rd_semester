#ifndef BUTTON_MANAGER_H
#define BUTTON_MANAGER_H

#include "../GUI/Visual_object_base.hpp"
#include "../GUI/Button_delegate.hpp"
#include "../GUI/Button.hpp"

class Button_manager : public Visual_object
{
private:
	// Graphical_editor_main_page *parent;
	Radius_vector current_end_position;

public:
	Button_manager(const size_t par_type, const Radius_vector &par_position, Color par_color, double par_width, double par_height);
	~Button_manager();

	void add_button(Button_delegate *par_delegate, const char *par_text, const Color par_color, const size_t par_width, const size_t par_height = DEFAULT_BUTTON_HEIGHT);
};

#endif // BUTTON_MANAGER_H
