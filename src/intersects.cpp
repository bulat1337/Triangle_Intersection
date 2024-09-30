#include "intersects.h"

#include "vec.h"
#include "plane.h"
#include "triangle.h"
#include "distances.h"
#include "segment.h"
#include "interval.h"
#include "utils.h"

namespace
{
	Triangle2 project(const Triangle3& triangle, utils::Axis max_normal_axis)
	{
		switch(max_normal_axis)
		{
			case utils::Axis::x:
				#ifdef ENABLE_LOGGING
				std::clog << "Projecting on Oyz\n";
				#endif

				return Triangle2(  Point2(triangle.pnt_1().y(), triangle.pnt_1().z())
										, Point2(triangle.pnt_2().y(), triangle.pnt_2().z())
										, Point2(triangle.pnt_3().y(), triangle.pnt_3().z()));
			case utils::Axis::y:
				#ifdef ENABLE_LOGGING
				std::clog << "Projecting on Oxz\n";
				#endif

				return Triangle2(  Point2(triangle.pnt_1().x(), triangle.pnt_1().z())
										, Point2(triangle.pnt_2().x(), triangle.pnt_2().z())
										, Point2(triangle.pnt_3().x(), triangle.pnt_3().z()));
			case utils::Axis::z:
				#ifdef ENABLE_LOGGING
				std::clog << "Projecting on Oxy\n";
				#endif

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

				std::clog 	<< "Testing if "
							<< rhs_side.pnt_1().x() << ' '
							<< rhs_side.pnt_1().y() << ' '
							<< "to "
							<< rhs_side.pnt_2().x() << ' '
							<< rhs_side.pnt_2().y() << '\n'
							<< "intersects "
							<< lhs_side.pnt_1().x() << ' '
							<< lhs_side.pnt_1().y() << ' '
							<< "to "
							<< lhs_side.pnt_2().x() << ' '
							<< lhs_side.pnt_2().y() << '\n';

				if (lhs_side.intersects(rhs_side))
				{
					std::clog << "Yes they do\n";
					return true;
				}
				std::clog << "No they are not\n";
			}
		}

		std::clog << "Checking if rhs is in lhs\n";
		if (lhs.contains(rhs)) return true;
		std::clog << "No it's not\n";

		std::clog << "Checking if lhs is in rhs\n";
		if (rhs.contains(lhs)) return true;
		std::clog << "No it's not\n";

		return false;
	}
}

bool intersects3(Triangle3& lhs, Triangle3& rhs)
{
	//	1. Compute plane equation of rhs triangle (pi_2).

	Plane3 rhs_plane(rhs);
	Distances lhs_dists(lhs, rhs_plane);

	std::clog 	<< "lhs distances: "
				<< lhs_dists.first()
				<< ' '
				<< lhs_dists.second()
				<< ' '
				<< lhs_dists.third() << '\n';

	// 2. Reject as trivial if all points of lhs triangle are on same side.
	if(lhs_dists.same_sign())
	{
		std::clog << "All points of lhs triangle are on same side\n";
		return false;
	}

	// 3. Compute plane equation of lhs triangle (pi_1).
	Plane3 lhs_plane(lhs);
	Distances rhs_dists(rhs, lhs_plane);

	std::clog 	<< "rhs distances: "
				<< rhs_dists.first()
				<< ' '
				<< rhs_dists.second()
				<< ' '
				<< rhs_dists.third() << '\n';

	// 4. Reject as trivial if all points of rhs triangle are on same side.
	if(rhs_dists.same_sign())
	{
		std::clog << "All points of lhs triangle are on same side\n";
		return false;
	}

	// 5. If triangles are co-planar solve 2D task

	if(lhs_dists.are_trivial() || rhs_dists.are_trivial())
	{
		#ifdef ENABLE_LOGGING
		std::clog << "It's 2D case.\n";
		#endif

		utils::Axis max_normal_axis = utils::get_max_axis(lhs_plane.normal());

		std::clog 	<< "Plane normal: "
					<< lhs_plane.normal().x() << ' '
					<< lhs_plane.normal().y() << ' '
					<< lhs_plane.normal().z() << '\n';

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

	std::clog	<< "lhs after sorting:\n"
				<< lhs.pnt_1() << '\n'
				<< lhs.pnt_2() << '\n'
				<< lhs.pnt_3() << '\n';

	std::clog	<< "rhs after sorting:\n"
				<< rhs.pnt_1() << '\n'
				<< rhs.pnt_2() << '\n'
				<< rhs.pnt_3() << '\n';

	switch(max_axis)
	{
		case utils::Axis::x:
		{
			std::clog << "Projecting points on x\n";
			double sim_coeff = lhs_dists.first() / (lhs_dists.first() - lhs_dists.second());
			lhs_min = lhs.pnt_1().x() + (lhs.pnt_2().x() - lhs.pnt_1().x()) * sim_coeff;

			std::clog 	<< "lhs_min = " << lhs.pnt_1().x() << " + ("
						<< lhs.pnt_2().x() << " - "
						<< lhs.pnt_1().x() << " )"
						<< " * " << sim_coeff << '\n';

			sim_coeff = lhs_dists.third() / (lhs_dists.third() - lhs_dists.second());
			lhs_max = lhs.pnt_3().x() + (lhs.pnt_2().x() - lhs.pnt_3().x()) * sim_coeff;



			sim_coeff = rhs_dists.first() / (rhs_dists.first() - rhs_dists.second());;
			rhs_min = rhs.pnt_1().x() + (rhs.pnt_2().x() - rhs.pnt_1().x()) * sim_coeff;

			std::clog 	<< "rhs_min = " << rhs.pnt_1().x() << " + ("
						<< rhs.pnt_2().x() << " - "
						<< rhs.pnt_1().x() << " )"
						<< " * " << sim_coeff << '\n';

			sim_coeff = rhs_dists.third() / (rhs_dists.third() - rhs_dists.second());
			rhs_max = rhs.pnt_3().x() + (rhs.pnt_2().x() - rhs.pnt_3().x()) * sim_coeff;
			break;
		}
		case utils::Axis::y:
		{
			std::clog << "Projecting points on y\n";
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
			std::clog << "Projecting points on z\n";
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

	std::clog << "lhs interval: [" << lhs_interval.min() << " ; " << lhs_interval.max() << "]\n";
	std::clog << "rhs interval: [" << rhs_interval.min() << " ; " << rhs_interval.max() << "]\n";
	if (lhs_interval.max() < rhs_interval.min()) return false;
	if (rhs_interval.max() < lhs_interval.min()) return false;

	return true;
}
