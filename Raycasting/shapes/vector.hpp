#ifndef VECTOR_SHAPE
#define VECTOR_SHAPE

/**
 * Todo: separate vectors from each other
 * 
 * 
 */

#include <cmath>

#include "shape_base.hpp"

#include "simple_drawing.hpp"

extern const sf::Color DEFAULT_COLOR; 

extern const double ARROW_ANGLE;
extern const double ARROW_LEN_PERCENTAGE;
extern const double ARROW_LEN_DEFAULT;
extern const double VECTOR_LEN_DEFAULT;

extern const double CIRCLE_RADIUS;

Point_3d rotate_point_on_flat(Point_3d point_0, Point_3d point, double angle);

class Vector_3d : public Shape
{

protected:
	Point_3d begin_point;
	Point_3d end_point;

public:
	Vector_3d(Point_3d par_begin_point, Point_3d par_end_point);
	Vector_3d(const Vector_3d &other);

	virtual void draw_shape(sf::RenderWindow *window);

	Point_3d get_begin_point() const { return begin_point; }
	Point_3d get_end_point()   const { return end_point; }

	virtual void set_end_point(Point_3d par_end_point);

	const Vector_3d operator+=(const Vector_3d &other)
	{
		return Vector_3d(begin_point += other.get_begin_point(), end_point += other.get_end_point());
	}
	const Vector_3d operator*=(const double scale)
	{
		Point_3d radius_vector = end_point;

		radius_vector -= begin_point;
		radius_vector *= scale;

		return Vector_3d(begin_point, end_point += radius_vector);
	}

	const Vector_3d normalize();
	const Vector_3d to_mathematical() const;
	const double    scalar_multiplication(const Vector_3d &other) const;
	const double    length() const;
	const double    cosine_of_angle_between(const Vector_3d &other);
};

class Vector_w_arrow_3d : public Vector_3d
{

private:
	Point_3d left_tail_end;
	Point_3d right_tail_end;

	void calculate_arrow_ends(double par_projection_y, double par_projection_x, double par_projection_z);

public:
	Vector_w_arrow_3d(Point_3d par_begin_point, Point_3d par_end_point);

	virtual void draw_shape(sf::RenderWindow *window);

	virtual void set_end_point(Point_3d par_end_point);

	const Vector_w_arrow_3d operator+=(const Vector_w_arrow_3d &other)
	{
		return Vector_w_arrow_3d(begin_point += other.get_begin_point(), end_point += other.get_end_point());
	}
	const Vector_w_arrow_3d operator*=(const double scale)
	{
		Point_3d radius_vector = end_point;

		radius_vector -= begin_point;
		radius_vector *= scale;
		
		return Vector_w_arrow_3d(begin_point, end_point += radius_vector);
	}

	const Vector_w_arrow_3d normalize();
};

#endif // VECTOR_SHAPE
