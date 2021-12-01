#include "Plugin_manager.hpp"

static PRGBA *Plugin_manager::get_pixels()
{
	return (PRGBA*)Toolbar::get_instance()->get_active_tool()->get_data();
}

static void Plugin_manager::get_size(size_t *width, size_t *height)
{
	Vector_ll params = Toolbar::get_instance()->get_active_tool()->get_params();

	(*width) = (size_t)params.get_x(); 
	(*height) = (size_t)params.get_y(); 
}

// ????????????????????????????????/
static void Plugin_manager::release_pixels(PRGBA *pixels)
{
	;
}

static PRGBA Plugin_manager::get_color()
{
	return (PRGBA)Toolbar::get_instance()->get_color();
}

static float Plugin_manager::get_size()
{
	return (float)Toolbar::get_instance()->get_active_tool()->get_size();
}

static void Plugin_manager::circle(PVec2f position, float radius, PRGBA color, const PRenderMode *render_mode)
{
	Vector_ll position = Vector_ll((long long)position.x, (long long)position.y);
	Color color = { color.r, color.g, color.b, color.a };

	draw_circle(position, (double)radius, color, color);
}

static void Plugin_manager::rectangle(PVec2f p1, PVec2f p2, PRGBA color, const PRenderMode *render_mode)
{
	Vector_ll position = { 0, 0 };
	long long x_pos = p1.x < p2.x ? p1.x : p2.x;
	long long y_pos = p1.y < p2.y ? p1.y : p2.y;

	Vector_ll position = Vector_ll(x_pos, y_pos);
	Color color = { color.r, color.g, color.b, color.a };

	size_t width = (size_t)((fabs)(p2.x - p1.x));
	size_t height = (size_t)((fabs)(p2.y - p1.y));

	draw_rectangle(position, width, height, color, color);
}

static void Plugin_manager::triangle(PVec2f p1, PVec2f p2, PVec2f p3, PRGBA color, const PRenderMode *render_mode)
{
	Vector_ll point1 = Vector_ll((long long)p1.x, (long long)p1.y);
	Vector_ll point2 = Vector_ll((long long)p2.x, (long long)p2.y);
	Vector_ll point3 = Vector_ll((long long)p3.x, (long long)p3.y);

	Color color = { color.r, color.g, color.b, color.a };

	draw_triangle(point1, point2, point3, color, color);
}

static void line(PVec2f start, PVec2f end, PRGBA color, const PRenderMode *render_mode)
{
	Vector_ll point1 = Vector_ll((long long)start.x, (long long)start.y);
	Vector_ll point2 = Vector_ll((long long)end.x, (long long)end.y);

	Color color = { color.r, color.g, color.b, color.a };

	draw_line(point1, point2, color);
}

static void pixels(PVec2f position, const PRGBA *data, size_t width, size_t height, const PRenderMode *render_mode)
{
	Vector_ll position = Vector_ll(x_pos, y_pos);

	draw_image((Color*)data, position, (size_t)width, (size_t)height);
}

