#include "Shape_manager.hpp"

Shape_manager::Shape_manager(const size_t par_shapes_amount) : shapes(par_shapes_amount)
{
	;
}

void Shape_manager::add_shape(Shape *par_shape)
{
	shapes.add_to_end(par_shape);
}

void Shape_manager::control_physics_and_drawing(Screen_information *screen, const double delta_time)
{
	for (int i = 0; i < 1000; ++i)
		tick(screen, delta_time/1000); // wow
	draw_everything(screen);
}

void Shape_manager::tick(Screen_information *screen, const double delta_time)
{
	// printf("tick\n");

	size_t shapes_amount = shapes.get_length();
	Shape **shapes_array = shapes.get_array();

	Radius_vector *new_positions = new Radius_vector[shapes_amount];

	for (size_t i = 0; i < shapes_amount; ++i)
	{
		Radius_vector velocity(shapes_array[i]->get_velocity());
		Radius_vector next_position = shapes_array[i]->count_move(delta_time);

		Wall_type wall = check_the_bounds(screen, shapes_array[i], next_position);
		bounds_collision_reaction(screen, shapes_array[i], &next_position, wall);

		new_positions[i] += next_position;
		
		// count all distances and find collisions + react them
		for (size_t j = i + 1; j < shapes_amount; ++j)
		{
			// Смотрим, какого типа фигуры (смотрю в функции)
			if (collision_detection(shapes_array[i], shapes_array[j]))
			{
				collision_reaction(shapes_array[i], shapes_array[j]);
			}
		}
	}

	set_vectors(new_positions, &position_setter);
	// set_vectors(new_directons, &velocity_setter);

	delete [] new_positions;
	// delete [] new_directons;
}

void position_setter(Shape *changable, const Radius_vector &new_vector)
{
	changable->set_centre_position(new_vector);
}

void velocity_setter(Shape *changable, const Radius_vector &new_vector)
{
	changable->set_velocity(new_vector);
}

void Shape_manager::set_vectors(const Radius_vector* new_vectors, void (*setter)(Shape *changable, const Radius_vector &new_vector))
{
	size_t shapes_amount = shapes.get_length();
	Shape **shapes_array = shapes.get_array();

	// Radius_vector **new_array = new_vectors.get_array();

	for (size_t i = 0; i < shapes_amount; ++i)
	{
		setter(shapes_array[i], new_vectors[i]);
	}
}

Wall_type Shape_manager::check_the_bounds(Screen_information *screen, const Shape *shape, const Radius_vector &next_position) // передать size параметром
{
	size_t width  = screen->get_width();
	size_t height = screen->get_height();

	double x = next_position.get_x();
	double y = next_position.get_y();

	// double size = shape.get_size();
	double x_offset = 0;
	double y_offset = 0;

	Shape_types shape_type = (Shape_types)shape->get_type();
	if (shape_type == Shape_types::MOLECULA)
	{
		x_offset = y_offset = ((Molecula*)shape)->get_radius();
	}
	else if (shape_type == Shape_types::RECTANGLE)
	{
		x_offset = ((Rectangle*)shape)->get_width()/2.0;
		y_offset = ((Rectangle*)shape)->get_height()/2.0;
	}

	if (x - x_offset < 0) // - size
	{
		return Wall_type::LEFT; 
	}
	if (y + y_offset > height) // + size
	{
		return Wall_type::UP;
	}
	if (x + x_offset > width) // + size
	{
		return Wall_type::RIGHT; 
	}
	if (y - y_offset < 0) // - size
	{
		return Wall_type::DOWN;
	}

	return Wall_type::NO;
}

bool Shape_manager::collision_detection(const Shape *first, const Shape *second)
{
	// double current_distance = count_distance(first, second);
	// if (current_distance < 0)
	// {
	// 	printf("%lg\n", current_distance);
	// 	return true;
	// }
	Shape_types first_type = (Shape_types)first->get_type();
	Shape_types second_type = (Shape_types)second->get_type();

	return detection_functions[(char)first_type * shape_types_amount + (char)second_type](first, second);
}

