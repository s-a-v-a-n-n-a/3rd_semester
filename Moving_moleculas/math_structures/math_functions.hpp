#ifndef MATH_FUNCTIONS
#define MATH_FUNCTIONS

const double EPSILON = 0.0000001;

inline double cosine_scalar(double scalar, double length_1, double length_2)
{
	if (!length_1 || !length_2)
		return 0;

	return scalar/(length_1 * length_2);
}

inline double calculate_power(double value, int power)
{
	if (power == 0)
		return 1.0;

	double answer = 1.0;
	double multiplier = value;

	while (power)
	{
		if (power & 1)
			answer = (answer * multiplier);
		multiplier *= multiplier;
		power >>= 1;
	}

	return answer;
}

#endif // MATH_FUNCTIONS
