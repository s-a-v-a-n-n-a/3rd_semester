#include <SFML/Graphics.hpp>

#include <ctime>

#include "./simple_list/simple_list.hpp"

#include "./shapes/coordinate_axes.hpp"
#include "./shapes/derived_shapes.hpp"
#include "./shapes/structures.hpp"

int main()
{
	time_t timer = 0;

    sf::RenderWindow window(sf::VideoMode(700, 700), "It works");

    System_of_axes axes_1 = {};
    axes_1.init(100, 100, -100, 100, -100, 100);
    System_of_axes axes_2 = {};
    axes_2.init(400, 100, 0, 100, -100, 100);

    Vector vector_w_arrow = {};
    vector_w_arrow.init_relative(axes_1, {200, 200}, 50, 50);
    Vector vector_w_arrow2 = {};
    vector_w_arrow2.init_relative(axes_1, {50, 200}, -100, 200);
    

    Chart chart_1 = {};
    chart_1.init(axes_1, get_ordinate_for_parabola);
    

    Chart chart_2 = {};
    chart_2.init(axes_2, get_ordinate_for_parabola);


    Work_field *work_field_1 = work_field_create(axes_1);
    work_field_1->add_shape(&vector_w_arrow);
    work_field_1->add_shape(&vector_w_arrow2);
    work_field_1->add_shape(&chart_1);

    Work_field *work_field_2 = work_field_create(axes_2);
    work_field_2->add_shape(&chart_2);
    

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

        window.display();

        if (timer == 60)
            break;
    }

    work_field_delete(work_field_1);
    work_field_delete(work_field_2);

    return 0;
}