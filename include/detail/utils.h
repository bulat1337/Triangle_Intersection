#ifndef UTILS_H
#define UTILS_H

#include <cmath>   // for isnan, fabs
#include <cstdlib> // for abs

#include "vec.h" // for Vec3

namespace t_inter
{

namespace detail
{

namespace utils
{
const double fp_tolerance = 1e-8;

inline int cmp_double(double lhs, double rhs)
{
    if (std::isnan(lhs) && std::isnan(rhs))
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

template <typename T> int sign(T val) { return (T(0) < val) - (val < T(0)); }

enum class Axis
{
    x,
    y,
    z
};

template <typename FltPnt> Axis get_max_axis(const Vec3<FltPnt> &vec)
{
    if (cmp_double(std::abs(vec.x), std::abs(vec.y)) >= 0)
    {
        if (cmp_double(std::abs(vec.x), std::abs(vec.z)) >= 0)
        {
            return Axis::x;
        }

        return Axis::z;
    }
    else
    {
        if (cmp_double(std::abs(vec.y), std::abs(vec.z)) >= 0)
        {
            return Axis::y;
        }

        return Axis::z;
    }
}
} // namespace utils

}; // namespace detail

}; // namespace t_inter

#endif // UTILS_H
