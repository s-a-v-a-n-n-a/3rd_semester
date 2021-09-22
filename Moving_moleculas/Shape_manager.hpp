#ifndef MOLECULA_MANAGER
#define MOLECULA_MANAGER

#include "Molecula.hpp"
#include "simple_list/simple_list.hpp" // <not in project>

#include "math_structures/math_functions.hpp"

void position_setter(Shape *changable, const Radius_vector &new_vector);
void direction_setter(Shape *changable, const Radius_vector &new_vector);

class Shape_manager // <no realization>
{
private:
	List<Shape*> shapes;
	
public:
	Shape_manager(const size_t par_shapes_amount);
	Shape_manager(const Shape_manager &other) = delete;
	~Shape_manager() = default;

	void add_shape(Shape *par_shape);
	size_t get_shapes_amount() { return shapes.get_length(); }

	void control_physics_and_drawing(Screen_information *screen, const double delta_time);

	void draw_everything(Screen_information *screen);

	void tick(Screen_information *screen, const double delta_time);
	void set_vectors(const Radius_vector *new_vectors, void (*setter)(Shape *changable, const Radius_vector &new_vector));

	Wall_type check_the_bounds(Screen_information *screen, const Shape &shape, const Radius_vector &next_position);
	void bounds_collision_reaction(Screen_information *screen, Shape *shape, Radius_vector *par_next_position, Wall_type wall_type);

	void count_physics();
	double count_distance(const Shape &first, const Shape &second);

	bool collision_detection(const Shape &first, const Shape &second);
	void collision_reaction(Shape *first, Shape *second);

	void update_directions();
};

#endif // MOLECULA_MANAGER
