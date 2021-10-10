#ifndef RECTANGLE_CLASS
#define RECTANGLE_CLASS

#include "../sfml_drawing/screen_functions.hpp" 
#include "../math_structures/Radius_vector.hpp"
#include "../Shape_base/Shape.hpp"

// убрать задание размера
class Rectangle : public Shape 
{
private:
	double scale;

	double width;
	double height;

public:
	Rectangle() = delete;
	Rectangle(const double par_scale,
			  const char par_type, const Radius_vector &par_centre_position, const Radius_vector &par_velocity, const double par_weight, const Color par_color = WHITE,
		      const bool par_active = true, const bool par_just_born = false);
	Rectangle(const Rectangle &other) = delete;
	// Rectangle(Rectangle &&other) = delete;
	~Rectangle() = default;

	// Radius_vector count_move(double delta_time) override;
	// void move(const Radius_vector &par_centre_position) override;

	void set_weight(const double par_weight) override;

	double get_width() const { return width; }
	double get_height() const { return height; }
	// void set_width(const double par_width) { assert(par_width >= 0); width = par_width; }
	// void set_height(const double par_height) { assert(par_height >= 0); height = par_height; }

	// double get_size() const override { return get_side()/2; }
	void draw(Screen_information *screen) override;
};

#endif // RECTANGLE_CLASS
