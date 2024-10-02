#ifndef BOUNDING_BOX_H
#define BOUNDING_BOX_H

#include "cmath"

#include "vec.h"
#include "triangle.h"

class Bounding_box
{
  private:
	Point3 min_;
	Point3 max_;

  public:
	Bounding_box(const Point3& min, const Point3& max) :
		min_(min), max_(max) {}

	Bounding_box(const Triangle3& triangle)
	{
		min_.x() = std::min({triangle.pnt_1().x(), triangle.pnt_2().x(), triangle.pnt_3().x()});
		min_.y() = std::min({triangle.pnt_1().y(), triangle.pnt_2().y(), triangle.pnt_3().y()});
		min_.z() = std::min({triangle.pnt_1().z(), triangle.pnt_2().z(), triangle.pnt_3().z()});

		max_.x() = std::max({triangle.pnt_1().x(), triangle.pnt_2().x(), triangle.pnt_3().x()});
		max_.y() = std::max({triangle.pnt_1().y(), triangle.pnt_2().y(), triangle.pnt_3().y()});
		max_.z() = std::max({triangle.pnt_1().z(), triangle.pnt_2().z(), triangle.pnt_3().z()});
	}

	const Point3& min() const { return min_; }
	const Point3& max() const { return max_; }
};

#endif // BOUNDING_BOX_H
