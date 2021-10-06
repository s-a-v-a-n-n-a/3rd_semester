#include "Shape_manager.hpp"

Shape_manager::Shape_manager(const Radius_vector &par_position, const Color &par_color, const size_t par_width, const size_t par_height) 
: Visual_object(par_position, par_color, par_width, par_height), shapes()
{
	system_energy = 0;
}

void Shape_manager::add_shape(Shape *par_shape)
{
	// system_energy += par_shape->get_velocity().length() * par_shape->get_velocity().length() * par_shape->get_weight() / 2.0;

	shapes.add_to_end(par_shape);
}

void Shape_manager::delete_shape(const size_t index)
{
	// Shape *deletable = shapes.get_array()[index];
	// system_energy -= deletable->get_velocity().length() * deletable->get_velocity().length() * deletable->get_weight() / 2.0;

	shapes.slow_delete(index);
}

void Shape_manager::control_physics_and_drawing(Screen_information *screen, const double delta_time)
{
	for (int i = 0; i < 1; ++i)
		tick(screen, delta_time/1); // wow
	draw(screen);
}

void Shape_manager::tick(Screen_information *screen, const double delta_time)
{
	size_t shapes_amount = shapes.get_length();
	Shape **shapes_array = shapes.get_array();

	Radius_vector *new_positions = new Radius_vector[shapes_amount];
	for (size_t i = 0; i < shapes_amount; ++i)
	{
		Radius_vector velocity(shapes_array[i]->get_velocity());
		Radius_vector next_position = shapes_array[i]->count_move(delta_time);

		Radius_vector next_position_copy(next_position);

		Wall_type wall = check_the_bounds(screen, shapes_array[i], next_position);
		bounds_collision_reaction(screen, shapes_array[i], &next_position, wall);

		new_positions[i] += next_position;
	}
	set_vectors(new_positions, &position_setter);
	delete [] new_positions;

	for (size_t i = 0; i < shapes_amount; ++i)
	{
		if (shapes.get_array()[i]->get_active())
		{
			for (size_t j = i + 1; j < shapes_amount; ++j)
			{
				// Смотрим, какого типа фигуры (смотрю в функции)
				if (shapes.get_array()[j]->get_active())
				{
					if (collision_detection(shapes.get_array()[i], shapes.get_array()[j]))
					{
						if (shapes.get_array()[i]->count_energy() + shapes.get_array()[j]->count_energy() < CRITICAL_ENERGY)
							collision_physical_reaction(shapes.get_array()[i], shapes.get_array()[j]);
						else
							collision_reaction(shapes.get_array()[i], shapes.get_array()[j]);
					}
				}
			}
		}
	}

	shapes_amount = shapes.get_length();
	for (size_t i = 0; i < shapes_amount; ++i)
	{
		if(!(shapes.get_array()[i]->get_active()) && shapes.get_array()[i]->get_just_born())
		{
			shapes.get_array()[i]->set_just_born(false);
			shapes.get_array()[i]->set_active(true);
		}
	}
	int index = 0;
	while (index < shapes.get_length())
	{
		if (!(shapes.get_array()[index]->get_active()))
		{
			shapes.slow_delete(index);
			index--;
		}

		index++;
	}
}

void position_setter(Shape *changable, const Radius_vector &new_vector)
{
	changable->move(new_vector);
}

void velocity_setter(Shape *changable, const Radius_vector &new_vector)
{
	changable->set_velocity(new_vector);
}

void Shape_manager::set_vectors(const Radius_vector* new_vectors, void (*setter)(Shape *changable, const Radius_vector &new_vector))
{
	size_t shapes_amount = shapes.get_length();
	Shape **shapes_array = shapes.get_array();

	for (size_t i = 0; i < shapes_amount; ++i)
	{
		setter(shapes_array[i], new_vectors[i]);
	}
}

Wall_type Shape_manager::check_the_bounds(Screen_information *screen, const Shape *shape, const Radius_vector &next_position) // передать size параметром
{
	size_t x_pos = get_position().get_x();
	size_t y_pos = get_position().get_y();

	size_t width  = get_width();
	size_t height = get_height();

	double x = next_position.get_x();
	double y = next_position.get_y();

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

	if (x - x_offset < x_pos) // - size
	{
		return Wall_type::LEFT; 
	}
	if (y + y_offset > y_pos + height) // + size
	{
		return Wall_type::UP;
	}
	if (x + x_offset > x_pos + width) // + size
	{
		return Wall_type::RIGHT; 
	}
	if (y - y_offset < y_pos) // - size
	{
		return Wall_type::DOWN;
	}

	return Wall_type::NO;
}

