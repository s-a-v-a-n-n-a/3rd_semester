#ifndef ACCELERATING_RECTANGLE_CLASS
#define ACCELERATING_RECTANGLE_CLASS

#include "sfml_drawing/screen_functions.hpp" // <not in project>
#include "Radius_vector.hpp" // <not in project>
#include "Shape.hpp"

class Accelerating_rectangle : public Rectangle // <no realization>
{
private:
	Radius_vector acceleration;

public:
	Accelerating_rectangle(const Radius_vector &par_acceleration, const double par_side, const Radius_vector &par_centre_position, const Radius_vector &par_direction, const double par_weight, const Color par_color = WHITE);
	Accelerating_rectangle(const Accelerating_rectangle &other) = delete;
	~Accelerating_rectangle() = default;

	void move(const Radius_vector &par_centre_position);
};

#endif // ACCELERATING_RECTANGLE_CLASS
