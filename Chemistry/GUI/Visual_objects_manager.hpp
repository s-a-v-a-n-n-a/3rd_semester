#ifndef VISUAL_OBJECTS_MANAGER
#define VISUAL_OBJECTS_MANAGER

#include "Visual_object_base.hpp"
#include "../sfml_drawing/screen_functions.hpp"
#include "../Shape_manager/Shape_manager.hpp"
#include "Shape_delegates.hpp"
#include "Button.hpp"
#include "Amounts_graph.hpp"

extern const size_t DEFAULT_WIDTH;
extern const size_t DEFAULT_HEIGHT;

extern const size_t DEFAULT_SHAPE_MANAGER_WIDTH;
extern const size_t DEFAULT_SHAPE_MANAGER_HEIGHT;

extern const Radius_vector DEFAULT_SHAPE_MANAGER_POS;

extern const size_t DEFAULT_BUTTON_WIDTH;
extern const size_t DEFAULT_BUTTON_HEIGHT;

extern const char DEFAULT_ADD_MOLECULA_TEXT[];
extern const char DEFAULT_ADD_RECTANGLE_TEXT[];

extern const size_t DEFAULT_AMOUNTS_GRAPH_WIDTH;
extern const size_t DEFAULT_AMOUNTS_GRAPH_HEIGHT;

extern const Color DEFAULT_MOLECULA_COLOR;
extern const Color DEFAULT_RECTANGLE_COLOR;

class Visual_objects_manager : public Visual_object
{
private:
	// List<Visual_object*> objects;

	// Radius_vector position;
	// Color color;

	// size_t width;
	// size_t height;

	// bool active;
	
	Shape_manager *manager;

public:
	Visual_objects_manager(const Radius_vector &par_position, const Color &par_color, const size_t par_width, const size_t par_height);
	~Visual_objects_manager();

	void draw(Screen_information *screen) override;
	bool check_click(const double par_x, const double par_y) override;
	void tick(Screen_information *screen, const double delta_time) override;

	Shape_manager *get_manager() const { return manager; }
};

#endif // VISUAL_OBJECTS_MANAGER
