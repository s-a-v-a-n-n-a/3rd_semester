#include <SFML/Graphics.hpp>

/**
 * Todo: delete magic
 * 
 * 
 */

// #include "shapes/circle.hpp"
#include "shapes/lightened_sphere.hpp"

int main()
{
    sf::RenderWindow window(sf::VideoMode(700, 700), "It works");

    Screen_information screen(700, 700);

    Circle test({150, 150}, 200);
    // test.draw_shape(&screen);

    Lightened_sphere test_sphere(test, {0, 0, 300}, {700, 700, 0});
    // test_sphere.draw_z(&screen);
    test_sphere.draw_lambert_and_fong(&screen);

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
        
        draw_shape_sfml(&window, screen);

        window.display();
    }

    return 0;
}
