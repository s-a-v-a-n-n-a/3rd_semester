#include "Tools.hpp"

Tool::Tool()
: pressed(false), name(nullptr)
{
	color = DEFAULT_TOOL_COLOR;
	size = DEFAULT_TOOL_SIZE;

	data = NULL;
}

Tool::Tool(const char *par_name)
: pressed(false), name(nullptr)
{
	size_t name_size = strlen(par_name);

	name = new char[name_size + 1];
	strncpy(name, par_name, name_size);
	name[name_size] = 0;
}

Tool::~Tool()
{
	if (name)
	{
		delete [] name;
	}
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
	{ 
		apply(data, data_params, position);
		pressed = true;
	}
}

void Tool::on_mouse_release(const Vector_ll &position)
{
	// if (pressed)
	// 	apply(data, data_params, position);
	// printf("Tool released!!!!!!!!!!!\n");
	pressed = false;
}

void Tool::release_data() {}

