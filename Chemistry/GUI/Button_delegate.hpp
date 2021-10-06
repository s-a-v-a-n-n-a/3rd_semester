#ifndef BUTTON_DELEGATE
#define BUTTON_DELEGATE

#include "../Shape_manager/Shape_manager.hpp"

class Button_delegate
{
public:
	virtual void click_reaction() = 0;
};

#endif // BUTTON_DELEGATE
