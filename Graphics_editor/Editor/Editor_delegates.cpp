#include "Editor_delegates.hpp"

Create_canvas::Create_canvas(Canvas_manager_manager *par_manager)
{
	// pencil = par_pencil;
	manager = par_manager;

	// low_limits = par_low_limits;
	// high_limits = par_high_limits;
}

bool Create_canvas::on_mouse_click(const size_t par_x, const size_t par_y)
{
	// Canvas_manager *canvas = new Canvas_manager(pencil, low_limits, WHITE, high_limits.get_x(), high_limits.get_y());
	manager->add_canvas();

	return true;
}

Interactive_create_canvas::Interactive_create_canvas(Canvas_manager_manager *par_manager, Visual_object *par_to_interact)
: Create_canvas(par_manager), Interactive(par_to_interact)
{
	;
}

bool Interactive_create_canvas::on_mouse_move(const Vector_ll from, const Vector_ll to) 
{
	return Interactive::on_mouse_move(from, to);
}


Animating_create_canvas::Animating_create_canvas(Canvas_manager_manager *par_manager, Visual_object *par_to_animate)
: Create_canvas(par_manager), Animating(par_to_animate)
{
	;
}

bool Animating_create_canvas::on_mouse_click(const size_t par_x, const size_t par_y)
{
	Create_canvas::on_mouse_click(par_x, par_y);
	return Animating::on_mouse_click(par_x, par_y);
}

bool Animating_create_canvas::on_mouse_move(const Vector_ll from, const Vector_ll to)
{
	return Animating::on_mouse_move(from, to);
}


Canvas_keeper::Canvas_keeper(Visual_object *par_to_keep)
{
	to_keep = par_to_keep;
}

bool Canvas_keeper::on_mouse_click(const size_t par_x, const size_t par_y)
{
	to_keep->set_active_state(true);
	to_keep->set_visible(true);
	to_keep->set_reactive(true);

	return true;
}

Red_component_changer::Red_component_changer(Canvas *par_to_change)
: to_change(par_to_change)
{
	;
}

bool Red_component_changer::on_mouse_click(const size_t par_x, const size_t par_y)
{
	to_change->set_red(par_x, par_y);

	return true;
}

bool Red_component_changer::on_mouse_move(const Vector_ll from, const Vector_ll to)
{
	to_change->set_red(to.get_x(), to.get_y());

	return true;
}
