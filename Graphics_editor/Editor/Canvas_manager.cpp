#include "Canvas_manager.hpp"

Canvas_manager::Canvas_manager(const size_t par_type, const Radius_vector &par_position, const Color &par_color, const size_t par_width, const size_t par_height, Pencil *par_pencil, const Radius_vector &offset, const size_t predecessors_amount)
: Visual_object(par_type, par_position, par_color, par_width, par_height)
{
	// size_t button_height = 80;
	// set_height(par_height - DEFAULT_BUTTON_HEIGHT);
	// set_position(par_position - Radius_vector(0.0, DEFAULT_BUTTON_HEIGHT));
	// create Canvas
	// ------------------------------------------------------------------------------
	printf("Canvas_manager position: %lg, %lg\n", par_position.get_x(), par_position.get_y());

	Canvas *canvas = new Canvas((size_t)Vidget_type::CANVAS, 
								par_position + Radius_vector(0.0, DEFAULT_BUTTON_HEIGHT), 
								WHITE, 
								par_width, 
								par_height - DEFAULT_BUTTON_HEIGHT, 
								par_pencil);

	// создаёт кнопку управления
	// ------------------------------------------------------------------------------
	tab = new Tab((size_t)Vidget_type::TAB,
				  offset + Radius_vector(predecessors_amount * DEFAULT_TAB_WIDTH, 0.0),
				  GREY,
				  DEFAULT_TAB_WIDTH,
				  DEFAULT_BUTTON_HEIGHT,
				  this);

	add_visual_object(canvas);
	// add_visual_object(control);
	add_visual_object(tab);
}

Canvas_manager::~Canvas_manager()
{
	Visual_object **objects = get_objects()->get_array();
	size_t objects_amount = get_objects()->get_length();

	for (size_t i = 0; i < objects_amount; ++i)
	{
		delete objects[i];
	}
}

void Canvas_manager::draw(Screen_information *screen)
{
	assert(screen);

	if (get_reactive())
	{
		Visual_object **objects_array = get_objects()->get_array();
		size_t objects_amount = get_objects()->get_length();

		for (size_t i = 0; i < objects_amount; ++i)
		{
			if (objects_array[i]->get_visible())
			{
				objects_array[i]->draw(screen);
			}
		}
	}
}


void Canvas_manager::set_offset(const Radius_vector &par_offset) 
{ 
	tab->set_position(get_position() + par_offset); 
}

Radius_vector Canvas_manager::get_offset() const 
{ 
	return tab->get_position() - get_position(); 
}
