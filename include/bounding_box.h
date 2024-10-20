#ifndef BOUNDING_BOX_H
#define BOUNDING_BOX_H

#include <algorithm>   // for max, min

#include "triangle.h"  // for Triangle3
#include "vec.h"

template <typename FltPnt>
class Bounding_box
{
  private:
	Point3<FltPnt> min_;
	Point3<FltPnt> max_;

  public:
	Bounding_box(const Point3<FltPnt>& min, const Point3<FltPnt>& max) :
		min_(min), max_(max) {}

	Bounding_box(const Triangle3<FltPnt>& triangle)
	{
		min_.set_x(std::min({triangle.pnt_1().x(), triangle.pnt_2().x(), triangle.pnt_3().x()}));
		min_.set_y(std::min({triangle.pnt_1().y(), triangle.pnt_2().y(), triangle.pnt_3().y()}));
		min_.set_z(std::min({triangle.pnt_1().z(), triangle.pnt_2().z(), triangle.pnt_3().z()}));

		max_.set_x(std::max({triangle.pnt_1().x(), triangle.pnt_2().x(), triangle.pnt_3().x()}));
		max_.set_y(std::max({triangle.pnt_1().y(), triangle.pnt_2().y(), triangle.pnt_3().y()}));
		max_.set_z(std::max({triangle.pnt_1().z(), triangle.pnt_2().z(), triangle.pnt_3().z()}));
	}

	const Point3<FltPnt>& min() const { return min_; }
	const Point3<FltPnt>& max() const { return max_; }
};

#endif // BOUNDING_BOX_H
