#ifndef SHAPE_CLASS
#define SHAPE_CLASS

#include "sfml_drawing/screen_functions.hpp"
#include "Radius_vector.hpp"

class Shape
{
private:
	Radius_vector centre_position;

	double weight;
	Radius_vector direction;

	Color color;
public:
	Shape();
	Shape(const Radius_vector &par_centre_position, const Radius_vector &par_direction, const double par_weight, const Color par_color = WHITE);
	~Shape() = default;

	double get_weight() const { return weight; }
	Radius_vector get_centre_position() const { return centre_position; }
	Radius_vector get_direction() const { return direction; }
	Color get_color() const { return color; }

	void set_weight(const double par_weight) { weight = par_weight; }
	void set_centre_position(const Radius_vector &par_centre_position) { centre_position = par_centre_position; }
	void set_direction(const Radius_vector &par_direction) { direction = par_direction; }
	void set_color(const Color par_color) { color = par_color; }

	virtual double get_size() const { return 0.0; }
	virtual void draw(Screen_information *screen) {;}
};

#endif // SHAPE_CLASS
