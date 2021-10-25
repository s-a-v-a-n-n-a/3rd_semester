#include "Drop_down_menu.hpp"

Drop_down_menu_manager::Drop_down_menu_manager(const size_t par_type, const Vector_ll &par_position, const Color &par_color, const size_t par_width, const size_t par_height, Visual_object *to_control)
: Visual_object(par_type, par_position, par_color, par_width, par_height)
{
	Drop_and_down_action *drop_and_down = new Drop_and_down_action(); // ??????????????????????????????
	Button *menu = new Button(Vidget_type::BUTTON, par_position, WHITE, par_width, par_height, drop_and_down, "Canvas");

	Drop_down_menu *subordinate = new Drop_down_menu(Vidget_type::DROP_DOWN_MENU, par_position + Vector_ll(0.0, 80.0), par_color, par_width, par_height, to_control);

	add_visual_object(menu);
	add_visual_object(subordinate);

	subordinate->set_visible(false);
	subordinate->set_reactive(false);
}

// функция добавления кнопки
// функция удаления кнопки

Drop_down_menu::Drop_down_menu(const size_t par_type, const Vector_ll &par_position, const Color &par_color, const size_t par_width, const size_t par_height, Button_delegate *par_delegate)
: Visual_object(par_type, par_position, par_color, par_width, par_height)
{
	// Хранить будем конкретного делегата
	// Canvas_keeper *keep = new Canvas_keeper(to_control);
	Button *menu = new Button(Vidget_type::BUTTON, par_position, par_color, par_width, par_height, par_delegate, ""); // to change text

	add_visual_object(menu);
}

// функция добавления кнопки
// функция удаления кнопки
