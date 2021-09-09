#include <SFML/Graphics.hpp>

#include <ctime>

#include "./simple_list/simple_list.hpp"

#include "./shapes/coordinate_axes.hpp"
#include "./shapes/derived_shapes.hpp"
#include "./shapes/structures.hpp"

int main()
{

    sf::RenderWindow window(sf::VideoMode(700, 700), "It works");

    System_of_axes axes_1({100, 100}, -100, 100, -100, 100);
    System_of_axes axes_2({400, 100}, 0, 100, -100, 100);

    Vector vector_w_arrow(axes_1, {200, 200}, 50, 50);
    Vector vector_w_arrow2(axes_1, {50, 200}, -100, 200);
    

    Chart chart_1(axes_1, get_ordinate_for_parabola);
    Chart chart_2(axes_2, get_ordinate_for_parabola);


    Work_field *work_field_1 = new Work_field(axes_1); 

    work_field_1->add_shape((Shape*)&vector_w_arrow);
    work_field_1->add_shape((Shape*)&vector_w_arrow2);
    work_field_1->add_shape((Shape*)&chart_1);

    Work_field *work_field_2 = new Work_field(axes_2); 

    work_field_2->add_shape((Shape*)&chart_2);

    Vector_w_arrow vector_rotating({200, 200}, {300, 300});
    Point end = {300, 300};
    
    int i = 50;

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
        
        work_field_1->draw(&window);
        work_field_2->draw(&window);
        
        vector_rotating.set_end_point(rotate_point(vector_rotating.get_begin_point(), vector_rotating.get_end_point(), i * 180.0 / M_PI));
        vector_rotating.draw_shape(&window);   

        window.display();
    }

    delete work_field_1;
    delete work_field_2;

    return 0;
}