#ifndef VISUAL_OBJECT_BASE
#define VISUAL_OBJECT_BASE

#include <cstdio>
#include <cstdlib>
#include <cassert>

#include "../simple_list/simple_list.hpp"
#include "../sfml_drawing/screen_functions.hpp"
#include "../math_structures/Radius_vector.hpp"

class Visual_object
{
private:
	List<Visual_object*> objects;
	Visual_object *current_active;

	Radius_vector position;
	Color color;

	size_t width;
	size_t height;

	bool active;
	bool visible;
	bool reactive;
	bool alive;

public:
	Visual_object() = delete;
	Visual_object(const Radius_vector &par_position, const Color &par_color, const size_t par_width, const size_t par_height);
	virtual ~Visual_object() = default;

	virtual void add_visual_object(Visual_object *par_object) { objects.add_to_end(par_object); }
	virtual void slow_delete_visual_object(size_t index) { objects.slow_delete(index); }
	virtual void very_slow_delete_visual_object(Visual_object *par_object);

	virtual void draw(Screen_information *screen);

	virtual bool point_inside (const size_t par_x, const size_t par_y);
	virtual bool on_mouse  (const bool clicked, const size_t par_x, const size_t par_y); //const Mouse_event par_event, 
	// virtual bool on_key_press(const Key_event par_event);

	virtual void tick(Screen_information *screen, const double delta_time);

	List<Visual_object*>   *get_objects()        		{ return &objects; }
	Radius_vector  			get_position() 		const 	{ return position; }
	Color         		 	get_color()    		const 	{ return color; }
	size_t         			get_width()    		const 	{ return width; }
	size_t         			get_height()   		const 	{ return height; }
	Visual_object 		   *get_active() 				{ return current_active; }
	bool					get_active_state() 	const 	{ return active; }
	bool				    get_visible()  	   	const 	{ return visible; }
	bool				    get_reactive()  	const 	{ return reactive; }
	bool				    get_alive()  		const 	{ return alive; }

	virtual void set_position 		(const Radius_vector &par_position) { position = par_position; }
	virtual void set_color    		(const Color &par_color)            { color = par_color; }
	virtual void set_width    		(const size_t par_width)            { width = par_width; }
	virtual void set_height   		(const size_t par_height)           { height = par_height; }
	virtual void set_active_state   (const bool par_active)             { active = par_active; }
	virtual void set_active  		(Visual_object *par_current_active)	{ current_active = par_current_active; }
	virtual void set_visible		(const bool par_visible)			{ visible = par_visible; }
	virtual void set_reactive		(const bool par_reactive)			{ reactive = par_reactive; }
	virtual void set_alive			(const bool par_alive)			{ alive = par_alive; }
};

#endif // VISUAL_OBJECT_BASE
