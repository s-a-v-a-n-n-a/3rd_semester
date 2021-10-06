#ifndef GRAPHICAL_SHAPE_CLASS
#define GRAPHICAL_SHAPE_CLASS

#include "sfml_drawing/screen_functions.hpp"
#include "Radius_vector.hpp"

class Graphical_shape
{
private:
	const int type;

	Radius_vector centre_position;

	Color color;
public:
	Graphical_shape();
	Graphical_shape(const int par_type);
	Graphical_shape(const Radius_vector &par_centre_position, const Color par_color = WHITE); // const Radius_vector &par_centre_position, 
	~Graphical_shape() = default;

	Radius_vector get_centre_position() const { return centre_position; }
	Color         get_color() const { return color; }

	void set_centre_position(const Radius_vector &par_centre_position) { centre_position = par_centre_position; }
	void set_color(const Color par_color) { color = par_color; }

	virtual void draw(Screen_information *screen) {;}
};

#endif // GRAPHICAL_SHAPE_CLASS

