#ifndef COLORS_USED
#define COLORS_USED

const unsigned char MAX_COLOR_VALUE = 255;

struct Color 
{
	unsigned char a;
	unsigned char r;
	unsigned char g;
	unsigned char b;

	unsigned char get_a() const { return a; }
	unsigned char get_r() const { return r; }
	unsigned char get_g() const { return g; }
	unsigned char get_b() const { return b; }

	void set_a(unsigned char par_a) { a = par_a; }
	void set_r(unsigned char par_r) { r = par_r; }
	void set_g(unsigned char par_g) { g = par_g; }
	void set_b(unsigned char par_b) { b = par_b; }

	friend bool operator==(const Color &left, const Color &right)
	{
		if (left.a == right.a && left.r == right.r && left.g == right.g && left.b == right.b)
			return true;

		return false;
	}

	friend bool operator!=(const Color &left, const Color &right)
	{
		if (left.a != right.a || left.r != right.r || left.g != right.g || left.b != right.b)
			return true;

		return false;
	}

	const Color operator*=(const double value)
	{
		r = double(r) * value;
		g = double(g) * value;
		b = double(b) * value;

		return *this;
	}

	const Color operator/=(const double value)
	{
		if (value == 0)
			return *this;

		r = double(r) / value;
		g = double(g) / value;
		b = double(b) / value;

		return *this;
	}
};

const Color BLACK  = { 255, 0, 0, 0 };
const Color WHITE  = { 255, 255, 255, 255 };
const Color RED    = { 255, 255, 0, 0 };
const Color GREEN  = { 255, 0, 255, 0 };
const Color BLUE   = { 255, 0, 0, 255 };
const Color YELLOW = { 255, 255, 255, 0 };
const Color PURPLE = { 255, 128, 0, 128 };
const Color FUCHSIA = { 255, 255, 0, 255 };
const Color MEDIUM_PURPLE = { 255, 147, 112, 219 };
const Color DARK_GREY = {255, 32, 32, 32};
const Color GREY = {255, 182, 182, 182};

#endif // COLORS_USED
