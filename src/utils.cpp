#include "utils.h"
#include "vec.h"

#include <cmath>

int utils::cmp_double(double lhs, double rhs)
{
    if(std::isnan(lhs) && std::isnan(rhs))
    {
        return 0;
    }
    if (fabs(lhs - rhs) < fp_tolerance)
    {
        return 0;
    }
    else if ((lhs - rhs) > fp_tolerance)
    {
        return 1;
    }
    else
    {
        return -1;
    }
}

utils::Axis utils::get_max_axis(const Vec3& vec)
{
	if (utils::cmp_double(std::abs(vec.x()), std::abs(vec.y())) >= 0)
	{
		if (utils::cmp_double(std::abs(vec.x()), std::abs(vec.z())) >= 0)
		{
			return Axis::x;
		}

		return Axis::z;
	}
	else
	{
		if (utils::cmp_double(std::abs(vec.y()), std::abs(vec.z())) >= 0)
		{
			return Axis::y;
		}

		return Axis::z;
	}
}
