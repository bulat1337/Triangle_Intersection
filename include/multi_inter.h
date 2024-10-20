#ifndef SPATIAL_HASH_H
#define SPATIAL_HASH_H

#include <algorithm>       // for max, min
#include <cmath>           // for floor, sqrt
#include <iostream>        // for cerr, cout
#include <set>             // for set
#include <unordered_map>   // for operator==, unordered_map, __hash_map_cons...
#include <unordered_set>   // for unordered_set
#include <vector>          // for vector
#include <stddef.h>       // for size_t
#include <functional>     // for hash, __scalar_hash
#include <istream>        // for istream
#include <utility>        // for pair

#include "bounding_box.h"  // for Bounding_box
#include "intersects.h"    // for intersects3
#include "log.h"           // for LOG, MSG
#include "vec.h"           // for Vec3, operator-, operator>>, Point3
#include "cell.h"         // for Cell
#include "triangle.h"     // for Triangle3


namespace multi_inter
{

template <typename FltPnt>
Cell discretize(const Point3<FltPnt>& point, double cell_size)
{
	return Cell
	(
		  static_cast<long long>(std::floor(point.x() / cell_size))
		, static_cast<long long>(std::floor(point.y() / cell_size))
		, static_cast<long long>(std::floor(point.z() / cell_size))
	);
}

enum class status_t
{
	  all_good
	, invalid_amount
	, invalid_coordinate
};

template <typename FltPnt>
using LabeledTriangle  = std::pair<Triangle3<FltPnt>, size_t>;

template <typename FltPnt>
using LabeledTriangles = std::vector<LabeledTriangle<FltPnt>>;

struct Hash_Cell
{
	size_t operator() (const Cell& key) const
	{
		return 	  std::hash<long long>()(key.x * 73856093)
				^ std::hash<long long>()(key.y * 19349663)
				^ std::hash<long long>()(key.z * 83492791);
	}
};

template <typename FltPnt>
class Grid
{
  private:
	std::unordered_map<	  Cell
						, std::vector<std::pair<Triangle3<FltPnt>, size_t>>
						, Hash_Cell> cells_;

	double cell_size_ = 0.0;

  public:
	Grid(double cell_size) :
		cell_size_(cell_size) {}

	void insert_all(LabeledTriangles<FltPnt>& triangles)
	{
		for (auto& triangle : triangles)
		{
			LOG("Inserting {}\n", triangle.second);
			insert(triangle);
		}
	}

	void insert(LabeledTriangle<FltPnt>& trgl)
	{
		Bounding_box bounding_box(trgl.first);

		LOG( "Bounding box is from ({}, {}, {}) to ({}, {}, {})\n"
			, bounding_box.min().x(), bounding_box.min().y(), bounding_box.min().z()
			, bounding_box.max().x(), bounding_box.max().y(), bounding_box.max().z());

		trgl.first.set_min_cell(discretize(bounding_box.min(), cell_size_));
		trgl.first.set_max_cell(discretize(bounding_box.max(), cell_size_));

		MSG("Bounding box is contained in cells:\n");
		for (long long x = trgl.first.min_cell().x; x <= trgl.first.max_cell().x; ++x)
		{
			for (long long y = trgl.first.min_cell().y; y <= trgl.first.max_cell().y; ++y)
			{
				for (long long z = trgl.first.min_cell().z; z <= trgl.first.max_cell().z; ++z)
				{
					LOG("({}, {}, {})\n", x, y, z);
					Cell cell_key(x, y, z);
					cells_[cell_key].push_back(trgl);
				}
			}
		}
	}

	auto find(const Cell& pnt) const { return cells_.find(pnt); }

	auto end() const { return cells_.end(); }

	auto at(const Cell& pnt) const { return cells_.at(pnt); }

