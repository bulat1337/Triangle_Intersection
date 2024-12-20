#ifndef DISTANCES_H
#define DISTANCES_H

#include <cmath> // for fabs

#include "plane.h" // for Plane3
#include "utils.h" // for fp_tolerance
#include "vec.h"   // for dot, Point3

namespace t_inter
{

namespace detail
{

template <typename FltPnt> class Distances final
{
  public:
    FltPnt first;
    FltPnt second;
    FltPnt third;

  private:
    FltPnt calc_dist(const Point3<FltPnt> &pnt,
                     const Plane3<FltPnt> &plane) const
    {
        return static_cast<FltPnt>(dot(plane.normal(), pnt) + plane.origin());
    }

  public:
    Distances(const Point3<FltPnt> &pnt_1, const Point3<FltPnt> &pnt_2,
              const Point3<FltPnt> &pnt_3, const Plane3<FltPnt> &plane)
        : first(calc_dist(pnt_1, plane))
        , second(calc_dist(pnt_2, plane))
        , third(calc_dist(pnt_3, plane))
    {}

    bool same_sign() const
    {
        if (std::fabs(first) < utils::fp_tolerance ||
            std::fabs(second) < utils::fp_tolerance ||
            std::fabs(third) < utils::fp_tolerance)
        {
            return false;
        }

        return (first > 0 && second > 0 && third > 0) ||
               (first < 0 && second < 0 && third < 0);
    }

    bool are_trivial() const
    {
        return (std::fabs(first) < utils::fp_tolerance &&
                std::fabs(second) < utils::fp_tolerance &&
                std::fabs(third) < utils::fp_tolerance);
    }
};

}; // namespace detail

}; // namespace t_inter

#endif // DISTANCES_H
