#ifndef SEGMENT_H
#define SEGMENT_H

#include <ostream>  // for ostream

#include "utils.h"  // for cmp_double
#include "vec.h"    // for Point2, Vec2

class Segment2
{
  private:
	Point2 pnt_1_;
	Point2 pnt_2_;

	bool is_point(const Vec2& direc) const
	{
		return utils::cmp_double(direc.x(), 0) == 0 && utils::cmp_double(direc.y(), 0) == 0;
	}

	bool point_on_segment(const Point2& pnt, const Segment2& sgm) const;


  public:
	Segment2(const Point2& pnt_1, const Point2& pnt_2):
		pnt_1_(pnt_1), pnt_2_(pnt_2) {}

	const Point2& pnt_1() const{ return pnt_1_; }

	const Point2& pnt_2() const { return pnt_2_; }

	bool intersects(const Segment2& other) const;
};

std::ostream& operator << (std::ostream& out, const Segment2& sgm);

#endif // SEGMENT_H
