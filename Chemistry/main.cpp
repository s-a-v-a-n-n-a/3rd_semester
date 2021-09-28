#include <cstdio>
#include <cstdlib>

#include <SFML/Graphics.hpp>

#include "Shapes_interactions/Shapes_set.hpp"

#include "sfml_drawing/screen_functions.hpp"
#include "Shape_manager/Shape_manager.hpp"

void draw_world();

int main()
{
	draw_world();

	return 0;
}

void draw_world()
{
	sf::RenderWindow window(sf::VideoMode(1000, 1000), "It works");
	window.setFramerateLimit(60);

    Screen_information screen(1000, 1000);
    Shape_manager world(10);
    Molecula a(15.0, (char)Shape_types::MOLECULA, Radius_vector(100, 100), Radius_vector(50, 20), 1.0, WHITE, true, true);
    Molecula b(20.0, (char)Shape_types::MOLECULA, Radius_vector(200, 100), Radius_vector(10, 10), 2.0, WHITE, true, true);
    
    Rectangle c2(30.0, 30.0, (char)Shape_types::RECTANGLE, Radius_vector(250, 100), Radius_vector(0, 40), 2.0, WHITE, true, true);
    Rectangle c3(70.0, 70.0, (char)Shape_types::RECTANGLE, Radius_vector(250, 600), Radius_vector(0, -40), 2.0, WHITE, true, true);
    
    world.add_shape(&a);
    world.add_shape(&b);
    world.add_shape(&c2);
    world.add_shape(&c3);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
               window.close();
            }
        }

        window.clear();
        
		screen.reset();
        world.control_physics_and_drawing(&screen, 0.16);
        draw_shape_sfml(&window, screen);

        window.display();
    }
}
