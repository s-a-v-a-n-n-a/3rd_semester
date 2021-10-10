#include "Visual_objects_manager.hpp"

const size_t DEFAULT_WIDTH  = 1000;
const size_t DEFAULT_HEIGHT = 1000;

const size_t DEFAULT_SHAPE_MANAGER_WIDTH  = 700;
const size_t DEFAULT_SHAPE_MANAGER_HEIGHT = 700;

const Radius_vector DEFAULT_SHAPE_MANAGER_POS = Radius_vector(0.0, 0.0);

const size_t DEFAULT_BUTTON_WIDTH  = 200;
const size_t DEFAULT_BUTTON_HEIGHT = 100;

extern const char DEFAULT_ADD_MOLECULA_TEXT[]  = "Add molecule";
extern const char DEFAULT_ADD_RECTANGLE_TEXT[] = "Add rectangle";

const size_t DEFAULT_AMOUNTS_GRAPH_WIDTH  = 700;
const size_t DEFAULT_AMOUNTS_GRAPH_HEIGHT = 200;

const Color DEFAULT_MOLECULA_COLOR  = MEDIUM_PURPLE;
const Color DEFAULT_RECTANGLE_COLOR = FUCHSIA;



Visual_objects_manager::Visual_objects_manager(const Radius_vector &par_position, const Color &par_color, const size_t par_width, const size_t par_height)
: Visual_object(par_position, par_color, par_width, par_height)
{
	// create Shape manager
	// ------------------------------------------------------------------------------
	size_t manager_width = par_width < DEFAULT_SHAPE_MANAGER_WIDTH? par_width / 2 : DEFAULT_SHAPE_MANAGER_WIDTH;
	size_t manager_height = par_width < DEFAULT_SHAPE_MANAGER_HEIGHT? par_height / 2 : DEFAULT_SHAPE_MANAGER_HEIGHT;
	manager = new Shape_manager(DEFAULT_SHAPE_MANAGER_POS, BLACK, manager_width, manager_height);
   
    // create 2 buttons
    // ------------------------------------------------------------------------------
	size_t button_width = par_width / 2 < DEFAULT_BUTTON_WIDTH? par_width / 2 : DEFAULT_BUTTON_WIDTH;
    size_t button_height = par_height / 2 < DEFAULT_BUTTON_HEIGHT? par_height / 2 : DEFAULT_BUTTON_HEIGHT;

    Add_molecula_delegate *molecula_delegate = new Add_molecula_delegate(manager);
    Button *add_molecula = new Button(molecula_delegate, 
    								  DEFAULT_ADD_MOLECULA_TEXT, 
    								  Radius_vector(Radius_vector(par_width, 0) - Radius_vector(button_width, 0.0)), 
    								  DEFAULT_MOLECULA_COLOR, 
    								  button_width, 
    								  button_height);

    Add_rectangle_delegate *rectangle_delegate = new Add_rectangle_delegate(manager);
    Button *add_rectangle = new Button(rectangle_delegate, 
    								   DEFAULT_ADD_RECTANGLE_TEXT, 
    								   Radius_vector(Radius_vector(par_width, 0) - Radius_vector(button_width, -2.0 * button_height)), 
    								   DEFAULT_RECTANGLE_COLOR, 
    								   button_width, 
    								   button_height);
    
    // create amounts graph
    // ------------------------------------------------------------------------------
    size_t graph_width = par_width;
    size_t graph_height = par_height < DEFAULT_AMOUNTS_GRAPH_HEIGHT? par_height / 2 : DEFAULT_AMOUNTS_GRAPH_HEIGHT;

    Amounts_graph *graph = new Amounts_graph(manager, Radius_vector(Radius_vector(0, par_height) - Radius_vector(0, graph_height)), BLACK, graph_width, graph_height);
    graph->set_shape_color(Shape_types::MOLECULA, DEFAULT_MOLECULA_COLOR);
    graph->set_shape_color(Shape_types::RECTANGLE, DEFAULT_RECTANGLE_COLOR);

    // create another button (the one that checks architecture)
    // -----------------------------------------------------------------------------
    Change_scale *change_scale = new Change_scale(graph);
    Button *change_scale_button = new Button(change_scale, 
    								  "change graph scale", 
    								  Radius_vector(Radius_vector(par_width, 0) - Radius_vector(button_width, -3.0 * button_height)), 
    								  RED, // ???????????????????????????????? 
    								  button_width, 
    								  button_height);
    
    
    // add all objects
    // ------------------------------------------------------------------------------
    add_visual_object(manager);
    add_visual_object(add_molecula);
    add_visual_object(add_rectangle);
    add_visual_object(graph);

    add_visual_object(change_scale_button);
}

Visual_objects_manager::~Visual_objects_manager()
{
	Visual_object **objects = get_objects()->get_array();
	size_t objects_amount = get_objects()->get_length();

	for (size_t i = 0; i < objects_amount; ++i)
	{
		delete objects[i];
	}
}

void Visual_objects_manager::draw(Screen_information *screen)
{
	Visual_object::draw(screen);

	size_t objects_amount = get_objects()->get_length();
	for (size_t i = 0; i < objects_amount; ++i)
	{
		(get_objects()->get_array()[i])->draw(screen);
	}
}

bool Visual_objects_manager::check_click(const double par_x, const double par_y)
{
	size_t objects_amount = get_objects()->get_length();
	if (point_inside(par_x, par_y))
	{
		for (size_t i = 0; i < objects_amount; ++i)
		{
			if ((get_objects()->get_array()[i])->check_click(par_x, par_y)) // ??????
			{
				return true;
			}
		}
	}

	return false;
}

void Visual_objects_manager::tick(Screen_information *screen, const double delta_time)
{
	size_t objects_amount = get_objects()->get_length();
	for (size_t i = 0; i < objects_amount; ++i)
	{
		(get_objects()->get_array()[i])->tick(screen, delta_time);
	}
}
