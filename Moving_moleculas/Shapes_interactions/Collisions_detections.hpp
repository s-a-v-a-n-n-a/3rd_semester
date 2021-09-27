#ifndef COLLISION_DETECTIONS
#define COLLISION_DETECTIONS

#include "Shapes_set.hpp"
// #include "../Shape.hpp"

bool molecula_molecula_collision_detection(const Shape *par_first, const Shape *par_second);
bool molecula_rectangle_collision_detection(const Shape *par_first, const Shape *par_second);
bool rectangle_rectangle_collision_detection(const Shape *par_first, const Shape *par_second);

typedef bool (*detection_function)(const Shape *par_first, const Shape *par_second);

extern detection_function detection_functions[shape_types_amount * shape_types_amount];

#endif // COLLISION_DETECTIONS
