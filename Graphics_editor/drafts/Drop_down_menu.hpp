#ifndef DROP_DOWN_MENU
#define DROP_DOWN_MENU

#include "../GUI/Visual_object_base.hpp"

class Drop_down_menu_manager : public Visual_object
{
private:

public:
	Drop_down_menu_manager(const size_t par_type, const Radius_vector &par_position, const Color &par_color, const size_t par_width, const size_t par_height, Visual_object *to_control);
	~Drop_down_menu_manager();
};

class Drop_down_menu : public Visual_object
{
private:

public:
	Drop_down_menu(const size_t par_type, const Radius_vector &par_position, const Color &par_color, const size_t par_width, const size_t par_height, Visual_object *to_control);
	~Drop_down_menu();
};

#endif // DROP_DOWN_MENU
