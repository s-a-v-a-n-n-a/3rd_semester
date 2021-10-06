#include "Collisions_reactions.hpp"

void (*reaction_functions[shape_types_amount * shape_types_amount])(List<Shape*> *engine, const Shape *par_first, const Shape *par_second) =
{
	molecula_molecula_collision_reaction, molecula_rectangle_collision_reaction,
	molecula_rectangle_collision_reaction, rectangle_rectangle_collision_reaction
};

void molecula_molecula_collision_reaction(List<Shape*> *engine, const Shape *par_first, const Shape *par_second)
{
	Molecula *first  = (Molecula*)par_first;
	Molecula *second = (Molecula*)par_second;

	if (!first->get_active() || !second->get_active())
		return;

	double rectangle_weight = first->get_weight() + second->get_weight();
	double rectangle_size   = (first->get_radius() + second->get_radius()) * 2.0;

	Radius_vector first_velocity  = first->get_velocity();
	Radius_vector second_velocity = second->get_velocity();
	double doubled_kinetic_energy = first->get_weight() * first_velocity.length() * first_velocity.length() + 
									second->get_weight() * second_velocity.length() * second_velocity.length(); 
	
	Radius_vector rectangle_velocity((first->get_velocity() * first->get_weight() + second->get_velocity() * second->get_weight())/(first->get_weight() + second->get_weight()));
	rectangle_velocity.normalization();
	rectangle_velocity *= sqrt(doubled_kinetic_energy / rectangle_weight);

	Color first_color  = first->get_color();
	Color second_color = second->get_color();
	Color rectangle_color = { MAX_COLOR_VALUE, MAX_COLOR_VALUE, 
		                      (unsigned char)(MAX_COLOR_VALUE - (unsigned char)(second_color.get_g()/(second->get_radius())) - (unsigned char)(first_color.get_g()/(first->get_radius()))),
							  (unsigned char)(MAX_COLOR_VALUE - (unsigned char)(second_color.get_b()/(second->get_radius())) - (unsigned char)(first_color.get_b()/(first->get_radius()))) };
	
	Radius_vector rectangle_centre_position((first->get_centre_position() + second->get_centre_position()) / 2.0);
	
	Rectangle *molecules_sum = new Rectangle(rectangle_size, rectangle_size, (char)(Shape_types::RECTANGLE), rectangle_centre_position, rectangle_velocity, rectangle_weight, rectangle_color, false, true);
	engine->add_to_end(molecules_sum);

	first->set_active(false);
	second->set_active(false);
}

void molecula_rectangle_collision_reaction(List<Shape*> *engine, const Shape *par_first, const Shape *par_second)
{
	Molecula *first = NULL;
	Rectangle *second = NULL;

	if ((Shape_types)par_first->get_type() == Shape_types::MOLECULA)
	{
		first = (Molecula*)par_first;
		second = (Rectangle*)par_second;
	}
	else
	{
		first = (Molecula*)par_second;
		second = (Rectangle*)par_first;
	}

	if (!first->get_active() || !second->get_active())
		return;

	Radius_vector first_velocity = first->get_velocity();
	Radius_vector second_velocity = second->get_velocity();
	double doubled_kinetic_energy = first->get_weight() * first_velocity.length() * first_velocity.length() + 
							 		second->get_weight() * second_velocity.length() * second_velocity.length(); 

	Radius_vector rectangle_velocity((first->get_velocity() * first->get_weight() + second->get_velocity() * second->get_weight())/(first->get_weight() + second->get_weight()));
	rectangle_velocity.normalization();
	rectangle_velocity *= sqrt(doubled_kinetic_energy / (first->get_weight() + second->get_weight()));

	second->set_velocity(rectangle_velocity);
	
	double rectangle_size = first->get_radius() * 2.0 + second->get_width();
	second->set_width(rectangle_size);
	second->set_height(rectangle_size);

	second->set_weight(second->get_weight() + first->get_weight());

	Color second_color = second->get_color();
	Color first_color = first->get_color();

	if (second_color.get_g() - first_color.get_g()/(unsigned char)first->get_radius() >= 0)
		second_color.set_g(second_color.get_g() - first_color.get_g()/(unsigned char)first->get_radius());
	else
		second_color.set_g(0);
	
	if (second_color.get_b() - first_color.get_b()/(unsigned char)first->get_radius() >= 0)
		second_color.set_b(second_color.get_b() - first_color.get_b()/(unsigned char)first->get_radius());
	else
		second_color.set_b(0);
	second->set_color(second_color);

	first->set_active(false);
}

void rectangle_rectangle_collision_reaction(List<Shape*> *engine, const Shape *par_first, const Shape *par_second)
{
	Rectangle *first = (Rectangle*)par_first;
	Rectangle *second = (Rectangle*)par_second;

	if (!first->get_active() || !second->get_active())
		return;

	Radius_vector centre_position((first->get_centre_position() + second->get_centre_position())/2.0);	
	size_t moleculas_amount = size_t(first->get_weight() + second->get_weight());

	double moleculas_circle_radius = 2.0 * moleculas_amount / M_PI / 2.0 * (rand()%50 + 1);
	double angle = 2.0 * M_PI / moleculas_amount;

	Radius_vector point(centre_position.get_x(), centre_position.get_y() - moleculas_circle_radius);
	
	Radius_vector first_velocity = first->get_velocity();
	Radius_vector second_velocity = second->get_velocity();
	double doubled_kinetic_energy = first->get_weight() * first_velocity.length() * first_velocity.length() + 
							 		second->get_weight() * second_velocity.length() * second_velocity.length();
	double molecule_velocity_module = sqrt(doubled_kinetic_energy / moleculas_amount);

	for (size_t i = 0; i < moleculas_amount; ++i)
	{
		Radius_vector molecula_velocity(point - centre_position);
		molecula_velocity.normalization();
		molecula_velocity *= molecule_velocity_module;

		Molecula *molecules_sum = new Molecula(10.0, (char)(Shape_types::MOLECULA), point, molecula_velocity, 1.0, WHITE, false, true);
		engine->add_to_end(molecules_sum);

		point.rotate_point(centre_position, angle);
	}

	first->set_active(false);
	first->set_just_born(false);

	second->set_active(false);
	second->set_just_born(false);
}