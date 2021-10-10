#ifndef BUTTON_CLASS
#define BUTTON_CLASS

#include <SFML/Graphics.hpp>

#include "Visual_object_base.hpp"
#include "Button_delegate.hpp" 
#include "Text.hpp"

const Color DEFAULT_TEXT_COLOR = WHITE;

struct Button : public Visual_object
{
private:
	// List<Visual_object*> objects;

	// Radius_vector position;
	// Color color;

	// size_t width;
	// size_t height;

	// bool active;

	Button_delegate *click;

public:
	Button() = delete;
	Button(Button_delegate *par_click, const char *par_text, const Radius_vector &par_position, Color par_color, double par_width, double par_height);
	~Button();

	void draw(Screen_information *screen) override;
	bool check_click(double par_x, double par_y) override;
};

#endif // BUTTON_CLASS
