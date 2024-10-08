#ifndef BOUNDING_BOX_H
#define BOUNDING_BOX_H

#include "vec.h"

class Triangle3;

class Bounding_box
{
  private:
	Point3 min_;
	Point3 max_;

  public:
	Bounding_box(const Point3& min, const Point3& max) :
		min_(min), max_(max) {}

	Bounding_box(const Triangle3& triangle);

	const Point3& min() const { return min_; }
	const Point3& max() const { return max_; }
};

#endif // BOUNDING_BOX_H
