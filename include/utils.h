#ifndef UTILS_H
#define UTILS_H

class Vec3;

namespace utils
{
	const double fp_tolerance = 1e-8;
	int cmp_double(double first_double, double second_double);

	template <typename T>
	int sign(T val)
	{
		return (T(0) < val) - (val < T(0));
	}
	
}


#endif // UTILS_H
