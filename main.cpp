#include <iostream> // for basic_ostream, operator<<, cin, cout
#include <set>      // for set, __tree_const_iterator
#include <stddef.h> // for size_t

#include "log.h"
#include "t_inter.h" // for Grid, calc_cell_size, get_triangles, inter...

int main()
{
    t_inter::status_t status = t_inter::status_t::all_good;

    MSG("Getting triangles\n");
    t_inter::LabeledTriangles<double> triangles;
    status = t_inter::get_triangles(std::cin, triangles);
    if (t_inter::check_status(status))
        return 0;

    MSG("Calculating cell_size\n");
    double cell_size = t_inter::calc_cell_size(triangles);

    LOG("Cell size: {}\n", cell_size);

    t_inter::Grid<double> grid(cell_size);

    MSG("Inserting triangles in the grid\n");
    grid.insert_all(triangles);

    std::set<size_t> intersecting_ids;

    MSG("Intersecting close triangles\n");
    t_inter::intersect_close_trinagles(intersecting_ids, triangles, grid);

    MSG("The result:\n");
    for (const auto &elem : intersecting_ids)
    {
        std::cout << elem << '\n';
    }

    return 0;
}
