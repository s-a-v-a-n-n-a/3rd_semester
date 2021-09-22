#ifndef BIND_VECTOR_CLASS
#define BIND_VECTOR_CLASS

#include "Radius_vector.hpp"
#include "../math_structures/math_functions.hpp"

#include "../math_structures/Matrix_4.hpp"

class Bind_vector
{
	Radius_vector begin;
	Radius_vector end;

public:
	Bind_vector(Radius_vector par_begin, Radius_vector par_end);
	Bind_vector(const Bind_vector& other);

	void set_begin_point(const Radius_vector& par_begin) { begin = par_begin; }
	void set_end_point  (const Radius_vector& par_end)   { end = par_end; }

	void set_length(double par_length);

	Radius_vector get_begin_point () const { return begin; }
	Radius_vector get_end_point   () const { return end; }

	double get_length() const { return sqrt((end.get_x() - begin.get_x()) * (end.get_x() - begin.get_x()) + (end.get_y() - begin.get_y()) * (end.get_y() - begin.get_y()) + (end.get_z() - begin.get_z()) * (end.get_z() - begin.get_z())); }

	Bind_vector reflect_vector_relative_vector(const Bind_vector& vector_0);

	Radius_vector to_radius_vector() const
	{
		return Radius_vector(end - begin);
	}

	Bind_vector& operator*=(const double scale)
	{
		Radius_vector radius_vector = end;

		radius_vector -= begin;
		radius_vector *= scale;
		
		end = begin;
		end += radius_vector;

		return *this;
	} 

	

	// void rotate_point(double angle);

	Radius_vector mul_vector_and_matrix4(const Matrix_4 &matrix, const Radius_vector &vector)
	{
		Radius_vector result(vector);

		Matrix_4 other_matrix(vector, vector, vector, vector);
		Matrix_4 to_multiply(matrix);
 		to_multiply *= other_matrix;

 		result.set_x(to_multiply.elements[0][0]);
 		result.set_y(to_multiply.elements[1][1]);
 		result.set_z(to_multiply.elements[2][2]);
	 
	    return result;
	}

	void rotate_point(double angle_y, double angle_z)
	{
		double cos_y = cos(angle_y);
		double sin_y = sin(angle_y);

		double cos_z = cos(angle_z);
		double sin_z = sin(angle_z);

		
		double array_y[] = { cos_y,      0, sin_y, 0,
						     0,          1, 0,     0,
						     -1 * sin_y, 0, cos_y, 0,
						     0,          0, 0,     1 };
		Matrix_4 matrix_y(array_y);

		double array_z[] = { cos_z, -1 * sin_z, 0, 0,
						     sin_z,      cos_z, 0, 0,
						     0,          0,     1, 0,
						     0,          0,     0, 1 };
		Matrix_4 matrix_z(array_z);

		matrix_y *= matrix_z;

		Radius_vector radius_vector = to_radius_vector();
		radius_vector = mul_vector_and_matrix4(matrix_y, radius_vector);

		end = begin;
		end += radius_vector;
	}
};

#endif // BIND_VECTOR_CLASS