// get function for changing velocity
// передавать фигуру в парметрах
// учитывать размер
void Shape_manager::bounds_collision_reaction(Screen_information *screen, Shape *shape, Radius_vector *par_next_position, Wall_type wall_type)
{
	size_t width  = screen->get_width();
	size_t height = screen->get_height();

	Radius_vector next_position(shape->get_centre_position());
	Radius_vector velocity(shape->get_velocity());

	// double shape_size = shape->get_size();

	double position_x = next_position.get_x();
	double position_y = next_position.get_y();

	double velocity_x = velocity.get_x();
	double velocity_y = velocity.get_y();

	Radius_vector relative_vector(position_x, position_y);

	double x_offset = 0;
	double y_offset = 0;

	Shape_types shape_type = (Shape_types)shape->get_type();
	if (shape_type == Shape_types::MOLECULA)
	{
		x_offset = y_offset = ((Molecula*)shape)->get_radius();
	}
	else if (shape_type == Shape_types::RECTANGLE)
	{
		x_offset = ((Rectangle*)shape)->get_width()/2.0;
		y_offset = ((Rectangle*)shape)->get_height()/2.0;
	}

	// printf("\nposition was %lg %lg\n", next_position.get_x(), next_position.get_y());
	// printf("velocity was %lg %lg\n", velocity.get_x(), velocity.get_y());

	// switch
	switch (wall_type)
	{
	case Wall_type::NO:
		return;
		break;

	case Wall_type::RIGHT:
		relative_vector.set_x(width);
		position_x += x_offset; 
		break;

	case Wall_type::LEFT:
		relative_vector.set_x(0);
		position_x -= x_offset;
		break;

	case Wall_type::UP:
		relative_vector.set_y(height);
		position_y += y_offset;
		break;

	case Wall_type::DOWN:
		relative_vector.set_y(0);
		position_y -= y_offset;
		break;

	default:
		break;
	}

	Radius_vector position_change(relative_vector - Radius_vector(position_x, position_y));
	next_position += position_change * 2.0;

	position_change.normalization();
	Radius_vector velocity_change = position_change * position_change.get_projection(velocity);
	velocity += velocity_change * (-2.0); // минус ???

	shape->set_velocity(velocity);
	*par_next_position = next_position;

	// printf("position now %lg %lg\n", next_position.get_x(), next_position.get_y());
	// printf("velocity now %lg %lg\n", velocity.get_x(), velocity.get_y());
}

void Shape_manager::draw_everything(Screen_information *screen)
{
	size_t shapes_amount = get_shapes_amount();
	Shape **shapes_array = shapes.get_array();
	for (size_t i = 0; i < shapes_amount; ++i)
	{
		shapes_array[i]->draw(screen);
	}
}

// double Shape_manager::count_distance(const Shape &first, const Shape &second)
// {
// 	// printf("%lg %lg\n", first.get_size(), second.get_size());
// 	return Radius_vector(first.get_centre_position() - second.get_centre_position()).length() - first.get_size() - second.get_size();
// }

// шарики плохо расталкиваются, когда летят в одном направлении
void Shape_manager::collision_reaction(Shape *first, Shape *second)
{
	// count line between centres
	Radius_vector collision_line(second->get_centre_position() - first->get_centre_position());
	collision_line.normalization();
	
	// count normal
	Radius_vector normal(collision_line.normal());

	// cound average velocity
	Radius_vector first_velocity(first->get_velocity());
	Radius_vector second_velocity(second->get_velocity());

	double first_weight = first->get_weight();
	double second_weight = second->get_weight();

	Radius_vector average_velocity((first_velocity * first_weight + second_velocity * second_weight)/(first_weight + second_weight));

	first_velocity  -= average_velocity;
	second_velocity -= average_velocity;
	
	// count each velocitys projections
	Radius_vector first_projection_c  = collision_line * collision_line.get_projection(first_velocity) * first_weight;
	Radius_vector second_projection_c = collision_line * collision_line.get_projection(second_velocity) * second_weight;

	if (first_projection_c.get_angle(collision_line) > EPSILON && second_projection_c.get_angle(collision_line * (-1)) > EPSILON)
		return;
	
	Radius_vector first_projection_n  = normal * normal.get_projection(first_velocity) * first_weight;
	Radius_vector second_projection_n = normal * normal.get_projection(second_velocity) * second_weight;
	
	Radius_vector first_new_velocity  = (second_projection_c + first_projection_n) / first_weight;
	Radius_vector second_new_velocity = (first_projection_c + second_projection_n) / second_weight;

	first_new_velocity  += average_velocity;
	second_new_velocity += average_velocity;

	// first_new_velocity += first_velocity;
	// second_new_velocity -= second_velocity;
	
	first->set_velocity(first_new_velocity);
	second->set_velocity(second_new_velocity);
}
