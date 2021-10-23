#ifndef CANVAS_H
#define CANVAS_H

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
	Canvas(const size_t par_type, const Radius_vector &par_position, const Color &par_color, const size_t par_width, const size_t par_height, Pencil *par_pencil);

	~Canvas()
	{
		delete [] drawing;
	}

	void draw(Screen_information *screen) override;
	bool point_inside (const size_t par_x, const size_t par_y) override;
	bool on_mouse  (const Mouse_state state, const size_t par_x, const size_t par_y) override; // const Mouse_event par_event, 
	// bool on_key_pressed(const unsigned key_mask) override;

	// надо как-то получить цвет карандаша
	void tick(Screen_information *screen, const double delta_time) override { ; }
};

#endif // CANVAS_H
