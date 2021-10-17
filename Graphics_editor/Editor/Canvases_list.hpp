#ifndef CANVASES_LIST
#define CANVASES_LIST

#include "../GUI/Visual_object_base.hpp"

#include "Canvas_manager.hpp"

class Canvases_list : public Visual_object
{
private:
	List<Canvas_manager*> current_canvases;

public:
	Canvases_list(const Radius_vector &par_position, Color par_color, double par_width, double par_height)
	: Visual_object(par_position, par_color, par_width, par_height)
	{
		set_active(NULL);
	}

	~Canvases_list()
	{
		Visual_object **objects = get_objects()->get_array();
		size_t objects_amount = get_objects()->get_length();

		for (size_t i = 0; i < objects_amount; ++i)
		{
			delete objects[i];
		}

		// Не удалять холсты!!! Не забота текущего виджета
	}

	void draw(Screen_information *screen) override
	{
		Visual_object::draw(screen);

		Visual_object **objects = get_objects()->get_array();
		size_t objects_amount = get_objects()->get_length();

		for (size_t i = 0; i < objects_amount; ++i)
		{
			objects[i]->draw(screen);
		}
	}

	void delete_canvas();
}

#endif CANVASES_LIST
