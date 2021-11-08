#ifndef CANVAS_MANAGER_MANAGER_H
#define CANVAS_MANAGER_MANAGER_H

#include "../GUI/Visual_object_base.hpp"

class Canvas_manager_manager;

#include "Window_control_panel.hpp"
#include "Canvas_manager.hpp"
#include "Pencil.hpp"

// #include "Drop_down_menu.hpp"

class Canvas_manager_manager : public Visual_object
{
private:
	Pencil *pencil;
	// Drop_down_menu *drop_and_down_menu;

public:
	Canvas_manager_manager(const size_t par_type, const Vector_ll &par_position, const Color &par_color, const size_t par_width, const size_t par_height, Pencil *par_pencil);
	Canvas_manager_manager(const size_t par_type, const Vector_ll &par_position, Texture *par_texture, const size_t par_width, const size_t par_height, Pencil *par_pencil);
	~Canvas_manager_manager() = default;

	Window_control_panel *create_control_panel(Visual_object *parent, const Vector_ll &position, const size_t width, const size_t height);

	void tick(Screen_information *screen, const double delta_time) override;
	void draw(Screen_information *screen) override;

	bool on_mouse_click(const bool state, const size_t par_x, const size_t par_y);
	bool on_mouse_move(const Vector_ll from, const Vector_ll to) override;

	void add_canvas();
};

#endif // CANVAS_MANAGER_MANAGER_H
