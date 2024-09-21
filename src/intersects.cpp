#include "intersects.h"

#include "vec3.h"
#include "plane.h"
#include "triangle.h"
#include "distances.h"

bool intersects(const Triangle& lhs, const Triangle& rhs)
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
		// 2D task
	}

	// 6. Compute intersection line and project onto largest axis.



	// 7. Compute the intervals for each triangle.

	// 8. Intersect the intervals.

}
