#ifndef RADIUS_VECTOR_CLASS
#define RADIUS_VECTOR_CLASS

#include <cmath>

// #include "../math_structures/Matrix_4.hpp"

class Radius_vector
{
private:
	double x;
	double y;
	// double z;

	bool valid;

public:

	Radius_vector(double par_x = 0.0, double par_y = 0.0) // double par_z = 0.0
	{
		x = par_x;
		y = par_y;
		// z = par_z;

		valid = true;
	}
	Radius_vector(const Radius_vector& other)
	{
		x = other.x;
		y = other.y;
		// z = other.z;

		valid = true;
	}

	const Radius_vector& operator=(const Radius_vector& other) { x = other.get_x(); y = other.get_y(); return *this; } // z = other.get_z(); 

	const Radius_vector& operator+=(const Radius_vector &other) { x += other.get_x(); y += other.get_y(); return *this; } // z += other.get_z();
	const Radius_vector& operator-=(const Radius_vector &other) { x -= other.get_x(); y -= other.get_y(); return *this; } // z -= other.get_z(); 
	const Radius_vector& operator*=(const double scale) { x *= scale; y *= scale; return *this; } // z *= scale;
	const Radius_vector& operator/=(const double scale) 
	{ 
		if (scale == 0) 
		{
			valid = false;
			return *this; 
		}

		x /= scale; y /= scale; // z /= scale; 
		return *this; 
	} 
	
	const Radius_vector operator+(const Radius_vector &other) const { return { x + other.get_x(), y + other.get_y() }; } // z + other.get_z() 
	const Radius_vector operator-(const Radius_vector &other) const { return { x - other.get_x(), y - other.get_y() }; } // z - other.get_z()
	const Radius_vector operator*(const double scale) const { return { x * scale, y * scale }; } // z * scale
	const Radius_vector operator/(const double scale) const 
	{
		if (scale == 0) 
		{
			return Radius_vector(*this); 
		}

		return { x / scale, y / scale };
	}
	
	void componentwise_multiplication(const Radius_vector &other)
	{ 
		x *= other.get_x();
		y *= other.get_y();
		// z *= other.get_z();
	}

	const double scalar_multiplication(const Radius_vector &other) const
	{
		return x * other.get_x() + y * other.get_y(); // + z * other.get_z()
	}

	const double length() const
	{
		return sqrt(x * x + y * y); // + z * z
	}

	double get_x() const { return x; }
	double get_y() const { return y; }
	// double get_z() const { return z; }

	void set_x(double par_x) { x = par_x; }
	void set_y(double par_y) { y = par_y; }
	// void set_z(double par_z) { z = par_z; }

	Radius_vector reflect_vector         (const Radius_vector& normal);
	// Radius_vector mul_vector_and_matrix4 (const Matrix_4 &matrix) const;
	// Radius_vector rotate_point           (const double angle_y, const double angle_z) const;

	void normalization();
	const Radius_vector normal() const { return Radius_vector(-1 * y, x); } 
	const double get_angle(const Radius_vector &other) { return acos(scalar_multiplication(other)/(length() * other.length())); }
	const double get_cos_angle(const Radius_vector &other) { return scalar_multiplication(other)/(length() * other.length()); }
	const double get_projection(const Radius_vector &other) { if (!length()) return 0; return scalar_multiplication(other)/length(); }
};

#endif // RADIUS_VECTOR_CLASS
