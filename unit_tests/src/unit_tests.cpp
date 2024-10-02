#include <fstream>
#include <format>
#include <string>

#include <gtest/gtest.h>

#include "intersects.h"
#include "test_utils.h"

TEST(two_dimentional, basic_1)
{
	Point3 A1(2.0, 2.0, 0.0);
	Point3 B1(8.0, 2.0, 0.0);
	Point3 C1(2.0, 10.0, 0.0);

	Point3 A2(4.0, 4.0, 0.0);
	Point3 B2(8.0, 4.0, 0.0);
	Point3 C2(8.0, 7.0, 0.0);

	Triangle3 triangle_1(A1, B1, C1);
	Triangle3 triangle_2(A2, B2, C2);

	EXPECT_EQ(intersects3(triangle_1, triangle_2), true);
}

TEST(two_dimentional, basic_2)
{
	Triangle3 triangle_1(Point3(2.0, 2.0, 0.0)
						, Point3(2.0, 10.0, 0.0)
						, Point3(8.0, 2.0, 0.0));

	Triangle3 triangle_2(Point3(7.0, 4.0, 0.0)
						, Point3(8.0, 7.0, 0.0)
						, Point3(8.0, 4.0, 0.0));

	EXPECT_EQ(intersects3(triangle_1, triangle_2), false);
}

TEST(two_dimentional, basic_3)
{
	Triangle3 triangle_1(Point3(2.0, 2.0, 0.0)
						, Point3(8.0, 2.0, 0.0)
						, Point3(2.0, 10.0, 0.0));

	Triangle3 triangle_2(Point3(5.0, 6.0, 0.0)
						, Point3(8.0, 4.0, 0.0)
						, Point3(8.0, 7.0, 0.0));

	EXPECT_EQ(intersects3(triangle_1, triangle_2), true);
}

TEST(two_dimentional, basic_4)
{
	Point3 A1(2.0, 2.0, 0.0);
	Point3 B1(8.0, 2.0, 0.0);
	Point3 C1(2.0, 10.0, 0.0);

	Point3 A2(3.0, 3.0, 0.0);
	Point3 B2(5.0, 3.0, 0.0);
	Point3 C2(5.0, 5.0, 0.0);

	Triangle3 triangle_1(A1, B1, C1);
	Triangle3 triangle_2(A2, B2, C2);

	EXPECT_EQ(intersects3(triangle_1, triangle_2), true);
}

//треугольник(2|0|0 1|1|0 4|1|0)
//треугольник(3|1|0 4|4|0 2|4|0)
TEST(two_dimentional, one_point_intersection)
{
	Point3 A1(2.0, 0.0, 0.0);
	Point3 B1(1.0, 1.0, 0.0);
	Point3 C1(4.0, 1.0, 0.0);

	Point3 A2(3.0, 1.0, 0.0);
	Point3 B2(4.0, 4.0, 0.0);
	Point3 C2(2.0, 4.0, 0.0);

	Triangle3 triangle_1(A1, B1, C1);

	Triangle3 triangle_2(A2, B2, C2);

	EXPECT_EQ(intersects3(triangle_1, triangle_2), true);
}

// треугольник(2|0|0 1|1|0 4|1|0)
// треугольник(2|-2|0 4|4|0 5|7|0)
TEST(two_dimentional, degen_triangle_1)
{
	Point3 A1(2.0, 0.0, 0.0);
	Point3 B1(1.0, 1.0, 0.0);
	Point3 C1(4.0, 1.0, 0.0);

	Point3 A2(2.0, -2.0, 0.0);
	Point3 B2(4.0, 4.0, 0.0);
	Point3 C2(5.0, 7.0, 0.0);

	Triangle3 triangle_1(A1, B1, C1);

	Triangle3 triangle_2(A2, B2, C2);

	EXPECT_EQ(intersects3(triangle_1, triangle_2), true);
}

// треугольник(2|0|0 1|1|0 4|1|0)
// треугольник(-1|-2|0 -3|-4|0 -4|-5|0)
TEST(two_dimentional, degen_triangle_2)
{
	Point3 A1(2.0, 0.0, 0.0);
	Point3 B1(1.0, 1.0, 0.0);
	Point3 C1(4.0, 1.0, 0.0);

	Point3 A2(-1.0, -2.0, 0.0);
	Point3 B2(-3.0, -4.0, 0.0);
	Point3 C2(-4.0, -5.0, 0.0);

	Triangle3 triangle_1(A1, B1, C1);

	Triangle3 triangle_2(A2, B2, C2);

	EXPECT_EQ(intersects3(triangle_1, triangle_2), false);
}

