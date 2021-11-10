#include "Canvas.hpp"

Canvas::Canvas(const Visual_object::Config &par_base, Pencil *par_pencil)
: Visual_object(par_base), pencil(par_pencil), current_drawing_color(BLACK), drawing_state(false)
{
	drawing = new Color[get_width() * get_height()];
	for (size_t i = 0; i < get_width() * get_height(); ++i)
		drawing[i] = WHITE;
}

// Canvas::Canvas(const size_t par_type, const Vector_ll &par_position, const Color &par_color, const size_t par_width, const size_t par_height, Pencil *par_pencil)
// : Visual_object(par_type, par_position, par_color, par_width, par_height)
// {
// 	pencil = par_pencil;

// 	current_drawing_color = BLACK;

// 	drawing = new Color[par_width * par_height];
// 	for (size_t i = 0; i < par_width * par_height; ++i)
// 		drawing[i] = WHITE;

// 	drawing_state = false;
// }

// Canvas::Canvas(const size_t par_type, const Vector_ll &par_position, Texture *par_texture, const size_t par_width, const size_t par_height, Pencil *par_pencil)
// : Visual_object(par_type, par_position, par_texture, par_width, par_height)
// {
// 	size_t new_width = par_texture->get_width();
// 	size_t new_height = par_texture->get_height();

// 	pencil = par_pencil;

// 	current_drawing_color = BLACK;

// 	drawing = new Color[par_width * par_height];
// 	for (size_t i = 0; i < par_width * par_height; ++i)
// 		drawing[i] = WHITE;

// 	drawing_state = false;
// }

void Canvas::draw_point(const size_t par_x, const size_t par_y)
{
	size_t width = get_width();
	size_t height = get_height();

	size_t position_x = get_position().get_x();
	size_t position_y = get_position().get_y();

	// size_t y_coord = position_y + get_height() - (par_y - position_y);

	size_t pencil_size = pencil->get_size() / 2;

	size_t begin_x = par_x - position_x > pencil_size ? par_x - position_x - pencil_size : par_x - position_x;
	size_t begin_y = par_y - position_y > pencil_size ? par_y - position_y - pencil_size : par_y - position_y;

	size_t end_x = par_x - position_x + pencil_size < width ? par_x - position_x + pencil_size : par_x - position_x;
	size_t end_y = par_y - position_y + pencil_size < height ? par_y - position_y + pencil_size : par_y - position_y;

	for (size_t i = begin_y; i < end_y; ++i)
		for (size_t j = begin_x; j < end_x; ++j)
			drawing[i * width + j] = current_drawing_color;

	get_texture()->set_texture(drawing, get_width(), get_height());
}

void Canvas::draw(Screen_information *screen)
{
	Visual_object::draw(screen);

	// size_t width = get_width();
	// size_t height = get_height();

	// Color current_color = get_color();

	// Vector_ll position(get_position());

	// screen->draw_image(drawing, get_position(), width, height);
}

bool Canvas::point_inside (const size_t par_x, const size_t par_y)
{
	size_t low_bound_x = get_position().get_x();
	size_t low_bound_y = get_position().get_y();

	if (par_x >= low_bound_x && par_x < low_bound_x + get_width() && par_y >= low_bound_y && par_y <= low_bound_y + get_height())
		return true;

	return false;
}

void Canvas::set_red (const unsigned char from, const unsigned char to)
{
	size_t width = get_width();
	size_t height = get_height();

	// printf("from: %u, to: %u\n", from, to);

	for (size_t i = 0; i < width * height; ++i)
	{
		if (drawing[i].get_r() == from)
		{
			drawing[i].set_r(to);
		}
	}

	get_texture()->set_texture(drawing, get_width(), get_height());
}

void Canvas::set_green (const unsigned char from, const unsigned char to)
{
	size_t width = get_width();
	size_t height = get_height();

	for (size_t i = 0; i < width * height; ++i)
	{
		if (drawing[i].get_g() == from)
		{
			drawing[i].set_g(to);
		}
	}

	get_texture()->set_texture(drawing, get_width(), get_height());
}

void Canvas::set_blue (const unsigned char from, const unsigned char to)
{
	size_t width = get_width();
	size_t height = get_height();

	for (size_t i = 0; i < width * height; ++i)
	{
		if (drawing[i].get_b() == from)
		{
			drawing[i].set_b(to);
		}
	}

	get_texture()->set_texture(drawing, get_width(), get_height());
}

bool Canvas::on_mouse_click (const bool state, const size_t par_x, const size_t par_y)
{
	if (!point_inside(par_x, par_y))
		return false;

	if (pencil->get_color() != current_drawing_color)
		current_drawing_color = pencil->get_color();

	if (state)
	{
		drawing_state = true;

		draw_point(par_x, par_y);
	}
	else if (!state)
	{
		drawing_state = false;

		return true;
	}

	return true;
}

bool Canvas::on_mouse_move(const Vector_ll from, const Vector_ll to)
{
	if (point_inside(to.get_x(), to.get_y()))
	{
		if (drawing_state)
		{
			draw_point(to.get_x(), to.get_y());
		}

		return true;
	}
	else
	{
		drawing_state = false;
		return false;
	}
}
