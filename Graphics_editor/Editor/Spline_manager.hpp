#ifndef SPLINE_MANAGER_H
#define SPLINE_MANAGER_H

#include "../GUI/Visual_object_base.hpp"
#include "../GUI/Interpolator.hpp"

#include "Editor_delegates.hpp"

#include "Window_control_panel.hpp"

class Spline_manager : public Visual_object
{

public:
	Spline_manager(const size_t par_type, const Vector_ll &par_position, Texture *par_texture, const size_t par_width, const size_t par_height, Canvas *canvas)
	: Visual_object(par_type, par_position, par_texture, par_width, par_height)
	{
		Window_control_panel *control = create_control_panel(this, par_position, par_width, DEFAULT_BUTTON_HEIGHT);

		Spline *spline = create_spline(par_position + Vector_ll(0, DEFAULT_BUTTON_HEIGHT), par_width, par_height - DEFAULT_BUTTON_HEIGHT, canvas);
	}
	~Spline_manager() = default;

	Spline *create_spline(const Vector_ll &position, const size_t width, const size_t height, Canvas *canvas)
	{
		Red_component_changer *delegate = new Red_component_changer(canvas);

		Spline *spline = new Spline((size_t)Vidget_type::SPLINE, position, GREY, width, height, delegate);
		add_visual_object(spline);

		return spline;
	}

	Window_control_panel *create_control_panel(Visual_object *parent, const Vector_ll &position, const size_t width, const size_t height)
	{
		Full_texture *texture = new Full_texture(WINDOW_HEADER, width, height);
		Window_control_panel *control = new Window_control_panel((size_t)Vidget_type::WINDOW_CONTROL_PANEL, 
																position, 
																texture, 
																width, 
																height, 
																parent);
		add_visual_object(control);

		return control;
	}
};

#endif // SPLINE_MANAGER_H