// треугольник(2|0|0 1|1|0 4|1|0)
// треугольник(3|1|0 4|4|0 5|7|0)
TEST(two_dimentional, degen_triangle_one_point_intersection)
{
	Point3 A1(2.0, 0.0, 0.0);
	Point3 B1(1.0, 1.0, 0.0);
	Point3 C1(4.0, 1.0, 0.0);

	Point3 A2(3.0, 1.0, 0.0);
	Point3 B2(4.0, 4.0, 0.0);
	Point3 C2(5.0, 7.0, 0.0);

	Triangle3 triangle_1(A1, B1, C1);

	Triangle3 triangle_2(A2, B2, C2);

	EXPECT_EQ(intersects3(triangle_1, triangle_2), true);
}

// треугольник(2|0|0 1|1|0 4|1|0)
// треугольник(2|0.5|0.0 2|0.5|0.0 2|0.5|0.0)
TEST(two_dimentional, contained_superdegen)
{
	Point3 A1(2.0, 0.0, 0.0);
	Point3 B1(1.0, 1.0, 0.0);
	Point3 C1(4.0, 1.0, 0.0);

	Point3 A2(2.0, 0.5, 0.0);
	Point3 B2(2.0, 0.5, 0.0);
	Point3 C2(2.0, 0.5, 0.0);

	Triangle3 triangle_1(A1, B1, C1);

	Triangle3 triangle_2(A2, B2, C2);

	EXPECT_EQ(intersects3(triangle_1, triangle_2), true);
}

// треугольник(2|0|0 1|1|0 4|1|0)
// треугольник(2|0|0 2|0|0 2|0|0)
TEST(two_dimentional, superdegen_on_vert)
{
	Point3 A1(2.0, 0.0, 0.0);
	Point3 B1(1.0, 1.0, 0.0);
	Point3 C1(4.0, 1.0, 0.0);

	Point3 A2(2.0, 0.0, 0.0);
	Point3 B2(2.0, 0.0, 0.0);
	Point3 C2(2.0, 0.0, 0.0);

	Triangle3 triangle_1(A1, B1, C1);

	Triangle3 triangle_2(A2, B2, C2);

	EXPECT_EQ(intersects3(triangle_1, triangle_2), true);
}

// треугольник(2|0|0 1|1|0 4|1|0)
// треугольник(2|1|0 2|1|0 2|1|0)
TEST(two_dimentional, superdegen_on_side)
{
	Point3 A1(2.0, 0.0, 0.0);
	Point3 B1(1.0, 1.0, 0.0);
	Point3 C1(4.0, 1.0, 0.0);

	Point3 A2(2.0, 1.0, 0.0);
	Point3 B2(2.0, 1.0, 0.0);
	Point3 C2(2.0, 1.0, 0.0);

	Triangle3 triangle_1(A1, B1, C1);

	Triangle3 triangle_2(A2, B2, C2);

	EXPECT_EQ(intersects3(triangle_1, triangle_2), true);
}

// треугольник(2|0|0 1|1|0 4|1|0)
// треугольник(3|1|0 4|4|0 5|7|0)
TEST(two_dimentional, not_contained_superdegen)
{
	Point3 A1(2.0, 0.0, 0.0);
	Point3 B1(1.0, 1.0, 0.0);
	Point3 C1(4.0, 1.0, 0.0);

	Point3 A2(5.0, 5.0, 0.0);
	Point3 B2(5.0, 5.0, 0.0);
	Point3 C2(5.0, 5.0, 0.0);

	Triangle3 triangle_1(A1, B1, C1);

	Triangle3 triangle_2(A2, B2, C2);

	EXPECT_EQ(intersects3(triangle_1, triangle_2), false);
}

TEST(threeDimentional, basic_1)
{
	Point3 A1(1.0, 4.0, 1.0);
	Point3 B1(-4.0, 2.0, 3.0);
	Point3 C1(1.0, 1.0, 1.0);

	Point3 A2(1.0, 4.0, 3.0);
	Point3 B2(-4.0, 2.0, 1.0);
	Point3 C2(1.0, 1.0, 3.0);

	Triangle3 triangle_1(A1, B1, C1);

	Triangle3 triangle_2(A2, B2, C2);

	EXPECT_EQ(intersects3(triangle_1, triangle_2), true);
}

TEST(threeDimentional, basic_2)
{
	Point3 A1(1.0, -4.0, 1.0);
	Point3 B1(-4.0, -2.0, 3.0);
	Point3 C1(0.5, -1.0, 1.0);

	Point3 A2(1.0, -4.0, 3.0);
	Point3 B2(-4.0, -2.0, 1.0);
	Point3 C2(1.0, -1.0, 3.0);

	Triangle3 triangle_1(A1, B1, C1);

	Triangle3 triangle_2(A2, B2, C2);

	EXPECT_EQ(intersects3(triangle_1, triangle_2), true);
}

