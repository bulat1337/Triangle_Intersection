#ifndef DISTANCES_H
#define DISTANCES_H

#include "plane.h"  // for Plane3
#include "vec.h"    // for dot, Point3

class Triangle3;

class Distances
{
  public:
	double first;
	double second;
	double third;

  private:
	double calc_dist(const Point3& pnt, const Plane3& plane) const
	{
		return dot(plane.normal(), pnt) + plane.origin();
	}

  public:
	Distances(const Triangle3& triangle, const Plane3& plane);

	bool same_sign() const;
	bool are_trivial() const;
};

#endif // DISTANCES_H
