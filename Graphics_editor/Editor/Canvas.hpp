#ifndef CANVAS
#define CANVAS

#include "../GUI/Visual_object_base.hpp"
#include "Pencil.hpp"

class Canvas : public Visual_object
{
private:
	Pencil *pencil;

	// Color current_background_color;
	Color current_drawing_color;

	Color *drawing;

	bool drawing_state;

public:
	Canvas() = delete;
	// + храним информацию о главном
	Canvas(Pencil *par_pencil, const Radius_vector &par_position, const Color &par_color, const size_t par_width, const size_t par_height)
	: Visual_object(par_position, par_color, par_width, par_height)
	{
		pencil = par_pencil;

		// current_background_color = WHITE;
		current_drawing_color = BLACK;

		drawing = new Color[par_width * par_height];
		for (size_t i = 0; i < par_width * par_height; ++i)
			drawing[i] = WHITE;

		drawing_state = false;
	}

	~Canvas()
	{
		delete [] drawing;
	}

	void draw(Screen_information *screen) override;
	bool point_inside (const size_t par_x, const size_t par_y) override;
	bool on_mouse  (const bool clicked, const size_t par_x, const size_t par_y) override; // const Mouse_event par_event, 

	// надо как-то получить цвет карандаша
	void tick(Screen_information *screen, const double delta_time) override { ; }
};

#endif // CANVAS
