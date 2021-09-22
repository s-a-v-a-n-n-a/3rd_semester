#ifndef SIMPLE_SLIDER
#define SIMPLE_SLIDER

#include "../simple_list/simple_list.hpp"
#include "../sfml_drawing/simple_drawing.hpp"

#include "../shapes/lightened_sphere.hpp"

void increase_value(const size_t &value)
{
	value += 10;
}

void decrease_value(const size_t &value)
{
	value -= 10;
}

/*
void set_red_component(Lightened_sphere *sphere)
{
	Radius_vector color(sphere->get_sphere_color());
    color.set_x(current_position / 255);
    sphere->set_sphere_color(color);
}
*/

struct Simple_slider
{
	double left_corner_x;
	double left_corner_y;

	Text text;

	// double slider_x;
	// double slider_y;
	size_t slider_size;

	size_t current_position; // axe x

	Button button_increase;
	Button button_decrease;

	void (*change_state(Lightened_sphere *sphere))

	Simple_slider(char par_text[30], double par_left_corner_x, double par_left_corner_y, size_t par_slider_size, void (*par_change_state)(Lightened_sphere *sphere))
	{
		// strcpy(text, par_text, 30);

		left_corner_x = par_left_corner_x;
		left_corner_y = par_left_corner_y;

		slider_size = par_slider_size;

		text.set_text(par_text);
		text.set_text(par_left_corner_x + 10, par_left_corner_y + 10);

		button_increase.set_text("+10");
		button_increase.set_function(&increase_value);
		button_increase.set_position(left_corner_x + slider_size - 10, left_corner_y + 10); // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

		button_decrease.set_text("-10");
		button_decrease.set_function(&decrease_value);
		button_decrease.set_position(left_corner_x + slider_size - 50, left_corner_y + 10); // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	
		change_state = par_change_state;
	}

	void draw(sf::RenderWindow *window)
	{
		double size_y = 150;
		double size_x = 300;
		// size_x += 20;

		sf::RectangleShape slider_space(sf::Vector2f(size_x, size_y));
		slider_space.setPosition(left_corner_x, left_corner_y);
		slider_space.setFillColor(sf::Color::Grey);

		window->draw(slider_space);

		// draw_line
		draw_line_sfml(window, { left_corner_x + 10, left_corner_y + size_y/2 }, { par_left_corner_x + 10 + slider_size, left_corner_y + size_y/2 } );
		// draw_position
		draw_circle_sfml(window, { left_corner_x + 10 + current_position, left_corner_y + size_y/2 }, 10);

		text.draw();

		button_increase.draw();
		button_decrease.draw();
	}

	void check_changes(Lightened_sphere *sphere)
	{
		if (event.type == sf::Event::MouseEntered)
		{
			if (event.type == sf::Event::MouseMoved)
			{
			    printf("new mouse x: %u\nnew mouse y: %u\n", event.mouseMove.x, event.mouseMove.y);
			    unsigned mouse_position_x = event.mouseMove.x;
			    unsigned mouse_position_y = event.mouseMove.y;
			    
			    button_increase.check_click(current_position, mouse_position_x, mouse_position_y);
			    button_decrease.check_click(current_position, mouse_position_x, mouse_position_y);
			    
			    change_state(sphere);
			}
		}
	}
};

#endif // SIMPLE_SLIDER
