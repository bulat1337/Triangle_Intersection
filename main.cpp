#include <stddef.h>        // for size_t
#include <iostream>        // for basic_ostream, operator<<, cin, cout
#include <set>             // for set, __tree_const_iterator

#include "multi_inter.h"  // for Grid, calc_cell_size, get_triangles, inter...
#include "log.h"

int main()
{
	MSG("Getting triangles\n");
	multi_inter::LabeledTriangles triangles = multi_inter::get_triangles(std::cin);

	MSG("Calculating cell_size\n");
	double cell_size = multi_inter::calc_cell_size(triangles);

	LOG("Cell size: {}\n", cell_size);

	multi_inter::Grid grid(cell_size);

	MSG("Inserting triangles in the grid\n");
	grid.insert_all(triangles);

	std::set<size_t> intersecting_ids;

	MSG("Intersecting close triangles\n");
	multi_inter::intersect_close_trinagles(intersecting_ids, triangles, grid);

	MSG("The result:\n");
	for (const auto& elem : intersecting_ids)
	{
		std::cout << elem << '\n';
	}


	return 0;
}
