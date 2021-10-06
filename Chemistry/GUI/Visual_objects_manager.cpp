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
	// size_t manager_width = par_width < DEFAULT_SHAPE_MANAGER_WIDTH? par_width : DEFAULT_SHAPE_MANAGER_WIDTH;
	// size_t manager_height = par_width < DEFAULT_SHAPE_MANAGER_HEIGHT? par_height : DEFAULT_SHAPE_MANAGER_HEIGHT;
	manager = new Shape_manager(DEFAULT_SHAPE_MANAGER_POS, BLACK, DEFAULT_SHAPE_MANAGER_WIDTH, DEFAULT_SHAPE_MANAGER_HEIGHT);
   
    Add_molecula_delegate *molecula_delegate = new Add_molecula_delegate(manager);
    Button *add_molecula = new Button(molecula_delegate, 
    								  DEFAULT_ADD_MOLECULA_TEXT, 
    								  Radius_vector(DEFAULT_SHAPE_MANAGER_POS + Radius_vector(DEFAULT_SHAPE_MANAGER_WIDTH, 0.0)), 
    								  DEFAULT_MOLECULA_COLOR, 
    								  DEFAULT_BUTTON_WIDTH, 
    								  DEFAULT_BUTTON_HEIGHT);

    Add_rectangle_delegate *rectangle_delegate = new Add_rectangle_delegate(manager);
    Button *add_rectangle = new Button(rectangle_delegate, 
    								   DEFAULT_ADD_RECTANGLE_TEXT, 
    								   Radius_vector(DEFAULT_SHAPE_MANAGER_POS + Radius_vector(DEFAULT_SHAPE_MANAGER_WIDTH, 
    								   DEFAULT_BUTTON_HEIGHT * 2)), 
    								   DEFAULT_RECTANGLE_COLOR, 
    								   DEFAULT_BUTTON_WIDTH, 
    								   DEFAULT_BUTTON_HEIGHT);
    
    Amounts_graph *graph = new Amounts_graph(manager, Radius_vector(DEFAULT_SHAPE_MANAGER_POS + Radius_vector(0, DEFAULT_SHAPE_MANAGER_HEIGHT)), BLACK, DEFAULT_AMOUNTS_GRAPH_WIDTH, DEFAULT_AMOUNTS_GRAPH_HEIGHT);
    graph->set_shape_color(Shape_types::MOLECULA, DEFAULT_MOLECULA_COLOR);
    graph->set_shape_color(Shape_types::RECTANGLE, DEFAULT_RECTANGLE_COLOR);
    
    add_visual_object(manager);
    add_visual_object(add_molecula);
    add_visual_object(add_rectangle);
    add_visual_object(graph);
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
