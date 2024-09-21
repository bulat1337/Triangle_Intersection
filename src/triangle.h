#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "vec.h"
#include "utils.h"

template <typename Point>
class Triangle
{
  private:
	Point pnt_1_;
	Point pnt_2_;
	Point pnt_3_;

  public:
	Triangle(const Point& pnt_1, const Point& pnt_2, const Point& pnt_3):
		pnt_1_(pnt_1), pnt_2_(pnt_2), pnt_3_(pnt_3) {}

	const Point& pnt_1() const
	{
		return pnt_1_;
	}

	const Point& pnt_2() const
	{
		return pnt_2_;
	}

	const Point& pnt_3() const
	{
		return pnt_3_;
	}

	const Point& operator [] (size_t pnt_id) const
	{
		switch (pnt_id)
		{
			case 0:
				return pnt_1_;
			case 1:
				return pnt_2_;
			case 2:
				return pnt_3_;
			default:
				throw std::logic_error("Invalid point index");
		}
	}


	bool contains(const Triangle<Point>& other) const
	{
		Point a_to_pnt = other.pnt_1_ - pnt_1_;

		Point a_to_b   = pnt_2_ - pnt_1_;
		Point a_to_c   = pnt_3_ - pnt_1_;

		double ab_projection = dot(a_to_pnt, a_to_b.clockwise_normal());
		double ac_projection = dot(a_to_pnt, a_to_c.clockwise_normal());

		if (utils::cmp_double(ab_projection, 0) == utils::cmp_double(ac_projection, 0))
			return false;

		Point b_to_c = pnt_3_ - pnt_2_;
		double bc_projection = dot(a_to_pnt, b_to_c);

		if (utils::cmp_double(ab_projection, 0) != utils::cmp_double(bc_projection, 0))
			return false;

		return true;
	}
};

#endif // TRIANGLE_H
