#ifndef EDITOR_DELEGATES
#define EDITOR_DELEGATES

class Create_canvas;
class Canvas_keeper;

#include "../GUI/Button_delegate.hpp"
#include "Canvas_manager_manager.hpp"


class Create_canvas : public Button_delegate
{
private:
	// Pencil *pencil;
	Canvas_manager_manager *manager;

public:
	Create_canvas(Canvas_manager_manager *par_manager);

	bool on_mouse_click(const size_t par_x, const size_t par_y) override;
};

class Canvas_keeper : public Button_delegate
{
private:
	Visual_object *to_keep;

public:
	Canvas_keeper(Visual_object *par_to_keep);

	bool on_mouse_click(const size_t par_x, const size_t par_y) override;
};

#endif // EDITOR_DELEGATES