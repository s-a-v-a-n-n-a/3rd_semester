#ifndef GRAPHICAL_DELEGATES
#define GRAPHICAL_DELEGATES

#include "../GUI/Button_delegate.hpp"

#include "Pencil.hpp"
// #include "Canvas_manager.hpp"

// create cpp version

class Canvas_manager;

class Interactive
{
private:
	Visual_object *to_interact;

public:
	Interactive(Visual_object *par_to_interact) 
	: to_interact(nullptr)
	{
		to_interact = par_to_interact;
	}

	bool on_mouse_move(const Vector_ll from, const Vector_ll to)
	{
		Color changing_color = to_interact->get_color();
		int new_a = (int)MAX_COLOR_VALUE;
		
		if (to_interact->point_inside(to.get_x(), to.get_y()))
		{
			changing_color.set_a(new_a * 3 / 4);
		}
		else if(!to_interact->point_inside(to.get_x(), to.get_y()) && to_interact->point_inside(from.get_x(), from.get_y()))
		{
			changing_color.set_a(new_a);
		}

		to_interact->set_color(changing_color);

		return true;
	}

	void set_interactive(Visual_object *par_to_interact)
	{
		to_interact = par_to_interact;
	}
};

class Restore_delegate : public Button_delegate
{
private:
	Visual_object *to_restore;

public:
	Restore_delegate(Visual_object *par_to_restore)
	: to_restore(nullptr)
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

class Restore_interactive_delegate : public Restore_delegate, public Interactive
{
public:
	Restore_interactive_delegate(Visual_object *par_to_restore, Visual_object *par_to_interact) 
	: Restore_delegate(par_to_restore), Interactive(par_to_interact)
	{
		;
	}

	bool on_mouse_move(const Vector_ll from, const Vector_ll to) override
	{
		return Interactive::on_mouse_move(from, to);
	}

	// bool on_mouse_move(const Vector_ll from, const Vector_ll to) override
	// {
	// 	Color changing_color = to_interact->get_color();
	// 	int new_a = (int)MAX_COLOR_VALUE;
		
	// 	if (to_interact->point_inside(to.get_x(), to.get_y()))
	// 	{
	// 		changing_color.set_a(new_a * 3 / 4);
	// 	}
	// 	else if(!to_interact->point_inside(to.get_x(), to.get_y()) && to_interact->point_inside(from.get_x(), from.get_y()))
	// 	{
	// 		changing_color.set_a(new_a);
	// 	}

	// 	to_interact->set_color(changing_color);

	// 	return true;
	// }

	// void set_interactive(Visual_object *par_to_interact)
	// {
	// 	to_interact = par_to_interact;
	// }
};

class Roll_up_delegate : public Button_delegate
{
private: 
	Visual_object *to_roll_up;

public:
	Roll_up_delegate(Visual_object *par_to_roll_up)
	: to_roll_up(nullptr)
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
	: to_close(nullptr)
	{
		to_close = par_to_close;
	}

	bool on_mouse_click(const size_t par_x, const size_t par_y) override
	{
		to_close->set_alive(false);

		return false;
	}
};

class Close_interactive_delegate : public Close_delegate
{
private:
	Visual_object *to_interact;

public:
	Close_interactive_delegate(Visual_object *par_to_close, Visual_object *par_to_interact) 
	: Close_delegate(par_to_close), to_interact(nullptr)
	{
		to_interact = par_to_interact;
	}

	bool on_mouse_move(const Vector_ll from, const Vector_ll to) override
	{
		Color changing_color = to_interact->get_color();
		int new_a = (int)MAX_COLOR_VALUE;
		
		if (to_interact->point_inside(to.get_x(), to.get_y()))
		{
			changing_color.set_a(new_a * 3 / 4);
		}
		else if(!to_interact->point_inside(to.get_x(), to.get_y()) && to_interact->point_inside(from.get_x(), from.get_y()))
		{
			changing_color.set_a(new_a);
		}

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
	: pencil(nullptr), color(WHITE)
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

class Change_thickness : public Button_delegate
{
private:
	Pencil *pencil;
	size_t size;

public:
	Change_thickness(Pencil *par_pencil, const size_t par_size)
	: pencil(nullptr), size(0)
	{
		pencil = par_pencil;
		size = par_size;
	}

	bool on_mouse_click(const size_t par_x, const size_t par_y) override
	{
		pencil->set_size(size);

		return true;
	}
};

class Drag_and_drop_delegate : public Button_delegate
{
private:
	Visual_object *to_change_place;

	bool clicked;

	Vector_ll first_position;
	Vector_ll last_position;

public:
	Drag_and_drop_delegate(Visual_object *par_to_change_place) 
	: to_change_place(nullptr), clicked(false), first_position(0, 0), last_position(0, 0)
	{
		to_change_place = par_to_change_place;
	}

	bool on_mouse_click(const size_t par_x, const size_t par_y) override
	{
		clicked = true;

		first_position = Vector_ll(par_x, par_y);

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

	bool on_mouse_move(const Vector_ll from, const Vector_ll to) override
	{
		if (clicked)
		{
			last_position = to;

			to_change_place->set_position(to_change_place->get_position() + last_position - first_position);
			first_position = last_position;
		}

		return true;
	}
};

#endif // GRAPHICAL_DELEGATES
