#ifndef SPLINE_MANAGER_H
#define SPLINE_MANAGER_H

#include "../GUI/Visual_object_base.hpp"

#include "Spline.hpp"
#include "Editor_delegates.hpp"

#include "Window_control_panel.hpp"

class Spline_manager : public Visual_object
{

public:
	Spline_manager(const Visual_object::Config &par_base, Canvas *canvas)
	: Visual_object(par_base)
	{
		Window_control_panel *control = create_control_panel(this, get_position(), get_width(), DEFAULT_BUTTON_HEIGHT);

		Spline *spline = create_spline(get_position() + Vector_ll(0, DEFAULT_BUTTON_HEIGHT), get_width(), get_height() - DEFAULT_BUTTON_HEIGHT, canvas);
	}
	~Spline_manager() = default;

	Spline *create_spline(const Vector_ll &position, const size_t width, const size_t height, Canvas *canvas)
	{
		Red_component_changer *delegate = new Red_component_changer(canvas);

		Visual_object::Config spline_base = { (size_t)Vidget_type::SPLINE, 
												position, 
												nullptr, 
												GREY,
												width,
												height};

		Spline *spline = new Spline(spline_base, delegate);
		add_visual_object(spline);

		return spline;
	}

	Window_control_panel *create_control_panel(Visual_object *parent, const Vector_ll &position, const size_t width, const size_t height)
	{
		Full_texture *texture = Resources::get_instance()->create_texture(WINDOW_HEADER, width, height);
		Visual_object::Config panel_base = { (size_t)Vidget_type::WINDOW_CONTROL_PANEL, 
												position, 
												texture, 
												TRANSPARENT,
												width,
												height};

		Window_control_panel *control = new Window_control_panel(panel_base, parent);
		add_visual_object(control);

		return control;
	}
};

#endif // SPLINE_MANAGER_H
