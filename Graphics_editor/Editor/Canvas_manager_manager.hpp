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
	Canvas_manager_manager(const size_t par_type, const Vector_ll &par_position, Texture *par_texture, Pencil *par_pencil);
	~Canvas_manager_manager() = default;

	void tick(Screen_information *screen, const double delta_time) override;
	void draw(Screen_information *screen) override;

	void add_canvas();
};

#endif // CANVAS_MANAGER_MANAGER_H
