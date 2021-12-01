#ifndef PLUGIN_MANAGER_H
#define PLUGIN_MANAGER_H

#include "plugin_std.hpp"

#include "../Tools/Toolbar.hpp"

#include "../sfml_drawing/screen_functions.hpp"
#include "../simple_list/simple_list.hpp"

class Plugin_manager
{
private:
	List<Plugin*> plugins; // надо ли?

	static PRGBA *get_pixels();
    static void get_size(size_t *width, size_t *height);

	static void release_pixels(PRGBA *pixels);	

	static PRGBA get_color();
    static float get_size();

	static void circle(PVec2f position, float radius, PRGBA color, const PRenderMode *render_mode);
	static void rectangle(PVec2f p1, PVec2f p2, PRGBA color, const PRenderMode *render_mode);
	static void triangle(PVec2f p1, PVec2f p2, PVec2f p3, PRGBA color, const PRenderMode *render_mode);
	static void line(PVec2f start, PVec2f end, PRGBA color, const PRenderMode *render_mode);

	static void pixels(PVec2f position, const PRGBA *data, size_t width, size_t height, const PRenderMode *render_mode);

public:
	Plugin_manager();
};

#endif // PLUGIN_MANAGER_H
