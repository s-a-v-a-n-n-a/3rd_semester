#ifndef VISUAL_OBJECT_BASE
#define VISUAL_OBJECT_BASE

#include <cstdio>
#include <cstdlib>
#include <cassert>

#include "../simple_list/simple_list.hpp"
#include "../sfml_drawing/screen_functions.hpp"
#include "../sfml_drawing/Texture.hpp"
#include "../math_structures/Radius_vector.hpp"

#include "../Editor/Vidget_types.hpp"

class Visual_object
{
private:
	const size_t type;

	// Visual_object *parent;
	List<Visual_object*> objects;
	Visual_object *current_active;

	Vector_ll stable_position;
	Texture *texture;
	Vector_ll position;
	Color color;

	size_t width;
	size_t height;

	bool active;
	bool visible;
	bool reactive;
	bool alive;

public:
	Visual_object() = delete;
	Visual_object(const size_t par_type, const Vector_ll &par_position, const Color &par_color, const size_t par_width, const size_t par_height);
	Visual_object(const size_t par_type, const Vector_ll &par_position, Texture *par_texture, const size_t par_width = 0, const size_t par_height = 0);
	~Visual_object() = default;
	
	virtual void add_visual_object(Visual_object *par_object);
	virtual void slow_delete_visual_object(size_t index);
	virtual long long very_slow_delete_visual_object(Visual_object *par_object);

	virtual void draw(Screen_information *screen);

	virtual bool point_inside (const size_t par_x, const size_t par_y);
	virtual bool on_mouse_click  (const bool state, const size_t par_x, const size_t par_y); //const Mouse_event par_event,
	virtual bool on_mouse_move	(const Vector_ll from, const Vector_ll to);
	virtual bool on_key_pressed(const unsigned key_mask); 
	// virtual bool on_key_press(const Key_event par_event);

	virtual void tick(Screen_information *screen, const double delta_time);

	List<Visual_object*>   *get_objects()        		{ return &objects; }
	Vector_ll  				get_position() 		const 	{ return position; }
	Color         		 	get_color()    		const 	{ return color; }
	size_t         			get_width()    		const 	{ return width; }
	size_t         			get_height()   		const 	{ return height; }
	Visual_object 		   *get_active() 				{ return current_active; }
	bool					get_active_state() 	const 	{ return active; }
	bool				    get_visible()  	   	const 	{ return visible; }
	bool				    get_reactive()  	const 	{ return reactive; }
	bool				    get_alive()  		const 	{ return alive; }
	size_t					get_type()			const	{ return type; }
	Texture 			   *get_texture()				{ return texture; }

	virtual void set_position 		(const Vector_ll &par_position);
	virtual void set_color    		(const Color &par_color)            { color = par_color; }
	virtual void set_width    		(const size_t par_width)            { width = par_width; }
	virtual void set_height   		(const size_t par_height)           { height = par_height; }
	virtual void set_active_state   (const bool par_active)             { active = par_active; }
	virtual void set_active  		(Visual_object *par_current_active)	{ current_active = par_current_active; }
	virtual void set_visible		(const bool par_visible)			{ visible = par_visible; }
	virtual void set_reactive		(const bool par_reactive)			{ reactive = par_reactive; }
	virtual void set_alive			(const bool par_alive)				{ alive = par_alive; }
	virtual void set_texture 		(Texture *par_texture)				{ texture = par_texture; }
};

#endif // VISUAL_OBJECT_BASE
