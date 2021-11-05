#ifndef GRAPHICAL_DELEGATES
#define GRAPHICAL_DELEGATES

#include "../GUI/Button_delegate.hpp"
#include "../sfml_drawing/Animating_texture.hpp"
#include "../GUI/Animations.hpp"

#include "Pencil.hpp"
// #include "Canvas_manager.hpp"

// create cpp version

class Canvas_manager;

class Interactive
{
private:
	Visual_object *to_interact;

public:
	Interactive(Visual_object *par_to_interact);

	bool on_mouse_move(const Vector_ll from, const Vector_ll to);

	void set_interactive(Visual_object *par_to_interact);
};

class Animating : virtual public Button_delegate
{
private:
	Visual_object *to_animate;

	Animation *move_in;
	long long move_in_index;

	Animation *move_out;
	long long move_out_index;

public:
	Animating(Visual_object *par_to_animate);

	bool on_mouse_click(const size_t par_x, const size_t par_y) override;
	bool on_mouse_move(const Vector_ll from, const Vector_ll to) override;

	void set_animating(Visual_object *par_to_animate);
};

class Restore_delegate : virtual public Button_delegate
{
private:
	Visual_object *to_restore;

public:
	Restore_delegate(Visual_object *par_to_restore);

	bool on_mouse_click(const size_t par_x, const size_t par_y) override;
};

class Animating_restore_delegate : public Restore_delegate, public Animating
{
public:
	Animating_restore_delegate(Visual_object *par_to_restore, Visual_object *par_to_interact);

	bool on_mouse_click(const size_t par_x, const size_t par_y) override;
	bool on_mouse_move(const Vector_ll from, const Vector_ll to) override;
};

class Restore_interactive_delegate : public Restore_delegate, public Interactive
{
public:
	Restore_interactive_delegate(Visual_object *par_to_restore, Visual_object *par_to_interact);

	bool on_mouse_move(const Vector_ll from, const Vector_ll to) override;
};

class Roll_up_delegate : virtual public Button_delegate
{
private: 
	Visual_object *to_roll_up;

public:
	Roll_up_delegate(Visual_object *par_to_roll_up);

	bool on_mouse_click(const size_t par_x, const size_t par_y) override;
	Visual_object *get_roll_up();
};

class Animating_roll_up_delegate : public Roll_up_delegate, public Animating
{
public:
	Animating_roll_up_delegate(Visual_object *par_to_roll_up, Visual_object *par_to_interact);

	bool on_mouse_click(const size_t par_x, const size_t par_y) override;
	bool on_mouse_move(const Vector_ll from, const Vector_ll to) override;
};

class Close_delegate : public Button_delegate
{
private: 
	Visual_object *to_close;

public:
	Close_delegate(Visual_object *par_to_close);

	bool on_mouse_click(const size_t par_x, const size_t par_y) override;
};

class Close_interactive_delegate : public Close_delegate
{
private:
	Visual_object *to_interact;

public:
	Close_interactive_delegate(Visual_object *par_to_close, Visual_object *par_to_interact);

	bool on_mouse_move(const Vector_ll from, const Vector_ll to) override;
};

class Change_color : public Button_delegate
{
private:
	Pencil *pencil;
	Color color;

public:
	Change_color(Pencil *par_pencil, const Color &par_color);

	bool on_mouse_click(const size_t par_x, const size_t par_y) override;
};

class Change_thickness : public Button_delegate
{
private:
	Pencil *pencil;
	size_t size;

public:
	Change_thickness(Pencil *par_pencil, const size_t par_size);

	bool on_mouse_click(const size_t par_x, const size_t par_y) override;
};

class Drag_and_drop_delegate : public Button_delegate
{
private:
	Visual_object *to_change_place;

	bool clicked;

	Vector_ll first_position;
	Vector_ll last_position;

public:
	Drag_and_drop_delegate(Visual_object *par_to_change_place);

	bool on_mouse_click(const size_t par_x, const size_t par_y) override;
	bool on_mouse_release();
	bool on_mouse_move(const Vector_ll from, const Vector_ll to) override;
};

#endif // GRAPHICAL_DELEGATES
