#ifndef APP_INTERFACE_H
#define APP_INTERFACE_H

#include "../sfml_drawing/screen_functions.hpp"

struct GEditor_interface
{
	struct GDrawing
	{
		void (*draw_circle)(const Vector_ll &position, const double radius, const Color color);
		void (*draw_rectangle)(const Vector_ll &position, const double width, const double height, const Color color);
		void (*draw_triangle)(const Vector_ll &point1, const Vector_ll &point2, const Vector_ll &point3, const Color color);
		void (*draw_line)(const Vector_ll &point1, const Vector_ll &point2, const Color color);
	
		void (*draw_pixels)(const Vector_ll &position, const Color *pixels, const size_t width, const size_t height);
	}
};

#endif // APP_INTERFACE_H
