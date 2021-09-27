#ifndef RECTANGLE_CLASS
#define RECTANGLE_CLASS

#include "../sfml_drawing/screen_functions.hpp" // <not in project>
#include "../math_structures/Radius_vector.hpp" // <not in project>
#include "../Shape_base/Shape.hpp"

class Rectangle : public Shape // <no realization>
{
private:
	// double side;
	double width;
	double height;

	bool valid;

public:
	Rectangle(const double par_width, const double par_height, const char par_type, const Radius_vector &par_centre_position, const Radius_vector &par_velocity, const double par_weight, const Color par_color = WHITE);
	Rectangle(const Rectangle &other) = delete;
	// Rectangle(Rectangle &&other) = delete;
	~Rectangle() = default;

	// Radius_vector count_move(double delta_time) override;
	// void move(const Radius_vector &par_centre_position) override;

	double get_width() const { return width; }
	double get_height() const { return height; }
	void set_width(const double par_width) { width = par_width; }
	void set_height(const double par_height) { height = par_height; }

	// double get_size() const override { return get_side()/2; }
	void draw(Screen_information *screen) override;
};

#endif // RECTANGLE_CLASS
