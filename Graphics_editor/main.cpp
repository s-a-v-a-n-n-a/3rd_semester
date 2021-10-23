#include "cstdio"
#include "cstdlib"

#include "Editor/Graphical_editor_main_page.hpp"

const size_t DEFAULT_SIZE = 1800;

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
	Graphical_editor_main_page *editor = new Graphical_editor_main_page((size_t)Vidget_type::EDITOR, Radius_vector(0, 0), DARK_GREY, DEFAULT_SIZE, DEFAULT_SIZE);

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
        unsigned key_state = 0;
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
            editor->on_mouse(Mouse_state::CLICKED, click_place.get_x(), click_place.get_y());

            break;
        }

        case Sfml_events::MOUSE_RELEASED:
        {
            Radius_vector click_place(screen.get_mouse_position());

            editor->on_mouse(Mouse_state::RELEASED, click_place.get_x(), click_place.get_y());

            break;
        }

        case Sfml_events::MOUSE_MOVED:
        {
            Radius_vector click_place(screen.get_mouse_position());
            editor->on_mouse(Mouse_state::MOVED, click_place.get_x(), click_place.get_y());

            break;
        }

        case Sfml_events::KEY_U:
            key_state |= (unsigned)Key_state::KEY_U;
            editor->on_key_pressed(key_state);

            break;

        case Sfml_events::KEY_R:
            key_state |= (unsigned)Key_state::KEY_R;
            editor->on_key_pressed(key_state);

            break;

        case Sfml_events::KEY_G:
            key_state |= (unsigned)Key_state::KEY_G;
            editor->on_key_pressed(key_state);

            break;

        case Sfml_events::KEY_B:
            key_state |= (unsigned)Key_state::KEY_B;
            
            editor->on_key_pressed(key_state);

            break;

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
