#include "test_utils.h"

#include <gtest/gtest.h>

#include <fstream>
#include <format>
#include <string>
#include <iostream>
#include <vector>
#include <unordered_map>
#include <ranges>

#include "spatial_hash.h"

namespace
{


std::string get_result(const std::string& file_name)
{
	std::ifstream test_data(file_name);

	if(!test_data.is_open())
		throw std::runtime_error(std::format("Can't open {}\n", file_name));

	LabeledTriangles triangles = get_triangles(test_data);

	double cell_size = calc_cell_size(triangles);

	Grid grid(cell_size);

	grid.insert_all(triangles);

	std::set<size_t> intersecting_ids;

	intersect_close_trinagles(intersecting_ids, triangles, grid);

	std::string result;

	for (const auto& elem : intersecting_ids)
	{
		result += std::to_string(elem) + '\n';
	}

	return result;
}

std::string get_answer(const std::string& file_name)
{
	std::ifstream answer_file(file_name);

	if(!answer_file.is_open())
		throw std::runtime_error(std::format("Can't open {}\n", file_name));

	std::string answer(	(std::istreambuf_iterator<char>(answer_file)),
						std::istreambuf_iterator<char>());

	return answer;
}

}

void test_utils::run_test(const std::string& test_name)
{
	std::string test_folder = "tests";

	std::string test_path = std::string(TEST_DATA_DIR) + test_folder + test_name;
	std::string result = get_result(test_path + ".dat");
	std::string answer = get_answer(test_path + ".ans");

	EXPECT_EQ(result, answer);
}
