#ifndef THICKNESS_PALETTE_H
#define THICKNESS_PALETTE_H

#include "../GUI/Visual_object_base.hpp"
#include "Graphical_delegates.hpp"

class Thickness_palette : public Visual_object
{
private:

public:
	Thickness_palette(const size_t par_type, const Vector_ll &par_position, const Color &par_color, const size_t par_width, const size_t par_height, Pencil *par_pencil)
	: Visual_object(par_type, par_position, par_color, par_width, par_height)
	{
		// create BLACK button 
		// ATTENTION
		// MAGIC
		// ------------------------------------------------------------------------
		Button_manager *panel = new Button_manager((size_t)Vidget_type::BUTTON_MANAGER, par_position, TRANSPARENT, par_width, DEFAULT_BUTTON_HEIGHT);

	    size_t offset = 0;
	    Change_thickness *change_thickness_1 = new Change_thickness(par_pencil, 1);
    	Full_texture *texture = new Full_texture(TEXT_TEXTURE, DEFAULT_BUTTON_HEIGHT, DEFAULT_BUTTON_HEIGHT);
    	// offset += texture->get_width();

    	panel->add_button(change_thickness_1, "1", texture, par_width/4, par_width/4);

    	Change_thickness *change_thickness_5 = new Change_thickness(par_pencil, 5);
    	panel->add_button(change_thickness_5, "5", texture, par_width/4, par_width/4);

    	Change_thickness *change_thickness_10 = new Change_thickness(par_pencil, 10);
    	panel->add_button(change_thickness_10, "10", texture, par_width/4, par_width/4);

    	Change_thickness *change_thickness_20 = new Change_thickness(par_pencil, 20);
    	panel->add_button(change_thickness_20, "20", texture, par_width/4, par_width/4);
		
		add_visual_object(panel);
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

#endif // THICKNESS_PALETTE_H
