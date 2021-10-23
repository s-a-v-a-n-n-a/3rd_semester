#include "Canvas.hpp"

Canvas::Canvas(const size_t par_type, const Radius_vector &par_position, const Color &par_color, const size_t par_width, const size_t par_height, Pencil *par_pencil)
: Visual_object(par_type, par_position, par_color, par_width, par_height)
{
	printf("Canvas position: %lg, %lg\n", par_position.get_x(), par_position.get_y());
	

	pencil = par_pencil;

	// current_background_color = WHITE;
	current_drawing_color = BLACK;

	drawing = new Color[par_width * par_height];
	for (size_t i = 0; i < par_width * par_height; ++i)
		drawing[i] = WHITE;

	drawing_state = false;
}

void Canvas::draw(Screen_information *screen)
{
	Visual_object::draw(screen);

	size_t width = get_width();
	size_t height = get_height();

	Color current_color = get_color();

	Radius_vector position(get_position());

	screen->draw_image(drawing, get_position(), width, height);
}

bool Canvas::point_inside (const size_t par_x, const size_t par_y)
{
	size_t low_bound_x = get_position().get_x();
	size_t low_bound_y = get_position().get_y();

	if (par_x >= low_bound_x && par_x < low_bound_x + get_width() && par_y >= low_bound_y && par_y <= low_bound_y + get_height())
		return true;

	return false;
}

bool Canvas::on_mouse (const Mouse_state state, const size_t par_x, const size_t par_y)
{
	if (!point_inside(par_x, par_y))
		return false;

	if (pencil->get_color() != current_drawing_color)
		current_drawing_color = pencil->get_color();

	if (state == Mouse_state::CLICKED)
	{
		drawing_state = true;
	}
	else if (state == Mouse_state::RELEASED)
	{
		drawing_state = false;

		return true;
	}
	else if (drawing_state)
	{
		size_t width = get_width();
		size_t height = get_height();

		size_t position_x = get_position().get_x();
		size_t position_y = get_position().get_y();

		// printf("%lu\n", (par_x - position_x) * height + (par_y - position_y));

		size_t begin_x = par_x - position_x > 10 ? par_x - position_x - 10 : par_x - position_x;
		size_t begin_y = par_y - position_y > 10 ? par_y - position_y - 10 : par_y - position_y;

		size_t end_x = par_x - position_x + 10 < width ? par_x - position_x + 10 : par_x - position_x;
		size_t end_y = par_y - position_y + 10 < height ? par_y - position_y + 10 : par_y - position_y;

		for (size_t i = begin_y; i < end_y; ++i)
			for (size_t j = begin_x; j < end_x; ++j)
				drawing[i * width + j] = current_drawing_color;
	}

	return true;
}
