#ifndef BUTTON_CLASS
#define BUTTON_CLASS

#include <SFML/Graphics.hpp>

#include "Visual_object_base.hpp"
#include "Button_delegate.hpp" 
#include "Text.hpp"

const Color DEFAULT_TEXT_COLOR = BLACK;
extern const size_t DEFAULT_BUTTON_HEIGHT;

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
	Button(const size_t par_type, const Radius_vector &par_position, Color par_color, double par_width, double par_height,
		   Button_delegate *par_click, const char *par_text);
	~Button();

	void set_delegate(Button_delegate *par_click) { click = par_click; }

	void draw(Screen_information *screen) override;
	bool on_mouse(const Mouse_state state, const size_t par_x, const size_t par_y) override; // const Mouse_event par_event, 
	void tick(Screen_information *screen, const double delta_time) override { ; }
};

#endif // BUTTON_CLASS
