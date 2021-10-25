#include "Graphical_editor_main_page.hpp"

const size_t DEFAULT_CANVAS_SIZE = 1200;

const size_t DEFAULT_CANVAS_POS_X = 400;
const size_t DEFAULT_CANVAS_POS_Y = 400;

const size_t DEFAULT_COLOR_VIDGET_POS_X = 0;
const size_t DEFAULT_COLOR_VIDGET_POS_Y = 200;

const size_t DEFAULT_SIZE_VIDGET_POS_X = 0;
const size_t DEFAULT_SIZE_VIDGET_POS_Y = 800;

const size_t DEFAULT_BUTTON_WIDTH = 200;

const char CANVAS_TEXT[] = " Canvas ";
const char NEW_CANVAS_TEXT[] = " New canvas ";
const char COLOR_TEXT[] = " Color ";
const char SIZE_TEXT[] = " Size ";

Graphical_editor_main_page::Graphical_editor_main_page(const size_t par_type, const Vector_ll &par_position, const Color &par_color, const size_t par_width, const size_t par_height)
: Visual_object(par_type, par_position, par_color, par_width, par_height), pencil()
{
	// create Edtor_control_panel
	// ----------------------------------------------------------------------
	Button_manager *panel = new Button_manager((size_t)Vidget_type::BUTTON_MANAGER, par_position, GREY, par_width, DEFAULT_BUTTON_HEIGHT);

	Canvas_manager_manager *canvas = new Canvas_manager_manager((size_t)Vidget_type::CANVAS_MANAGER_MANAGER, par_position + Vector_ll(DEFAULT_CANVAS_POS_X, DEFAULT_CANVAS_POS_Y), MEDIUM_GREY, DEFAULT_CANVAS_SIZE, DEFAULT_CANVAS_SIZE, &pencil);

	Full_texture *tools_texture = new Full_texture(TOOLS_BACKGROUND_TEXTURE);
	Full_texture *brushes_texture = new Full_texture(BRUSHES_BACKGROUND_TEXTURE);
	Tools_vidget *tools_vidget = new Tools_vidget((size_t)Vidget_type::PALETTE, par_position + Vector_ll(DEFAULT_COLOR_VIDGET_POS_X, DEFAULT_COLOR_VIDGET_POS_Y), tools_texture, &pencil);
	Brush_size_manager *brushes_vidget = new Brush_size_manager((size_t)Vidget_type::PALETTE, par_position + Vector_ll(DEFAULT_SIZE_VIDGET_POS_X, DEFAULT_SIZE_VIDGET_POS_Y), brushes_texture, &pencil);

	Restore_interactive_delegate *canvas_restore = new Restore_interactive_delegate(canvas, NULL);
    Button *canvas_restore_button = panel->add_button(canvas_restore, CANVAS_TEXT, WHITE, DEFAULT_BUTTON_WIDTH);
    canvas_restore->set_interactive(canvas_restore_button);

    Interactive_create_canvas *canvas_creator = new Interactive_create_canvas(canvas, NULL);
	Button *canvas_controller = panel->add_button(canvas_creator, NEW_CANVAS_TEXT, WHITE, DEFAULT_BUTTON_WIDTH);
	canvas_creator->set_interactive(canvas_controller);

	Restore_interactive_delegate *tools_restore = new Restore_interactive_delegate(tools_vidget, NULL);
    Button *tools_restore_button = panel->add_button(tools_restore, COLOR_TEXT, WHITE, DEFAULT_BUTTON_WIDTH);
    tools_restore->set_interactive(tools_restore_button);

    Restore_interactive_delegate *brushes_restore = new Restore_interactive_delegate(brushes_vidget, NULL);
    Button *brushes_restore_button = panel->add_button(brushes_restore, SIZE_TEXT, WHITE, DEFAULT_BUTTON_WIDTH);
    brushes_restore->set_interactive(brushes_restore_button);

	add_visual_object(panel);
	add_visual_object(tools_vidget);
	add_visual_object(brushes_vidget);
	add_visual_object(canvas);

	set_active(canvas);
}

Graphical_editor_main_page::Graphical_editor_main_page(const size_t par_type, const Vector_ll &par_position, Texture *texture)
: Visual_object(par_type, par_position, texture), pencil()
{
	Button_manager *panel = new Button_manager((size_t)Vidget_type::BUTTON_MANAGER, par_position, GREY, texture->get_width(), DEFAULT_BUTTON_HEIGHT);

	Canvas_manager_manager *canvas = new Canvas_manager_manager((size_t)Vidget_type::CANVAS_MANAGER_MANAGER, par_position + Vector_ll(DEFAULT_CANVAS_POS_X, DEFAULT_CANVAS_POS_Y), MEDIUM_GREY, DEFAULT_CANVAS_SIZE, DEFAULT_CANVAS_SIZE, &pencil);

	Full_texture *tools_texture = new Full_texture(TOOLS_BACKGROUND_TEXTURE);
	Full_texture *brushes_texture = new Full_texture(BRUSHES_BACKGROUND_TEXTURE);
	Tools_vidget *tools_vidget = new Tools_vidget((size_t)Vidget_type::PALETTE, par_position + Vector_ll(DEFAULT_COLOR_VIDGET_POS_X, DEFAULT_COLOR_VIDGET_POS_Y), tools_texture, &pencil);
	Brush_size_manager *brushes_vidget = new Brush_size_manager((size_t)Vidget_type::PALETTE, par_position + Vector_ll(DEFAULT_SIZE_VIDGET_POS_X, DEFAULT_SIZE_VIDGET_POS_Y), brushes_texture, &pencil);

	Restore_delegate *canvas_restore = new Restore_delegate(canvas);
    panel->add_button(canvas_restore, CANVAS_TEXT, WHITE, DEFAULT_BUTTON_WIDTH);

    Create_canvas *canvas_creator = new Create_canvas(canvas);
	panel->add_button(canvas_creator, NEW_CANVAS_TEXT, WHITE, DEFAULT_BUTTON_WIDTH);

	Restore_delegate *tools_restore = new Restore_delegate(tools_vidget);
    panel->add_button(tools_restore, COLOR_TEXT, WHITE, DEFAULT_BUTTON_WIDTH);

    Restore_interactive_delegate *brushes_restore = new Restore_interactive_delegate(brushes_vidget, NULL);
    Button *brushes_restore_button = panel->add_button(brushes_restore, SIZE_TEXT, WHITE, DEFAULT_BUTTON_WIDTH);
    brushes_restore->set_interactive(brushes_restore_button);

	add_visual_object(panel);
	add_visual_object(tools_vidget);
	add_visual_object(brushes_vidget);
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
