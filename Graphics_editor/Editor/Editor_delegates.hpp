#ifndef EDITOR_DELEGATES
#define EDITOR_DELEGATES

class Create_canvas;
class Canvas_keeper;

#include "../GUI/Button_delegate.hpp"
#include "Canvas_manager_manager.hpp"
#include "Graphical_delegates.hpp"


class Create_canvas : virtual public Button_delegate
{
private:
	// Pencil *pencil;
	Canvas_manager_manager *manager;

public:
	Create_canvas(Canvas_manager_manager *par_manager);

	bool on_mouse_click(const size_t par_x, const size_t par_y) override;
};

class Interactive_create_canvas : public Create_canvas, public Interactive
{
public:
	Interactive_create_canvas(Canvas_manager_manager *par_manager, Visual_object *par_to_interact);

	bool on_mouse_move(const Vector_ll from, const Vector_ll to) override;
};

class Animating_create_canvas : public Create_canvas, public Animating
{
public:
	Animating_create_canvas(Canvas_manager_manager *par_manager, Visual_object *par_to_animate);

	bool on_mouse_click(const size_t par_x, const size_t par_y) override;

	bool on_mouse_move(const Vector_ll from, const Vector_ll to) override;
};

class Canvas_keeper : public Button_delegate
{
private:
	Visual_object *to_keep;

public:
	Canvas_keeper(Visual_object *par_to_keep);

	bool on_mouse_click(const size_t par_x, const size_t par_y) override;
};

// -------------------------------------------------------------------------------------------------

class Effect_changer : public Button_delegate
{
protected:
	Canvas *to_change;

public:
	Effect_changer(Canvas *par_to_change) : to_change(par_to_change) {;}

	void set_changable(Canvas *par_to_change) { to_change = par_to_change; }

	bool on_mouse_click(const size_t par_x, const size_t par_y) override { return false; }
	bool on_mouse_move(const Vector_ll from, const Vector_ll to) override { return false; }
};

// -------------------------------------------------------------------------------------------------

class Red_component_changer : public Effect_changer
{
private:

public:
	Red_component_changer(Canvas *par_to_change) : Effect_changer(par_to_change) {;}

	bool on_mouse_click(const size_t par_x, const size_t par_y) override;
	bool on_mouse_move(const Vector_ll from, const Vector_ll to) override;
};

// -------------------------------------------------------------------------------------------------

class Green_component_changer : public Effect_changer
{
private:
public:
	Green_component_changer(Canvas *par_to_change) : Effect_changer(par_to_change) {;}

	bool on_mouse_click(const size_t par_x, const size_t par_y) override;
	bool on_mouse_move(const Vector_ll from, const Vector_ll to) override;
};

// -------------------------------------------------------------------------------------------------

class Blue_component_changer : public Effect_changer
{
private:
public:
	Blue_component_changer(Canvas *par_to_change) : Effect_changer(par_to_change) {;}

	bool on_mouse_click(const size_t par_x, const size_t par_y) override;
	bool on_mouse_move(const Vector_ll from, const Vector_ll to) override;
};

#endif // EDITOR_DELEGATES