#include "Radius_vector.hpp"

Radius_vector Radius_vector::reflect_vector(const Radius_vector& normal)
{
	Radius_vector tmp_normal(normal);
	Radius_vector tmp_vector(*this);

	// tmp_normal.set_length(1.0);
	tmp_normal /= tmp_normal.length();
	double projection = tmp_vector.scalar_multiplication(tmp_normal) * 2.0;
	if (projection < 0)
		projection *= -1;

	tmp_normal *= projection;
	tmp_vector += tmp_normal;

	return tmp_vector;
}

Radius_vector Radius_vector::mul_vector_and_matrix4(const Matrix_4 &matrix) const 
{
	Radius_vector result(*this);

	double vector_array[] = { get_x(), get_x(), get_x(), get_x(), 
	                          get_y(), get_y(), get_y(), get_y(),
	                          get_z(), get_z(), get_z(), get_z(),
	                              1.0,     1.0,     1.0,     1.0 };
	Matrix_4 other_matrix(vector_array);
	Matrix_4 to_multiply(matrix);
	to_multiply *= other_matrix;

	result.set_x(to_multiply.elements[0][0]);
	result.set_y(to_multiply.elements[1][1]);
	result.set_z(to_multiply.elements[2][2]);
 
    return result;
}


Radius_vector Radius_vector::rotate_point(const double angle_y, const double angle_z) const 
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

	Radius_vector radius_vector(mul_vector_and_matrix4(matrix_y));

	return radius_vector;
}
