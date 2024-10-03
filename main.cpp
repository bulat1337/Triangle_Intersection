#include <unordered_map>
#include <unordered_set>
#include <set>
#include <vector>
#include <cmath>

#include "intersects.h"
#include "bounding_box.h"
#include "log.h"
#include "spatial_hash.h"


int main()
{
	LabeledTriangles triangles = get_triangles(std::cin);

	double cell_size = calc_cell_size(triangles);

	Grid grid(cell_size);

	grid.insert_all(triangles);

	std::set<size_t> intersecting_ids;

	intersect_close_trinagles(intersecting_ids, triangles, grid);

	for (const auto& elem : intersecting_ids)
	{
		std::cout << elem << '\n';
	}


	return 0;
}
