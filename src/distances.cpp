#include "distances.h"

#include "triangle.h"

Distances::Distances(const Triangle<Point3>& triangle, const Plane3& plane)
	: first_(calc_dist(triangle.pnt_1(), plane)),
	  second_(calc_dist(triangle.pnt_2(), plane)),
	  third_(calc_dist(triangle.pnt_3(), plane))
{
	std::clog << "Distance of " << triangle.pnt_1() << " is " << first_ << '\n';
	std::clog << "Distance of " << triangle.pnt_2() << " is " << second_ << '\n';
	std::clog << "Distance of " << triangle.pnt_3() << " is " << third_ << '\n';
}

bool Distances::same_sign() const
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

bool Distances::are_trivial() const
{
	return (std::fabs(first_) < utils::fp_tolerance
			&& std::fabs(second_) < utils::fp_tolerance
			&& std::fabs(third_) < utils::fp_tolerance);
}
