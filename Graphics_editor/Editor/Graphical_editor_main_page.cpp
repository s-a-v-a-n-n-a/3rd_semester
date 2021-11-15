#include "Graphical_editor_main_page.hpp"

const size_t DEFAULT_CANVAS_SIZE = 300;

const size_t DEFAULT_CANVAS_POS_X = 400;
const size_t DEFAULT_CANVAS_POS_Y = 400;

const size_t DEFAULT_COLOR_VIDGET_WIDTH = MAX_COLOR_VALUE + 20;
const size_t DEFAULT_COLOR_VIDGET_HEIGHT = MAX_COLOR_VALUE + 20 + 90; //  + DEFAULT_BUTTON_HEIGHT
const size_t DEFAULT_COLOR_VIDGET_POS_X = 0;
const size_t DEFAULT_COLOR_VIDGET_POS_Y = 100;

const size_t DEFAULT_SIZE_VIDGET_POS_X = 0;
const size_t DEFAULT_SIZE_VIDGET_POS_Y = 400;

const size_t DEFAULT_BUTTON_WIDTH = 200;

const size_t DEFAULT_TEXT_OFFSET = 20;

const char CANVAS_TEXT[]     = " Canvas ";
const char NEW_CANVAS_TEXT[] = " New canvas ";
const char COLOR_TEXT[]      = " Color ";
const char SIZE_TEXT[]       = " Size ";
const char SPLINE_TEXT[]     = " SPline ";

Graphical_editor_main_page::Graphical_editor_main_page(const Visual_object::Config &par_base)
: Visual_object(par_base), pencil()
{
	Vector_ll par_position = get_position();
	size_t par_width = get_width();

	Button_manager *panel = create_button_panel(par_position, par_width, INCREASED_BUTTON_HEIGHT);
	
	Canvas_manager_manager *canvas = create_canvas_manager(par_position + Vector_ll(DEFAULT_CANVAS_POS_X, DEFAULT_CANVAS_POS_Y), DEFAULT_CANVAS_SIZE, DEFAULT_CANVAS_SIZE + DEFAULT_BUTTON_HEIGHT);
	// canvas->set_visible(false);

	Color_selection_window *tools_vidget = create_color_vidget(par_position + Vector_ll(DEFAULT_COLOR_VIDGET_POS_X, DEFAULT_COLOR_VIDGET_POS_Y), DEFAULT_COLOR_VIDGET_WIDTH, DEFAULT_COLOR_VIDGET_HEIGHT);
	tools_vidget->set_visible(false);
	tools_vidget->set_reactive(false);

	Brush_size_selection_window *brushes_vidget = create_size_vidget(par_position + Vector_ll(DEFAULT_SIZE_VIDGET_POS_X, DEFAULT_SIZE_VIDGET_POS_Y), THICK_PALETTE_WIDTH, THICK_PALETTE_HEIGHT);
	brushes_vidget->set_visible(false);
	brushes_vidget->set_reactive(false);

    Effects_window *spline = create_effects_window(par_position + Vector_ll(0, 700), 400, 400 + DEFAULT_BUTTON_HEIGHT, canvas->get_active_canvas());
	
	size_t current_button_size = get_text_length(GHOST_TYPE, CANVAS_TEXT, INCREASED_BUTTON_HEIGHT / 2);
	create_restore_button(panel, canvas, CANVAS_TEXT, current_button_size + DEFAULT_TEXT_OFFSET * 2, INCREASED_BUTTON_HEIGHT);

    current_button_size = get_text_length(GHOST_TYPE, NEW_CANVAS_TEXT, INCREASED_BUTTON_HEIGHT / 2);
	create_canvas_creator(panel, canvas, NEW_CANVAS_TEXT, current_button_size + DEFAULT_TEXT_OFFSET * 2, INCREASED_BUTTON_HEIGHT);

    current_button_size = get_text_length(GHOST_TYPE, COLOR_TEXT, INCREASED_BUTTON_HEIGHT / 2);
	create_restore_button(panel, tools_vidget, COLOR_TEXT, current_button_size + DEFAULT_TEXT_OFFSET * 2, INCREASED_BUTTON_HEIGHT);

    current_button_size = get_text_length(GHOST_TYPE, SIZE_TEXT, INCREASED_BUTTON_HEIGHT / 2);
	create_restore_button(panel, brushes_vidget, SIZE_TEXT, current_button_size + DEFAULT_TEXT_OFFSET * 2, INCREASED_BUTTON_HEIGHT);

    current_button_size = get_text_length(GHOST_TYPE, SPLINE_TEXT, INCREASED_BUTTON_HEIGHT / 2);
	create_restore_button(panel, spline, SPLINE_TEXT, current_button_size + DEFAULT_TEXT_OFFSET * 2, INCREASED_BUTTON_HEIGHT);

    // test
    // create_test_button(par_position + Vector_ll(0, 1000), "", 300, 300);

	set_active(canvas);
}

