#ifndef SHAPE_DELEGATES
#define SHAPE_DELEGATES

#include "Button_delegate.hpp"

class Add_molecula_delegate : public Button_delegate
{
private:
	Shape_manager *manager;
	
public:
	Add_molecula_delegate(Shape_manager *par_manager)
	{
		manager = par_manager;
	}

	void click_reaction() override
	{
		Radius_vector position = manager->get_position();
		size_t width = manager->get_width();
		size_t height = manager->get_height();

		int size  = rand()%50 + 1;
        int x_dir = rand()%20 - 10;
        int y_dir = rand()%20 - 10;

        int x_pos = rand()%(width - size * 2) + size + position.get_x();
        int y_pos = rand()%(height - size * 2) + size + position.get_y(); 

		Molecula *shape = new Molecula(size, (char)Shape_types::MOLECULA, Radius_vector(x_pos, y_pos), Radius_vector(x_dir, y_dir), 1.0, WHITE);
        manager->add_shape(shape);
	}
};

class Add_rectangle_delegate : public Button_delegate
{
private:
	Shape_manager *manager;

public:
	Add_rectangle_delegate(Shape_manager *par_manager)
	{
		manager = par_manager;
	}

	void click_reaction() override
	{
		Radius_vector position = manager->get_position();
		size_t width = manager->get_width();
		size_t height = manager->get_height();

		int size  = rand()%50 + 1;
        int x_dir = rand()%20 - 10;
        int y_dir = rand()%20 - 10;
        
        int x_pos = rand()%(width - size * 2) + size + position.get_x();
        int y_pos = rand()%(height - size * 2) + size + position.get_y();

		Rectangle *shape = new Rectangle(size * 2, size * 2, (char)Shape_types::RECTANGLE, Radius_vector(x_pos, y_pos), Radius_vector(x_dir, y_dir), 1.0, WHITE);
        manager->add_shape(shape);
	}
};

#endif // SHAPE_DELEGATES
