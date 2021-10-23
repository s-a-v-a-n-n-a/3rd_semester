#ifndef BUTTON_MANAGER
#define BUTTON_MANAGER

#include "../GUI/Visual_object_base.hpp"
#include "../GUI/Button.hpp"

class Button_manager : public Visual_object
{
private:
	List<Button*> buttons;
public:
	Button_manager();
	~Button_manager() { ; }

	void add_button(Button *par_button) { buttons.add_to_end(par_button); }
	void delete_button(Button *par_button) 
	{  
		// type_amount[par_object->get_type()]--;

		// Visual_object **objects_array = objects.get_array();
		// size_t objects_amount = objects.get_length();

		// for (size_t i = 0; i < objects_amount; ++i)
		// {
		// 	if(objects_array[i] == par_object)
		// 	{
		// 		objects.slow_delete(i);
				
		// 		return i;
		// 	}
		// }

		// return -1;
	}
};

#endif // BUTTON_MANAGER
