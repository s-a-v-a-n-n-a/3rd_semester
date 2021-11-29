#ifndef TOOLS_H 
#define TOOLS_H

#include "../simple_list/simple_list.hpp"
#include "../sfml_drawing/colors.hpp"
#include "../sfml_drawing/screen_functions.hpp"

// #include "../EditorCanvas.hpp"

const Color DEFAULT_TOOL_COLOR = RED;
const size_t DEFAULT_TOOL_SIZE = 20;

class Tool
{
protected:
	Color color;
	size_t size;

public:
	Tool()
	{
		color = DEFAULT_TOOL_COLOR;
		size = DEFAULT_TOOL_SIZE;
	}

	virtual void set_color(const Color &par_color) { color = par_color; }
	virtual void set_size(const size_t par_size) { size = par_size; }

	virtual Color get_color() { return color; }
	virtual size_t get_size() { return size; }

	// virtual void apply(Canvas *to_apply, const Vector_ll &position) = 0;
	virtual void apply(Color *to_apply, const Vector_ll &parameters, const Vector_ll &position) = 0;
};

#endif // TOOLS_H
