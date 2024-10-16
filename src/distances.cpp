#include "distances.h"

#include <cmath>       // for fabs

#include "triangle.h"  // for Triangle3
#include "utils.h"     // for fp_tolerance

Distances::Distances(const Triangle3& triangle, const Plane3& plane)
	: first(calc_dist(triangle.pnt_1(), plane)),
	  second(calc_dist(triangle.pnt_2(), plane)),
	  third(calc_dist(triangle.pnt_3(), plane)) {}

bool Distances::same_sign() const
{
	if (std::fabs(first) < utils::fp_tolerance
		|| std::fabs(second) < utils::fp_tolerance
		|| std::fabs(third) < utils::fp_tolerance)
	{
		return false;
	}

	return 	(first > 0 && second > 0 && third > 0)
			|| (first < 0 && second < 0 && third < 0);
}

bool Distances::are_trivial() const
{
	return (std::fabs(first) < utils::fp_tolerance
			&& std::fabs(second) < utils::fp_tolerance
			&& std::fabs(third) < utils::fp_tolerance);
}
