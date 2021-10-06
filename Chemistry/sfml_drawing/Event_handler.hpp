#ifndef EVENT_HANDLER
#define EVENT_HANDLER

#include <SFML/Graphics.hpp>

enum class Sfml_events
{
	NOTHING,
	WINDOW_CLOSED,
	MOUSE_CLICKED,
	MOUSE_RELEASED
};

class Event_handler
{
public:
	Sfml_events detect_event(sf::RenderWindow &window, sf::Event &event)
	{
		if(window.pollEvent(event)) 
		{
			if (event.type == sf::Event::Closed)
	        {
	           return Sfml_events::WINDOW_CLOSED;
	        }

	        if (event.type == sf::Event::MouseButtonPressed)
	        {
	        	return Sfml_events::MOUSE_CLICKED;
	        }

	        if (event.type == sf::Event::MouseButtonReleased)
	        {
	        	return Sfml_events::MOUSE_RELEASED;
	        }
	    }

        return Sfml_events::NOTHING;
	}
};

#endif // EVENT_HANDLER
