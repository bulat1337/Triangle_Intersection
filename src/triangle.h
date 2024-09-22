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

	Vec& max_vec(Vec& vec_1, Vec& vec_2, Vec& vec_3)
	{
		if (vec_1.sq_length() > vec_2.sq_length())
		{
			if (vec_1.sq_length() > vec_3.sq_length())
			{
				std::clog << "Fist vector is max\n";
				return vec_1;
			}
			else
			{
				std::cout << "Third vector is max\n";
				return vec_3;
			}
		}
		else
		{
			if (vec_2.sq_length() > vec_3.sq_length())
			{
				std::cout << "Second vector is max\n";
				return vec_2;
			}
			else
			{
				std::cout << "Third vector is max\n";
				return vec_3;
			}
		}
	}

  public:
	Triangle(const Point& pnt_1, const Point& pnt_2, const Point& pnt_3):
		pnt_1_(pnt_1), pnt_2_(pnt_2), pnt_3_(pnt_3)
	{
		std::clog << "Generic constructor called\n";
	}

// 	Triangle(	const Point3& pnt_1
// 				, const Point3& pnt_2
// 				, const Point3& pnt_3) requires(std::is_same_v<Point, Point3>)
// 	{
// 		std::clog << "Sorting contructor called\n";
//
// 		normal_ = cross(pnt_2 - pnt_1, pnt_3 - pnt_1);
// 		if (utils::cmp_double(normal_.sq_length(), 0) != 0)	normal_ = unit_vector(normal_);
// 		else std::clog << "normal vector is null sized\n";
//
// 		std::array<Point, 3> points = {pnt_1, pnt_2, pnt_3};
//
// 		Point center = (pnt_1 + pnt_2 + pnt_3) / 3.0;
//
// 		Point axis_x = Point(1.0, 0.0, 0.0);
// 		Point axis_y = Point(0.0, 1.0, 0.0);
// 		Point axis_z = Point(0.0, 0.0, 1.0);
//
// 		Vec nx_cross = cross(axis_x, normal_);
// 		Vec ny_cross = cross(axis_y, normal_);
// 		Vec nz_cross = cross(axis_z, normal_);
//
// 		Point p = max_vec(nx_cross, ny_cross, nz_cross);
//
// 		if (utils::cmp_double(p.sq_length(), 0) != 0) p = unit_vector(p);
// 		else std::clog << "p vector is null sized\n";
//
// 		Point q = cross(normal_, p);
// 		if (utils::cmp_double(q.sq_length(), 0) != 0) q = unit_vector(q);
// 		else std::clog << "q vector is null sized\n";
//
// 		std::clog << "before sorting:\n";
// 		for(const auto& point : points)
// 		{
// 			std::clog 	<< point.x()
// 						<< ' '
// 						<< point.y()
// 						<< ' '
// 						<< point.z()
// 						<< '\n';
// 		}
//
// 		std::sort(	points.begin()
// 					, points.end()
// 					, [&center, this, &p, &q](const Point& p1, const Point& p2)
// 		{
// 			Vec r1 = p1 - center;
// 			Vec r2 = p2 - center;
//
// 			double t1 = dot(normal_, cross(r1, p));
// 			double u1 = dot(normal_, cross(r1, q));
// 			double t2 = dot(normal_, cross(r2, p));
// 			double u2 = dot(normal_, cross(r2, q));
//
// 			std::clog << "t1 = " << t1 << '\n';
// 			std::clog << "u1 = " << u1 << '\n';
// 			std::clog << "t2 = " << t2 << '\n';
// 			std::clog << "u2 = " << u2 << '\n';
//
// 			return utils::cmp_double(atan2(u2, t2), atan2(u1, t1)) < 0;
// 		});
//
// 		std::clog << "after sorting:\n";
// 		for(const auto& point : points)
// 		{
// 			std::clog 	<< point.x()
// 						<< ' '
// 						<< point.y()
// 						<< ' '
// 						<< point.z()
// 						<< '\n';
// 		}
//
// 		pnt_1_ = points[0];
// 		pnt_2_ = points[1];
// 		pnt_3_ = points[2];
// 	}

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
