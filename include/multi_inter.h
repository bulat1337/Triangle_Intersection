#ifndef SPATIAL_HASH_H
#define SPATIAL_HASH_H

#include <stddef.h>       // for size_t

#include <functional>     // for hash
#include <istream>        // for istream
#include <set>            // for set
#include <unordered_map>  // for unordered_map
#include <utility>        // for pair
#include <vector>         // for vector

#include "triangle.h"     // for Triangle3
#include "vec.h"          // for Point3
#include "cell.h"

namespace multi_inter
{

enum class status_t
{
	  all_good
	, invalid_amount
	, invalid_coordinate
};

using LabeledTriangle  = std::pair<Triangle3, size_t>;
using LabeledTriangles = std::vector<LabeledTriangle>;

struct Hash_Cell
{
	size_t operator() (const Cell& key) const
	{
		return 	  std::hash<long long>()(key.x * 73856093)
				^ std::hash<long long>()(key.y * 19349663)
				^ std::hash<long long>()(key.z * 83492791);
	}
};

class Grid
{
  private:
	std::unordered_map<Cell, std::vector<std::pair<Triangle3, size_t>>, Hash_Cell> cells_;

	double cell_size_ = 0.0;

  public:
	Grid(double cell_size) :
		cell_size_(cell_size) { cells_.reserve(100000); }

	void insert_all(LabeledTriangles& triangles);

	void insert(LabeledTriangle& trgl);

	auto find(const Cell& pnt) const { return cells_.find(pnt); }

	auto end() const { return cells_.end(); }

	auto at(const Cell& pnt) const { return cells_.at(pnt); }

	void dump_cells() const;
};

status_t get_triangles(std::istream& in, LabeledTriangles& triangles);

[[nodiscard]] double calc_cell_size(const LabeledTriangles& triangles);

void intersect_close_trinagles(	  std::set<size_t>& intersecting_ids
								, const LabeledTriangles& triangles
								, const Grid& grid);

bool check_status(status_t status);

};

#endif
