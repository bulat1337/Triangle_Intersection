#include "intersects.h"

#include <cassert>

int main()
{
	// test 1 (true)

	Point3 A1(2.0, 2.0, 0.0);
	Point3 B1(8.0, 2.0, 0.0);
	Point3 C1(2.0, 10.0, 0.0);

	Point3 A2(4.0, 4.0, 0.0);
	Point3 B2(8.0, 4.0, 0.0);
	Point3 C2(8.0, 7.0, 0.0);

	Triangle triangle_1(A1, B1, C1);
	Triangle triangle_2(A2, B2, C2);

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
	A1 = Point3(2.0, 2.0, 0.0);
	B1 = Point3(8.0, 2.0, 0.0);
	C1 = Point3(2.0, 10.0, 0.0);

	A2 = Point3(3.0, 3.0, 0.0);
	B2 = Point3(5.0, 3.0, 0.0);
	C2 = Point3(5.0, 5.0, 0.0);

	triangle_1 = Triangle(A1, B1, C1);
	triangle_2 = Triangle(A2, B2, C2);

	assert(intersects3(triangle_1, triangle_2) == true);
	std::clog << "test_4 passed\n\n";

	// test 5 (true)

	A1 = Point3(1.0, 4.0, 1.0);
	B1 = Point3(-4.0, 2.0, 3.0);
	C1 = Point3(1.0, 1.0, 1.0);

	A2 = Point3(1.0, 4.0, 3.0);
	B2 = Point3(-4.0, 2.0, 1.0);
	C2 = Point3(0.5, 1.0, 3.0);

	triangle_1 = Triangle(C1, B1, A1);

	triangle_2 = Triangle(A2, C2, B2);

	assert(intersects3(triangle_1, triangle_2) == true);
	std::clog << "test_5 passed\n\n";

	// test_6 (true)

	A1 = Point3(1.0, -4.0, 1.0);
	B1 = Point3(-4.0, -2.0, 3.0);
	C1 = Point3(1.0, -1.0, 1.0);

	A2 = Point3(1.0, -4.0, 3.0);
	B2 = Point3(-4.0, -2.0, 1.0);
	C2 = Point3(0.5, -1.0, 3.0);

	triangle_1 = Triangle(C1, B1, A1);

	triangle_2 = Triangle(A2, C2, B2);

	assert(intersects3(triangle_1, triangle_2) == true);
	std::clog << "test_6 passed\n\n";

	// test_7 (true)

// 	A1 = Point3( 1.0, 4.0, 1.0);
// 	B1 = Point3(-4.0, 2.0, 3.0);
// 	C1 = Point3(1.0, 1.0, 1.0);
//
// 	A2 = Point3( 1.0, 2.5, 3.0);
// 	B2 = Point3(-4.0, 0.0, 1.0);
// 	C2 = Point3(-4.0, 4.0, 1.0);
//
// 	triangle_1 = Triangle(C1, B1, A1);
//
// 	triangle_2 = Triangle(A2, C2, B2);
//
// 	assert(intersects3(triangle_1, triangle_2) == true);
// 	std::clog << "test_7 passed\n\n";

	return 0;
}
