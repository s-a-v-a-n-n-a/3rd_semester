#include "Application.hpp"

const size_t DEFAULT_SIZE = 1800;

Application *Application::app = nullptr;
Application_destroyer Application::destroyer;

Application::Application()
: graphics_wrapper(nullptr), default_main(nullptr), current_main(nullptr), timer()
{
    graphics_wrapper = new Screen_information(DEFAULT_SIZE, DEFAULT_SIZE);

	Graphical_editor_main_page *editor = new Graphical_editor_main_page({(size_t)Vidget_type::EDITOR, Vector_ll(0, 0), nullptr, DARK_GREY, DEFAULT_SIZE, DEFAULT_SIZE});
	default_main = editor;
	current_main = default_main;

    plugins = new Plugin_manager();
}

Application::~Application()
{
	delete plugins;

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

size_t Application::get_time()
{
    return timer.get_passed_time();
}

Visual_object * Application::get_default()
{
    return default_main;
}

Visual_object * Application::get_main()
{
    return current_main;
}

void Application::set_default()
{
	current_main = default_main;
}

void Application::set_main(Visual_object *object)
{
	current_main = object;
}

void Application::add_plugin(const char *plugin_name)
{
    plugins->add_plugin(plugin_name);
}

Plugin_manager *Application::get_plugins()
{
    return plugins;
}

void Application::add_visual_object(Visual_object *object)
{
    default_main->add_visual_object(object);
}

void Application::draw()
{
	default_main->draw(graphics_wrapper);

	if (current_main != default_main)
    {
		graphics_wrapper->draw_rectangle({0, 0}, default_main->get_width(), default_main->get_height(), {100, 100, 100, 150}, {100, 100, 100, 150});
        current_main->draw(graphics_wrapper);
    }
}

void Application::tick()
{
    Animation_manager::get_instance()->tick(0.005);
	
	default_main->tick(graphics_wrapper, 0.05);

	if (current_main != default_main)
    {
		if (!(current_main->get_alive()))
        {
            delete current_main;
            set_default();
            return;
        }
        current_main->tick(graphics_wrapper, 0.05);
    }
}

void Application::launch()
{
	Vector_ll click_place(0, 0);

	bool open = true;
    while(open)
    {
        unsigned key_state = 0;
        graphics_wrapper->reset();
        
        // Sfml_events result = graphics_wrapper->event_handler.detect_event(graphics_wrapper->window, graphics_wrapper->event);
        Event result = graphics_wrapper->event_handler.detect_event(graphics_wrapper->window, graphics_wrapper->event);
        
        switch (result.type)
        {
        case Event_type::WINDOW:
            graphics_wrapper->window.close();
            open = false;
            break;

        case Event_type::MOUSE:
        {
            switch (result.event)
            {
            case (size_t)Mouse_state::CLICKED:
                click_place = graphics_wrapper->get_mouse_position();
                current_main->on_mouse_click(true, click_place.get_x(), click_place.get_y());

                break;
            
            case (size_t)Mouse_state::RELEASED:
                click_place = graphics_wrapper->get_mouse_position();
                current_main->on_mouse_click(false, click_place.get_x(), click_place.get_y());

                break;
            case (size_t)Mouse_state::MOVED:
            {
                Vector_ll move_place(graphics_wrapper->get_mouse_position());
                current_main->on_mouse_move(click_place, move_place);
                click_place = move_place;

                break;
            }
            default:
                break;
            }
            
            break;
        }
        case Event_type::KEYBOARD:
            switch (result.event)
            {
            case (size_t)Key_state::PRESSED:
                key_state |= result.sender;
                current_main->on_key_pressed(true, key_state);

                break;

            case (size_t)Key_state::RELEASED:
                key_state |= result.sender;
                current_main->on_key_pressed(false, key_state);

                break;

            default:
                break;
            }

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
