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

Canvas_keeper::Canvas_keeper(Visual_object *par_to_keep)
{
	printf("created\n");

	to_keep = par_to_keep;
}

bool Canvas_keeper::on_mouse_click(const size_t par_x, const size_t par_y)
{
	to_keep->set_visible(true);
	to_keep->set_reactive(true);

	return true;
}
