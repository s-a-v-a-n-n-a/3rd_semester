#include "cstdio"
#include "cstdlib"

#include "Editor/Graphical_editor_main_page.hpp"
// #include "Editor/Application.hpp"

const size_t DEFAULT_SIZE = 1800;

Graphical_editor_main_page *create_editor	();
void 						delete_editor	(Graphical_editor_main_page *editor);
void 						draw_editor		(Graphical_editor_main_page *editor);

int main()
{
	// Application::get_app()->launch();
    Graphical_editor_main_page *editor = create_editor();
	draw_editor(editor);
	delete_editor(editor);
}

Graphical_editor_main_page *create_editor()
{
	Graphical_editor_main_page *editor = new Graphical_editor_main_page({(size_t)Vidget_type::EDITOR, Vector_ll(0, 0), nullptr, DARK_GREY, DEFAULT_SIZE, DEFAULT_SIZE});

	return editor;
}

void delete_editor(Graphical_editor_main_page *editor)
{
	delete editor;
}

Vector_ll click_place(0, 0);

// maybe class Application's method
// it may can also capture mouse
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
            screen.window.close();
            open = false;
            break;

        case Sfml_events::MOUSE_CLICKED:
        {
            click_place = screen.get_mouse_position();
            editor->on_mouse_click(true, click_place.get_x(), click_place.get_y());

            break;
        }

        case Sfml_events::MOUSE_RELEASED:
        {
            click_place = screen.get_mouse_position();

            editor->on_mouse_click(false, click_place.get_x(), click_place.get_y());

            break;
        }

        case Sfml_events::MOUSE_MOVED:
        {
            Vector_ll move_place(screen.get_mouse_position());
            // move_place.set_y(screen.get_height() - move_place.get_y());
            // click_place.set_y(screen.get_height() - click_place.get_y());
            editor->on_mouse_move(click_place, move_place);
            click_place = move_place;

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

        Animation_manager::get_instance()->tick(0.005);
        editor->tick(&screen, 0.005);
        editor->draw(&screen);
        // Animation_manager::get_instance()->draw(&screen);
        
        screen.sfml_update_mouse_state();

        screen.window.display();
    }
}
