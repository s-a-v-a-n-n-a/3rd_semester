#ifndef EDITOR_DELEGATES
#define EDITOR_DELEGATES

#include "../GUI/Button_delegate.hpp"

#include "Pencil.hpp"
// #include "Canvas_manager.hpp"

// create cpp version

class Canvas_manager;

class Roll_up_delegate : public Button_delegate
{
private: 
	Visual_object *to_roll_up;

public:
	Roll_up_delegate(Visual_object *par_to_roll_up)
	{
		to_roll_up = par_to_roll_up;
	}

	void on_mouse_click() override
	{
		printf("trying to react\n");

		to_roll_up->set_visible(false);
		to_roll_up->set_reactive(false);
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

	void on_mouse_click() override
	{
		// delete to_close
		to_close->set_alive(false);
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

	void on_mouse_click() override
	{
		pencil->set_color(color);
	}
};

class Create_canvas : public Button_delegate
{
private:
	Radius_vector low_limits;
	Radius_vector high_limits;

public:
	Create_canvas(const Radius_vector &par_low_limits, const Radius_vector &par_high_limits)
	{
		low_limits = par_low_limits;
		high_limits = par_high_limits;
	}

	void on_mouse_click() override
	{
		;
	}
};

#endif // EDITOR_DELEGATES
