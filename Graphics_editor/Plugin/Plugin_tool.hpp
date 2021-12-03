#ifndef PLUGIN_TOOL_H
#define PLUGIN_TOOL_H

#include "../GUI/Tool.hpp"

const PPluginInterface *(*get_plugin_interface)();

class Plugin_tool : public Plugin, public Tool
{
private:
	PPluginInterface *plugin;
	Visual_object *surface;

public:
	Plugin_tool(const char *dll_name, const PAppInterface *interface)
	: Tool(), Plugin(dll_name), plugin(nullptr), surface(nullptr)
	{
		get_plugin_interface = (PPluginInterface *(*)())dlsym(handle, "PGET_INTERFACE_FUNC");
		plugin = get_plugin_interface();
		
		PPluginStatus result = plugin->init(interface);
		if (result != PPS_OK)
			printf("Could not initialize plugin tool\n");
	} 

	~Plugin_tool()
	{
		plugin->deinit();
	}

	void on_mouse_move(const Vector_ll &from, const Vector_ll &to) override
	{
		if (pressed)
		{
			PVec2f mouse_pos = { (float)position.get_x(), (float)position.get_y() };
			plugin->on_press(mouse_pos);
		}
	}
	void on_mouse_press(Color *to_apply, const Vector_ll &parameters, const Vector_ll &position) override
	{
		Tool::on_mouse_press(to_apply, parameters, position);

		PVec2f mouse_pos = { (float)position.get_x(), (float)position.get_y() };
		plugin->on_press(mouse_pos);
	}
	void on_mouse_release(const Vector_ll &position) override
	{
		if (pressed)
		{
			PVec2f mouse_pos = { (float)position.get_x(), (float)position.get_y() };
			plugin->on_release(mouse_pos);

			pressed = false;
		}
	}

	void set_surface(Visual_object *par_surface)
	{
		surface = par_surface;
	}

	Visual_object *get_surface()
	{
		return surface;
	}

	PPluginInterface *get_plugin()
	{
		return plugin;
	}
};

#endif // PLUGIN_TOOL_H
