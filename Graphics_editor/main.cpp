#include "cstdio"
#include "cstdlib"

#include "Editor/Graphical_editor_main_page.hpp"

const size_t DEFAULT_SIZE = 1500;

Graphical_editor_main_page *create_editor	();
void 						delete_editor	(Graphical_editor_main_page *editor);
void 						draw_editor		(Graphical_editor_main_page *editor);

int main()
{
	Graphical_editor_main_page *editor = create_editor();
	draw_editor(editor);
	delete_editor(editor);
}

Graphical_editor_main_page *create_editor()
{
	Graphical_editor_main_page *editor = new Graphical_editor_main_page(Radius_vector(0, 0), BLACK, DEFAULT_SIZE, DEFAULT_SIZE);

	return editor;
}

void delete_editor(Graphical_editor_main_page *editor)
{
	delete editor;
}

void draw_editor(Graphical_editor_main_page *editor)
{
	Screen_information screen(DEFAULT_SIZE, DEFAULT_SIZE);

    bool open = true;
    while(open)
    {
        screen.reset();
        
        Sfml_events result = screen.event_handler.detect_event(screen.window, screen.event);
        switch (result)
        {
        case Sfml_events::WINDOW_CLOSED:
            // printf("oh hello\n");
            screen.window.close();
            open = false;
            break;

        case Sfml_events::MOUSE_CLICKED:
        {
            Radius_vector click_place(screen.get_mouse_position());
            // while(screen.event_handler.detect_event(screen.window, screen.event) != Sfml_events::MOUSE_RELEASED)
            // {
            //     screen.sfml_update_mouse_position();
            //     click_place = Radius_vector(screen.get_mouse_position());
            //     printf("x: %lg, y: %lg\n", click_place.get_x(), click_place.get_y());

            //     printf("clicked\n");

            //     editor->on_mouse(true, click_place.get_x(), click_place.get_y()); 
            //     editor->draw(&screen);
            //     screen.window.display();
            // }
            // printf("released\n");
            editor->on_mouse(true, click_place.get_x(), click_place.get_y());

            break;
        }

        case Sfml_events::MOUSE_RELEASED:
        {
            Radius_vector click_place(screen.get_mouse_position());

            printf("released\n");

            editor->on_mouse(false, click_place.get_x(), click_place.get_y());

            break;
        }

        case Sfml_events::MOUSE_MOVED:
        {
            Radius_vector click_place(screen.get_mouse_position());
            editor->on_mouse(true, click_place.get_x(), click_place.get_y());

            break;
        }

        default:
            break;
        }

        // // user_window.tick(&screen, 0.05);
        editor->tick(&screen, 0.05);
        editor->draw(&screen);
        
        screen.sfml_update_mouse_state();

        screen.window.display();
    }
}
