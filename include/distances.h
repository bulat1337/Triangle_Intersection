#ifndef DISTANCES_H
#define DISTANCES_H

#include <cmath>
#include "vec.h"
#include "plane.h"
#include "utils.h"

template <typename Point>
class Triangle;

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
	Distances(const Triangle<Point3>& triangle, const Plane3& plane);

	double first() const { return first_; }
	double second() const { return second_; }
	double third() const { return third_; }

	double& first() { return first_; }
	double& second() { return second_; }
	double& third() { return third_; }

	bool same_sign() const;
	bool are_trivial() const;
};

#endif // DISTANCES_H
