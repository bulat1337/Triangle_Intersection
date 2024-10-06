#include "intersects.h"

#include <stddef.h>     // for size_t

#include "distances.h"  // for Distances
#include "interval.h"   // for Interval
#include "log.h"        // for MSG, LOG
#include "plane.h"      // for Plane3
#include "segment.h"    // for Segment2
#include "triangle.h"   // for Triangle3, Triangle2, Triangle_Base
#include "utils.h"      // for Axis, get_max_axis
#include "vec.h"        // for Vec3, Point2, cross

namespace
{
	Triangle2 project(const Triangle3& triangle, utils::Axis max_normal_axis)
	{
		switch(max_normal_axis)
		{
			case utils::Axis::x:
				MSG("Projecting on Oyz\n");

				return Triangle2(  Point2(triangle.pnt_1().y(), triangle.pnt_1().z())
										, Point2(triangle.pnt_2().y(), triangle.pnt_2().z())
										, Point2(triangle.pnt_3().y(), triangle.pnt_3().z()));
			case utils::Axis::y:
				MSG("Projecting on Oxz\n");

				return Triangle2(  Point2(triangle.pnt_1().x(), triangle.pnt_1().z())
										, Point2(triangle.pnt_2().x(), triangle.pnt_2().z())
										, Point2(triangle.pnt_3().x(), triangle.pnt_3().z()));
			case utils::Axis::z:
				MSG("Projecting on Oxy\n");

				return Triangle2(  Point2(triangle.pnt_1().x(), triangle.pnt_1().y())
										, Point2(triangle.pnt_2().x(), triangle.pnt_2().y())
										, Point2(triangle.pnt_3().x(), triangle.pnt_3().y()));
		}
	}

	bool intersects2(const Triangle2& lhs, const Triangle2& rhs)
	{
		for (size_t lhs_side_id = 0; lhs_side_id < 3; ++lhs_side_id)
		{
			Segment2 lhs_side(lhs[lhs_side_id], lhs[lhs_side_id >= 2 ? 0 : lhs_side_id + 1]);
			for (size_t rhs_side_id = 0; rhs_side_id < 3; ++rhs_side_id)
			{
				Segment2 rhs_side(rhs[rhs_side_id], rhs[rhs_side_id >= 2 ? 0 : rhs_side_id + 1]);

				LOG("Testing if side {} intersects {}\n", lhs_side_id, rhs_side_id);

				if (lhs_side.intersects(rhs_side))
				{
					MSG("Yes they do\n");
					return true;
				}
				MSG("No they are not\n");
			}
		}

		MSG("Checking if rhs is in lhs\n");
		if (lhs.contains(rhs)) return true;
		MSG("No it's not\n");

		MSG("Checking if lhs is in rhs\n");
		if (rhs.contains(lhs)) return true;
		MSG("No it's not\n");

		return false;
	}
}

