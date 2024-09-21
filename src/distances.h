#ifndef DISTANCES_H
#define DISTANCES_H

#include <cmath>

#include "vec3.h"
#include "triangle.h"
#include "plane.h"
#include "utils.h"

class Distances
{
  private:
	double first_;
	double second_;
	double third_;

	double calc_dist(const Point3& pnt, const Plane3& plane) const
	{
		return dot(plane.normal, pnt) + plane.origin;
	}

  public:
	Distances(const Triangle& triangle, const Plane3& plane):
		first_	(calc_dist(triangle.pnt_1, plane))
		, secind(calc_dist(triangle.pnt_2, plane))
		, third	(calc_dist(triangle.pnt_3, plane)) {}

	bool same_sign() const
	{
		if (std::fabs(a) < utils::fp_tolerance
			|| std::fabs(b) < utils::fp_tolerance
			|| std::fabs(c) < utils::fp_tolerance)
		{
			return false;
		}

		return (a > 0 && b > 0 && c > 0) || (a < 0 && b < 0 && c < 0);
	}

	bool are_trivial() const
	{
		return first_.near_zero() && second_.near_zero() && third_.near_zero();
	}



};

#endif // DISTANCES_H
