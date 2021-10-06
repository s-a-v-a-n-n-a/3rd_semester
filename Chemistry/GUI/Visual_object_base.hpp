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

	Radius_vector position;
	Color color;

	size_t width;
	size_t height;

	bool active;

public:
	Visual_object() = delete;
	Visual_object(const Radius_vector &par_position, const Color &par_color, const size_t par_width, const size_t par_height);
	virtual ~Visual_object() = default;

	virtual void add_visual_object(Visual_object *par_object) { objects.add_to_end(par_object); }

	virtual void draw(Screen_information *screen);

	virtual bool point_inside (const double par_x, const double par_y);
	virtual bool check_click  (const double par_x, const double par_y)
	{
		if (point_inside(par_x, par_y))
		{
			set_active(true);

			return true;
		}

		return false;
	}

	virtual void tick(Screen_information *screen, const double delta_time) { ; }

	List<Visual_object*> *get_objects() { return &objects; }
	Radius_vector get_position() const { return position; }
	Color         get_color()    const { return color; }
	size_t        get_width()    const { return width; }
	size_t        get_height()   const { return height; }

	virtual void set_position (const Radius_vector &par_position) { position = par_position; }
	virtual void set_color    (const Color &par_color)            { color = par_color; }
	virtual void set_width    (const size_t par_width)            { width = par_width; }
	virtual void set_height   (const size_t par_height)           { height = par_height; }
	virtual void set_active   (const bool par_active)             { active = par_active; }
};

#endif // VISUAL_OBJECT_BASE
