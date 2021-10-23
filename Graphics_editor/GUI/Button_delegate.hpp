#ifndef BUTTON_DELEGATE
#define BUTTON_DELEGATE

#include <cstdio>
#include <cstdlib>

class Button_delegate
{
public:
	virtual bool on_mouse_click(const size_t par_x, const size_t par_y) = 0;
	virtual bool on_mouse_release() { return false; }
	virtual bool on_mouse_move(const size_t par_x, const size_t par_y) { return false; }
};

#endif // BUTTON_DELEGATE
