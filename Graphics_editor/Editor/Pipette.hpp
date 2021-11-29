#ifndef PIPETTE_H
#define PIPETTE_H

#include "Toolbar.hpp"

class Pipette : public Tool 
{
public:
	Pipette()
	: Tool() 
	{ 
		Tool::set_color(DEFAULT_BACKGROUND_COLOR); 
	}
	~Pipette() = default;
	
	void apply(Canvas *to_apply, const Vector_ll &position) override
	{
		size_t width = to_apply->get_width();
		size_t height = to_apply->get_height();

		Vector_ll canvas_position = to_apply->get_position();

		size_t position_x = position.get_x() - canvas_position.get_x();
		size_t position_y = position.get_y() - canvas_position.get_y();
		
		// Tools::set_color(position_y * width + position_y);
		Toolbar::get_instance()->set_color(to_apply->get_drawing()[position_y * width + position_x]);
	}

	void set_color(const Color &par_color) override { ; }
};


#endif // PIPETTE_H
