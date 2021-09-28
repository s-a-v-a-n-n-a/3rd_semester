#ifndef SHAPE_CLASS
#define SHAPE_CLASS

#include <assert.h>

#include "../sfml_drawing/screen_functions.hpp"
#include "../math_structures/Radius_vector.hpp"
#include "../math_structures/math_functions.hpp"

class Shape
{
private:
	const char type;

	Radius_vector centre_position;

	double weight;
	Radius_vector velocity;

	Color color;

	bool active;
	bool just_born;
public:
	Shape() = delete;
	Shape(const char par_type);
	Shape(const char par_type, const Radius_vector &par_centre_position, const Radius_vector &par_velocity, const double par_weight, const Color par_color = WHITE, 
		  const bool par_active = true, const bool par_just_born = false);
	~Shape() = default;

	char get_type() const { return type; }
	double get_weight() const { return weight; }
	Radius_vector get_centre_position() const { return centre_position; }
	Radius_vector get_velocity() const { return velocity; }
	Color get_color() const { return color; }
	bool get_active() const { return active; }
	bool get_just_born() const { return just_born; }

	void set_weight(const double par_weight) { assert(par_weight); weight = par_weight; }
	void set_centre_position(const Radius_vector &par_centre_position) { centre_position = par_centre_position; }
	void set_velocity(const Radius_vector &par_velocity) { velocity = par_velocity; }
	void set_color(const Color par_color) { color = par_color; }
	void set_active(const bool par_active) { active = par_active; }
	void set_just_born(const bool par_just_born) { just_born = par_just_born; }

	// virtual double get_size() const { return 0.0; }
	virtual void draw(Screen_information *screen) { ; }

	virtual Radius_vector count_move(const double delta_time) { return Radius_vector(centre_position + velocity * delta_time); };
	virtual void move(const Radius_vector &par_centre_position) { set_centre_position(par_centre_position); }
};

#endif // SHAPE_CLASS

/*
// physics

#ifndef PHYSICAL_SHAPE_CLASS
#define PHYSICAL_SHAPE_CLASS

#include "sfml_drawing/screen_functions.hpp"
#include "Radius_vector.hpp"

class Physical_shape
{
private:
	// Radius_vector centre_position; // ???

	double weight;
	Radius_vector velocity;

	// Color color;
public:
	Shape();
	Shape(const Radius_vector &par_velocity, const double par_weight); // const Radius_vector &par_centre_position, 
	~Shape() = default;

	double get_weight() const { return weight; }
	// Radius_vector get_centre_position() const { return centre_position; }
	Radius_vector get_velocity() const { return velocity; }
	// Color get_color() const { return color; }

	void set_weight(const double par_weight) { weight = par_weight; }
	// void set_centre_position(const Radius_vector &par_centre_position) { centre_position = par_centre_position; }
	void set_velocity(const Radius_vector &par_velocity) { velocity = par_velocity; }
	// void set_color(const Color par_color) { color = par_color; }

	virtual double get_size() const { return 0.0; }
	// virtual void draw(Screen_information *screen) {;}
};

#endif // PHYSICAL_SHAPE_CLASS

// graphics

#ifndef GRAPHICAL_SHAPE_CLASS
#define GRAPHICAL_SHAPE_CLASS

#include "sfml_drawing/screen_functions.hpp"
#include "Radius_vector.hpp"

class Graphical_shape
{
private:
	Radius_vector centre_position;

	Color color;
public:
	Shape();
	Shape(const Radius_vector &par_centre_position, const Color par_color = WHITE); // const Radius_vector &par_centre_position, 
	~Shape() = default;

	Radius_vector get_centre_position() const { return centre_position; }
	Color get_color() const { return color; }

	void set_centre_position(const Radius_vector &par_centre_position) { centre_position = par_centre_position; }
	void set_color(const Color par_color) { color = par_color; }

	virtual void draw(Screen_information *screen) {;}
};

#endif // GRAPHICAL_SHAPE_CLASS

// shape

*/

