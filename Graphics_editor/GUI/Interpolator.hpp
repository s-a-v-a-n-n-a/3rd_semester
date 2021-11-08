#ifndef INTERPOLATOR_H
#define INTERPOLATOR_H

#include <vector>
#include <cmath>

#include "../GUI/Visual_object_base.hpp"
#include "../GUI/Button.hpp"

#include "../Editor/Graphical_delegates.hpp"

#include "../simple_list/simple_list.hpp"

const size_t DECREASED_DOT_SIZE = 5;
const size_t DEFAULT_DOT_SIZE = 10;

void merging_length(std::vector<Vector_d> &arr, long long sz_arr_1, long long sz_arr, long long index_to_begin);
void merge_sort(std::vector<Vector_d> &arr, long long sz_arr, long long index_to_begin, void merging(std::vector<Vector_d> &arr, long long sz_arr_1, long long sz_arr, long long index_to_begin));

class Interpolator
{
private:
	std::vector<Vector_d> reference_points;
public:
	Interpolator(const std::vector<Vector_d> &par_reference_points)
	{
		size_t points_amount = par_reference_points.size();
		for (size_t i = 0; i < points_amount; ++i)
		{
			reference_points.push_back(par_reference_points[i]);
		}

		merge_sort(reference_points, points_amount, 0, merging_length);
	}

	void add_point(const Vector_d &par_point)
	{
		// resort
		reference_points.push_back(par_point);
		size_t points_amount = reference_points.size();
		
		Vector_d tmp_point = par_point;
		Vector_d point = par_point;

		size_t index_to_insert = 1;
		for (size_t i = 0; i < points_amount - 1; ++i)
		{
			if (point.get_x() >= reference_points[i].get_x() && point.get_x() <= reference_points[i + 1].get_x())
			{
				index_to_insert = i + 1;
				break;
			}
			
			index_to_insert++;
		}

		for (size_t i = index_to_insert; i < points_amount; ++i)
		{
			point = tmp_point;
			tmp_point = reference_points[i];
			
			reference_points[i] = point;
		}
	}

	double get_t(const Vector_d &point_0, const Vector_d &point_1, double t, double alpha) 
	{
	    Vector_d d = point_1 - point_0;
	    double a = d.scalar_multiplication(d);
	    double b = std::pow(a, alpha * 0.5);
	    return (b + t);
	}

	double linear_interpolation(double a, double b, double t)
	{
		if (t >= 0 && t <= 1)
			return a + (b - a) * t;
		else if (t < 0)
			return a;
		else
			return b;
	}

	// code from wikipedia
	Vector_d interpolation(const Vector_d &point_0, const Vector_d &point_1, const Vector_d &point_2, const Vector_d &point_3, double t, double alpha)
	{
		// Vector_d direction = point_1 - point_0;
		// direction.normalization();

		// if (direction.get_x())
		// {
		// 	return point_0 + direction * (t - point_0.get_x()) / direction.get_x();
		// }
		// else 
		// 	return point_1;

		double t1 = 0.0f;
	    double t2 = get_t(point_0, point_1, t1, alpha);
	    double t3 = get_t(point_1, point_2, t2, alpha);
	    double t4 = get_t(point_2, point_3, t3, alpha);

	    t = linear_interpolation(t2, t3, t);
	    Vector_d A1 = point_0 * ((t2 - t) / (t2 - t1)) + point_1 * ((t - t1) / (t2 - t1));
	    Vector_d A2 = point_1 * ((t3 - t) / (t3 - t2)) + point_2 * ((t - t2) / (t3 - t2));
	    Vector_d A3 = point_2 * ((t4 - t) / (t4 - t3)) + point_3 * ((t - t3) / (t4 - t3));

	    Vector_d B1 = A1 * ((t3 - t) / (t3 - t1)) + A2 * ((t - t1) / (t3 - t1));
	    Vector_d B2 = A2 * ((t4 - t) / (t4 - t2)) + A3 * ((t - t2) / (t4 - t2));
	    
	    Vector_d C  = B1 * ((t3 - t) / (t3 - t2)) + B2 * ((t - t2) / (t3 - t2));
	    
	    return C;
	}
	

