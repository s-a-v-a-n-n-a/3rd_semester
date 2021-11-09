#include "Tab.hpp"

const size_t DEFAULT_TAB_WIDTH = 250;
const size_t DEFAULT_TAB_HEIGHT = 80;

Tab::Tab(const size_t par_type, const Vector_ll &par_position, const Color &par_color, const size_t par_width, const size_t par_height, Visual_object *par_parent)
: Visual_object(par_type, par_position, par_color, par_width, par_height)
{
	parent = par_parent;

	size_t button_width = 150;
    size_t button_height = 80;

    Canvas_keeper *keep = new Canvas_keeper(parent);
    Button *keeper = new Button((size_t)Vidget_type::BUTTON,
    							par_position, // get_position() + Vector_ll(get_objects()->get_length() * 250, 0.0), 
								WHITE, 
								button_width, 
								par_height,
								keep, 
								" Canvas ");


    Button *closing = new Button((size_t)Vidget_type::BUTTON,
    							par_position + Vector_ll(button_width, 0.0), // get_position() + Vector_ll(get_objects()->get_length() * 250 + 150, 0.0),
    							WHITE,
    							100,
    							par_height,
    							NULL,
    							"X");
    Close_delegate *close = new Close_delegate(parent);
    closing->set_delegate(close);
   

    add_visual_object(keeper);
    add_visual_object(closing);
}

Tab::Tab(const size_t par_type, const Vector_ll &par_position, Texture *par_texture, const size_t par_width, const size_t par_height, Visual_object *par_parent)
: Visual_object(par_type, par_position, par_texture, par_width, par_height)
{
    parent = par_parent;

    
    size_t button_height = 80;

    Canvas_keeper *keep = new Canvas_keeper(parent);
    size_t button_width = get_text_length(GHOST_TYPE, " Canvas ", button_height/2);
    Button *keeper = new Button((size_t)Vidget_type::BUTTON,
                                par_position + Vector_ll(30, 0), // get_position() + Vector_ll(get_objects()->get_length() * 250, 0.0), 
                                TRANSPARENT, 
                                button_width, 
                                par_height,
                                keep, 
                                " Canvas ");


    Full_texture *texture = new Full_texture(CLOSE_TEXTURE, INCREASED_BUTTON_HEIGHT, INCREASED_BUTTON_HEIGHT);
    Button *closing = new Button((size_t)Vidget_type::BUTTON,
                                par_position + Vector_ll(get_width(), 0) - Vector_ll(80, 0), // get_position() + Vector_ll(get_objects()->get_length() * 250 + 150, 0.0),
                                texture,
                                texture->get_width(), par_height,
                                NULL,
                                "");
    Close_delegate *close = new Close_delegate(parent);
    closing->set_delegate(close);
   

    add_visual_object(keeper);
    add_visual_object(closing);
}

void Tab::draw(Screen_information *screen)
{
    if (get_active_state())
    {
        Animating_texture *texture = (Animating_texture *)get_texture();
        texture->set_current_texture(texture->get_default_texture());
    }
    else
    {
        Animating_texture *texture = (Animating_texture *)get_texture();
        texture->set_current_texture(texture->get_inactive_texture());
    }

    Visual_object::draw(screen);
}
