#ifndef MOLECULA_MANAGER
#define MOLECULA_MANAGER

#include "../Shapes_interactions/Collisions_detections.hpp"
#include "../Shapes_interactions/Collisions_reactions.hpp"
#include "../Shapes_interactions/Shapes_set.hpp"

#include "../Shape_base/Shape.hpp"
#include "../simple_list/simple_list.hpp" // <not in project>

#include "../math_structures/math_functions.hpp"

// #include "Shapes_set.hpp"

void position_setter(Shape *changable, const Radius_vector &new_vector);
void velocity_setter(Shape *changable, const Radius_vector &new_vector);

class Shape_manager // <no realization>
{
private:
	List<Shape*> shapes;
	
public:
	Shape_manager(const size_t par_shapes_amount);
	Shape_manager(const Shape_manager &other) = delete;
	~Shape_manager() = default;

	void add_shape(Shape *par_shape);

	List<Shape*> *get_shapes() { return &shapes; }
	size_t get_shapes_amount() { return shapes.get_length(); }

	void control_physics_and_drawing(Screen_information *screen, const double delta_time);

	void draw_everything(Screen_information *screen);

	void tick(Screen_information *screen, const double delta_time);
	void set_vectors(const Radius_vector *new_vectors, void (*setter)(Shape *changable, const Radius_vector &new_vector));

	Wall_type check_the_bounds(Screen_information *screen, const Shape *shape, const Radius_vector &next_position);
	void bounds_collision_reaction(Screen_information *screen, Shape *shape, Radius_vector *par_next_position, Wall_type wall_type);

	void count_physics();
	double count_distance(const Shape &first, const Shape &second);

	bool collision_detection(const Shape *first, const Shape *second);
	void collision_reaction(Shape *first, Shape *second);

	// void update_velocitys();
};

// void molecula_molecula_collision_reaction(Shape_manager *engine, const Shape *par_first, const Shape *par_second);
// void molecula_rectangle_collision_reaction(Shape_manager *engine, const Shape *par_first, const Shape *par_second);
// void rectangle_rectangle_collision_reaction(Shape_manager *engine, const Shape *par_first, const Shape *par_second);

// typedef void (*reaction_function)(Shape_manager *engine, const Shape *par_first, const Shape *par_second);

// extern reaction_function reaction_functions[shape_types_amount * shape_types_amount];

#endif // MOLECULA_MANAGER
