#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <cmath>

#include <array>
#include <algorithm>

#include "vec.h"
#include "utils.h"
#include "distances.h"

template <typename Point>
class Triangle_Base
{
  protected:
	Point pnt_1_;
	Point pnt_2_;
	Point pnt_3_;


  public:
  	Triangle_Base() = default;

  	Triangle_Base(const Point2& pnt_1, const Point2& pnt_2, const Point2& pnt_3):
		pnt_1_(pnt_1), pnt_2_(pnt_2), pnt_3_(pnt_3) {}

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

	Triangle_Base& operator = (const Triangle_Base& other)
	{
		pnt_1_ = other.pnt_1();
		pnt_2_ = other.pnt_2();
		pnt_3_ = other.pnt_3();

		return *this;
	}
};

class Triangle3 : public Triangle_Base<Point3>
{
  private:

  public:
	// разбить на функции
	Triangle3(	const Point3& pnt_1
				, const Point3& pnt_2
				, const Point3& pnt_3)
	{
		Vec3 normal = cross(pnt_2 - pnt_1, pnt_3 - pnt_1);
		if (utils::cmp_double(normal.sq_length(), 0) != 0)
			normal = unit_vector(normal);
		else std::clog << "Normal vector is null-sized\n";

		Point3 center = (pnt_1 + pnt_2 + pnt_3) / 3.0;

		auto dominant_axis = std::max({	std::abs(normal.x())
										, std::abs(normal.y())
										, std::abs(normal.z())});

		std::array<Point3, 3> points = {pnt_1, pnt_2, pnt_3};

		if (utils::cmp_double(dominant_axis, std::abs(normal.z())) == 0)
		{
			// projecting on XY
			std::sort(points.begin(), points.end(), [&center](const Point3& p1, const Point3& p2)
			{
				double angle1 = atan2(p1.y() - center.y(), p1.x() - center.x());
				double angle2 = atan2(p2.y() - center.y(), p2.x() - center.x());
				return angle1 < angle2;
			});
		}
		else if (utils::cmp_double(dominant_axis, std::abs(normal.x())))
		{
			// projecting on YZ
			std::sort(points.begin(), points.end(), [&center](const Point3& p1, const Point3& p2)
			{
				double angle1 = atan2(p1.z() - center.z(), p1.y() - center.y());
				double angle2 = atan2(p2.z() - center.z(), p2.y() - center.y());
				return angle1 < angle2;
			});
		}
		else
		{
			// projecting on XZ
			std::sort(points.begin(), points.end(), [&center](const Point3& p1, const Point3& p2) {
				double angle1 = atan2(p1.z() - center.z(), p1.x() - center.x());
				double angle2 = atan2(p2.z() - center.z(), p2.x() - center.x());
				return angle1 < angle2;
			});
		}

		std::clog << "After sorting:\n";
		for (const auto& point : points)
		{
			std::clog << point.x() << ' ' << point.y() << ' ' << point.z() << '\n';
		}

		pnt_1_ = points[0];
		pnt_2_ = points[1];
		pnt_3_ = points[2];
	}

	void distance_sort(Distances& dists)
	{
		if (utils::sign(dists.second()) != utils::sign(dists.first())
			&& utils::sign(dists.second()) != utils::sign(dists.third()))
		{
			std::clog << "Already sorted\n";
			return;
		}

		if (utils::sign(dists.second()) == utils::sign(dists.first()))
		{
			std::swap(dists.first(), dists.second());
			std::swap(dists.second(), dists.third());

			std::swap(pnt_1_, pnt_2_);
			std::swap(pnt_2_, pnt_3_);
		}
		else
		{
			std::swap(dists.second(), dists.third());
			std::swap(dists.first(), dists.second());

			std::swap(pnt_2_, pnt_3_);
			std::swap(pnt_1_, pnt_2_);
		}
	}
};

class Triangle2 : public Triangle_Base<Point2>
{
  public:
	Triangle2(const Point2& pnt_1, const Point2& pnt_2, const Point2& pnt_3):
		Triangle_Base(pnt_1, pnt_2, pnt_3) {}

	bool contains(const Triangle2& other) const
	{
		Vec2 a_to_pnt = other.pnt_1_ - pnt_1_;

		Vec2 a_to_b   = pnt_2_ - pnt_1_;
		Vec2 a_to_c   = pnt_3_ - pnt_1_;

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

		Vec2 b_to_c   = pnt_3_ - pnt_2_;
		Vec2 b_to_pnt = other.pnt_1_ - pnt_2_;

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
