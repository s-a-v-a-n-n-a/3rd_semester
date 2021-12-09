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
    Colored_point light(Radius_vector(150, 350, 500), Radius_vector(255, 255, 102));

    Lightened_sphere test_sphere(test, Radius_vector(255.0, 192.0, 203.0), light, Radius_vector(350, 350, 500));
    
    test_sphere.draw_lambert_and_fong_in_color(&screen);

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
        
        test_sphere.draw_lambert_and_fong_in_color(&screen);
        test_sphere.move_light_in_circle();
        draw_shape_sfml(&window, screen);

        window.display();
    }

    return 0;
}
