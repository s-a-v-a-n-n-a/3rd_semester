#ifndef SPLINE_H 
#define SPLINE_H

#include "../GUI/Visual_object_base.hpp"
#include "../GUI/Button.hpp"

#include "../Editor/Graphical_delegates.hpp"

#include "../simple_list/simple_list.hpp"

#include "../math_structures/Interpolator.hpp"

const size_t DECREASED_DOT_SIZE = 5;
const size_t DEFAULT_DOT_SIZE = 10;

class Spline : public Visual_object
{
private:
	Button_delegate *delegate;

	std::vector<Vector_d> points;

	long long high_limit;
	long long low_limit;

public:
	Spline(const Visual_object::Config &par_base, Button_delegate *par_delegate)
	: Visual_object(par_base), points(get_width(), 0), delegate(par_delegate), high_limit(MAX_COLOR_VALUE), low_limit(MAX_COLOR_VALUE)
	{
		Button *left = new Button({(size_t)Vidget_type::BUTTON, get_position() + Vector_ll(0, get_height()), nullptr, BLACK, DEFAULT_DOT_SIZE, DEFAULT_DOT_SIZE}, NULL, "");
		Drag_and_drop_delegate *drag = new Drag_and_drop_delegate(left);
		left->set_delegate(drag);

		get_objects()->add_to_end(left);

		Button *right = create_spline_dot(get_position() + Vector_ll(get_width(), 0), DEFAULT_DOT_SIZE, DEFAULT_DOT_SIZE);
	}
	~Spline() { delete delegate; };

	void set_delegate(Button_delegate *par_delegate) { delegate = par_delegate; }

	Button *create_spline_dot(const Vector_ll &position, const size_t width, const size_t height)
	{
		Button *dot = new Button({(size_t)Vidget_type::BUTTON, position, nullptr, BLACK, width, height}, NULL, "");
		Drag_and_drop_delegate *drag = new Drag_and_drop_delegate(dot);
		dot->set_delegate(drag);

		add_visual_object(dot);

		return dot;
	}

	void recount(Interpolator *interpolator)
	{
		size_t width = get_width();
		size_t last_reference = 0;
		for (size_t i = 0; i < width; ++i)
		{
			points[i] = interpolator->get_point(i, &last_reference); 
		}
	}

	void add_visual_object(Visual_object *par_object) override
	{
		std::vector<Vector_d> reference_points;

		size_t points_amount = get_objects()->get_length();
		Visual_object **points_array = get_objects()->get_array();
		
		for (size_t i = 0; i < points_amount; ++i)
		{
			reference_points.push_back(Vector_d(points_array[i]->get_position().get_x() - get_position().get_x(), points_array[i]->get_position().get_y() - get_position().get_y()));
		}
		
		Interpolator *interpolator = new Interpolator(reference_points);
		interpolator->add_point(Vector_d(par_object->get_position().get_x() - get_position().get_x(), par_object->get_position().get_y() - get_position().get_y()));

		recount(interpolator);

		delete interpolator;

		get_objects()->add_to_end(par_object);
	}

	void draw(Screen_information *screen) override
	{
		screen->draw_rectangle(get_position(), get_color(), get_width(), get_height());

		Visual_object **objects_array = get_objects()->get_array();
		size_t objects_amount = get_objects()->get_length();

		for (size_t i = 2; i < objects_amount; ++i)
		{
			if (objects_array[i]->get_visible())
			{
				objects_array[i]->draw(screen);
			}
		}

		size_t points_amount = get_width();
		for (size_t i = 0; i < points_amount - 1; ++i)
		{
			screen->draw_line(Vector_ll((size_t)points[i].get_x() + get_position().get_x() + DEFAULT_DOT_SIZE/2, (size_t)points[i].get_y() + get_position().get_y() + DEFAULT_DOT_SIZE/2), Vector_ll((size_t)points[i + 1].get_x() + get_position().get_x() + DEFAULT_DOT_SIZE/2, (size_t)points[i + 1].get_y() + get_position().get_y() + DEFAULT_DOT_SIZE/2), BLACK); // а если хочу разноцветные линии?
		}
	}

	Vector_ll create_color_relation(const size_t max_x, const size_t max_y, const size_t par_x, const size_t par_y)
	{
		double scale_x = ((double)(par_x - get_position().get_x()) / (double)get_width());
		double scale_y = ((double)(par_y - get_position().get_y()) / (double)get_height());

		return Vector_ll((size_t)(((double)max_x) * scale_x), (size_t)(((double)max_y) * scale_y));
	}
	
	bool on_mouse_click (const bool state, const size_t par_x, const size_t par_y) override
	{
		if (point_inside(par_x, par_y))
		{
			size_t points_amount = get_objects()->get_length();
			
			for (long long i = (long long)points_amount - 1; i >= 0; --i)
			{
				if ((get_objects()->get_array()[i])->on_mouse_click(state, par_x, par_y))//(((get_objects()->get_array()[i])->get_reactive() || state == Mouse_state::MOVED) && (get_objects()->get_array()[i])->on_mouse(state, par_x, par_y)) // ??????
				{
					Vector_ll par = create_color_relation(MAX_COLOR_VALUE, MAX_COLOR_VALUE, par_x, par_y);

					delegate->on_mouse_click(par.get_x(), par.get_y());

					return true;
				}

				set_active_state(false);
			}

			Interpolator *interpolator = new Interpolator(points);
			size_t reference_index = 0;
			Vector_d check_point = interpolator->get_point((double)par_x - get_position().get_x(), &reference_index);

			if (check_point.get_y() + DEFAULT_DOT_SIZE >= par_y - get_position().get_y() && check_point.get_y() - DEFAULT_DOT_SIZE <= par_y - get_position().get_y())
			{
				Button *new_dot = create_spline_dot(Vector_ll(par_x, par_y), DEFAULT_DOT_SIZE, DEFAULT_DOT_SIZE);

				Vector_ll par = create_color_relation(MAX_COLOR_VALUE, MAX_COLOR_VALUE, par_x, par_y);
				
				delegate->on_mouse_click(par.get_x(), par.get_y());
			}
		}

		return false;
	}
	
	bool on_mouse_move (const Vector_ll from, const Vector_ll to) override
	{
		bool standart_result = Visual_object::on_mouse_move(from, to);

		if (standart_result && delegate)
		{
			delegate->on_mouse_move(from, create_color_relation(MAX_COLOR_VALUE, MAX_COLOR_VALUE, to.get_x(), to.get_y()));
		}

		return standart_result;
	}
};

#endif // SPLINE_H
