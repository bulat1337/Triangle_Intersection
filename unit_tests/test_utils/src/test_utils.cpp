#include "test_utils.h"

#include <fstream>       // for basic_ifstream, ifstream
#include <gtest/gtest.h> // for Message, CmpHelperEQ, CmpHelperEQFailure
#include <iterator>      // for istreambuf_iterator
#include <set>           // for set, __tree_const_iterator
#include <stddef.h>      // for size_t
#include <string>        // for allocator, char_traits, basic_string, string

#include "multi_inter.h" // for Grid, calc_cell_size, get_triangles, inter...

namespace
{

std::string get_result(const std::string &file_name)
{
    std::ifstream test_data;

    test_data.exceptions(std::ifstream::badbit);

    test_data.open(file_name);

    multi_inter::LabeledTriangles<double> triangles;

    multi_inter::get_triangles(test_data, triangles);

    double cell_size = multi_inter::calc_cell_size(triangles);

    multi_inter::Grid<double> grid(cell_size);

    grid.insert_all(triangles);

    std::set<size_t> intersecting_ids;

    multi_inter::intersect_close_trinagles(intersecting_ids, triangles, grid);

    std::string result;

    for (const auto &elem : intersecting_ids)
    {
        result += std::to_string(elem) + '\n';
    }

    return result;
}

std::string get_answer(const std::string &file_name)
{
    std::ifstream answer_file;

    answer_file.exceptions(std::ifstream::badbit);

    answer_file.open(file_name);

    std::string answer((std::istreambuf_iterator<char>(answer_file)),
                       std::istreambuf_iterator<char>());

    return answer;
}

} // namespace

void test_utils::run_test(const std::string &test_name)
{
    std::string test_folder = "data";

    std::string test_path =
        std::string(TEST_DATA_DIR) + test_folder + test_name;
    std::string result = get_result(test_path + ".dat");
    std::string answer = get_answer(test_path + ".ans");

    EXPECT_EQ(result, answer);
}
