#include "intersects.h"

#include <cassert>

int main()
{
	// test 1 (true)
	Triangle triangle_1(	Point3(2.0, 2.0, 0.0)
							, Point3(8.0, 2.0, 0.0)
							, Point3(2.0, 10.0, 0.0));

	Triangle triangle_2(	Point3(4.0, 4.0, 0.0)
							, Point3(8.0, 4.0, 0.0)
							, Point3(8.0, 7.0, 0.0));

	assert(intersects3(triangle_1, triangle_2) == true);

	std::clog << "test_1 passed\n\n";

	// test 2 (false)
	triangle_1 = Triangle(	Point3(2.0, 2.0, 0.0)
							, Point3(2.0, 10.0, 0.0)
							, Point3(8.0, 2.0, 0.0));

	triangle_2 = Triangle(	Point3(7.0, 4.0, 0.0)
							, Point3(8.0, 7.0, 0.0)
							, Point3(8.0, 4.0, 0.0));

	assert(intersects3(triangle_1, triangle_2) == false);
	std::clog << "test_2 passed\n\n";

	// test 3 (true)
	triangle_1 = Triangle(	Point3(2.0, 2.0, 0.0)
							, Point3(8.0, 2.0, 0.0)
							, Point3(2.0, 10.0, 0.0));

	triangle_2 = Triangle(	Point3(5.0, 6.0, 0.0)
							, Point3(8.0, 4.0, 0.0)
							, Point3(8.0, 7.0, 0.0));

	assert(intersects3(triangle_1, triangle_2) == true);
	std::clog << "test_3 passed\n\n";

	// test 4 (true)
	triangle_1 = Triangle(	Point3(2.0, 2.0, 0.0)
							, Point3(8.0, 2.0, 0.0)
							, Point3(2.0, 10.0, 0.0));

	triangle_2 = Triangle(	Point3(3.0, 3.0, 0.0)
							, Point3(5.0, 3.0, 0.0)
							, Point3(5.0, 5.0, 0.0));

	assert(intersects3(triangle_1, triangle_2) == true);
	std::clog << "test_3 passed\n\n";

	// test 5 (true)

	Point3 A1(1.0, 4.0, 1.0);
	Point3 B1(-4.0, 2.0, 3.0);
	Point3 C1(1.0, 1.0, 1.0);

	Point3 A2(1.0, 4.0, 3.0);
	Point3 B2(-4.0, 2.0, 1.0);
	Point3 C2(0.5, 1.0, 3.0);

	triangle_1 = Triangle(A1, B1, C1);

	triangle_2 = Triangle(A2, B2, C2);

	assert(intersects3(triangle_1, triangle_2) == true);
	std::clog << "test_4 passed\n\n";

	return 0;
}
