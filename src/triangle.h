#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <cmath>

#include <array>
#include <algorithm>
#include <type_traits>

#include "vec.h"
#include "utils.h"

template <typename Point>
class Triangle
{
  private:
	using Vec = Point;

	Point pnt_1_;
	Point pnt_2_;
	Point pnt_3_;

	Vec normal_;

  public:
	Triangle(const Point& pnt_1, const Point& pnt_2, const Point& pnt_3):
		pnt_1_(pnt_1), pnt_2_(pnt_2), pnt_3_(pnt_3)
	{
		std::clog << "Generic constructor called\n";
	}

	Triangle(	const Point3& pnt_1
				, const Point3& pnt_2
				, const Point3& pnt_3) requires(std::is_same_v<Point, Point3>)
	{
		std::clog << "Sorting constructor called\n";

		normal_ = cross(pnt_2 - pnt_1, pnt_3 - pnt_1);
		if (utils::cmp_double(normal_.sq_length(), 0) != 0)
			normal_ = unit_vector(normal_);
		else std::clog << "Normal vector is null-sized\n";

		Point center = (pnt_1 + pnt_2 + pnt_3) / 3.0;

		auto dominant_axis = std::max({	std::abs(normal_.x())
										, std::abs(normal_.y())
										, std::abs(normal_.z())});

		std::array<Point, 3> points = {pnt_1, pnt_2, pnt_3};

		if (dominant_axis == std::abs(normal_.z()))
		{
			// projecting on XY
			std::sort(points.begin(), points.end(), [&center](const Point& p1, const Point& p2)
			{
				double angle1 = atan2(p1.y() - center.y(), p1.x() - center.x());
				double angle2 = atan2(p2.y() - center.y(), p2.x() - center.x());
				return angle1 < angle2;
			});
		}
		else if (dominant_axis == std::abs(normal_.x()))
		{
			// projecting on YZ
			std::sort(points.begin(), points.end(), [&center](const Point& p1, const Point& p2)
			{
				double angle1 = atan2(p1.z() - center.z(), p1.y() - center.y());
				double angle2 = atan2(p2.z() - center.z(), p2.y() - center.y());
				return angle1 < angle2;
			});
		}
		else
		{
			// projecting on XZ
			std::sort(points.begin(), points.end(), [&center](const Point& p1, const Point& p2)
			{
				double angle1 = atan2(p1.z() - center.z(), p1.x() - center.x());
				double angle2 = atan2(p2.z() - center.z(), p2.x() - center.x());
				return angle1 < angle2;
			});
		}

		std::clog << "After sorting:\n";
		for (const auto& point : points) {
			std::clog << point.x() << ' ' << point.y() << ' ' << point.z() << '\n';
		}

		pnt_1_ = points[0];
		pnt_2_ = points[1];
		pnt_3_ = points[2];
	}

	const Point& pnt_1() const { return pnt_1_; }
	const Point& pnt_2() const { return pnt_2_; }
	const Point& pnt_3() const { return pnt_3_; }

	const Point& operator [] (size_t pnt_id) const
	{
		switch (pnt_id)
		{
			case 0: return pnt_1_;
			case 1: return pnt_2_;
			case 2: return pnt_3_;
			default: throw std::logic_error("Invalid point index");
		}
	}

	bool contains(const Triangle<Point>& other) const
	{
		Vec a_to_pnt = other.pnt_1_ - pnt_1_;

		Vec a_to_b   = pnt_2_ - pnt_1_;
		Vec a_to_c   = pnt_3_ - pnt_1_;

		double ab_norm_proj = dot(a_to_pnt, a_to_b.clockwise_normal());
		std::clog << "ab_norm_proj = " << ab_norm_proj << '\n';
		double ac_norm_proj = dot(a_to_pnt, a_to_c.clockwise_normal());
		std::clog << "ac_norm_proj = " << ac_norm_proj << '\n';

		bool ab_proj_sign = utils::cmp_double(ab_norm_proj, 0) > 0;
		bool ac_proj_sign = utils::cmp_double(ac_norm_proj, 0) > 0;

		if (ab_proj_sign == ac_proj_sign)
		{
			std::clog << "ab_proj_sign == ac_proj_sign\n";
			return false;
		}

		Vec b_to_c   = pnt_3_ - pnt_2_;
		Vec b_to_pnt = other.pnt_1_ - pnt_2_;

		double bc_norm_proj = dot(b_to_pnt, b_to_c.clockwise_normal());

		bool bc_proj_sign = utils::cmp_double(bc_norm_proj, 0) > 0;

		if (bc_proj_sign != ab_proj_sign)
		{
			std::clog << "bc_proj_sign != ab_proj_sign\n";
			return false;
		}

		return true;
	}
};

#endif // TRIANGLE_H