	Vector_d get_point(double x, size_t *last_ref_point)
	{
		printf("reference points amount: %lu\n", reference_points.size());

		while (*last_ref_point + 1 < reference_points.size() && x > reference_points[*last_ref_point + 1].get_x())
		{
			(*last_ref_point)++;
		}
		
		if (*last_ref_point == 0)
		{
			Vector_d point_0 = Vector_d(reference_points[0].get_x() - DEFAULT_DOT_SIZE, reference_points[0].get_y());
			
			Vector_d point_1 = Vector_d(reference_points[0].get_x(), reference_points[0].get_y());
			Vector_d point_2 = Vector_d(reference_points[1].get_x(), reference_points[1].get_y());

			Vector_d point_3 = point_2;

			if (reference_points.size() <= 2)
			{
				point_3 = Vector_d(reference_points[1].get_x(), reference_points[1].get_y() + DEFAULT_DOT_SIZE);
			}
			else
				point_3 = Vector_d(reference_points[*last_ref_point + 2].get_x(), reference_points[*last_ref_point + 2].get_y());

			printf("0 p0: %lg, %lg; p1: %lg, %lg; p2: %lg, %lg; p3: %lg, %lg\n", point_0.get_x(), point_0.get_y(), point_1.get_x(), point_1.get_y(), point_2.get_x(), point_2.get_y(), point_3.get_x(), point_3.get_y());
			printf("t: %lg\n", (x - point_1.get_x())/(point_2.get_x() - point_1.get_x()));
			return interpolation(point_0, point_1, point_2, point_3, (x - point_1.get_x())/(point_2.get_x() - point_1.get_x()), 0.5);
		}
		
		if (*last_ref_point == reference_points.size() - 2)
		{
			Vector_d point_1 = Vector_d(reference_points[*last_ref_point].get_x(), reference_points[*last_ref_point].get_y());
			Vector_d point_2 = Vector_d(reference_points[*last_ref_point + 1].get_x(), reference_points[*last_ref_point + 1].get_y());

			Vector_d point_3 = Vector_d(reference_points[*last_ref_point + 1].get_x(), reference_points[*last_ref_point + 1].get_y() + DEFAULT_DOT_SIZE);
			
			Vector_d point_0 = point_1;

			if (reference_points.size() <= 2)
			{
				point_0 = Vector_d(reference_points[0].get_x() - DEFAULT_DOT_SIZE, reference_points[0].get_y());
			}
			else
				point_0 = Vector_d(reference_points[*last_ref_point - 1].get_x(), reference_points[*last_ref_point - 1].get_y());

			printf("1 p0: %lg, %lg; p1: %lg, %lg; p2: %lg, %lg; p3: %lg, %lg\n", point_0.get_x(), point_0.get_y(), point_1.get_x(), point_1.get_y(), point_2.get_x(), point_2.get_y(), point_3.get_x(), point_3.get_y());
			printf("t: %lg\n", (x - point_1.get_x())/(point_2.get_x() - point_1.get_x()));
			return interpolation(point_0, point_1, point_2, point_3, (x - point_1.get_x())/(point_2.get_x() - point_1.get_x()), 0.5);

		}

		// Vector_d point_0 = reference_points[(*last_ref_point)]; 
		// Vector_d point_1 = reference_points[(*last_ref_point) + 1];

		// Vector_d closest = point_1 - point_0;
		Vector_d point_0 = reference_points[(*last_ref_point) - 1]; 

		Vector_d point_1 = reference_points[(*last_ref_point)]; 
		Vector_d point_2 = reference_points[(*last_ref_point) + 1];
		
		Vector_d point_3 = reference_points[(*last_ref_point) + 2];

		Vector_d closest = point_1 - point_0;

		printf("x p0: %lg, %lg; p1: %lg, %lg; p2: %lg, %lg; p3: %lg, %lg\n", point_0.get_x(), point_0.get_y(), point_1.get_x(), point_1.get_y(), point_2.get_x(), point_2.get_y(), point_3.get_x(), point_3.get_y());
		printf("t: %lg\n", (x - point_1.get_x())/(point_2.get_x() - point_1.get_x()));
		return interpolation(point_0, point_1, point_2, point_3, (x - point_1.get_x())/(point_2.get_x() - point_1.get_x()), 0.5);
		// return interpolation(point_0, point_1, point_0, point_1, x, 0.5);
	}
};

