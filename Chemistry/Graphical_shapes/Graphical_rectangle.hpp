#ifndef GRAPHICAL_RECTANGLE
#define GRAPHICAL_RECTANGLE

#include "../Graphical_shape_base/Graphical_shape.hpp"

class Graphical_rectangle : public Graphical_shape
{
	double width;
	double height;

public:
	Rectangle() = delete;
	Rectangle(const double par_width, const double par_height, 
		      const char par_type, const Radius_vector &par_centre_position, const Color par_color = WHITE);
	Rectangle(const Rectangle &other) = delete;
	// Rectangle(Rectangle &&other) = delete;
	~Rectangle() = default;

	double get_width()  const { return width; }
	double get_height() const { return height; }
	
	void set_width (const double par_width)  { assert(par_width >= 0); width = par_width; }
	void set_height(const double par_height) { assert(par_height >= 0); height = par_height; }

	void draw(Screen_information *screen) override;
}

#endif // GRAPHICAL_RECTANGLE
