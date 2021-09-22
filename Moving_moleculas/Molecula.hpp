#ifndef MOLECULA_CLASS
#define MOLECULA_CLASS

#include "sfml_drawing/screen_functions.hpp" // <not in project>
#include "Radius_vector.hpp" // <not in project>
#include "Shape.hpp"

class Molecula : public Shape // <no realization>
{
private:
	double radius;

	bool valid;

public:
	Molecula(const double par_radius, const Radius_vector &par_centre_position, const Radius_vector &par_direction, const double par_weight, const Color par_color = WHITE);
	Molecula(const Molecula &other) = delete;
	// Molecula(Molecula &&other) = delete;
	~Molecula() = default;

	void move(const Radius_vector &par_centre_position);

	double get_radius() const { if (radius < 0) { printf("AAA\n"); } return radius; }
	void set_radius(const double par_radius) { radius = par_radius; }

	double get_size() const override { return get_radius(); }
	void draw(Screen_information *screen) override;
};

#endif // MOLECULA_CLASS
