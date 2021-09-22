#ifndef BUTTON_CLASS
#define BUTTON_CLASS

#include <SFML/Graphics.hpp>

#include "Text.hpp"

/*
sf::Text text;

// select the font
text.setFont(font); // font is a sf::Font

// set the string to display
text.setString("Hello world");

// set the character size
text.setCharacterSize(24);
*/

struct Button
{
	double left_corner_x;
	double left_corner_y;

	Text text;
	void (*react)(const size_t &value);

	Button()
	{
		left_corner_x = 0;
		left_corner_y = 0;

		react = NULL;
	}

	Button(char par_text[30], double par_left_corner_x, double par_left_corner_y, void (*par_react)(const size_t &value))
	{
		// strcpy(text, par_text, 30);

		left_corner_x = par_left_corner_x;
		left_corner_y = par_left_corner_y;

		text.set_text(par_text);
		text.set_position(left_corner_x + 10, left_corner_y + 10);

		react = par_react;
	}

	void draw(sf::RenderWindow *window)
	{
		double size_y = 30;
		double size_x = strlen(text);
		size_x += 20;

		sf::RectangleShape button_space(sf::Vector2f(size_x, size_y));
		button_space.setPosition(left_corner_x, left_corner_y);
		button_space.setFillColor(sf::Color::White);

		window->draw(button_space);

		text.draw(window);
	}

	bool point_in_button(const double x, const double y)
	{
		if (x >= left_corner_x && x <= left_corner_x + size_x &&
			y >= left_corner_y && y <= left_corner_y + size_y)
			return true;
		
		return false;
	}

	void set_text(const char par_text[30])
	{
		text.set_text(par_text);
	}

	void set_function(void (*par_react)(const size_t &value))
	{
		react = par_react;
	}

	void set_position(double par_x, double par_y)
	{
		left_corner_x = par_x;
		left_corner_y = par_y;
	}

	void check_click(const size_t &value, double par_x, double par_y)
	{
		if (point_in_button(par_x, par_y))
		{
			if (event.mouseButton.button == sf::Mouse::Left)
		    {
		        // std::cout << "the right button was pressed" << std::endl;
		        // std::cout << "mouse x: " << event.mouseButton.x << std::endl;
		        // std::cout << "mouse y: " << event.mouseButton.y << std::endl;
	
		        react(value);
		    }
		}
	}
};

#endif // BUTTON_CLASS
