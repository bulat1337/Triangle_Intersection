#ifndef DETAIL_H
#define DETAIL_H

#include <fstream>       // for basic_ifstream, ifstream
#include <gtest/gtest.h> // for Message, CmpHelperEQ, CmpHelperEQFailure
#include <iterator>      // for istreambuf_iterator
#include <set>           // for set, __tree_const_iterator
#include <stddef.h>      // for size_t
#include <string>        // for allocator, char_traits, basic_string, string

#include "t_inter.h" // for Grid, calc_cell_size, get_triangles, inter...

namespace test_utils
{

namespace detail
{

inline std::string get_answer(const std::string &file_name)
{
    std::ifstream answer_file;

    answer_file.exceptions(std::ifstream::badbit);

    answer_file.open(file_name);

    std::string answer((std::istreambuf_iterator<char>(answer_file)),
                       std::istreambuf_iterator<char>());

    return answer;
}

template <typename T> std::string get_result(const std::string &file_name)
{
    t_inter::status_t status = t_inter::status_t::all_good;

    std::ifstream test_data;

    test_data.open(file_name);

    if (!test_data.is_open())
        status = t_inter::status_t::invalid_open;
    if (t_inter::check_status(status))
        return std::string();

    MSG("Getting triangles\n");
    t_inter::LabeledTriangles<T> triangles;
    status = t_inter::get_triangles(test_data, triangles);
    if (t_inter::check_status(status))
        return std::string();

    MSG("Calculating cell_size\n");
    T cell_size = t_inter::calc_cell_size(triangles);

    LOG("Cell size: {}\n", cell_size);

    t_inter::Grid<T> grid(cell_size);

    MSG("Inserting triangles in the grid\n");
    grid.insert_all(triangles);

    std::set<size_t> intersecting_ids;

    MSG("Intersecting close triangles\n");
    t_inter::intersect_close_trinagles(intersecting_ids, triangles, grid);

    std::string result;

    for (const auto &elem : intersecting_ids)
    {
        result += std::to_string(elem) + '\n';
    }

    return result;
}

}; // namespace detail

}; // namespace test_utils

#endif
