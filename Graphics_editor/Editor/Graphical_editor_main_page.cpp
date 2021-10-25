#include "Graphical_editor_main_page.hpp"

Graphical_editor_main_page::Graphical_editor_main_page(const size_t par_type, const Vector_ll &par_position, const Color &par_color, const size_t par_width, const size_t par_height)
: Visual_object(par_type, par_position, par_color, par_width, par_height), pencil()
{
	// create Edtor_control_panel
	// ----------------------------------------------------------------------
	Button_manager *panel = new Button_manager((size_t)Vidget_type::BUTTON_MANAGER, par_position, GREY, par_width, DEFAULT_BUTTON_HEIGHT);

	Canvas_manager_manager *canvas = new Canvas_manager_manager((size_t)Vidget_type::CANVAS_MANAGER_MANAGER, par_position + Vector_ll(400, 400), MEDIUM_GREY, 1200, 1200, &pencil);

	Full_texture *texture = new Full_texture(TOOLS_BACKGROUND_TEXTURE);
	Tools_vidget *tools_vidget = new Tools_vidget((size_t)Vidget_type::PALETTE, par_position + Vector_ll(0, 200), texture, &pencil);

	Restore_interactive_delegate *canvas_restore = new Restore_interactive_delegate(canvas, NULL);
    Button *canvas_restore_button = panel->add_button(canvas_restore, " Canvas ", WHITE, 150);
    canvas_restore->set_interactive(canvas_restore_button);

    Interactive_create_canvas *canvas_creator = new Interactive_create_canvas(canvas, NULL);
	Button *canvas_controller = panel->add_button(canvas_creator, " New canvas ", WHITE, 200);
	canvas_creator->set_interactive(canvas_controller);

	Restore_interactive_delegate *tools_restore = new Restore_interactive_delegate(tools_vidget, NULL);
    Button *tools_restore_button = panel->add_button(tools_restore, " Tools ", WHITE, 150);
    tools_restore->set_interactive(tools_restore_button);

	add_visual_object(panel);
	add_visual_object(tools_vidget);
	add_visual_object(canvas);

	set_active(canvas);
}

Graphical_editor_main_page::Graphical_editor_main_page(const size_t par_type, const Vector_ll &par_position, Texture *texture)
: Visual_object(par_type, par_position, texture), pencil()
{
	Button_manager *panel = new Button_manager((size_t)Vidget_type::BUTTON_MANAGER, par_position, GREY, get_width(), DEFAULT_BUTTON_HEIGHT);

	Canvas_manager_manager *canvas = new Canvas_manager_manager((size_t)Vidget_type::CANVAS_MANAGER_MANAGER, par_position + Vector_ll(400.0, 400.0), WHITE, 1000, 1000, &pencil);

	Tools_vidget *tools_vidget = new Tools_vidget((size_t)Vidget_type::PALETTE, par_position + Vector_ll(0, 200), WHITE, 300, 700, &pencil);	

	Restore_delegate *canvas_restore = new Restore_delegate(canvas);
    panel->add_button(canvas_restore, "Canvas", WHITE, 150);

    Create_canvas *canvas_creator = new Create_canvas(canvas);
	panel->add_button(canvas_creator, "New canvas", WHITE, 150);

	Restore_delegate *tools_restore = new Restore_delegate(tools_vidget);
    panel->add_button(tools_restore, "Tools", WHITE, 150);

	add_visual_object(panel);
	add_visual_object(tools_vidget);
	add_visual_object(canvas);

	set_active(canvas);
}

Graphical_editor_main_page::~Graphical_editor_main_page()
{
	Visual_object **objects = get_objects()->get_array();
	size_t objects_amount = get_objects()->get_length();

	for (size_t i = 0; i < objects_amount; ++i)
	{
		delete objects[i];
	}
}

bool Graphical_editor_main_page::on_key_pressed(const unsigned key_mask)
{
	if (key_mask == (unsigned)Key_state::KEY_U)
	{
		pencil.set_color(BLACK);
		return true;
	}
	else if (key_mask == (unsigned)Key_state::KEY_R)
	{
		pencil.set_color(RED);
		return true;
	}
	else if (key_mask == (unsigned)Key_state::KEY_G)
	{
		pencil.set_color(GREEN);
		return true;
	}
	else if (key_mask == (unsigned)Key_state::KEY_B)
	{
		pencil.set_color(BLUE);
		return true;
	}

	return false;
}

// void Graphical_editor_main_page::tick(Screen_information *screen, const double delta_time)
// {
// 	assert(screen);

// 	Visual_object **objects_array = objects.get_array();
// 	size_t objects_amount = objects.get_length();

// 	for (size_t i = 0; i < objects_amount; ++i)
// 	{
// 		// printf("%d\n", objects_array[i]->get_visible());
// 		if (!objects_array[i]->get_alive())
// 		{
// 			if (objects_array[i]->get_type() == Vidget_type::CANVAS_MANAGER)
// 			{
// 				;
// 			}
// 			else
// 			{
// 				slow_delete_visual_object(i);
// 				i--;
// 				objects_amount--;
// 				continue;
// 			}
// 		}

// 		objects_array[i]->tick(screen, delta_time);
// 	}
// }