bool intersects3(Triangle3 lhs, Triangle3 rhs)
{
	//	1. Compute plane equation of rhs triangle (pi_2).

	Plane3 rhs_plane(rhs);
	LOG( "rhs_plane normal: ({}, {}, {})\n"
		, rhs_plane.normal().x()
		, rhs_plane.normal().y()
		, rhs_plane.normal().z());

	Distances lhs_dists(lhs, rhs_plane);

	LOG("lhs distances: {} {} {}\n", lhs_dists.first(), lhs_dists.second(), lhs_dists.third());

	// 2. Reject as trivial if all points of lhs triangle are on same side.
	if(lhs_dists.same_sign())
	{
		MSG("All points of lhs triangle are on same side\n");
		return false;
	}

	// 3. Compute plane equation of lhs triangle (pi_1).
	Plane3 lhs_plane(lhs);
	LOG( "lhs_plane normal: ({}, {}, {})\n"
		, lhs_plane.normal().x()
		, lhs_plane.normal().y()
		, lhs_plane.normal().z());

	Distances rhs_dists(rhs, lhs_plane);

	LOG("rhs distances: {} {} {}\n", rhs_dists.first(), rhs_dists.second(), rhs_dists.third());

	// 4. Reject as trivial if all points of rhs triangle are on same side.
	if(rhs_dists.same_sign())
	{
		MSG("All points of lhs triangle are on same side\n");
		return false;
	}

	// 5. If triangles are co-planar solve 2D task

	if(lhs_dists.are_trivial() || rhs_dists.are_trivial())
	{
		#ifdef ENABLE_LOGGING
		MSG("It's 2D case.\n");
		#endif

		utils::Axis max_normal_axis = utils::get_max_axis(lhs_plane.normal());

		LOG( "Plane normal: ({}, {}, {})\n"
			, lhs_plane.normal().x()
			, lhs_plane.normal().y()
			, lhs_plane.normal().z());

		return intersects2(project(lhs, max_normal_axis), project(rhs, max_normal_axis));
	}

	// 6. Compute intersection line and project onto largest axis.
	// 7. Compute the intervals for each triangle.

	Vec3 intersection_line = cross(lhs_plane.normal(), rhs_plane.normal());

	utils::Axis max_axis = utils::get_max_axis(intersection_line);

	double lhs_min = 0.0;
	double lhs_max = 0.0;
	double rhs_min = 0.0;
	double rhs_max = 0.0;


	lhs.distance_sort(lhs_dists);
	rhs.distance_sort(rhs_dists);

	switch(max_axis)
	{
		case utils::Axis::x:
		{
			MSG("Projecting points on x\n");
			double sim_coeff = lhs_dists.first() / (lhs_dists.first() - lhs_dists.second());
			lhs_min = lhs.pnt_1().x() + (lhs.pnt_2().x() - lhs.pnt_1().x()) * sim_coeff;

			sim_coeff = lhs_dists.third() / (lhs_dists.third() - lhs_dists.second());
			lhs_max = lhs.pnt_3().x() + (lhs.pnt_2().x() - lhs.pnt_3().x()) * sim_coeff;

			sim_coeff = rhs_dists.first() / (rhs_dists.first() - rhs_dists.second());;
			rhs_min = rhs.pnt_1().x() + (rhs.pnt_2().x() - rhs.pnt_1().x()) * sim_coeff;

			sim_coeff = rhs_dists.third() / (rhs_dists.third() - rhs_dists.second());
			rhs_max = rhs.pnt_3().x() + (rhs.pnt_2().x() - rhs.pnt_3().x()) * sim_coeff;
			break;
		}
		case utils::Axis::y:
		{
			MSG("Projecting points on y\n");
			double sim_coeff = lhs_dists.first() / (lhs_dists.first() - lhs_dists.second());
			lhs_min = lhs.pnt_1().y() + (lhs.pnt_2().y() - lhs.pnt_1().y()) * sim_coeff;

			sim_coeff = lhs_dists.third() / (lhs_dists.third() - lhs_dists.second());
			lhs_max = lhs.pnt_3().y() + (lhs.pnt_2().y() - lhs.pnt_3().y()) * sim_coeff;

			sim_coeff = rhs_dists.first() / (rhs_dists.first() - rhs_dists.second());
			rhs_min = rhs.pnt_1().y() + (rhs.pnt_2().y() - rhs.pnt_1().y()) * sim_coeff;

			sim_coeff = rhs_dists.third() / (rhs_dists.third() - rhs_dists.second());
			rhs_max = rhs.pnt_3().y() + (rhs.pnt_2().y() - rhs.pnt_3().y()) * sim_coeff;
			break;
		}
		case utils::Axis::z:
		{
			MSG("Projecting points on z\n");
			double sim_coeff = lhs_dists.first() / (lhs_dists.first() - lhs_dists.second());
			lhs_min = lhs.pnt_1().z() + (lhs.pnt_2().z() - lhs.pnt_1().z()) * sim_coeff;

			sim_coeff = lhs_dists.third() / (lhs_dists.third() - lhs_dists.second());
			lhs_max = lhs.pnt_3().z() + (lhs.pnt_2().z() - lhs.pnt_3().z()) * sim_coeff;

			sim_coeff = rhs_dists.first() / (rhs_dists.first() - rhs_dists.second());
			rhs_min = rhs.pnt_1().z() + (rhs.pnt_2().z() - rhs.pnt_1().z()) * sim_coeff;

			sim_coeff = rhs_dists.third() / (rhs_dists.third() - rhs_dists.second());
			rhs_max = rhs.pnt_3().z() + (rhs.pnt_2().z() - rhs.pnt_3().z()) * sim_coeff;
			break;
		}
	}
	Interval lhs_interval(lhs_min, lhs_max);
	Interval rhs_interval(rhs_min, rhs_max);

	// 8. Intersect the intervals.

	LOG("lhs interval: [{} , {}]\n", lhs_interval.min(), lhs_interval.max());
	LOG("rhs interval: [{} , {}]\n", rhs_interval.min(), rhs_interval.max());
	if (lhs_interval.max() < rhs_interval.min()) return false;
	if (rhs_interval.max() < lhs_interval.min()) return false;

	return true;
}
