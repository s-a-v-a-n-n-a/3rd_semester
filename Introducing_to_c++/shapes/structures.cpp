#include "structures.hpp"

void Work_field::construct(System_of_axes coordinates, size_t list_size)
{
	this->coordinates.init(coordinates.left_high_corner_x, 
						   coordinates.left_high_corner_y,
						   coordinates.x_min,
						   coordinates.x_max,
						   coordinates.y_min,
						   coordinates.y_max);

	shapes = list_create(list_size);
}

void Work_field::destruct()
{
	list_delete(this->shapes);
}

Work_field *work_field_create(System_of_axes coordinates, size_t list_size)
{
	Work_field *thus = (Work_field*)calloc(1, sizeof(Work_field));

	if (thus)
		thus->construct(coordinates, list_size);

	return thus;
}

void work_field_delete(Work_field *thus)
{
	thus->destruct();

	free(thus);
}

void Work_field::add_shape(Shape *shape)
{
	list_add_to_end(this->shapes, shape);
}

void draw_axes(sf::RenderWindow *window, System_of_axes coordinates)
{
	double abs_max = coordinates.x_max;
	double abs_min = coordinates.x_min;
	// abs_min = (abs_min > 0 ? 0 : abs_min);
	if (abs_min > 0)
		abs_min = 0;

	double offset_out_of_border_x = (coordinates.x_min > 0 ? coordinates.x_min : 0);

	double ord_min = coordinates.y_min;
	double ord_max = coordinates.y_max;
	if (ord_max < 0)
		ord_max = 0;

	double offset_out_of_border_y = (coordinates.y_max < 0 ? coordinates.y_max : 0);

	double offset_x = coordinates.left_high_corner_x - (coordinates.x_min > 0 ? coordinates.x_min : 0);
	double offset_y = coordinates.left_high_corner_y + (coordinates.y_max < 0 ? coordinates.y_max : 0);

	// sf::Vertex abs_begin(sf::Vector2f(fabs(abs_min), fabs(ord_max)));
	// sf::Vertex abs_end  (sf::Vector2f(fabs(abs_max), fabs(ord_max)));

	// sf::Vertex ord_begin(sf::Vector2f(fabs(abs_min), fabs(ord_min)));
	// sf::Vertex ord_end  (sf::Vector2f(fabs(abs_min), fabs(ord_max)));

	Vector abscissa_axe = {};
    abscissa_axe.init_simple(offset_x, fabs(ord_max) + offset_y, fabs(abs_max - abs_min) + offset_x + (coordinates.x_max < 0 && coordinates.y_max < 0 ? fabs(coordinates.x_max) : 0), fabs(ord_max) + offset_y);
    // if (coordinates.x_max < 0 && coordinates.y_max < 0)
    // 	abscissa_axe.end_point_x += fabs(coordinates.x_max);
    abscissa_axe.draw_shape(&abscissa_axe, window);

    Vector ordinate_axe = {};
    ordinate_axe.init_simple(fabs(abs_min) + offset_x, fabs(ord_max - ord_min) + offset_y, fabs(abs_min) + offset_x, offset_y + (coordinates.x_min > 0 && coordinates.y_min > 0 ? coordinates.y_min : 0));
    // if (coordinates.x_min > 0 && coordinates.y_min > 0)
    // 	ordinate_axe.end_point_y += coordinates.y_min;
    ordinate_axe.draw_shape(&ordinate_axe, window);
}

void Work_field::draw(sf::RenderWindow *window)
{
	this->coordinates.draw(window);

	draw_axes(window, this->coordinates);

	size_t shapes_amount = shapes->length;
	for (size_t i = 0; i < shapes_amount; ++i)
	{
		(shapes->array[i])->draw_shape(shapes->array[i], window);
	}
}
