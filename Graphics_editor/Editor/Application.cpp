#include "Application.hpp"

const size_t DEFAULT_SIZE = 1800;

Application *Application::app = nullptr;
Application_destroyer Application::destroyer;

Application::Application()
: graphics_wrapper(nullptr), default_main(nullptr), current_main(nullptr)
{
	graphics_wrapper = new Screen_information(DEFAULT_SIZE, DEFAULT_SIZE);

	Graphical_editor_main_page *editor = new Graphical_editor_main_page({(size_t)Vidget_type::EDITOR, Vector_ll(0, 0), nullptr, DARK_GREY, DEFAULT_SIZE, DEFAULT_SIZE});
	default_main = editor;
	current_main = default_main;
}

Application::~Application()
{
	delete graphics_wrapper;
	delete default_main;
}

Application *Application::get_app()
{
	if (app == nullptr)
	{
		app = new Application();
		destroyer.initialize(app);
	}

	return app;
}

void Application::set_default()
{
	current_main = default_main;
}

void Application::set_main(Visual_object *object)
{
	current_main = object;
}

void Application::draw()
{
	default_main->draw(graphics_wrapper);

	if (current_main != default_main)
		current_main->draw(graphics_wrapper);
}

void Application::tick()
{
    Animation_manager::get_instance()->tick(0.005);
	
	default_main->tick(graphics_wrapper, 0.05);

	if (current_main != default_main)
		current_main->tick(graphics_wrapper, 0.05);
}

void Application::launch()
{
	Vector_ll click_place(0, 0);

	bool open = true;
    while(open)
    {
        unsigned key_state = 0;
        graphics_wrapper->reset();
        
        Sfml_events result = graphics_wrapper->event_handler.detect_event(graphics_wrapper->window, graphics_wrapper->event);
        
        switch (result)
        {
        case Sfml_events::WINDOW_CLOSED:
            graphics_wrapper->window.close();
            open = false;
            break;

        case Sfml_events::MOUSE_CLICKED:
        {
            click_place = graphics_wrapper->get_mouse_position();
            current_main->on_mouse_click(true, click_place.get_x(), click_place.get_y());

            break;
        }

        case Sfml_events::MOUSE_RELEASED:
        {
            click_place = graphics_wrapper->get_mouse_position();

            current_main->on_mouse_click(false, click_place.get_x(), click_place.get_y());

            break;
        }

        case Sfml_events::MOUSE_MOVED:
        {
            Vector_ll move_place(graphics_wrapper->get_mouse_position());
            current_main->on_mouse_move(click_place, move_place);
            click_place = move_place;

            break;
        }

        case Sfml_events::KEY_U:
            key_state |= (unsigned)Key_state::KEY_U;
            current_main->on_key_pressed(key_state);

            break;

        case Sfml_events::KEY_R:
            key_state |= (unsigned)Key_state::KEY_R;
            current_main->on_key_pressed(key_state);

            break;

        case Sfml_events::KEY_G:
            key_state |= (unsigned)Key_state::KEY_G;
            current_main->on_key_pressed(key_state);

            break;

        case Sfml_events::KEY_B:
            key_state |= (unsigned)Key_state::KEY_B;
            
            current_main->on_key_pressed(key_state);

            break;

        default:
            break;
        }

        tick();
        draw();
        
        graphics_wrapper->sfml_update_mouse_state();

        graphics_wrapper->window.display();
    }
}


Application_destroyer::~Application_destroyer() 
{ 
	delete app; 
}

void Application_destroyer::initialize(Application *par_app) 
{ 
	app = par_app; 
}
