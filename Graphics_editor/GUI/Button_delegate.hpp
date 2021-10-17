#ifndef BUTTON_DELEGATE
#define BUTTON_DELEGATE

class Button_delegate
{
public:
	virtual void on_mouse_click() = 0;
	virtual void on_mouse_released() { ; }
};

#endif // BUTTON_DELEGATE
