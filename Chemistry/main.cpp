#include <cstdio>
#include <cstdlib>
#include <ctime>

#include <SFML/Graphics.hpp>

#include "Shapes_interactions/Shapes_set.hpp"

#include "sfml_drawing/screen_functions.hpp"
#include "sfml_drawing/Event_handler.hpp"

#include "Shape_manager/Shape_manager.hpp"

#include "GUI/Visual_objects_manager.hpp"
#include "GUI/Button.hpp"

void draw_world();
void generate_random_shapes(Shape_manager *world, const Radius_vector &left_high, const Radius_vector &right_low);

int main()
{
	draw_world();

	return 0;
}

void draw_world()
{
	srand(time(0));

    Screen_information screen(1000, 1000);

    Visual_objects_manager user_window(Radius_vector(0, 0), BLACK, 1000, 1000);
    Shape_manager *world = user_window.get_manager();

    generate_random_shapes(world, world->get_position(), Radius_vector(world->get_width(), world->get_height()));

    bool open = true;
    while(open)
    {
        screen.reset();
        
        Sfml_events result = screen.event_handler.detect_event(screen.window, screen.event);
        switch (result)
        {
        case Sfml_events::WINDOW_CLOSED:
            screen.window.close();
            open = false;
            break;

        case Sfml_events::MOUSE_CLICKED:
        {
            Radius_vector click_place(screen.get_mouse_position());
            user_window.check_click(click_place.get_x(), click_place.get_y());
            break;
        }

        case Sfml_events::MOUSE_RELEASED:
            break;

        default:
            break;
        }

        user_window.tick(&screen, 0.05);
        user_window.draw(&screen);
        
        screen.sfml_update_mouse_state();

        screen.window.display();
    }
}

void generate_random_shapes(Shape_manager *world, const Radius_vector &left_high, const Radius_vector &right_low)
{
    for (int i = 0; i < 5; ++i)
    {
        size_t type = rand()%2;

        int size = rand() % 50 + 1;
        int x_dir = rand()%20 - 10;
        int y_dir = rand()%20 - 10;

        int x_pos = rand()%((size_t)(right_low - left_high).get_x() - size * 2) + size + left_high.get_x();
        int y_pos = rand()%((size_t)(right_low - left_high).get_y() - size * 2) + size + left_high.get_y();

        if (type == (size_t)Shape_types::MOLECULA)
        {
            Molecula *shape = new Molecula(size, (size_t)Shape_types::MOLECULA, Radius_vector(x_pos, y_pos), Radius_vector(x_dir, y_dir), 1.0);
            (*world).add_shape(shape);
        }
        else
        {
            Rectangle *shape = new Rectangle(size * 2, size * 2, (size_t)Shape_types::RECTANGLE, Radius_vector(x_pos, y_pos), Radius_vector(x_dir, y_dir), 1.0);
            (*world).add_shape(shape);
        }
    }
}

