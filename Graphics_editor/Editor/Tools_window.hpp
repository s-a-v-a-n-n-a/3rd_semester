#ifndef TOOLS_WINDOW_H
#define TOOLS_WINDOW_H

#include "../GUI/Visual_object_base.hpp"
#include "../GUI/Button.hpp"
#include "../Tools/Toolbar.hpp"

#include "Graphical_delegates.hpp"

class Color_button : public Button 
{
public:
	Color_button(const Visual_object::Config &par_base, Button_delegate *par_click, const char *par_text)
	: Button(par_base, par_click, par_text) {}

	void tick(Screen_information *screen, const double delta_time) override
	{
		set_color(Toolbar::get_instance()->get_color());
		
		Button::tick(screen, delta_time);
	}
};

class Tools_window : public Window
{
private:

public:
	Tools_window(const Visual_object::Config &par_base)
	: Window(par_base)
	{
		size_t tools_amount = Toolbar::get_instance()->get_tools_amount();
		std::vector<Tool*> tools = Toolbar::get_instance()->get_tools();

		size_t y_offset = DEFAULT_BUTTON_HEIGHT;
		for (size_t i = 0; i < tools_amount; i += 2)
		{
			create_pick_button(get_position() + Vector_ll(0, y_offset), get_width()/2, get_width()/2, TOOLS_BUTTONS[i], ACTIVE_TOOLS_BUTTONS[i], tools[i]);
			if (i + 1 < tools_amount)
				create_pick_button(get_position() + Vector_ll(get_width()/2, y_offset), get_width()/2, get_width()/2, TOOLS_BUTTONS[i + 1], ACTIVE_TOOLS_BUTTONS[i + 1], tools[i + 1]);
		
			y_offset += get_width()/2;
		}	

		Animating_texture *color_texture = Resources::get_instance()->create_texture(COLOR_BUTTON, get_width()/2, get_width()/2, ACTIVE_COLOR_BUTTON, NULL);

		Color_button *color_button = new Color_button({(size_t)Vidget_type::BUTTON, get_position() + Vector_ll(0, y_offset), color_texture, Toolbar::get_instance()->get_color(), get_width()/2, get_width()/2}, NULL, "");
		Animating_color_picker_creator *color_creator = new Animating_color_picker_creator({300, 300}, color_button);
		color_button->set_delegate(color_creator);
		add_visual_object(color_button);
	}

	Button *create_pick_button(const Vector_ll &position, const size_t width, const size_t height, const char *texture_name, const char *move_texture_name, Tool *tool)
	{
		// Full_texture *texture = Resources::get_instance()->create_texture(texture_name, width, height);
		Animating_texture *texture = Resources::get_instance()->create_texture(texture_name, width, height, move_texture_name, NULL);

		Button *pick_button = new Button({(size_t)Vidget_type::BUTTON, position, texture, TRANSPARENT, width, height}, NULL, "");
		Animating_pick_tool *picker = new Animating_pick_tool(tool, pick_button); // &tools,
		pick_button->set_delegate(picker); 

		add_visual_object(pick_button);

		return pick_button;
	}
};

#endif // TOOLS_WINDOW_H
