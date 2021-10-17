#ifndef PENCIL
#define PENCIL

#include "../sfml_drawing/colors.hpp"

class Pencil
{
private:
	Color color;
	size_t size;

public:
	Pencil()
	{
		color = BLACK;
		size = 20;
	}

	Pencil(const Color &par_color, const size_t par_size)
	{
		color = par_color;
		size = par_size;
	}

	~Pencil() = default;

	void set_color(const Color &par_color) { color = par_color; }
	void set_size(const size_t par_size) { size = par_size; }

	Color get_color() { return color; }
	size_t get_size() { return size; }
};

#endif // PENCIL
