#ifndef AMOUNTS_GRAPH
#define AMOUNTS_GRAPH

#include "Visual_object_base.hpp"
#include "../Shape_manager/Shape_manager.hpp"
#include "../Shapes_interactions/Shapes_set.hpp"

#include "../sfml_drawing/screen_functions.hpp"

class Amounts_graph : public Visual_object
{
private:
	Shape_manager *manager;
	
	size_t index_to_begin;
	size_t *shapes_amounts[shape_types_amount];
	Color shapes_colors[shape_types_amount];

public:
	Amounts_graph(Shape_manager *par_manager, const Radius_vector &par_position, const Color &par_color, const double par_width, const double par_height);
	~Amounts_graph();

	void set_shape_color(const Shape_types par_type, Color const &color) { shapes_colors[(size_t)par_type] = color; }

	void draw(Screen_information *screen) override;
	void tick(Screen_information *screen, const double delta_time) override;
};

#endif // AMOUNTS_GRAPH
