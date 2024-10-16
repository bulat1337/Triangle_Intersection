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

			return Triangle2(     Point2(triangle.pnt_1().y(), triangle.pnt_1().z())
								, Point2(triangle.pnt_2().y(), triangle.pnt_2().z())
								, Point2(triangle.pnt_3().y(), triangle.pnt_3().z()));
		case utils::Axis::y:
			MSG("Projecting on Oxz\n");

			return Triangle2(     Point2(triangle.pnt_1().x(), triangle.pnt_1().z())
								, Point2(triangle.pnt_2().x(), triangle.pnt_2().z())
								, Point2(triangle.pnt_3().x(), triangle.pnt_3().z()));
		case utils::Axis::z:
			MSG("Projecting on Oxy\n");

			return Triangle2(     Point2(triangle.pnt_1().x(), triangle.pnt_1().y())
								, Point2(triangle.pnt_2().x(), triangle.pnt_2().y())
								, Point2(triangle.pnt_3().x(), triangle.pnt_3().y()));
	}
}

bool intersects2(const Triangle2& lhs, const Triangle2& rhs)
{
	for (size_t lhs_side_id = 0; lhs_side_id < 3; ++lhs_side_id)
	{
		Segment2 lhs_side(    lhs[lhs_side_id]
							, lhs[lhs_side_id >= 2 ? 0 : lhs_side_id + 1]);

		for (size_t rhs_side_id = 0; rhs_side_id < 3; ++rhs_side_id)
		{
			Segment2 rhs_side(	  rhs[rhs_side_id]
								, rhs[rhs_side_id >= 2 ? 0 : rhs_side_id + 1]);

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

Interval compute_interval(	  Triangle3 triangle
							, Distances& triangle_dists
							, const utils::Axis& max_axis)
{
	triangle.distance_sort(triangle_dists);

	double min = 0.0;
	double max = 0.0;

	auto get_coord = [max_axis](const Point3& pnt)
	{
		switch (max_axis)
		{
			case utils::Axis::x: return pnt.x();
			case utils::Axis::y: return pnt.y();
			case utils::Axis::z: return pnt.z();
		}
	};

	double sim_coeff =	  triangle_dists.first
						/ (triangle_dists.first - triangle_dists.second);

	min = 	  get_coord(triangle.pnt_1())
			+ (get_coord(triangle.pnt_2()) - get_coord(triangle.pnt_1()))
			* sim_coeff;

	sim_coeff =   triangle_dists.third
				/ (triangle_dists.third - triangle_dists.second);

	max =	  get_coord(triangle.pnt_3())
			+ (get_coord(triangle.pnt_2()) - get_coord(triangle.pnt_3()))
			* sim_coeff;


	return Interval(min, max);
}
}

bool intersects3(const Triangle3& lhs, const Triangle3& rhs)
{
	Plane3 rhs_plane(rhs);

	Distances lhs_dists(lhs, rhs_plane);

	if(lhs_dists.same_sign())
	{
		MSG("All points of lhs triangle are on same side\n");
		return false;
	}

	Plane3 lhs_plane(lhs);

	Distances rhs_dists(rhs, lhs_plane);

	if(rhs_dists.same_sign())
	{
		MSG("All points of rhs triangle are on same side\n");
		return false;
	}

	if(lhs_dists.are_trivial() || rhs_dists.are_trivial())
	{
		MSG("It's 2D case.\n");

		utils::Axis max_normal_axis = utils::get_max_axis(lhs_plane.normal());

		return intersects2(	  project(lhs, max_normal_axis)
							, project(rhs, max_normal_axis));
	}

	Vec3 intersection_line = cross(lhs_plane.normal(), rhs_plane.normal());

	utils::Axis max_axis = utils::get_max_axis(intersection_line);

	Interval lhs_interval = compute_interval(lhs, lhs_dists, max_axis);
	Interval rhs_interval = compute_interval(rhs, rhs_dists, max_axis);

	LOG("lhs interval: [{} , {}]\n", lhs_interval.min(), lhs_interval.max());
	LOG("rhs interval: [{} , {}]\n", rhs_interval.min(), rhs_interval.max());

	if (lhs_interval.max() < rhs_interval.min()) return false;
	if (rhs_interval.max() < lhs_interval.min()) return false;

	return true;
}
