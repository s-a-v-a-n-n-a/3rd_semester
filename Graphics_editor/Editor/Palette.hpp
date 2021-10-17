#ifndef PALETTE
#define PALETTE

#include "../GUI/Visual_object_base.hpp"
#include "../GUI/Button.hpp"

#include "Editor_delegates.hpp"
#include "Pencil.hpp"

class Palette : public Visual_object
{
private:

public:
	Palette(Pencil *par_pencil, const Radius_vector &par_position, const Color &par_color, const size_t par_width, const size_t par_height)
	: Visual_object(par_position, par_color, par_width, par_height)
	{
		// create BLACK button 
		// ATTENTION
		// MAGIC
		// ------------------------------------------------------------------------
		size_t button_width = par_width / 5;
	    size_t button_height = par_height / 5;

	    Change_color *black_color = new Change_color(par_pencil, BLACK);
	    Button *black_button = new Button(par_position + Radius_vector(button_width, button_height), 
									  BLACK, 
									  button_width, 
									  button_height,
									  black_color, 
									  "-");

	    // create RED button 
		// ------------------------------------------------------------------------
		Change_color *red_color = new Change_color(par_pencil, RED);
	    Button *red_button = new Button(par_position + Radius_vector(button_width * 3, button_height), 
									  RED, 
									  button_width, 
									  button_height,
									  red_color, 
									  "-");

	    // create GREEN button 
		// ------------------------------------------------------------------------
		Change_color *green_color = new Change_color(par_pencil, GREEN);
	    Button *green_button = new Button(par_position + Radius_vector(button_width, button_height * 3), 
									  GREEN, 
									  button_width, 
									  button_height,
	    							  green_color, 
									  "-"); 
									  

	    // create BLUE button 
		// ------------------------------------------------------------------------
		Change_color *blue_color = new Change_color(par_pencil, BLUE);
	    Button *blue_button = new Button(par_position + Radius_vector(button_width * 3, button_height * 3), 
									  BLUE, 
									  button_width, 
									  button_height,
									  blue_color, 
									  "-");

	    add_visual_object(black_button);
	    add_visual_object(red_button);
	    add_visual_object(green_button);
	    add_visual_object(blue_button);

	    set_active(black_button);
	}
};

#endif // PALETTE
