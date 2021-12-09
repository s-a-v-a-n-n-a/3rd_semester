#ifndef SHAPE_DELEGATES
#define SHAPE_DELEGATES

#include "Button_delegate.hpp"
#include "../Shape_manager/Shape_manager.hpp"
#include "Amounts_graph.hpp"

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

		// int size  = 10;
        int x_dir = rand()%20 - 10;
        int y_dir = rand()%20 - 10;

        // int x_pos = rand()%(width - size * 2) + size + position.get_x();
        // int y_pos = rand()%(height - size * 2) + size + position.get_y(); 

		Molecula *shape = new Molecula((char)Shape_types::MOLECULA, Radius_vector(0.0, 0.0), Radius_vector(x_dir, y_dir), 100.0 * M_PI, WHITE);
        int size = (int)shape->get_radius();
		int x_pos = rand()%(width - size * 2) + size + position.get_x();
        int y_pos = rand()%(height - size * 2) + size + position.get_y();
        shape->set_centre_position(Radius_vector(x_pos, y_pos));

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

		// int size  = rand()%50 + 1;
        int x_dir = rand()%20 - 10;
        int y_dir = rand()%20 - 10;
        
        // int x_pos = rand()%(width - size * 2) + size + position.get_x();
        // int y_pos = rand()%(height - size * 2) + size + position.get_y();

		Rectangle *shape = new Rectangle(1.0, (char)Shape_types::RECTANGLE, Radius_vector(0.0, 0.0), Radius_vector(x_dir, y_dir), 100.0 * M_PI, WHITE);
		int size = (int)shape->get_width();
		int x_pos = rand()%(width - size * 2) + size + position.get_x();
        int y_pos = rand()%(height - size * 2) + size + position.get_y();
        shape->set_centre_position(Radius_vector(x_pos, y_pos));
        
        manager->add_shape(shape);
	}
};

class Change_scale : public Button_delegate
{
private:
	Amounts_graph *graph;

public:
	Change_scale(Amounts_graph *par_graph)
	{
		graph = par_graph;
	}

	void click_reaction() override
	{
		size_t shapes_amount = graph->get_manager()->get_shapes()->get_length();
		size_t **shapes_amounts = graph->get_shapes_amounts();

		size_t amounts_graph_width = graph->get_width();
		size_t amounts_graph_height = graph->get_height();
		
		size_t max_amount = 0;
		for (size_t i = 0; i < amounts_graph_width; ++i)
		{
			for (size_t j = 0; j < shape_types_amount; ++j)
			{
				if (shapes_amounts[j][i] > max_amount)
					max_amount = shapes_amounts[j][i];
				// printf("new scale %lg\n", graph->get_scale());
			}
		}

		if (max_amount * graph->get_scale() > amounts_graph_height)
		{
			// graph->set_scale(amounts_graph_width / shapes_amounts[i][j]);
			graph->set_scale(graph->get_scale() / (amounts_graph_height / max_amount));
		}
		else if (max_amount * graph->get_scale() < (amounts_graph_height / 2.0) && max_amount * graph->get_scale() * (amounts_graph_height / max_amount / 2.0) <= amounts_graph_height)
		{
			// printf("came here\n");
			graph->set_scale(graph->get_scale() * (amounts_graph_height / max_amount / 2.0));
		}
	}
};

#endif // SHAPE_DELEGATES