class Spline : public Visual_object
{
private:
	std::vector<Vector_d> points;

public:
	Spline(const size_t par_type, const Vector_ll &par_position, const Color &par_color, const size_t par_width = 0, const size_t par_height = 0)
	: Visual_object(par_type, par_position, par_color, par_width, par_height), points(par_width, 0)
	{
		// Button *left  = create_spline_dot(par_position + Vector_ll(0, par_height - DEFAULT_DOT_SIZE), DEFAULT_DOT_SIZE, DEFAULT_DOT_SIZE);
		Button *left = new Button((size_t)Vidget_type::BUTTON, par_position + Vector_ll(0, par_height), BLACK, DEFAULT_DOT_SIZE, DEFAULT_DOT_SIZE, NULL, "");
		Drag_and_drop_delegate *drag = new Drag_and_drop_delegate(left);
		left->set_delegate(drag);

		get_objects()->add_to_end(left);
		
		// printf("added left one\n");

		Button *right = create_spline_dot(par_position + Vector_ll(par_width, 0), DEFAULT_DOT_SIZE, DEFAULT_DOT_SIZE);
		
		printf("added right one\n");
	}
	~Spline() = default;

	Button *create_spline_dot(const Vector_ll &position, const size_t width, const size_t height)
	{
		Button *dot = new Button((size_t)Vidget_type::BUTTON, position, BLACK, width, height, NULL, "");
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
			// printf("y is %lg\n", points[i].get_y());
		}
	}

	void add_visual_object(Visual_object *par_object) override
	{
		std::vector<Vector_d> reference_points;

		size_t points_amount = get_objects()->get_length();
		Visual_object **points_array = get_objects()->get_array();
		
		// reference_points.push_back(Vector_d(points_array[0]->get_position().get_x() - get_position().get_x(), points_array[0]->get_position().get_y() - get_position().get_y() + DEFAULT_DOT_SIZE));
		// reference_points.push_back(Vector_d(points_array[1]->get_position().get_x() - get_position().get_x() + DEFAULT_DOT_SIZE, points_array[1]->get_position().get_y() - get_position().get_y()));
		for (size_t i = 0; i < points_amount; ++i)
		{
			// printf(":)\n");
			reference_points.push_back(Vector_d(points_array[i]->get_position().get_x() - get_position().get_x(), points_array[i]->get_position().get_y() - get_position().get_y()));
		}
		printf("reference_points size %lu\n", reference_points.size());

		Interpolator *interpolator = new Interpolator(reference_points);
		interpolator->add_point(Vector_d(par_object->get_position().get_x() - get_position().get_x(), par_object->get_position().get_y() - get_position().get_y()));

		recount(interpolator);

		delete interpolator;

		get_objects()->add_to_end(par_object);
	}

	void draw(Screen_information *screen) override
	{
		// Visual_object::draw(screen);
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
	
	bool on_mouse_click (const bool state, const size_t par_x, const size_t par_y) override
	{
		if (point_inside(par_x, par_y))
		{
			size_t points_amount = get_objects()->get_length();
			
			for (long long i = (long long)points_amount - 1; i >= 0; --i)
			{
				if ((get_objects()->get_array()[i])->on_mouse_click(state, par_x, par_y))//(((get_objects()->get_array()[i])->get_reactive() || state == Mouse_state::MOVED) && (get_objects()->get_array()[i])->on_mouse(state, par_x, par_y)) // ??????
				{
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
			}
		}

		return false;
	}
	
	// bool on_mouse_move	(const Vector_ll from, const Vector_ll to) override;
};

#endif // INTERPOLATOR_H
