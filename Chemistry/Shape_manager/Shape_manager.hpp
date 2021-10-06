#ifndef MOLECULA_MANAGER
#define MOLECULA_MANAGER

#include "../Shapes_interactions/Collisions_detections.hpp"
#include "../Shapes_interactions/Collisions_reactions.hpp"
#include "../Shapes_interactions/Shapes_set.hpp"

#include "../Shape_base/Shape.hpp"
#include "../simple_list/simple_list.hpp" 

#include "../math_structures/math_functions.hpp"

#include "../GUI/Visual_object_base.hpp"

// #include "Shapes_set.hpp"

void position_setter(Shape *changable, const Radius_vector &new_vector);
void velocity_setter(Shape *changable, const Radius_vector &new_vector);

class Shape_manager : public Visual_object
{
private:
	List<Shape*> shapes;
	double system_energy;
	
public:
	Shape_manager() = delete;
	Shape_manager(const Radius_vector &par_position, const Color &par_color, const size_t par_width, const size_t par_height);
	Shape_manager(const Shape_manager &other) = delete;
	~Shape_manager()
	{
		Shape **objects = shapes.get_array();
		size_t objects_amount = shapes.get_length();

		for (size_t i = 0; i < objects_amount; ++i)
		{
			delete objects[i];
		}
	}

	void add_shape(Shape *par_shape);
	void delete_shape(const size_t index);

	// я вам запрещаю!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	List<Shape*> *get_shapes() { return &shapes; }
	size_t get_shapes_amount() { return shapes.get_length(); }

	void control_physics_and_drawing(Screen_information *screen, const double delta_time);

	void draw(Screen_information *screen) override;

	void tick(Screen_information *screen, const double delta_time) override;
	void set_vectors(const Radius_vector *new_vectors, void (*setter)(Shape *changable, const Radius_vector &new_vector));

	Wall_type check_the_bounds(Screen_information *screen, const Shape *shape, const Radius_vector &next_position);
	void bounds_collision_reaction(Screen_information *screen, Shape *shape, Radius_vector *par_next_position, Wall_type wall_type);

	void count_physics();
	double count_distance(const Shape &first, const Shape &second);

	bool collision_detection(const Shape *first, const Shape *second);
	void collision_reaction(Shape *first, Shape *second);
	void collision_physical_reaction(Shape *first, Shape *second);
};

#endif // MOLECULA_MANAGER
