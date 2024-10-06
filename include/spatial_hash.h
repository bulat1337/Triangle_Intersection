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


using LabeledTriangle  = std::pair<Triangle3, size_t>;
using LabeledTriangles = std::vector<LabeledTriangle>;

struct Hash_point3
{
	size_t operator() (const Point3& key) const
	{
		return 	  std::hash<int>()(static_cast<int>(key.x() * 73856093))
				^ std::hash<int>()(static_cast<int>(key.y() * 19349663))
				^ std::hash<int>()(static_cast<int>(key.z() * 83492791));
	}
};

class Grid
{
  private:
	std::unordered_map<Point3, std::vector<std::pair<Triangle3, size_t>>, Hash_point3> cells_;

	double cell_size_ = 0.0;

  public:
	Grid(double cell_size);

	void insert_all(LabeledTriangles& triangles);

	void insert(LabeledTriangle& trgl);

	auto find(const Point3& pnt) const;

	auto end() const;

	auto at(const Point3& pnt) const;

	void dump_cells() const;
};


[[nodiscard]] LabeledTriangles get_triangles(std::istream& in);

[[nodiscard]] double calc_cell_size(const LabeledTriangles& triangles);

void intersect_close_trinagles(	  std::set<size_t>& intersecting_ids
								, const LabeledTriangles& triangles
								, const Grid& grid);

#endif
