#ifndef SCREEN_INFORMATION
#define SCREEN_INFORMATION

#include <SFML/Graphics.hpp>
#include <cstring>
#include <cstdio>

#include "Event_handler.hpp"

#include "colors.hpp"
#include "../math_structures/Radius_vector.hpp"

#include "../simple_list/simple_list.hpp"

typedef enum Screen_information_code_errors 
{ 
	SCREEN_OK,
    SCREEN_NULL,
    SCREEN_NO_CONSTRUCT,
    SCREEN_SEGMENT_FAULT
} screen_code;

enum class Wall_type
{
	NO,
	LEFT,
	UP,
	RIGHT,
	DOWN
};

extern const char *screen_state_text[];

class Screen_information 
{
private:
	Radius_vector mouse_position;
	bool mouse_clicked;

	Color *data;
	size_t width;
	size_t height;

public:
	Event_handler event_handler; 

	sf::RenderWindow window;
	sf::Event event; 
	sf::Mouse mouse;



	Screen_information(size_t par_width, size_t par_height);
	~Screen_information();

	screen_code set_color(size_t line, size_t column, Color color);
	
	// getters
	// ---------------------------------------------------------------------
	size_t get_width();
	size_t get_height();
	bool          get_mouse_pressed_state() { return mouse_clicked; }
	Radius_vector get_mouse_position() const { return mouse_position; }
	// ---------------------------------------------------------------------

	// setters 
	// ---------------------------------------------------------------------
	void set_mouse_state(const bool par_state) { mouse_clicked = par_state; }
	// ---------------------------------------------------------------------
	
	// drawings
	// ---------------------------------------------------------------------
	void draw_circle(const Radius_vector &par_position, const Color &par_color, const double par_radius);
	void draw_rectangle(const Radius_vector &par_position, const Color &par_color, const double par_width, const double par_height);
	void draw_point(const Radius_vector &point, const Color &par_color);
	void draw_text(const char *par_text, const Radius_vector &par_position, const Color &par_color, const size_t text_size);
	void draw_image(const Color *array, const Radius_vector &position, const size_t width, const size_t height);
	// ---------------------------------------------------------------------
	
	void reset();

	void sfml_update_mouse_state();
	void sfml_update_mouse_position();
	void sfml_update_mouse_pressed_state();

	void image_load(sf::Image *image, const Color *to_draw, const size_t width, const size_t height);

	friend void copy_color_from_sfml_color(Screen_information &screen, sf::Color color, size_t line, size_t column);
	friend screen_code screen_load(Screen_information &screen, sf::Image* image);
	friend void draw_shape_sfml(sf::RenderWindow *window, Screen_information &screen);
};

#endif // SCREEN_INFORMATION
