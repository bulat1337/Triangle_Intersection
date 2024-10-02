#include <unordered_map>
#include <vector>
#include <cmath>
#include <tuple>

#include "intersects.h"
#include "bounding_box.h"
#include "log.h"

struct Hash3D
{
	//hash = (Floor(pos.x / cellSize) * 73856093) ^ (Floor(pos.y / cellSize) * 19349663) ^ (Floor(pos.z / cellSize) * 83492791);

	std::size_t operator()(const Point3& key) const
	{
		return 	  std::hash<int>()(static_cast<int>(key.x()))
				^ std::hash<int>()(static_cast<int>(key.y()))
				^ std::hash<int>()(static_cast<int>(key.z()));
	}
};

using Grid = std::unordered_map<Point3, std::vector<std::pair<Triangle3, size_t>>, Hash3D>;

Point3 hash_point(const Point3& point, double cell_size)
{
	return Point3
	(
		std::floor(point.x() / cell_size),
		std::floor(point.y() / cell_size),
		std::floor(point.z() / cell_size)
	);
}

void insert_triangle(Triangle3& triangle, size_t triangle_id, Grid& grid, double cell_size)
{
	Bounding_box bounding_box(triangle);

	LOG( "Bounding box is from ({}, {}, {}) to ({}, {}, {})\n"
		, bounding_box.min().x(), bounding_box.min().y(), bounding_box.min().z()
		, bounding_box.max().x(), bounding_box.max().y(), bounding_box.max().z());

	triangle.min_cell() = hash_point(bounding_box.min(), cell_size);
	triangle.max_cell() = hash_point(bounding_box.max(), cell_size);

	MSG("Bounding box is contained in cells:\n");
	for (double x = triangle.min_cell().x(); x <= triangle.max_cell().x(); ++x)
	{
		for (double y = triangle.min_cell().y(); y <= triangle.max_cell().y(); ++y)
		{
			for (double z = triangle.min_cell().z(); z <= triangle.max_cell().z(); ++z)
			{
				LOG("({}, {}, {})\n", x, y, z);
				Point3 cell_key(x, y, z);
				grid[cell_key].push_back({triangle, triangle_id});
			}
		}
	}
}

std::vector<Triangle3> close_triangles(	  const Triangle3& triangle
										, size_t triangle_id
										, const Grid& grid)
{
	std::vector<Triangle3> potential_collisions;

	for (const auto& elem : grid)
	{
		LOG( "In cell ({}, {}, {})\n"
			, elem.first.x(), elem.first.y(), elem.first.z());

		LOG("There is {} triangles\n", elem.second.size());
	}

	for (double x = triangle.min_cell().x(); x <= triangle.max_cell().x(); ++x)
	{
		for (double y = triangle.min_cell().y(); y <= triangle.max_cell().y(); ++y)
		{
			for (double z = triangle.min_cell().z(); z <= triangle.max_cell().z(); ++z)
			{
				Point3 cell_key(x, y, z);

				if (grid.find(cell_key) != grid.end())
				{
					for (const auto& potential_triangle : grid.at(cell_key))
					{
						if (potential_triangle.second != triangle_id)
							potential_collisions.push_back(potential_triangle.first);
					}
				}
			}
		}
	}

	return potential_collisions;
}


int main()
{
	size_t triangle_amount = 0;

	std::cin >> triangle_amount;

	double cell_size = 2.0;
	Grid grid;
	std::vector<Triangle3> triangles;
	triangles.reserve(triangle_amount);

	for (size_t triangle_id = 0; triangle_id < triangle_amount; ++triangle_id)
	{
		Point3 pnt_1;
		Point3 pnt_2;
		Point3 pnt_3;

		std::cin >> pnt_1 >> pnt_2 >> pnt_3;

		Triangle3 triangle(pnt_1, pnt_2, pnt_3);

		insert_triangle(triangle, triangle_id, grid, cell_size);
		triangles.push_back(triangle);
	}

	for (size_t triangle_id = 0; triangle_id < triangle_amount; ++triangle_id)
	{
		std::vector<Triangle3> collisions = close_triangles(triangles[triangle_id], triangle_id, grid);

		for (const auto& potential : collisions)
		{
			//will intersect with itself
			if (intersects3(triangles[triangle_id], potential))
			{
				std::cout << triangle_id << '\n';

				break;
			}
		}
	}


	return 0;
}
