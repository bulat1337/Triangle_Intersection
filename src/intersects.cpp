#include "intersects.h"

#include "vec.h"
#include "plane.h"
#include "triangle.h"
#include "distances.h"
#include "segment.h"

enum class Axis
{
	x
	, y
	, z
};

bool intersects2(const Triangle<Point2>& lhs, const Triangle<Point2>& rhs)
{
	for (size_t lhs_side_id = 0; lhs_side_id < 2; ++lhs_side_id)
	{
		Segment2 lhs_side(lhs[lhs_side_id], lhs[lhs_side_id + 1]);
		for (size_t rhs_side_id = 0; rhs_side_id < 2; ++rhs_side_id)
		{
			Segment2 rhs_side(rhs[rhs_side_id], rhs[rhs_side_id + 1]);
			if (lhs_side.intersects(rhs_side))
			{
				return true;
			}
		}
	}

	if (lhs.contains(rhs)) return true;
	if (rhs.contains(lhs)) return true;

	return false;
}

Axis get_min_axis(const Vec3& vec)
{
    if (utils::cmp_double(vec.x(), vec.y()) <= 0)
    {
        if (utils::cmp_double(vec.x(), vec.z()) <= 0)
        {
            return Axis::x;
        }

        return Axis::z;
    }
    else
    {
        if (utils::cmp_double(vec.y(), vec.z()) <= 0)
        {
            return Axis::y;
        }

        return Axis::z;
    }
}

bool intersects3(const Triangle<Point3>& lhs, const Triangle<Point3>& rhs)
{
	//	1. Compute plane equation of rhs triangle (pi_2).
	Plane3 rhs_plane(rhs);
	Distances lhs_dists(lhs, rhs_plane);

	// 2. Reject as trivial if all points of lhs triangle are on same side.
	if(lhs_dists.same_sign()) return false;

	// 3. Compute plane equation of lhs triangle (pi_1).
	Plane3 lhs_plane(lhs);
	Distances rhs_dists(rhs, lhs_plane);

	// 4. Reject as trivial if all points of rhs triangle are on same side.
	if(rhs_dists.same_sign()) return false;

	// 5. If triangles are co-planar solve 2D task

	if(lhs_dists.are_trivial() || rhs_dists.are_trivial())
	{
		#ifdef ENABLE_LOGGING
		std::clog << "It's 2D case.\n";
		#endif

		// 2D task
		Axis min_axis = get_min_axis(lhs_plane.normal());

		switch(min_axis)
		{
			case Axis::x:
				#ifdef ENABLE_LOGGING
				std::clog << "Projecting on Oyz\n";
				#endif
				return intersects2(	Triangle<Point2>(	Point2(lhs.pnt_1().y(), lhs.pnt_1().z())
														, Point2(lhs.pnt_2().y(), lhs.pnt_2().z())
														, Point2(lhs.pnt_3().y(), lhs.pnt_3().z()))
									, Triangle<Point2>(	Point2(rhs.pnt_1().y(), rhs.pnt_1().z())
														, Point2(rhs.pnt_2().y(), rhs.pnt_2().z())
														, Point2(rhs.pnt_3().y(), rhs.pnt_3().z())));
			case Axis::y:
				#ifdef ENABLE_LOGGING
				std::clog << "Projecting on Oxz\n";
				#endif
				return intersects2(	Triangle<Point2>(	Point2(lhs.pnt_1().x(), lhs.pnt_1().z())
														, Point2(lhs.pnt_2().x(), lhs.pnt_2().z())
														, Point2(lhs.pnt_3().x(), lhs.pnt_3().z()))
									, Triangle<Point2>(	Point2(rhs.pnt_1().x(), rhs.pnt_1().z())
														, Point2(rhs.pnt_2().x(), rhs.pnt_2().z())
														, Point2(rhs.pnt_3().x(), rhs.pnt_3().z())));
			case Axis::z:
				#ifdef ENABLE_LOGGING
				std::clog << "Projecting on Oxy\n";
				#endif
				return intersects2(	Triangle<Point2>(	Point2(lhs.pnt_1().x(), lhs.pnt_1().y())
														, Point2(lhs.pnt_2().x(), lhs.pnt_2().y())
														, Point2(lhs.pnt_3().x(), lhs.pnt_3().y()))
									, Triangle<Point2>(	Point2(rhs.pnt_1().x(), rhs.pnt_1().y())
														, Point2(rhs.pnt_2().x(), rhs.pnt_2().y())
														, Point2(rhs.pnt_3().x(), rhs.pnt_3().y())));

		}
	}

	// TEMPORAY!!!!
	return false;

	// 6. Compute intersection line and project onto largest axis.



	// 7. Compute the intervals for each triangle.

	// 8. Intersect the intervals.

}
