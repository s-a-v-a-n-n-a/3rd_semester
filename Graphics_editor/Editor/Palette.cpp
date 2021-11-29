#include "Palette.hpp"

Palette::Palette(const Visual_object::Config &par_base, const Color &par_chosen_color)
: Closing_window(par_base)
{
	chosen_color = par_chosen_color;
	// create buttonы 
	// ------------------------------------------------------------------------
	// Visual_object::Config panel_base = { (size_t)Vidget_type::BUTTON_MANAGER, get_position(), nullptr, TRANSPARENT, get_width(), DEFAULT_BUTTON_HEIGHT };
	// Button_manager *panel = new Button_manager(panel_base);

    size_t offset = DEFAULT_BUTTON_HEIGHT;
    size_t button_size = get_width() / DEFAULT_COLORS_AMOUNT;
    // for (size_t i = 0; i < DEFAULT_COLORS_AMOUNT; ++i)
    // {
    // 	Change_color *change_color = new Change_color(COLOR_SEQUENCE[i]);
    // 	Full_texture *texture = new Full_texture(COLORED_BUTTONS[i]);
    // 	offset = texture->get_width();
    // 	panel->add_button(change_color, " ", texture, button_size, button_size);
    // }

    HSV hsv = get_hsv(par_chosen_color);
    Color picker_color = RED;
    if (hsv.h != 0)
    	picker_color = get_rgb({hsv.h, 255, 255});
    // printf("%d\n", hsv.v);
	// Full_texture *texture = new Full_texture(GRADIENT_BAR_TEXTURE, MAX_COLOR_VALUE, 20);
	// size_t size = par_width < (par_height - DEFAULT_BUTTON_HEIGHT) ? par_width : (par_height - DEFAULT_BUTTON_HEIGHT);

	size_t picker_size = (get_width() - 20) * 3 / 4;
	size_t button_width = (get_width() - 20) / 4;
	size_t buttin_height = get_height() / 6;

	picker = create_color_picker(get_position() + Vector_ll(10, (offset + 30)), picker_size, picker_size, picker_color);// new Color_picker((size_t)Vidget_type::COLOR_PICKER, par_position + Vector_ll(10, (offset + 30)), TRANSPARENT, MAX_COLOR_VALUE, MAX_COLOR_VALUE, par_pencil);
    gradient_bar = create_gradient_bar(get_position() + Vector_ll(10, offset + 10), picker_size, 20, picker, hsv);// new Gradient_bar((size_t)Vidget_type::GRADIENT_BAR, par_position + Vector_ll(10, offset + 10), texture, MAX_COLOR_VALUE, 20, par_pencil, picker);
   	// add_visual_object(panel);
   	old_color = new Button({(size_t)Vidget_type::BUTTON, get_position() + Vector_ll(picker_size + 20, (offset + 30)), nullptr, par_chosen_color, button_width, buttin_height}, NULL, "");
   	new_color = new Button({(size_t)Vidget_type::BUTTON, get_position() + Vector_ll(picker_size + 20, (offset + 30 + buttin_height)), nullptr, par_chosen_color, button_width, buttin_height}, NULL, "");

   	Popup_color_confirmation *delegate = new Popup_color_confirmation(this, &chosen_color);
   	ok_button = new Button({(size_t)Vidget_type::BUTTON, get_position() + Vector_ll(picker_size + 20, (offset + 60 + buttin_height * 2)), nullptr, GREY, button_width, get_height()/5}, delegate, "OK");

   	add_visual_object(old_color);
   	add_visual_object(new_color);
   	add_visual_object(ok_button);
}

Color_picker *Palette::create_color_picker(const Vector_ll &position, const size_t width, const size_t height, const Color &color)
{
	Visual_object::Config picker_base = { (size_t)Vidget_type::COLOR_PICKER, position, nullptr, TRANSPARENT, width, height };

	Color_picker *picker = new Color_picker(picker_base, color, &chosen_color);
	add_visual_object(picker);

	return picker;
}

Gradient_bar *Palette::create_gradient_bar(const Vector_ll &position, const size_t width, const size_t height, Color_picker *picker, const HSV &hsv)
{
	Full_texture *texture = Resources::get_instance()->create_texture(GRADIENT_BAR_TEXTURE, width, height);
	Visual_object::Config gradient_base = { (size_t)Vidget_type::GRADIENT_BAR, position, texture, TRANSPARENT, width, height };

    Gradient_bar *gradient = new Gradient_bar(gradient_base, picker, hsv);
	add_visual_object(gradient);

	return gradient;
}

void Palette::draw(Screen_information *screen)
{
	Visual_object::draw(screen);

	Visual_object **objects_array = get_objects()->get_array();
	size_t objects_amount = get_objects()->get_length();

	for (size_t i = 0; i < objects_amount; ++i)
	{
		if (objects_array[i]->get_visible())
		{
			objects_array[i]->draw(screen);
		}
	}
}

bool Palette::on_mouse_click(const bool state, const size_t par_x, const size_t par_y)
{
	if (point_inside(par_x, par_y))
	{
		bool result = Visual_object::on_mouse_click(state, par_x, par_y);

		if ((result = picker->on_mouse_click(state, par_x, par_y)) || (result = gradient_bar->on_mouse_click(state, par_x, par_y)))
		{
			new_color->set_color(chosen_color); 
		}
		if (!result)
		{
			result = ok_button->on_mouse_click(state, par_x, par_y);
		}
		return result;
	}

	return false;
}
