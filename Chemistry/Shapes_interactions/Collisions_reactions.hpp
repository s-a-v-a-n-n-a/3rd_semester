#ifndef COLLISIONS_REACTIONS
#define COLLISIONS_REACTIONS

#include "../simple_list/simple_list.hpp"
#include "Shapes_set.hpp"

void molecula_molecula_collision_reaction(List<Shape*> *engine, const Shape *par_first, const Shape *par_second);
void molecula_rectangle_collision_reaction(List<Shape*> *engine, const Shape *par_first, const Shape *par_second);
void rectangle_rectangle_collision_reaction(List<Shape*> *engine, const Shape *par_first, const Shape *par_second);

// void molecula_molecula_collision_reaction(List<Shape*> *engine, const Shape *par_first, const Shape *par_second);
// void molecula_rectangle_collision_reaction(List<Shape*> *engine, const Shape *par_first, const Shape *par_second);
// void rectangle_rectangle_collision_reaction(List<Shape*> *engine, const Shape *par_first, const Shape *par_second);

typedef void (*reaction_function)(List<Shape*> *engine, const Shape *par_first, const Shape *par_second);

extern reaction_function reaction_functions[shape_types_amount * shape_types_amount];

#endif // COLLISIONS_REACTIONS
