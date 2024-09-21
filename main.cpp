#include "intersects.h"

int main()
{
	// test 2 (true)
	Triangle triangle_1(	Point3(2.0, 2.0, 0.0)
							, Point3(2.0, 10.0, 0.0)
							, Point3(8.0, 2.0, 0.0));

	Triangle triangle_2(	Point3(4.0, 4.0, 0.0)
							, Point3(4.0, 4.0, 0.0)
							, Point3(8.0, 4.0, 0.0));

	std::cout << intersects3(triangle_1, triangle_2) << '\n';

	// test 2 (false)
	triangle_1 = Triangle(	Point3(2.0, 2.0, 0.0)
							, Point3(2.0, 10.0, 0.0)
							, Point3(8.0, 2.0, 0.0));

	triangle_2 = Triangle(	Point3(7.0, 4.0, 0.0)
							, Point3(8.0, 7.0, 0.0)
							, Point3(8.0, 4.0, 0.0));

	std::cout << intersects3(triangle_1, triangle_2) << '\n';

	// test 3 (true)
	triangle_1 = Triangle(	Point3(2.0, 2.0, 0.0)
							, Point3(2.0, 10.0, 0.0)
							, Point3(8.0, 2.0, 0.0));

	triangle_2 = Triangle(	Point3(5.0, 6.0, 0.0)
							, Point3(8.0, 7.0, 0.0)
							, Point3(8.0, 4.0, 0.0));

	std::cout << intersects3(triangle_1, triangle_2) << '\n';

	return 0;
}
