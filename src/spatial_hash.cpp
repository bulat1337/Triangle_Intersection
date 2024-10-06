#include "spatial_hash.h"

#include <algorithm>       // for max, min
#include <cmath>           // for floor
#include <set>             // for set
#include <unordered_map>   // for unordered_map, operator==, __hash_map_cons...
#include <unordered_set>   // for unordered_set
#include <vector>          // for vector

#include "bounding_box.h"  // for Bounding_box
#include "intersects.h"    // for intersects3
#include "log.h"           // for LOG, MSG

namespace
{

Point3 discretize(const Point3& point, double cell_size)
{
	return Point3
	(
		std::floor(point.x() / cell_size),
		std::floor(point.y() / cell_size),
		std::floor(point.z() / cell_size)
	);
}

};


Grid::Grid(double cell_size) :
	cell_size_(cell_size) {}

void Grid::insert_all(LabeledTriangles& triangles)
{
	for (auto& triangle : triangles)
	{
		insert(triangle);
	}
}

void Grid::insert(LabeledTriangle& trgl)
{
	Bounding_box bounding_box(trgl.first);

	LOG( "Bounding box is from ({}, {}, {}) to ({}, {}, {})\n"
		, bounding_box.min().x(), bounding_box.min().y(), bounding_box.min().z()
		, bounding_box.max().x(), bounding_box.max().y(), bounding_box.max().z());

	trgl.first.min_cell() = discretize(bounding_box.min(), cell_size_);
	trgl.first.max_cell() = discretize(bounding_box.max(), cell_size_);

	MSG("Bounding box is contained in cells:\n");
	for (double x = trgl.first.min_cell().x(); x <= trgl.first.max_cell().x(); ++x)
	{
		for (double y = trgl.first.min_cell().y(); y <= trgl.first.max_cell().y(); ++y)
		{
			for (double z = trgl.first.min_cell().z(); z <= trgl.first.max_cell().z(); ++z)
			{
				LOG("({}, {}, {})\n", x, y, z);
				Point3 cell_key(x, y, z);
				cells_[cell_key].push_back(trgl);
			}
		}
	}
}

auto Grid::find(const Point3& pnt) const
{
	return cells_.find(pnt);
}

auto Grid::end() const
{
	return cells_.end();
}

auto Grid::at(const Point3& pnt) const
{
	return cells_.at(pnt);
}

void Grid::dump_cells() const
{
	for ([[maybe_unused]]const auto& elem : cells_)
	{
		LOG( "In cell ({}, {}, {})\n"
			, elem.first.x(), elem.first.y(), elem.first.z());

		LOG("There is {} triangles\n", elem.second.size());
	}
}

namespace
{

const double cell_size_coeff = 1.1;

struct Hash_ul_pair
{
	size_t operator() (const std::pair<size_t, size_t>& ul_pair) const
	{
		// a >= b ? a * a + a + b : a + b * b;  where a, b >= 0
		return 	  ul_pair.first >= ul_pair.second
				? ul_pair.first * ul_pair.first + ul_pair.first + ul_pair.second
				: ul_pair.first + ul_pair.second * ul_pair.second;
	}
};

using CollisionSet     = std::unordered_set<std::pair<size_t, size_t>, Hash_ul_pair>;

void add_checked_collision(CollisionSet& added_potentials, size_t a, size_t b)
{
	added_potentials.insert({std::min(a, b), std::max(a, b)});
}

bool added_potentials_contains(const CollisionSet& added_potentials, size_t a, size_t b)
{
	return added_potentials.contains({std::min(a, b) , std::max(a, b)});
}

LabeledTriangles close_triangles(	  const LabeledTriangle& triangle
									, const Grid& grid
									, CollisionSet& added_potentials)
{
	LabeledTriangles potential_collisions;
	add_checked_collision(added_potentials, triangle.second, triangle.second);

	#ifdef ENABLE_LOGGING
	grid.dump_cells();
	#endif

	for (double x = triangle.first.min_cell().x(); x <= triangle.first.max_cell().x(); ++x)
	{
		for (double y = triangle.first.min_cell().y(); y <= triangle.first.max_cell().y(); ++y)
		{
			for (double z = triangle.first.min_cell().z(); z <= triangle.first.max_cell().z(); ++z)
			{
				Point3 cell_key(x, y, z);

				if (grid.find(cell_key) != grid.end())
				{
					for (const auto& potential_triangle : grid.at(cell_key))
					{
						if (!added_potentials_contains(	  added_potentials
														, triangle.second
														, potential_triangle.second))
						{

							potential_collisions.push_back(potential_triangle);

							add_checked_collision(	  added_potentials
													, triangle.second
													, potential_triangle.second);
						}
					}
				}
			}
		}
	}

	return potential_collisions;
}

};

[[nodiscard]] LabeledTriangles get_triangles(std::istream& in)
{
	size_t triangle_amount = 0;
	in >> triangle_amount;

	LabeledTriangles triangles;
	triangles.reserve(triangle_amount);

	for (size_t triangle_id = 0; triangle_id < triangle_amount; ++triangle_id)
	{
		Point3 pnt_1;
		Point3 pnt_2;
		Point3 pnt_3;

		in >> pnt_1 >> pnt_2 >> pnt_3;

		Triangle3 triangle(pnt_1, pnt_2, pnt_3);

		triangles.push_back({triangle, triangle_id});
	}

	return triangles;
}

[[nodiscard]] double calc_cell_size(const LabeledTriangles& triangles)
{
	double all_sides_length = 0;

	for (const auto& triangle : triangles)
	{
		Vec3 side_1 = triangle.first.pnt_2() - triangle.first.pnt_1();
		Vec3 side_2 = triangle.first.pnt_3() - triangle.first.pnt_2();
		Vec3 side_3 = triangle.first.pnt_1() - triangle.first.pnt_3();

		all_sides_length += side_1.length();
		all_sides_length += side_2.length();
		all_sides_length += side_3.length();
	}

	double cell_size = cell_size_coeff * (all_sides_length / triangles.size());
	LOG("Calculated cell size: {}\n", cell_size);

	return cell_size;
}

void intersect_close_trinagles(	  std::set<size_t>& intersecting_ids
								, const LabeledTriangles& triangles
								, const Grid& grid)
{
	#ifdef DEBUG
	size_t intersection_check_counter = 0;
	#endif

	CollisionSet added_potentials;

	for (const auto& triangle : triangles)
	{
		LabeledTriangles potential_collisions = close_triangles(  triangle
																, grid
																, added_potentials);

		for (const auto& potential : potential_collisions)
		{
			#ifdef DEBUG
			++intersection_check_counter;
			#endif

			LOG("checking intersection of {} and {}\n", triangle.second, potential.second);

			if (intersects3(triangle.first, potential.first))
			{
				LOG("{} intersects {}\n", triangle.second, potential.second);
				intersecting_ids.insert(triangle.second);
				intersecting_ids.insert(potential.second);
			}
		}
	}

	#ifdef DEBUG
	LOG("Intersection check amount: {}\n", intersection_check_counter);
	#endif
}
