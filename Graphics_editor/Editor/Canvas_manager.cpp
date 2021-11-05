#include "Canvas_manager.hpp"

Canvas_manager::Canvas_manager(const size_t par_type, const Vector_ll &par_position, const Color &par_color, const size_t par_width, const size_t par_height, Pencil *par_pencil, const size_t predecessors_amount)
: Visual_object(par_type, par_position, par_color, par_width, par_height)
{
	// create Canvas
	// ------------------------------------------------------------------------------
	Full_texture *canvas_texture = new Full_texture(CANVAS_TEXTURE, par_width, (size_t)(par_height - INCREASED_BUTTON_HEIGHT));
	Canvas *canvas = new Canvas((size_t)Vidget_type::CANVAS, 
								par_position + Vector_ll(0.0, INCREASED_BUTTON_HEIGHT), 
								canvas_texture, 
								par_width, 
								par_height - INCREASED_BUTTON_HEIGHT, 
								par_pencil);

	// создаёт кнопку управления
	// ------------------------------------------------------------------------------
	Animating_texture *tab_texture = new Animating_texture(TAB_TEXTURE, (size_t)280, INCREASED_BUTTON_HEIGHT);
	tab_texture->set_inactive_texture(TAB_INACTIVE_TEXTURE);
	tab = new Tab((size_t)Vidget_type::TAB,
				  par_position + Vector_ll(predecessors_amount * DEFAULT_TAB_WIDTH, 0.0),
				  tab_texture,
				  tab_texture->get_width(),
				  tab_texture->get_height(),
				  this);
	tab->set_active_state(true);
	

	add_visual_object(canvas);
	add_visual_object(tab);
}

Canvas_manager::Canvas_manager(const size_t par_type, const Vector_ll &par_position, Texture *par_texture, const size_t par_width, const size_t par_height, Pencil *par_pencil, const size_t predecessors_amount)
: Visual_object(par_type, par_position, par_texture, par_width, par_height)
{
	// create Canvas
	// ------------------------------------------------------------------------------
	// Canvas *canvas = new Canvas((size_t)Vidget_type::CANVAS, 
	// 							par_position + Vector_ll(0.0, DEFAULT_BUTTON_HEIGHT), 
	// 							WHITE, 
	// 							get_width(), 
	// 							get_height() - DEFAULT_BUTTON_HEIGHT, 
	// 							par_pencil);
	Full_texture *canvas_texture = new Full_texture(CANVAS_TEXTURE, par_width, par_height - INCREASED_BUTTON_HEIGHT);
	Canvas *canvas = new Canvas((size_t)Vidget_type::CANVAS, 
								par_position + Vector_ll(0.0, DEFAULT_BUTTON_HEIGHT), 
								canvas_texture, 
								par_width, 
								par_height - DEFAULT_BUTTON_HEIGHT, 
								par_pencil);

	// создаёт кнопку управления
	// ------------------------------------------------------------------------------
	// tab = new Tab((size_t)Vidget_type::TAB,
	// 			  par_position + Vector_ll(predecessors_amount * DEFAULT_TAB_WIDTH, 0.0),
	// 			  GREY,
	// 			  DEFAULT_TAB_WIDTH,
	// 			  DEFAULT_BUTTON_HEIGHT,
	// 			  this);
	Full_texture *tab_texture = new Full_texture(TAB_TEXTURE, (size_t)280, INCREASED_BUTTON_HEIGHT);
	tab = new Tab((size_t)Vidget_type::TAB,
				  par_position + Vector_ll(predecessors_amount * DEFAULT_TAB_WIDTH, 0.0),
				  tab_texture,
				  tab_texture->get_width(),
				  tab_texture->get_height(),
				  this);

	add_visual_object(canvas);
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
				objects_array[i]->set_active_state(get_active_state());
				objects_array[i]->draw(screen);
			}
		}
	}
}


void Canvas_manager::set_offset(const Vector_ll &par_offset) 
{ 
	tab->set_position(get_position() + par_offset); 
}

Vector_ll Canvas_manager::get_offset() const 
{ 
	return tab->get_position() - get_position(); 
}
