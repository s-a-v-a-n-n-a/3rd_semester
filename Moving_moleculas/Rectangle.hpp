#ifndef RECTANGLE_CLASS
#define RECTANGLE_CLASS

#include "sfml_drawing/screen_functions.hpp" // <not in project>
#include "Radius_vector.hpp" // <not in project>
#include "Shape.hpp"

class Rectangle : public Shape // <no realization>
{
private:
	double side;

	bool valid;

public:
	Rectangle(const double par_side, const Radius_vector &par_centre_position, const Radius_vector &par_direction, const double par_weight, const Color par_color = WHITE);
	Rectangle(const Rectangle &other) = delete;
	// Rectangle(Rectangle &&other) = delete;
	~Rectangle() = default;

	void move(const Radius_vector &par_centre_position);

	double get_side() const { return side; }
	void set_side(const double par_side) { side = par_side; }

	double get_size() const override { return get_side()/2; }
	void draw(Screen_information *screen) override;
};

#endif // RECTANGLE_CLASS
