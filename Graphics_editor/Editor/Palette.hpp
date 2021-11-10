#ifndef PALETTE_H
#define PALETTE_H

#include "../GUI/Visual_object_base.hpp"
#include "../GUI/Button_manager.hpp"
#include "../GUI/Resource_manager.hpp"
// #include "../GUI/Button.hpp"

#include "Graphical_delegates.hpp"
#include "Color_picker.hpp"
#include "Pencil.hpp"

#include "Gradient_bar.hpp"

class Palette : public Visual_object
{
private:

public:
	Palette(const Visual_object::Config &par_base, Pencil *par_pencil)
	: Visual_object(par_base)
	{
		// create buttonы 
		// ------------------------------------------------------------------------
		Visual_object::Config panel_base = { (size_t)Vidget_type::BUTTON_MANAGER, get_position(), nullptr, TRANSPARENT, get_width(), DEFAULT_BUTTON_HEIGHT };
		Button_manager *panel = new Button_manager(panel_base);

	    size_t offset = 0;
	    size_t button_size = get_width() / DEFAULT_COLORS_AMOUNT;
	    // for (size_t i = 0; i < DEFAULT_COLORS_AMOUNT; ++i)
	    // {
	    // 	Change_color *change_color = new Change_color(par_pencil, COLOR_SEQUENCE[i]);
	    // 	Full_texture *texture = new Full_texture(COLORED_BUTTONS[i]);
	    // 	offset = texture->get_width();
	    // 	panel->add_button(change_color, " ", texture, button_size, button_size);
	    // }

	    
		// Full_texture *texture = new Full_texture(GRADIENT_BAR_TEXTURE, MAX_COLOR_VALUE, 20);
		// size_t size = par_width < (par_height - DEFAULT_BUTTON_HEIGHT) ? par_width : (par_height - DEFAULT_BUTTON_HEIGHT);

		Color_picker *picker = create_color_picker(get_position() + Vector_ll(10, (offset + 30)), MAX_COLOR_VALUE, MAX_COLOR_VALUE, par_pencil);// new Color_picker((size_t)Vidget_type::COLOR_PICKER, par_position + Vector_ll(10, (offset + 30)), TRANSPARENT, MAX_COLOR_VALUE, MAX_COLOR_VALUE, par_pencil);
	    Gradient_bar *gradient = create_gradient_bar(get_position() + Vector_ll(10, offset + 10), MAX_COLOR_VALUE, 20, par_pencil, picker);// new Gradient_bar((size_t)Vidget_type::GRADIENT_BAR, par_position + Vector_ll(10, offset + 10), texture, MAX_COLOR_VALUE, 20, par_pencil, picker);

	   	add_visual_object(panel);
	   	// add_visual_object(gradient);
	   	// add_visual_object(picker);
	}

	Color_picker *create_color_picker(const Vector_ll &position, const size_t width, const size_t height, Pencil *par_pencil)
	{
		Visual_object::Config picker_base = { (size_t)Vidget_type::COLOR_PICKER, position, nullptr, TRANSPARENT, width, height };

		Color_picker *picker = new Color_picker(picker_base, par_pencil);
		add_visual_object(picker);

		return picker;
	}

	Gradient_bar *create_gradient_bar(const Vector_ll &position, const size_t width, const size_t height, Pencil *par_pencil, Color_picker *picker)
	{
		Full_texture *texture = Resources::get_instance()->create_texture(GRADIENT_BAR_TEXTURE, width, height);
		Visual_object::Config gradient_base = { (size_t)Vidget_type::GRADIENT_BAR, position, texture, TRANSPARENT, width, height };

	    Gradient_bar *gradient = new Gradient_bar(gradient_base, par_pencil, picker);
		add_visual_object(gradient);

		return gradient;
	}

	void draw(Screen_information *screen) override
	{
		Visual_object **objects_array = get_objects()->get_array();
		size_t objects_amount = get_objects()->get_length();

		for (size_t i = 0; i < objects_amount; ++i)
		{
			if (objects_array[i]->get_visible())
			{
				objects_array[i]->draw(screen);
			}
		}
	}
};

#endif // PALETTE_H