Effects_window *Graphical_editor_main_page::create_effects_window(const Vector_ll &position, const size_t width, const size_t height, Canvas *active_canvas)
{
	Full_texture *spline_background = Resources::get_instance()->create_texture(WINDOW_BACKGROUND, width, height);// new Full_texture(WINDOW_BACKGROUND, DEFAULT_COLOR_VIDGET_WIDTH, DEFAULT_COLOR_VIDGET_HEIGHT);

	Effects_window *spline = new Effects_window({(size_t)Vidget_type::EFFECTS_WINDOW, position, spline_background, TRANSPARENT, width, height}, active_canvas);
	add_visual_object(spline);

	return spline;
}

Button_manager *Graphical_editor_main_page::create_button_panel(const Vector_ll &position, const size_t width, const size_t height)
{
	Visual_object::Config panel_base = { (size_t)Vidget_type::BUTTON_MANAGER, position, nullptr, GREY, width, height };
	Button_manager *panel = new Button_manager(panel_base);
	add_visual_object(panel);

	return panel;
}

Canvas_manager_manager *Graphical_editor_main_page::create_canvas_manager(const Vector_ll &position, const size_t width, const size_t height)
{
	Canvas_manager_manager *canvas = new Canvas_manager_manager({(size_t)Vidget_type::CANVAS_MANAGER_MANAGER, position, nullptr, TRANSPARENT, width, height}, &pencil);
	add_visual_object(canvas);

	return canvas;
}

Color_selection_window *Graphical_editor_main_page::create_color_vidget(const Vector_ll &position, const size_t width, const size_t height)
{
	Full_texture *tools_background = Resources::get_instance()->create_texture(WINDOW_BACKGROUND, width, height);// new Full_texture(WINDOW_BACKGROUND, DEFAULT_COLOR_VIDGET_WIDTH, DEFAULT_COLOR_VIDGET_HEIGHT);
	
	Color_selection_window *tools_vidget = new Color_selection_window({(size_t)Vidget_type::PALETTE, position, tools_background, TRANSPARENT, width, height}, &pencil);
	add_visual_object(tools_vidget);

	return tools_vidget;
}

Brush_size_selection_window *Graphical_editor_main_page::create_size_vidget(const Vector_ll &position, const size_t width, const size_t height)
{
	// Full_texture *tools_background = Resources::get_instance()->create_texture(WINDOW_BACKGROUND, width, height);// new Full_texture(WINDOW_BACKGROUND, DEFAULT_COLOR_VIDGET_WIDTH, DEFAULT_COLOR_VIDGET_HEIGHT);
	Full_texture *brushes_background = Resources::get_instance()->create_texture(WINDOW_BACKGROUND, width, height);// new Full_texture(WINDOW_BACKGROUND, THICK_PALETTE_WIDTH, THICK_PALETTE_HEIGHT);
	
	Brush_size_selection_window *tools_vidget = new Brush_size_selection_window({(size_t)Vidget_type::PALETTE, position, brushes_background, TRANSPARENT, width, height}, &pencil);
	add_visual_object(tools_vidget);

	return tools_vidget;
}

Button *Graphical_editor_main_page::create_restore_button(Button_manager *panel, Visual_object *to_restore, const char *text, const size_t width, const size_t height)
{
	Animating_texture *texture = Resources::get_instance()->create_texture(SIMPLE_BUTTON, width, height, SIMPLE_BUTTON_MOVE, nullptr);

	Animating_restore_delegate *restore = new Animating_restore_delegate(to_restore, NULL);
    
    Button *restore_button = panel->add_button(restore, text, texture, width, height);
    if (restore_button)
    	restore->set_animating(restore_button);
    else
    	delete restore;

    return restore_button;
}

Button *Graphical_editor_main_page::create_canvas_creator(Button_manager *panel, Canvas_manager_manager *canvas_manager, const char *text, const size_t width, const size_t height)
{
	Animating_texture *canvas_create_texture = Resources::get_instance()->create_texture(SIMPLE_BUTTON, width, height, SIMPLE_BUTTON_MOVE, nullptr);

    Animating_create_canvas *canvas_creator = new Animating_create_canvas(canvas_manager, NULL);
	
	Button *canvas_controller = panel->add_button(canvas_creator, text, canvas_create_texture, width, height);
	if (canvas_controller)
		canvas_creator->set_animating(canvas_controller);
	else
		delete canvas_creator;

	return canvas_controller;
}

// test
Test_button *Graphical_editor_main_page::create_test_button(const Vector_ll &position, const char *text, const size_t width, const size_t height)
{
	Full_texture *test_texture = Resources::get_instance()->create_texture(TEST_WINDOW, width, height);// new Full_texture(TEST_WINDOW, 300, 300);
    
    Test_button *test_button = new Test_button({(size_t)Vidget_type::BUTTON, position, test_texture, TRANSPARENT, width, height}, NULL, text);
    Drag_and_drop_delegate *test_dnd = new Drag_and_drop_delegate(test_button);
    test_button->set_delegate(test_dnd); 

	add_visual_object(test_button);

	return test_button;
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
