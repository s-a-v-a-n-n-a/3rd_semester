#ifndef TOOLS_H 
#define TOOLS_H

#include "../simple_list/simple_list.hpp"
#include "../sfml_drawing/colors.hpp"
#include "../sfml_drawing/screen_functions.hpp"

#include "Canvas.hpp"

const Color DEFAULT_TOOL_COLOR = BLACK;
const size_t DEFAULT_TOOL_SIZE = 20;

class Tool
{
protected:
	Canvas *to_apply;

	Color color;
	size_t size;

public:
	Tool()
	{
		color = DEFAULT_TOOL_COLOR;
		size = DEFAULT_TOOL_SIZE;
	}

	void set_color(const Color &par_color) { color = par_color; }
	void set_size(const size_t par_size) { size = par_size; }

	Color get_color() { return color; }
	size_t get_size() { return size; }

	virtual void apply(Canvas *to_apply, const Vector_ll &position) = 0;
};

#endif // TOOLS_H
