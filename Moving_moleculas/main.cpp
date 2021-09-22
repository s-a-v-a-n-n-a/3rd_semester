#include <SFML/Graphics.hpp>

#include "sfml_drawing/screen_functions.hpp"
#include "Shape_manager.hpp"
#include "Molecula.hpp"

void draw_world();

int main()
{
	draw_world();

	return 0;
}

void draw_world()
{
	sf::RenderWindow window(sf::VideoMode(700, 700), "It works");

    Screen_information screen(700, 700);
    Shape_manager world(10);
    Molecula a(25, Radius_vector(100, 100), Radius_vector(0, 0), 0);
    Molecula b(25, Radius_vector(150, 100), Radius_vector(0, 0), 0, RED);
    Molecula c1(25, Radius_vector(200, 100), Radius_vector(0, 0), 0, BLUE);
    Molecula c2(25, Radius_vector(250, 100), Radius_vector(0, 0), 0, BLUE);
    Molecula c3(25, Radius_vector(300, 100), Radius_vector(0, 0), 0, BLUE);
    Molecula c4(25, Radius_vector(350, 100), Radius_vector(0, 0), 0, BLUE);
    Molecula c5(25, Radius_vector(400, 100), Radius_vector(0, 0), 0, BLUE);
    Molecula c6(25, Radius_vector(450, 100), Radius_vector(0, 0), 0, BLUE);
    Molecula c7(25, Radius_vector(500, 100), Radius_vector(100, 0), 0, BLUE);
    world.add_shape(&a);
    world.add_shape(&b);
    world.add_shape(&c1);
    world.add_shape(&c2);
    world.add_shape(&c3);
    world.add_shape(&c4);
    world.add_shape(&c5);
    world.add_shape(&c6);
    world.add_shape(&c7);

    // world.draw_everything(&screen);

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
        world.control_physics_and_drawing(&screen, 0.016);
        draw_shape_sfml(&window, screen);

        window.display();
    }
}
