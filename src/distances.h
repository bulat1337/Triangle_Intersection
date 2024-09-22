#ifndef DISTANCES_H
#define DISTANCES_H

#include <cmath>

#include "vec.h"
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
		return dot(plane.normal(), pnt) + plane.origin();
	}

  public:
	Distances(const Triangle<Point3>& triangle, const Plane3& plane):
		first_		(calc_dist(triangle.pnt_1(), plane))
		, second_	(calc_dist(triangle.pnt_2(), plane))
		, third_	(calc_dist(triangle.pnt_3(), plane)) {}

	bool same_sign() const
	{
		if (std::fabs(first_) < utils::fp_tolerance
			|| std::fabs(second_) < utils::fp_tolerance
			|| std::fabs(third_) < utils::fp_tolerance)
		{
			return false;
		}

		return 	(first_ > 0 && second_ > 0 && third_ > 0)
				|| (first_ < 0 && second_ < 0 && third_ < 0);
	}

	bool are_trivial() const
	{
		return 	(std::fabs(first_) < utils::fp_tolerance
				&& std::fabs(second_) < utils::fp_tolerance
				&& std::fabs(third_) < utils::fp_tolerance);
	}

	double first() const
	{
		return first_;
	}

	double second() const
	{
		return second_;
	}

	double third() const
	{
		return third_;
	}



};

#endif // DISTANCES_H
