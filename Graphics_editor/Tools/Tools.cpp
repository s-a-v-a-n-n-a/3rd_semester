#include "Tools.hpp"

Tool::Tool()
: pressed(false)
{
	color = DEFAULT_TOOL_COLOR;
	size = DEFAULT_TOOL_SIZE;

	data = NULL;
}

void Tool::on_mouse_move(const Vector_ll &from, const Vector_ll &to)
{
	if (pressed)
	{
		apply(data, data_params, to);
	}
}

void Tool::on_mouse_press(Color *to_apply, const Vector_ll &parameters, const Vector_ll &position)
{
	data = to_apply;
	data_params = parameters;

	if (!pressed) 
		pressed = true;
	else 
		pressed = false;
}

void Tool::on_mouse_release(const Vector_ll &position)
{
	if (pressed)
		apply(data, data_params, position);
	pressed = false;
}

void Tool::release_data() {}

