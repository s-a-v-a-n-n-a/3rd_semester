#include "Graphical_editor_main_page.hpp"

const size_t DEFAULT_CANVAS_SIZE = 1200;

const size_t DEFAULT_CANVAS_POS_X = 400;
const size_t DEFAULT_CANVAS_POS_Y = 400;

const size_t DEFAULT_COLOR_VIDGET_WIDTH = MAX_COLOR_VALUE + 20;
const size_t DEFAULT_COLOR_VIDGET_HEIGHT = MAX_COLOR_VALUE + 20 + 90; //  + DEFAULT_BUTTON_HEIGHT
const size_t DEFAULT_COLOR_VIDGET_POS_X = 0;
const size_t DEFAULT_COLOR_VIDGET_POS_Y = 200;

const size_t DEFAULT_SIZE_VIDGET_POS_X = 0;
const size_t DEFAULT_SIZE_VIDGET_POS_Y = 800;

const size_t DEFAULT_BUTTON_WIDTH = 200;

const size_t DEFAULT_TEXT_OFFSET = 20;

const char CANVAS_TEXT[] = " Canvas ";
const char NEW_CANVAS_TEXT[] = " New canvas ";
const char COLOR_TEXT[] = " Color ";
const char SIZE_TEXT[] = " Size ";

Graphical_editor_main_page::Graphical_editor_main_page(const size_t par_type, const Vector_ll &par_position, const Color &par_color, const size_t par_width, const size_t par_height)
: Visual_object(par_type, par_position, par_color, par_width, par_height), pencil()
{
	Button_manager *panel = new Button_manager((size_t)Vidget_type::BUTTON_MANAGER, par_position, GREY, par_width, INCREASED_BUTTON_HEIGHT);

	Canvas_manager_manager *canvas = new Canvas_manager_manager((size_t)Vidget_type::CANVAS_MANAGER_MANAGER, par_position + Vector_ll(DEFAULT_CANVAS_POS_X, DEFAULT_CANVAS_POS_Y), TRANSPARENT, DEFAULT_CANVAS_SIZE, DEFAULT_CANVAS_SIZE + DEFAULT_BUTTON_HEIGHT, &pencil);

	Full_texture *tools_background = new Full_texture(WINDOW_BACKGROUND, DEFAULT_COLOR_VIDGET_WIDTH, DEFAULT_COLOR_VIDGET_HEIGHT);
	Full_texture *brushes_background = new Full_texture(WINDOW_BACKGROUND, THICK_PALETTE_WIDTH, THICK_PALETTE_HEIGHT);

	// Full_texture *tools_texture = new Full_texture(TOOLS_BACKGROUND_TEXTURE);
	// Full_texture *brushes_texture = new Full_texture(BRUSHES_BACKGROUND_TEXTURE);
	Tools_vidget *tools_vidget = new Tools_vidget((size_t)Vidget_type::PALETTE, par_position + Vector_ll(DEFAULT_COLOR_VIDGET_POS_X, DEFAULT_COLOR_VIDGET_POS_Y), tools_background, DEFAULT_COLOR_VIDGET_WIDTH, DEFAULT_COLOR_VIDGET_HEIGHT, &pencil);
	Brush_size_manager *brushes_vidget = new Brush_size_manager((size_t)Vidget_type::PALETTE, par_position + Vector_ll(DEFAULT_SIZE_VIDGET_POS_X, DEFAULT_SIZE_VIDGET_POS_Y), brushes_background, THICK_PALETTE_WIDTH, THICK_PALETTE_HEIGHT, &pencil);

	size_t current_button_size = get_text_length(GHOST_TYPE, CANVAS_TEXT, INCREASED_BUTTON_HEIGHT / 2);

	Animating_texture *button_texture = new Animating_texture(SIMPLE_BUTTON, current_button_size + DEFAULT_TEXT_OFFSET * 2, INCREASED_BUTTON_HEIGHT);
	button_texture->set_move_texture(SIMPLE_BUTTON_MOVE);

	// Restore_interactive_delegate *canvas_restore = new Restore_interactive_delegate(canvas, NULL);
	Animating_restore_delegate *canvas_restore = new Animating_restore_delegate(canvas, NULL);
    Button *canvas_restore_button = panel->add_button(canvas_restore, CANVAS_TEXT, button_texture, current_button_size + DEFAULT_TEXT_OFFSET * 2, INCREASED_BUTTON_HEIGHT);
    canvas_restore->set_animating(canvas_restore_button);

    current_button_size = get_text_length(GHOST_TYPE, NEW_CANVAS_TEXT, INCREASED_BUTTON_HEIGHT / 2);

    Animating_texture *canvas_create_texture = new Animating_texture(SIMPLE_BUTTON, current_button_size + DEFAULT_TEXT_OFFSET * 2, INCREASED_BUTTON_HEIGHT);
	canvas_create_texture->set_move_texture(SIMPLE_BUTTON_MOVE);

    // Interactive_create_canvas *canvas_creator = new Interactive_create_canvas(canvas, NULL);
    Animating_create_canvas *canvas_creator = new Animating_create_canvas(canvas, NULL);
	Button *canvas_controller = panel->add_button(canvas_creator, NEW_CANVAS_TEXT, canvas_create_texture, current_button_size + DEFAULT_TEXT_OFFSET * 2, INCREASED_BUTTON_HEIGHT);
	canvas_creator->set_animating(canvas_controller);

    current_button_size = get_text_length(GHOST_TYPE, COLOR_TEXT, INCREASED_BUTTON_HEIGHT / 2);

	Animating_texture *tools_texture = new Animating_texture(SIMPLE_BUTTON, current_button_size + DEFAULT_TEXT_OFFSET * 2, INCREASED_BUTTON_HEIGHT);
	tools_texture->set_move_texture(SIMPLE_BUTTON_MOVE);

	// Restore_interactive_delegate *tools_restore = new Restore_interactive_delegate(tools_vidget, NULL);
	Animating_restore_delegate *tools_restore = new Animating_restore_delegate(canvas, NULL);
    Button *tools_restore_button = panel->add_button(tools_restore, COLOR_TEXT, tools_texture, current_button_size + DEFAULT_TEXT_OFFSET * 2, INCREASED_BUTTON_HEIGHT);
    tools_restore->set_animating(tools_restore_button);

    current_button_size = get_text_length(GHOST_TYPE, SIZE_TEXT, INCREASED_BUTTON_HEIGHT / 2);

    Animating_texture *brushes_texture = new Animating_texture(SIMPLE_BUTTON, current_button_size + DEFAULT_TEXT_OFFSET * 2, INCREASED_BUTTON_HEIGHT);
	brushes_texture->set_move_texture(SIMPLE_BUTTON_MOVE);

    // Restore_interactive_delegate *brushes_restore = new Restore_interactive_delegate(brushes_vidget, NULL);
	Animating_restore_delegate *brushes_restore = new Animating_restore_delegate(canvas, NULL);
    Button *brushes_restore_button = panel->add_button(brushes_restore, SIZE_TEXT, brushes_texture, current_button_size + DEFAULT_TEXT_OFFSET * 2, INCREASED_BUTTON_HEIGHT);
    brushes_restore->set_animating(brushes_restore_button);

    // test
    Full_texture *test_texture = new Full_texture(TEST_WINDOW, 300, 300);
    Test_button *test_button = new Test_button((size_t)Vidget_type::BUTTON, par_position + Vector_ll(0, 1000), test_texture, 300, 300, NULL, "");
    Drag_and_drop_delegate *test_dnd = new Drag_and_drop_delegate(test_button);
    test_button->set_delegate(test_dnd); 

	add_visual_object(panel);
	add_visual_object(tools_vidget);
	add_visual_object(brushes_vidget);
	add_visual_object(canvas);

	// test
	add_visual_object(test_button);

	set_active(canvas);
}