TEST(threeDimentional, basic_3)
{
	Point3 A1( 1.0, 4.0, 1.0);
	Point3 B1(-4.0, 2.0, 3.0);
	Point3 C1(1.0, 1.0, 1.0);

	Point3 A2( 1.0, 2.5, 3.0);
	Point3 B2(-4.0, 0.0, 1.0);
	Point3 C2(-4.0, 4.0, 1.0);

	Triangle3 triangle_1(C1, B1, A1);

	Triangle3 triangle_2(A2, C2, B2);

	EXPECT_EQ(intersects3(triangle_1, triangle_2), true);
}

TEST(threeDimentional, basic_4)
{
	Point3 A1(1.0, 4.0, 3.0);
	Point3 B1(2.0, 2.0, 2.0);
	Point3 C1(-3.0, 2.0, 1.5);

	Point3 A2(-1.0, -4.0, -2.5);
	Point3 B2(2.0, -2.0, 4.0);
	Point3 C2(-2.5, -2.5, 3.5);

	Triangle3 triangle_1(A1, B1, C1);

	Triangle3 triangle_2(A2, B2, C2);

	EXPECT_EQ(intersects3(triangle_1, triangle_2), false);
}

// треугольник(1.0|4.0|3.0 2.0|2.0|2.0 -3.0|2.0|1.5)
// треугольник(5.0|4.0|-2.5 8.0|2.0|4.0 3.5|2.5|3.5)
TEST(threeDimentional, basic_5)
{
	Point3 A1(1.0, 4.0, 3.0);
	Point3 B1(2.0, 2.0, 2.0);
	Point3 C1(-3.0, 2.0, 1.5);

	Point3 A2(5.0, 4.0, -2.5);
	Point3 B2(8.0, 2.0, 4.0);
	Point3 C2(3.5, 2.5, 3.5);

	Triangle3 triangle_1(A1, B1, C1);

	Triangle3 triangle_2(A2, B2, C2);

	EXPECT_EQ(intersects3(triangle_1, triangle_2), false);
}

//треугольник(2|0|0 1|1|0 4|1|0)
//треугольник(3|1|0 4|4|4 2|4|4)
TEST(threeDimentional, one_point_intersection)
{
	Point3 A1(2.0, 0.0, 0.0);
	Point3 B1(1.0, 1.0, 0.0);
	Point3 C1(4.0, 1.0, 0.0);

	Point3 A2(3.0, 1.0, 0.0);
	Point3 B2(4.0, 4.0, 4.0);
	Point3 C2(2.0, 4.0, 4.0);

	Triangle3 triangle_1(A1, B1, C1);

	Triangle3 triangle_2(A2, B2, C2);

	EXPECT_EQ(intersects3(triangle_1, triangle_2), true);
}

//треугольник(2|0|1 3|4|3 7|1|2)
//треугольник(-1|-2|0 -3|-4|0 -4|-5|0)
TEST(threeDimentional, degen_triangle_1)
{
	Point3 A1(2.0, 0.0, 1.0);
	Point3 B1(3.0, 4.0, 3.0);
	Point3 C1(7.0, 1.0, 2.0);

	Point3 A2(-1.0, -2.0, 0.0);
	Point3 B2(-3.0, -4.0, 0.0);
	Point3 C2(-4.0, -5.0, 0.0);

	Triangle3 triangle_1(A1, B1, C1);

	Triangle3 triangle_2(A2, B2, C2);

	EXPECT_EQ(intersects3(triangle_1, triangle_2), false);
}

// треугольник(2|0|1 3|8|3 7|6|2)
// треугольник(4|2|0 4|4|2 4|6|4)
TEST(threeDimentional, degen_triangle_2)
{
	Point3 A1(2.0, 0.0, 1.0);
	Point3 B1(3.0, 8.0, 3.0);
	Point3 C1(7.0, 6.0, 2.0);

	Point3 A2(4.0, 2.0, 0.0);
	Point3 B2(4.0, 4.0, 2.0);
	Point3 C2(4.0, 6.0, 4.0);

	Triangle3 triangle_1(A1, B1, C1);

	Triangle3 triangle_2(A2, B2, C2);

	EXPECT_EQ(intersects3(triangle_1, triangle_2), true);
}

// треугольник(2|0|1 3|8|3 7|6|2)
// треугольник(2|0|0 2|0|2 2|0|4)
TEST(threeDimentional, degen_triangle_one_point_intersection)
{
	Point3 A1(2.0, 0.0, 1.0);
	Point3 B1(3.0, 8.0, 3.0);
	Point3 C1(7.0, 6.0, 2.0);

	Point3 A2(2.0, 0.0, 0.0);
	Point3 B2(2.0, 0.0, 2.0);
	Point3 C2(2.0, 0.0, 4.0);

	Triangle3 triangle_1(A1, B1, C1);

	Triangle3 triangle_2(A2, B2, C2);

	EXPECT_EQ(intersects3(triangle_1, triangle_2), true);
}

#ifdef BD_TESTS



#endif

