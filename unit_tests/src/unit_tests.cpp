#include <fstream>
#include <format>
#include <string>

#include <gtest/gtest.h>

#include "intersects.h"
#include "test_utils.h"

TEST(twoDimentional, test_1)
{
	Point3 A1(2.0, 2.0, 0.0);
	Point3 B1(8.0, 2.0, 0.0);
	Point3 C1(2.0, 10.0, 0.0);

	Point3 A2(4.0, 4.0, 0.0);
	Point3 B2(8.0, 4.0, 0.0);
	Point3 C2(8.0, 7.0, 0.0);

	Triangle triangle_1(A1, B1, C1);
	Triangle triangle_2(A2, B2, C2);

	EXPECT_EQ(intersects3(triangle_1, triangle_2), true);
}

TEST(twoDimentional, test_2)
{
	Triangle triangle_1(Point3(2.0, 2.0, 0.0)
						, Point3(2.0, 10.0, 0.0)
						, Point3(8.0, 2.0, 0.0));

	Triangle triangle_2(Point3(7.0, 4.0, 0.0)
						, Point3(8.0, 7.0, 0.0)
						, Point3(8.0, 4.0, 0.0));

	EXPECT_EQ(intersects3(triangle_1, triangle_2), false);
}

TEST(twoDimentional, test_3)
{
	Triangle triangle_1(Point3(2.0, 2.0, 0.0)
						, Point3(8.0, 2.0, 0.0)
						, Point3(2.0, 10.0, 0.0));

	Triangle triangle_2(Point3(5.0, 6.0, 0.0)
						, Point3(8.0, 4.0, 0.0)
						, Point3(8.0, 7.0, 0.0));

	EXPECT_EQ(intersects3(triangle_1, triangle_2), true);
}

TEST(twoDimentional, test_4)
{
	Point3 A1(2.0, 2.0, 0.0);
	Point3 B1(8.0, 2.0, 0.0);
	Point3 C1(2.0, 10.0, 0.0);

	Point3 A2(3.0, 3.0, 0.0);
	Point3 B2(5.0, 3.0, 0.0);
	Point3 C2(5.0, 5.0, 0.0);

	Triangle triangle_1(A1, B1, C1);
	Triangle triangle_2(A2, B2, C2);

	EXPECT_EQ(intersects3(triangle_1, triangle_2), true);
}

TEST(threeDimentional, test_1)
{
	Point3 A1(1.0, 4.0, 1.0);
	Point3 B1(-4.0, 2.0, 3.0);
	Point3 C1(1.0, 1.0, 1.0);

	Point3 A2(1.0, 4.0, 3.0);
	Point3 B2(-4.0, 2.0, 1.0);
	Point3 C2(1.0, 1.0, 3.0);

	Triangle triangle_1(A1, B1, C1);

	Triangle triangle_2(A2, B2, C2);

	EXPECT_EQ(intersects3(triangle_1, triangle_2), true);
}

TEST(threeDimentional, test_2)
{
	Point3 A1(1.0, -4.0, 1.0);
	Point3 B1(-4.0, -2.0, 3.0);
	Point3 C1(0.5, -1.0, 1.0);

	Point3 A2(1.0, -4.0, 3.0);
	Point3 B2(-4.0, -2.0, 1.0);
	Point3 C2(1.0, -1.0, 3.0);

	Triangle triangle_1(A1, B1, C1);

	Triangle triangle_2(A2, B2, C2);

	EXPECT_EQ(intersects3(triangle_1, triangle_2), true);
}

TEST(threeDimentional, test_3)
{
	Point3 A1( 1.0, 4.0, 1.0);
	Point3 B1(-4.0, 2.0, 3.0);
	Point3 C1(1.0, 1.0, 1.0);

	Point3 A2( 1.0, 2.5, 3.0);
	Point3 B2(-4.0, 0.0, 1.0);
	Point3 C2(-4.0, 4.0, 1.0);

	Triangle triangle_1(C1, B1, A1);

	Triangle triangle_2(A2, C2, B2);

	EXPECT_EQ(intersects3(triangle_1, triangle_2), true);
}

TEST(threeDimentional, test_4)
{
	Point3 A1(1.0, 4.0, 3.0);
	Point3 B1(2.0, 2.0, 2.0);
	Point3 C1(-3.0, 2.0, 1.5);

	Point3 A2(-1.0, -4.0, -2.5);
	Point3 B2(2.0, -2.0, 4.0);
	Point3 C2(-2.5, -2.5, 3.5);

	Triangle triangle_1(A1, B1, C1);

	Triangle triangle_2(A2, B2, C2);

	EXPECT_EQ(intersects3(triangle_1, triangle_2), false);
}

TEST(threeDimentional, test_5)
{
	Point3 A1(1.0, 4.0, 3.0);
	Point3 B1(2.0, 2.0, 2.0);
	Point3 C1(-3.0, 2.0, 1.5);

	Point3 A2(5.0, 4.0, -2.5);
	Point3 B2(8.0, 2.0, 4.0);
	Point3 C2(3.5, 2.5, 3.5);

	Triangle triangle_1(A1, B1, C1);

	Triangle triangle_2(A2, B2, C2);

	EXPECT_EQ(intersects3(triangle_1, triangle_2), false);
}

#ifdef BD_TESTS



#endif

