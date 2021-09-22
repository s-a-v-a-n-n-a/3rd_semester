#ifndef COLORS_USED
#define COLORS_USED

const unsigned char MAX_COLOR_VALUE = 255;

struct Color 
{
	unsigned char a;
	unsigned char r;
	unsigned char g;
	unsigned char b;
};

const Color BLACK  = { 0, 0, 0, 0 };
const Color WHITE  = { 255, 255, 255, 255 };
const Color RED    = { 255, 255, 0, 0 };
const Color GREEN  = { 255, 0, 255, 0 };
const Color BLUE   = { 255, 0, 0, 255 };
const Color YELLOW = { 255, 255, 255, 0 };

#endif // COLORS_USED
