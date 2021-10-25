#ifndef CANVASES_LIST
#define CANVASES_LIST

#include <cstdlib>

#include "../GUI/Visual_object_base.hpp"
#include "../GUI/Button.hpp"

#include "Canvas_manager.hpp"
#include "Editor_delegates.hpp"

// class Canvas_tab : public Visual_object
// {
// private:
// 	Canvas_manager *to_manage;

// public:
// 	Canvas_tab(const Vector_ll &par_position, Color par_color, double par_width, double par_height);
// 	~Canvases_list();
// };

class Canvases_list : public Visual_object
{
private:
	List<Canvas_manager*> current_canvases;

public:
	Canvases_list(const size_t par_type, const Vector_ll &par_position, Color par_color, double par_width, double par_height)
	: Visual_object(par_type, par_position, par_color, par_width, par_height)
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

	void add_canvas(Canvas_manager *to_add);
	void delete_canvas(Canvas_manager *to_delete);

	// void tick(Screen_information *screen, const double delta_time) override;
};

#endif // CANVASES_LIST
