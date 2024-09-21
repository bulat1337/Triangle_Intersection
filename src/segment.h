#ifndef SEGMENT_H
#define SEGMENT_H

#include "vec.h"
#include "utils.h"

class Segment2
{
  private:
	Point2 pnt_1_;
	Point2 pnt_2_;

  public:
	Segment2(const Point2& pnt_1, const Point2& pnt_2):
		pnt_1_(pnt_1), pnt_2_(pnt_2) {}

	const Point2& pnt_1() const
	{
		return pnt_1_;
	}

	const Point2& pnt_2() const
	{
		return pnt_2_;
	}

	bool intersects(const Segment2& other) const
	{
		double t_num   = 	(pnt_1_.x() - other.pnt_1_.x()) * (other.pnt_1_.y() - other.pnt_2_.y())
							- (pnt_1_.y() - other.pnt_1_.y()) * (other.pnt_1_.x() - other.pnt_2_.x());

		double t_denom = 	(pnt_1_.x() - pnt_2_.x()) * (other.pnt_1_.y() - other.pnt_2_.y())
							- (pnt_1_.y() - pnt_2_.y()) * (other.pnt_1_.x() - other.pnt_2_.x());

		if(utils::cmp_double(t_denom, 0) == 0) return false;

		double coeff_t = t_num / t_denom;

		if(utils::cmp_double(coeff_t, 1) > 0 || utils::cmp_double(coeff_t, 0) < 0) return false;

		double u_num   = 	(pnt_1_.x() - pnt_2_.x()) * (pnt_1_.y() - other.pnt_1_.y())
							- (pnt_1_.y() - pnt_2_.y()) * (pnt_1_.x() - other.pnt_1_.x());

		double u_denom = 	(pnt_1_.x() - pnt_2_.x()) * (other.pnt_1_.y() - other.pnt_2_.y())
							- (pnt_1_.y() - pnt_2_.y()) * (other.pnt_1_.x() - other.pnt_2_.x());

		if(utils::cmp_double(u_denom, 0) == 0) return false;

		double coeff_u = - u_num / u_denom;

		if(utils::cmp_double(coeff_u, 1) > 0 || utils::cmp_double(coeff_u, 0) < 0) return false;

		return true;
	}

};

#endif // SEGMENT_H
