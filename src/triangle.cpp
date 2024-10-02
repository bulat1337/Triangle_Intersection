#include "triangle.h"

#include <cmath>

#include <array>
#include <algorithm>

#include "vec.h"
#include "utils.h"
#include "distances.h"
#include "log.h"

void Triangle3::sort_vertices(std::array<Point3, 3>& points)
{
	Vec3 normal = cross(points[1] - points[0], points[2] - points[0]);
	if (utils::cmp_double(normal.sq_length(), 0) != 0)
		normal = unit_vector(normal);

	MSG("Normal vector is null-sized\n");

	Point3 center = (points[0] + points[1] + points[2]) / 3.0;

	utils::Axis dominant_axis = utils::get_max_axis(normal);

	switch(dominant_axis)
	{
		case utils::Axis::z:
			// projecting on XY
			std::sort(	  points.begin(), points.end()
						, [&center](const Point3& p1, const Point3& p2)
						{
							double angle1 = atan2(p1.y() - center.y(), p1.x() - center.x());
							double angle2 = atan2(p2.y() - center.y(), p2.x() - center.x());
							return angle1 < angle2;
						});
			break;
		case utils::Axis::x:
			// projecting on YZ
			std::sort(	  points.begin(), points.end()
						, [&center](const Point3& p1, const Point3& p2)
						{
							double angle1 = atan2(p1.z() - center.z(), p1.y() - center.y());
							double angle2 = atan2(p2.z() - center.z(), p2.y() - center.y());
							return angle1 < angle2;
						});
			break;
		case utils::Axis::y:
			// projecting on XZ
			std::sort(	  points.begin(), points.end()
						, [&center](const Point3& p1, const Point3& p2)
						{
							double angle1 = atan2(p1.z() - center.z(), p1.x() - center.x());
							double angle2 = atan2(p2.z() - center.z(), p2.x() - center.x());
							return angle1 < angle2;
						});
			break;
	}

	MSG("After sorting:\n");
	for ([[maybe_unused]]const auto& point : points)
	{
		LOG("{} {} {}\n", point.x(), point.y(), point.z());
	}
}

Triangle3::Triangle3(	const Point3& pnt_1
			, const Point3& pnt_2
			, const Point3& pnt_3)
{
	std::array<Point3, 3> points = {pnt_1, pnt_2, pnt_3};

	sort_vertices(points);

	pnt_1_ = points[0];
	pnt_2_ = points[1];
	pnt_3_ = points[2];
}

void Triangle3::distance_sort(Distances& dists)
{
	if    (utils::sign(dists.second()) != utils::sign(dists.first())
		&& utils::sign(dists.second()) != utils::sign(dists.third()))
	{
		MSG("Already sorted\n");
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

Point3&       Triangle3::min_cell()      { return min_cell_; }
const Point3& Triangle3::min_cell() const { return min_cell_; }
Point3&       Triangle3::max_cell()       { return max_cell_; }
const Point3& Triangle3::max_cell() const { return max_cell_; }


Triangle2::Triangle2(const Point2& pnt_1, const Point2& pnt_2, const Point2& pnt_3):
	Triangle_Base(pnt_1, pnt_2, pnt_3) {}

bool Triangle2::contains(const Triangle2& other) const
{
	Vec2 a_to_pnt = other.pnt_1_ - pnt_1_;

	Vec2 a_to_b   = pnt_2_ - pnt_1_;
	Vec2 a_to_c   = pnt_3_ - pnt_1_;

	double ab_norm_proj = dot(a_to_pnt, a_to_b.clockwise_normal());
	LOG("ab_norm_proj = {}\n", ab_norm_proj);

	double ac_norm_proj = dot(a_to_pnt, a_to_c.clockwise_normal());
	LOG("ac_norm_proj = {}\n", ab_norm_proj);

	bool ab_proj_sign = utils::cmp_double(ab_norm_proj, 0) > 0;
	bool ac_proj_sign = utils::cmp_double(ac_norm_proj, 0) > 0;

	if (ab_proj_sign == ac_proj_sign)
	{
		MSG("ab_proj_sign == ac_proj_sign\n");
		return false;
	}

	Vec2 b_to_c   = pnt_3_ - pnt_2_;
	Vec2 b_to_pnt = other.pnt_1_ - pnt_2_;

	double bc_norm_proj = dot(b_to_pnt, b_to_c.clockwise_normal());

	bool bc_proj_sign = utils::cmp_double(bc_norm_proj, 0) > 0;

	if (bc_proj_sign != ab_proj_sign)
	{
		MSG("bc_proj_sign != ab_proj_sign\n");
		return false;
	}

	return true;
}
