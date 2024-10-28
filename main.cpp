#include <stddef.h>   // for size_t
#include <iostream>   // for basic_ostream, operator<<, cin, cout
#include <set>        // for set, __tree_const_iterator

#include "log.h"      // for MSG, LOG
#include "status.h"   // for check_status, status_t
#include "t_inter.h"  // for Grid, calc_cell_size, get_triangles, intersect_...

int main()
{
    t_inter::status_t status = t_inter::status_t::all_good;

    MSG("Getting triangles\n");
    t_inter::LabeledTriangles<float> triangles;
    status = t_inter::get_triangles(std::cin, triangles);
    if (t_inter::check_status(status))
        return 0;

    MSG("Calculating cell_size\n");
    float cell_size = t_inter::calc_cell_size(triangles);

    LOG("Cell size: {}\n", cell_size);

    t_inter::Grid<float> grid(cell_size);

    MSG("Inserting triangles in the grid\n");
    grid.insert_all(triangles);

    std::set<size_t> intersecting_ids;

    MSG("Intersecting close triangles\n");
    status =
        t_inter::intersect_close_trinagles(intersecting_ids, triangles, grid);
    if (t_inter::check_status(status))
        return 0;

    MSG("The result:\n");
    for (const auto &elem : intersecting_ids)
    {
        std::cout << elem << '\n';
    }

    return 0;
}
