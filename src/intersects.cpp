#include "intersects.h"

#include "vec.h"
#include "plane.h"
#include "triangle.h"
#include "distances.h"
#include "segment.h"
#include "interval.h"

enum class Axis
{
	x
	, y
	, z
};

namespace
{
	Triangle<Point2> project(const Triangle<Point3>& triangle, Axis max_normal_axis)
	{
		switch(max_normal_axis)
		{
			case Axis::x:
				#ifdef ENABLE_LOGGING
				std::clog << "Projecting on Oyz\n";
				#endif

				return Triangle<Point2>(  Point2(triangle.pnt_1().y(), triangle.pnt_1().z())
										, Point2(triangle.pnt_2().y(), triangle.pnt_2().z())
										, Point2(triangle.pnt_3().y(), triangle.pnt_3().z()));
			case Axis::y:
				#ifdef ENABLE_LOGGING
				std::clog << "Projecting on Oxz\n";
				#endif

				return Triangle<Point2>(  Point2(triangle.pnt_1().x(), triangle.pnt_1().z())
										, Point2(triangle.pnt_2().x(), triangle.pnt_2().z())
										, Point2(triangle.pnt_3().x(), triangle.pnt_3().z()));
			case Axis::z:
				#ifdef ENABLE_LOGGING
				std::clog << "Projecting on Oxy\n";
				#endif

				return Triangle<Point2>(  Point2(triangle.pnt_1().x(), triangle.pnt_1().y())
										, Point2(triangle.pnt_2().x(), triangle.pnt_2().y())
										, Point2(triangle.pnt_3().x(), triangle.pnt_3().y()));
		}
	}

	bool intersects2(const Triangle<Point2>& lhs, const Triangle<Point2>& rhs)
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

	Axis get_max_axis(const Vec3& vec)
	{
		if (utils::cmp_double(vec.x(), vec.y()) >= 0)
		{
			if (utils::cmp_double(vec.x(), vec.z()) >= 0)
			{
				return Axis::x;
			}

			return Axis::z;
		}
		else
		{
			if (utils::cmp_double(vec.y(), vec.z()) >= 0)
			{
				return Axis::y;
			}

			return Axis::z;
		}
	}
}
bool intersects3(Triangle<Point3>& lhs, Triangle<Point3>& rhs)
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

		Axis max_normal_axis = get_max_axis(lhs_plane.normal());

		std::clog 	<< "Plane normal: "
					<< lhs_plane.normal().x() << ' '
					<< lhs_plane.normal().y() << ' '
					<< lhs_plane.normal().z() << '\n';

		return intersects2(project(lhs, max_normal_axis), project(rhs, max_normal_axis));
	}

	// 6. Compute intersection line and project onto largest axis.
	// 7. Compute the intervals for each triangle.

	Vec3 intersection_line = cross(lhs_plane.normal(), rhs_plane.normal());

	Axis max_axis = get_max_axis(intersection_line);

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
		case Axis::x:
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
		case Axis::y:
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
		case Axis::z:
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