Graphical_editor_main_page::Graphical_editor_main_page(const size_t par_type, const Vector_ll &par_position, Texture *texture, const size_t par_width, const size_t par_height)
: Visual_object(par_type, par_position, texture, par_width, par_height), pencil()
{
	Button_manager *panel = new Button_manager((size_t)Vidget_type::BUTTON_MANAGER, par_position, GREY, texture->get_width(), INCREASED_BUTTON_HEIGHT);

	Canvas_manager_manager *canvas = new Canvas_manager_manager((size_t)Vidget_type::CANVAS_MANAGER_MANAGER, par_position + Vector_ll(DEFAULT_CANVAS_POS_X, DEFAULT_CANVAS_POS_Y), MEDIUM_GREY, DEFAULT_CANVAS_SIZE, DEFAULT_CANVAS_SIZE, &pencil);

	// Full_texture *tools_texture = new Full_texture(TOOLS_BACKGROUND_TEXTURE);
	// Full_texture *brushes_texture = new Full_texture(BRUSHES_BACKGROUND_TEXTURE);
	Full_texture *tools_background = new Full_texture(WINDOW_BACKGROUND, DEFAULT_COLOR_VIDGET_WIDTH, DEFAULT_COLOR_VIDGET_HEIGHT);
	Full_texture *brushes_background = new Full_texture(WINDOW_BACKGROUND, THICK_PALETTE_WIDTH, THICK_PALETTE_HEIGHT);
	
	Tools_vidget *tools_vidget = new Tools_vidget((size_t)Vidget_type::PALETTE, par_position + Vector_ll(DEFAULT_COLOR_VIDGET_POS_X, DEFAULT_COLOR_VIDGET_POS_Y), tools_background, 0, 0, &pencil);
	Brush_size_manager *brushes_vidget = new Brush_size_manager((size_t)Vidget_type::PALETTE, par_position + Vector_ll(DEFAULT_SIZE_VIDGET_POS_X, DEFAULT_SIZE_VIDGET_POS_Y), brushes_background, 0, 0, &pencil);

	Restore_delegate *canvas_restore = new Restore_delegate(canvas);
    panel->add_button(canvas_restore, CANVAS_TEXT, WHITE, INCREASED_BUTTON_HEIGHT, INCREASED_BUTTON_HEIGHT);

    Create_canvas *canvas_creator = new Create_canvas(canvas);
	panel->add_button(canvas_creator, NEW_CANVAS_TEXT, WHITE, INCREASED_BUTTON_HEIGHT, INCREASED_BUTTON_HEIGHT);

	Restore_delegate *tools_restore = new Restore_delegate(tools_vidget);
    panel->add_button(tools_restore, COLOR_TEXT, WHITE, INCREASED_BUTTON_HEIGHT, INCREASED_BUTTON_HEIGHT);

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