	void dump_cells() const
	{
		for ([[maybe_unused]]const auto& elem : cells_)
		{
			LOG( "In cell ({}, {}, {})\n"
				, elem.first.x(), elem.first.y(), elem.first.z());

			LOG("There is {} triangles\n", elem.second.size());
		}
	}
};

// secondary

const double cell_size_coeff = 7.0;

struct Hash_ul_pair
{
	size_t operator() (const std::pair<size_t, size_t>& ul_pair) const
	{
		return 	  ul_pair.first >= ul_pair.second
				? ul_pair.first * ul_pair.first + ul_pair.first + ul_pair.second
				: ul_pair.first + ul_pair.second * ul_pair.second;
	}
};

using CollisionSet = std::unordered_set<std::pair<size_t, size_t>, Hash_ul_pair>;

void add_checked_collision(CollisionSet& added_potentials, size_t a, size_t b)
{
	added_potentials.insert({std::min(a, b), std::max(a, b)});
}

bool added_potentials_contains(const CollisionSet& added_potentials, size_t a, size_t b)
{
	return added_potentials.contains({std::min(a, b) , std::max(a, b)});
}

template <typename FltPnt>
LabeledTriangles<FltPnt>
close_triangles(  const LabeledTriangle<FltPnt>& triangle
				, const Grid<FltPnt>& grid
				, CollisionSet& added_potentials)
{
	LabeledTriangles<FltPnt> potential_collisions;
	add_checked_collision(added_potentials, triangle.second, triangle.second);

	#ifdef ENABLE_LOGGING
	grid.dump_cells();
	#endif

	for (long long x = triangle.first.min_cell().x; x <= triangle.first.max_cell().x; ++x)
	{
		for (long long y = triangle.first.min_cell().y; y <= triangle.first.max_cell().y; ++y)
		{
			for (long long z = triangle.first.min_cell().z; z <= triangle.first.max_cell().z; ++z)
			{
				Cell cell_key(x, y, z);

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

//

template <typename FltPnt>
status_t
get_triangles(std::istream& in, LabeledTriangles<FltPnt>& triangles)
{
	long long inputted_amount = 0;
	in >> inputted_amount;

	if (inputted_amount < 0)
	{
		return status_t::invalid_amount;
	}

	size_t triangle_amount = static_cast<size_t>(inputted_amount);

	triangles.reserve(triangle_amount);

	for (size_t triangle_id = 0; triangle_id < triangle_amount; ++triangle_id)
	{
		Point3<FltPnt> pnt_1;
		Point3<FltPnt> pnt_2;
		Point3<FltPnt> pnt_3;

		if (!(in >> pnt_1 >> pnt_2 >> pnt_3))
		{
			return status_t::invalid_coordinate;
		}

		Triangle3<FltPnt> triangle(pnt_1, pnt_2, pnt_3);

		triangles.push_back({triangle, triangle_id});
	}

	return status_t::all_good;
}

template <typename FltPnt>
[[nodiscard]] double
calc_cell_size(const LabeledTriangles<FltPnt>& triangles)
{
	double all_sides_length = 0;

	for (const auto& triangle : triangles)
	{
		Vec3 side_1 = triangle.first.pnt_2() - triangle.first.pnt_1();
		Vec3 side_2 = triangle.first.pnt_3() - triangle.first.pnt_2();
		Vec3 side_3 = triangle.first.pnt_1() - triangle.first.pnt_3();

		// sq_length
		all_sides_length += side_1.sq_length();
		all_sides_length += side_2.sq_length();
		all_sides_length += side_3.sq_length();
	}

	double cell_size = cell_size_coeff * std::sqrt((all_sides_length / (triangles.size() * 3)));
	LOG("Calculated cell size: {}\n", cell_size);

	return cell_size;
}

template <typename FltPnt>
void
intersect_close_trinagles(   std::set<size_t>& intersecting_ids
										, const LabeledTriangles<FltPnt>& triangles
										, const Grid<FltPnt>& grid)
{
	// #ifdef DEBUG
	size_t intersection_check_counter = 0;
	// #endif

	CollisionSet added_potentials;

	for (const auto& triangle : triangles)
	{
		LabeledTriangles<FltPnt> potential_collisions = close_triangles(  triangle
																		, grid
																		, added_potentials);

		LOG("Checking intersections of triangle {}\n", triangle.second);

		for (const auto& potential : potential_collisions)
		{
			// #ifdef DEBUG
			++intersection_check_counter;
			// #endif

			LOG("Checking the intersecton of {} and {}\n", triangle.second, potential.second);
			if (intersects3(triangle.first, potential.first))
			{
				LOG("YES: {} intersects {}\n\n", triangle.second, potential.second);
				intersecting_ids.insert(triangle.second);
				intersecting_ids.insert(potential.second);
			}
			else MSG("NO\n\n");
		}
	}

	// #ifdef DEBUG
	// LOG("Intersection check amount: {}\n", intersection_check_counter);
	// #endif

	std::cout << "Intersection check amount: " << intersection_check_counter << '\n';
}

bool check_status(status_t status)
{
	if (status == status_t::all_good) return false;

	switch (status)
	{
		case status_t::all_good:
			return true;
		case status_t::invalid_amount:
			std::cerr << 	"ERROR: Invalid amount: "
							"please enter non negative number\n";
			break;
		case status_t::invalid_coordinate:
			std::cerr << "ERROR: Please enter floating point as the triangle coordinate\n";
			break;
		default:
			std::cerr << "ERROR: Unknown\n";
	}

	return true;
}

};

#endif
