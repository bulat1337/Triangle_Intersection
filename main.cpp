#include <stddef.h>        // for size_t
#include <iostream>        // for basic_ostream, operator<<, cin, cout
#include <set>             // for set, __tree_const_iterator

#include "spatial_hash.h"  // for Grid, calc_cell_size, get_triangles, inter...


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
