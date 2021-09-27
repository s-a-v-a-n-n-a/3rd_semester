#include <SFML/Graphics.hpp>

#include "Shapes_interactions/Shapes_set.hpp"

#include "sfml_drawing/screen_functions.hpp"
#include "Shape_manager/Shape_manager.hpp"

#include "Shapes/Accelerating_rectangle.hpp"

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
    Molecula a(50.0, (char)Shape_types::MOLECULA, Radius_vector(100, 100), Radius_vector(50, 20), 1.0);
    Molecula b(25.0, (char)Shape_types::MOLECULA, Radius_vector(200, 100), Radius_vector(0, 0), 2.0, RED);
    Molecula c1(25.0, (char)Shape_types::MOLECULA, Radius_vector(500, 100), Radius_vector(100, 200), 1.0, BLUE);

    // corrrect acceleration in shape manager by moving methods to shape classes
    Accelerating_rectangle c2(Radius_vector(50, 0), 50.0, 80.0, (char)Shape_types::RECTANGLE, Radius_vector(250, 100), Radius_vector(-25, 25), 2.0, RED);
    Accelerating_rectangle c3(Radius_vector(50, 0), 60.0, 60.0, (char)Shape_types::RECTANGLE, Radius_vector(100, 100), Radius_vector(-50, 25), 2.0, BLUE);
    world.add_shape(&a);
    world.add_shape(&b);
    world.add_shape(&c1);
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
        world.control_physics_and_drawing(&screen, 0.016);
        draw_shape_sfml(&window, screen);

        window.display();
    }
}
