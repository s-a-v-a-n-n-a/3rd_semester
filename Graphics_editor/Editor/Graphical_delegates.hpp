#ifndef GRAPHICAL_DELEGATES
#define GRAPHICAL_DELEGATES

#include "../GUI/Button_delegate.hpp"

#include "Pencil.hpp"
// #include "Canvas_manager.hpp"

// create cpp version

class Canvas_manager;

class Restore_delegate : public Button_delegate
{
private:
	Visual_object *to_restore;

public:
	Restore_delegate(Visual_object *par_to_restore)
	{
		to_restore = par_to_restore;
	}

	bool on_mouse_click(const size_t par_x, const size_t par_y) override
	{
		to_restore->set_visible(true);
		to_restore->set_reactive(true);

		return true;
	}
};

class Roll_up_delegate : public Button_delegate
{
private: 
	Visual_object *to_roll_up;

public:
	Roll_up_delegate(Visual_object *par_to_roll_up)
	{
		to_roll_up = par_to_roll_up;
	}

	bool on_mouse_click(const size_t par_x, const size_t par_y) override
	{
		to_roll_up->set_visible(false);
		to_roll_up->set_reactive(false);

		return true;
	}
};

class Close_delegate : public Button_delegate
{
private: 
	Visual_object *to_close;

public:
	Close_delegate(Visual_object *par_to_close)
	{
		to_close = par_to_close;
	}

	bool on_mouse_click(const size_t par_x, const size_t par_y) override
	{
		// delete to_close
		to_close->set_alive(false);

		return false;
	}
};

class Close_interactive_delegate : public Close_delegate
{
private:
	Visual_object *to_interact;

public:
	Close_interactive_delegate(Visual_object *par_to_close, Visual_object *par_to_interact) : Close_delegate(par_to_close)
	{
		to_interact = par_to_interact;
	}

	bool on_mouse_move(const size_t par_x, const size_t par_y) override
	{
		Color changing_color = to_interact->get_color();
		// changing_color.set_a(MAX_COLOR_VALUE * 1 / 2);

		to_interact->set_color(changing_color);

		return true;
	}
};

class Change_color : public Button_delegate
{
private:
	Pencil *pencil;
	Color color;

public:
	Change_color(Pencil *par_pencil, const Color &par_color)
	{
		pencil = par_pencil;
		color = par_color;
	}

	bool on_mouse_click(const size_t par_x, const size_t par_y) override
	{
		pencil->set_color(color);

		return true;
	}
};

class Drag_and_drop_delegate : public Button_delegate
{
private:
	Visual_object *to_change_place;

	bool clicked;

	Radius_vector first_position;
	Radius_vector last_position;

public:
	Drag_and_drop_delegate(Visual_object *par_to_change_place)
	{
		to_change_place = par_to_change_place;
	}

	bool on_mouse_click(const size_t par_x, const size_t par_y) override
	{
		clicked = true;

		first_position = Radius_vector(par_x, par_y);

		to_change_place->set_reactive(false);

		return true;
	}

	bool on_mouse_release()
	{
		clicked = false;

		first_position = last_position;

		to_change_place->set_reactive(true);

		return true;
	}

	bool on_mouse_move(const size_t par_x, const size_t par_y) override
	{
		if (clicked)
		{
			last_position = Radius_vector(par_x, par_y);

			to_change_place->set_position(to_change_place->get_position() + last_position - first_position);
			first_position = last_position;
		}

		return true;
	}
};

#endif // GRAPHICAL_DELEGATES
