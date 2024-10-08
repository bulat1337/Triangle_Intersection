#ifndef DISTANCES_H
#define DISTANCES_H

#include "plane.h"  // for Plane3
#include "vec.h"    // for dot, Point3

class Triangle3;

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
	Distances(const Triangle3& triangle, const Plane3& plane);

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
