#ifndef EVENT_HANDLER
#define EVENT_HANDLER

#include <SFML/Graphics.hpp>

enum class Sfml_events
{
	NOTHING,
	WINDOW_CLOSED,
	MOUSE_CLICKED,
	MOUSE_RELEASED,
	MOUSE_MOVED,
	KEY_U,
	KEY_R,
	KEY_G,
	KEY_B
};

enum class Mouse_state
{
	RELEASED,
	CLICKED,
	MOVED
};

enum class Key_state
{
	KEY_U,
	KEY_R,
	KEY_G,
	KEY_B
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

	        if (event.type == sf::Event::MouseMoved)
	        {
	        	return Sfml_events::MOUSE_MOVED;
	        }

	        if (event.type == sf::Event::KeyPressed)
	        {
	        	switch(event.key.code)
	        	{
	        	case sf::Keyboard::U:
	        		return Sfml_events::KEY_U;
	        		break;

	        	case sf::Keyboard::R:
	        		return Sfml_events::KEY_R;
	        		break;

	        	case sf::Keyboard::G:
	        		return Sfml_events::KEY_G;
	        		break;

	        	case sf::Keyboard::B:
	        		return Sfml_events::KEY_B;
	        		break;

	        	default:
	        		break;
	        	}
	        }
	    }

        return Sfml_events::NOTHING;
	}
};

#endif // EVENT_HANDLER