bool Shape_manager::collision_detection(const Shape *first, const Shape *second)
{
	Shape_types first_type = (Shape_types)first->get_type();
	Shape_types second_type = (Shape_types)second->get_type();

	return detection_functions[(char)first_type * shape_types_amount + (char)second_type](first, second);
}

void Shape_manager::bounds_collision_reaction(Screen_information *screen, Shape *shape, Radius_vector *par_next_position, Wall_type wall_type)
{
	size_t x_pos = get_position().get_x();
	size_t y_pos = get_position().get_y();

	size_t width  = get_width();
	size_t height = get_height();

	Radius_vector next_position(shape->get_centre_position());
	Radius_vector velocity(shape->get_velocity());

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
}

void Shape_manager::draw(Screen_information *screen)
{
	size_t shapes_amount = get_shapes_amount();
	Shape **shapes_array = shapes.get_array();
	for (size_t i = 0; i < shapes_amount; ++i)
	{
		if (shapes_array[i]->get_active())
			shapes_array[i]->draw(screen);
	}
}

void Shape_manager::collision_reaction(Shape *first, Shape *second)
{
	Shape_types first_type = (Shape_types)first->get_type();
	Shape_types second_type = (Shape_types)second->get_type();

	reaction_functions[(char)first_type * shape_types_amount + (char)second_type](this->get_shapes(), first, second);
}

void Shape_manager::collision_physical_reaction(Shape *first, Shape *second)
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

// void molecula_molecula_collision_reaction(Shape_manager *engine, const size_t par_first_index, const size_t par_second_index)
// {
// 	Molecula *first = (Molecula*)(engine[par_first_index]);
// 	Molecula *second = (Molecula*)(engine[par_second_index]);

// 	if (!first->get_active() || !second->get_active())
// 		return;

// 	double rectangle_weight = first->get_weight() + second->get_weight();
// 	double rectangle_size = (first->get_radius() + second->get_radius()) * 2.0;
// 	Radius_vector rectangle_centre_position(first->get_centre_position - second->get_centre_position)/2.0;
// 	Radius_vector rectangle_velocity((first->get_velocity() * first->get_weight() + second->get_velocity() * second->get_weight())/(first->get_weight() + second-get_weight()));

// 	Rectangle *molecules_sum = new Rectangle(rectangle_size, rectangle_size, Shape_types::RECTANGLE, rectangle_centre_position, rectangle_velocity, rectangle_weight, WHITE, false, true);
// 	engine->add_shape(molecules_sum);

// 	first->set_active(false);
// 	second->set_active(false);
// }

// void molecula_rectangle_collision_reaction(Shape_manager *engine, const size_t par_first_index, const size_t par_second_index)
// {
// 	Molecula *first = NULL;
// 	Rectangle *second = NULL;

// 	if ((Shape_types)(engine[par_first_index]->get_type()) == Shape_types::MOLECULA)
// 	{
// 		first = (Molecula*)(engine[par_first_index]);
// 		second = (Rectangle*)(engine[par_second_index]);
// 	}
// 	else
// 	{
// 		first = (Molecula*)(engine[par_second_index]);
// 		second = (Rectangle*)(engine[par_first_index]);
// 	}

// 	second->set_weight(second->get_weight() + first->get_weight());
// 	double rectangle_size = first->get_radius() * 2.0 + second->get_width();
// 	second->set_width(rectangle_size);
// 	second->set_height(rectangle_size);

// 	first->set_active(false);
// }

// void rectangle_rectangle_collision_reaction(Shape_manager *engine, const size_t par_first_index, const size_t par_second_indexd)
// {
// 	Rectangle *first = (Rectangle*)(engine[par_first_index]);
// 	Rectangle *second = (Rectangle*)(engine[par_second_index]);

// 	Radius_vector centre_position(first->get_centre_position - second->get_centre_position)/2.0;	
// 	size_t moleculas_amount = size_t(first->get_weight() + second->get_weight());

// 	double moleculas_circle_radius = moleculas_amount / M_PI;
// 	Radius_vector point(centre_position.get_x, centre_position.get_y - moleculas_circle_radius);

// 	for (size_t i = 0; i < moleculas_amount; ++i)
// 	{
// 		Molecula *molecules_sum = new Molecula(1.0, Shape_types::MOLECULA, point, (point - centre_position).normalization(), 1.0, WHITE, false, true);
// 		engine->add_shape(molecules_sum);
// 	}

// 	first->set_active(false);
// 	first->set_just_born(false);

// 	second->set_active(false);
// 	second->set_just_born(false);
// }