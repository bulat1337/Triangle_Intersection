#include "intersects.h"  // for intersects3
#include "test_utils.h"  // for run_test
#include "triangle.h"    // for Triangle3
#include "vec.h"         // for Point3<double>
#include <gtest/gtest.h> // for Test, TestInfo (ptr only), Message, TEST
#include <string>        // for basic_string

TEST(two_dimentional, basic_1)
{
    Point3<double> A1(2.0, 2.0, 0.0);
    Point3<double> B1(8.0, 2.0, 0.0);
    Point3<double> C1(2.0, 10.0, 0.0);

    Point3<double> A2(4.0, 4.0, 0.0);
    Point3<double> B2(8.0, 4.0, 0.0);
    Point3<double> C2(8.0, 7.0, 0.0);

    Triangle3 triangle_1(A1, B1, C1);
    Triangle3 triangle_2(A2, B2, C2);

    EXPECT_EQ(intersects3(triangle_1, triangle_2), true);
}

TEST(two_dimentional, basic_2)
{
    Triangle3 triangle_1(Point3<double>(2.0, 2.0, 0.0),
                         Point3<double>(2.0, 10.0, 0.0),
                         Point3<double>(8.0, 2.0, 0.0));

    Triangle3 triangle_2(Point3<double>(7.0, 4.0, 0.0),
                         Point3<double>(8.0, 7.0, 0.0),
                         Point3<double>(8.0, 4.0, 0.0));

    EXPECT_EQ(intersects3(triangle_1, triangle_2), false);
}

TEST(two_dimentional, basic_3)
{
    Triangle3 triangle_1(Point3<double>(2.0, 2.0, 0.0),
                         Point3<double>(8.0, 2.0, 0.0),
                         Point3<double>(2.0, 10.0, 0.0));

    Triangle3 triangle_2(Point3<double>(5.0, 6.0, 0.0),
                         Point3<double>(8.0, 4.0, 0.0),
                         Point3<double>(8.0, 7.0, 0.0));

    EXPECT_EQ(intersects3(triangle_1, triangle_2), true);
}

TEST(two_dimentional, basic_4)
{
    Point3<double> A1(2.0, 2.0, 0.0);
    Point3<double> B1(8.0, 2.0, 0.0);
    Point3<double> C1(2.0, 10.0, 0.0);

    Point3<double> A2(3.0, 3.0, 0.0);
    Point3<double> B2(5.0, 3.0, 0.0);
    Point3<double> C2(5.0, 5.0, 0.0);

    Triangle3 triangle_1(A1, B1, C1);
    Triangle3 triangle_2(A2, B2, C2);

    EXPECT_EQ(intersects3(triangle_1, triangle_2), true);
}

// треугольник(2|0|0 1|1|0 4|1|0)
// треугольник(3|1|0 4|4|0 2|4|0)
TEST(two_dimentional, one_point_intersection)
{
    Point3<double> A1(2.0, 0.0, 0.0);
    Point3<double> B1(1.0, 1.0, 0.0);
    Point3<double> C1(4.0, 1.0, 0.0);

    Point3<double> A2(3.0, 1.0, 0.0);
    Point3<double> B2(4.0, 4.0, 0.0);
    Point3<double> C2(2.0, 4.0, 0.0);

    Triangle3 triangle_1(A1, B1, C1);

    Triangle3 triangle_2(A2, B2, C2);

    EXPECT_EQ(intersects3(triangle_1, triangle_2), true);
}

// треугольник(2|0|0 1|1|0 4|1|0)
// треугольник(2|-2|0 4|4|0 5|7|0)
TEST(two_dimentional, degen_triangle_1)
{
    Point3<double> A1(2.0, 0.0, 0.0);
    Point3<double> B1(1.0, 1.0, 0.0);
    Point3<double> C1(4.0, 1.0, 0.0);

    Point3<double> A2(2.0, -2.0, 0.0);
    Point3<double> B2(4.0, 4.0, 0.0);
    Point3<double> C2(5.0, 7.0, 0.0);

    Triangle3 triangle_1(A1, B1, C1);

    Triangle3 triangle_2(A2, B2, C2);

    EXPECT_EQ(intersects3(triangle_1, triangle_2), true);
}

// треугольник(2|0|0 1|1|0 4|1|0)
// треугольник(-1|-2|0 -3|-4|0 -4|-5|0)
TEST(two_dimentional, degen_triangle_2)
{
    Point3<double> A1(2.0, 0.0, 0.0);
    Point3<double> B1(1.0, 1.0, 0.0);
    Point3<double> C1(4.0, 1.0, 0.0);

    Point3<double> A2(-1.0, -2.0, 0.0);
    Point3<double> B2(-3.0, -4.0, 0.0);
    Point3<double> C2(-4.0, -5.0, 0.0);

    Triangle3 triangle_1(A1, B1, C1);

    Triangle3 triangle_2(A2, B2, C2);

    EXPECT_EQ(intersects3(triangle_1, triangle_2), false);
}

// треугольник(2|0|0 1|1|0 4|1|0)
// треугольник(3|1|0 4|4|0 5|7|0)
TEST(two_dimentional, degen_triangle_one_point_intersection)
{
    Point3<double> A1(2.0, 0.0, 0.0);
    Point3<double> B1(1.0, 1.0, 0.0);
    Point3<double> C1(4.0, 1.0, 0.0);

    Point3<double> A2(3.0, 1.0, 0.0);
    Point3<double> B2(4.0, 4.0, 0.0);
    Point3<double> C2(5.0, 7.0, 0.0);

    Triangle3 triangle_1(A1, B1, C1);

    Triangle3 triangle_2(A2, B2, C2);

    EXPECT_EQ(intersects3(triangle_1, triangle_2), true);
}

// треугольник(2|0|0 1|1|0 4|1|0)
// треугольник(2|0.5|0.0 2|0.5|0.0 2|0.5|0.0)
TEST(two_dimentional, contained_superdegen)
{
    Point3<double> A1(2.0, 0.0, 0.0);
    Point3<double> B1(1.0, 1.0, 0.0);
    Point3<double> C1(4.0, 1.0, 0.0);

    Point3<double> A2(2.0, 0.5, 0.0);
    Point3<double> B2(2.0, 0.5, 0.0);
    Point3<double> C2(2.0, 0.5, 0.0);

    Triangle3 triangle_1(A1, B1, C1);

    Triangle3 triangle_2(A2, B2, C2);

    EXPECT_EQ(intersects3(triangle_1, triangle_2), true);
}

// треугольник(2|0|0 1|1|0 4|1|0)
// треугольник(2|0|0 2|0|0 2|0|0)
TEST(two_dimentional, superdegen_on_vert)
{
    Point3<double> A1(2.0, 0.0, 0.0);
    Point3<double> B1(1.0, 1.0, 0.0);
    Point3<double> C1(4.0, 1.0, 0.0);

    Point3<double> A2(2.0, 0.0, 0.0);
    Point3<double> B2(2.0, 0.0, 0.0);
    Point3<double> C2(2.0, 0.0, 0.0);

    Triangle3 triangle_1(A1, B1, C1);

    Triangle3 triangle_2(A2, B2, C2);

    EXPECT_EQ(intersects3(triangle_1, triangle_2), true);
}

// треугольник(2|0|0 1|1|0 4|1|0)
// треугольник(2|1|0 2|1|0 2|1|0)
TEST(two_dimentional, superdegen_on_side)
{
    Point3<double> A1(2.0, 0.0, 0.0);
    Point3<double> B1(1.0, 1.0, 0.0);
    Point3<double> C1(4.0, 1.0, 0.0);

    Point3<double> A2(2.0, 1.0, 0.0);
    Point3<double> B2(2.0, 1.0, 0.0);
    Point3<double> C2(2.0, 1.0, 0.0);

    Triangle3 triangle_1(A1, B1, C1);

    Triangle3 triangle_2(A2, B2, C2);

    EXPECT_EQ(intersects3(triangle_1, triangle_2), true);
}

// треугольник(2|0|0 1|1|0 4|1|0)
// треугольник(3|1|0 4|4|0 5|7|0)
TEST(two_dimentional, not_contained_superdegen)
{
    Point3<double> A1(2.0, 0.0, 0.0);
    Point3<double> B1(1.0, 1.0, 0.0);
    Point3<double> C1(4.0, 1.0, 0.0);

    Point3<double> A2(5.0, 5.0, 0.0);
    Point3<double> B2(5.0, 5.0, 0.0);
    Point3<double> C2(5.0, 5.0, 0.0);

    Triangle3 triangle_1(A1, B1, C1);

    Triangle3 triangle_2(A2, B2, C2);

    EXPECT_EQ(intersects3(triangle_1, triangle_2), false);
}

TEST(three_dimentional, basic_1)
{
    Point3<double> A1(1.0, 4.0, 1.0);
    Point3<double> B1(-4.0, 2.0, 3.0);
    Point3<double> C1(1.0, 1.0, 1.0);

    Point3<double> A2(1.0, 4.0, 3.0);
    Point3<double> B2(-4.0, 2.0, 1.0);
    Point3<double> C2(1.0, 1.0, 3.0);

    Triangle3 triangle_1(A1, B1, C1);

    Triangle3 triangle_2(A2, B2, C2);

    EXPECT_EQ(intersects3(triangle_1, triangle_2), true);
}

TEST(three_dimentional, basic_2)
{
    Point3<double> A1(1.0, -4.0, 1.0);
    Point3<double> B1(-4.0, -2.0, 3.0);
    Point3<double> C1(0.5, -1.0, 1.0);

    Point3<double> A2(1.0, -4.0, 3.0);
    Point3<double> B2(-4.0, -2.0, 1.0);
    Point3<double> C2(1.0, -1.0, 3.0);

    Triangle3 triangle_1(A1, B1, C1);

    Triangle3 triangle_2(A2, B2, C2);

    EXPECT_EQ(intersects3(triangle_1, triangle_2), true);
}

TEST(three_dimentional, basic_3)
{
    Point3<double> A1(1.0, 4.0, 1.0);
    Point3<double> B1(-4.0, 2.0, 3.0);
    Point3<double> C1(1.0, 1.0, 1.0);

    Point3<double> A2(1.0, 2.5, 3.0);
    Point3<double> B2(-4.0, 0.0, 1.0);
    Point3<double> C2(-4.0, 4.0, 1.0);

    Triangle3 triangle_1(C1, B1, A1);

    Triangle3 triangle_2(A2, C2, B2);

    EXPECT_EQ(intersects3(triangle_1, triangle_2), true);
}

TEST(three_dimentional, basic_4)
{
    Point3<double> A1(1.0, 4.0, 3.0);
    Point3<double> B1(2.0, 2.0, 2.0);
    Point3<double> C1(-3.0, 2.0, 1.5);

    Point3<double> A2(-1.0, -4.0, -2.5);
    Point3<double> B2(2.0, -2.0, 4.0);
    Point3<double> C2(-2.5, -2.5, 3.5);

    Triangle3 triangle_1(A1, B1, C1);

    Triangle3 triangle_2(A2, B2, C2);

    EXPECT_EQ(intersects3(triangle_1, triangle_2), false);
}

// треугольник(1.0|4.0|3.0 2.0|2.0|2.0 -3.0|2.0|1.5)
// треугольник(5.0|4.0|-2.5 8.0|2.0|4.0 3.5|2.5|3.5)
TEST(three_dimentional, basic_5)
{
    Point3<double> A1(1.0, 4.0, 3.0);
    Point3<double> B1(2.0, 2.0, 2.0);
    Point3<double> C1(-3.0, 2.0, 1.5);

    Point3<double> A2(5.0, 4.0, -2.5);
    Point3<double> B2(8.0, 2.0, 4.0);
    Point3<double> C2(3.5, 2.5, 3.5);

    Triangle3 triangle_1(A1, B1, C1);

    Triangle3 triangle_2(A2, B2, C2);

    EXPECT_EQ(intersects3(triangle_1, triangle_2), false);
}

// треугольник(2|0|0 1|1|0 4|1|0)
// треугольник(3|1|0 4|4|4 2|4|4)
TEST(three_dimentional, one_point_intersection)
{
    Point3<double> A1(2.0, 0.0, 0.0);
    Point3<double> B1(1.0, 1.0, 0.0);
    Point3<double> C1(4.0, 1.0, 0.0);

    Point3<double> A2(3.0, 1.0, 0.0);
    Point3<double> B2(4.0, 4.0, 4.0);
    Point3<double> C2(2.0, 4.0, 4.0);

    Triangle3 triangle_1(A1, B1, C1);

    Triangle3 triangle_2(A2, B2, C2);

    EXPECT_EQ(intersects3(triangle_1, triangle_2), true);
}

// треугольник(2|0|1 3|4|3 7|1|2)
// треугольник(-1|-2|0 -3|-4|0 -4|-5|0)
TEST(three_dimentional, degen_triangle_1)
{
    Point3<double> A1(2.0, 0.0, 1.0);
    Point3<double> B1(3.0, 4.0, 3.0);
    Point3<double> C1(7.0, 1.0, 2.0);

    Point3<double> A2(-1.0, -2.0, 0.0);
    Point3<double> B2(-3.0, -4.0, 0.0);
    Point3<double> C2(-4.0, -5.0, 0.0);

    Triangle3 triangle_1(A1, B1, C1);

    Triangle3 triangle_2(A2, B2, C2);

    EXPECT_EQ(intersects3(triangle_1, triangle_2), false);
}

// треугольник(2|0|1 3|8|3 7|6|2)
// треугольник(4|2|0 4|4|2 4|6|4)
TEST(three_dimentional, degen_triangle_2)
{
    Point3<double> A1(2.0, 0.0, 1.0);
    Point3<double> B1(3.0, 8.0, 3.0);
    Point3<double> C1(7.0, 6.0, 2.0);

    Point3<double> A2(4.0, 2.0, 0.0);
    Point3<double> B2(4.0, 4.0, 2.0);
    Point3<double> C2(4.0, 6.0, 4.0);

    Triangle3 triangle_1(A1, B1, C1);

    Triangle3 triangle_2(A2, B2, C2);

    EXPECT_EQ(intersects3(triangle_1, triangle_2), true);
}

// треугольник(2|0|1 3|8|3 7|6|2)
// треугольник(2|0|0 2|0|2 2|0|4)
TEST(three_dimentional, degen_triangle_one_point_intersection)
{
    Point3<double> A1(2.0, 0.0, 1.0);
    Point3<double> B1(3.0, 8.0, 3.0);
    Point3<double> C1(7.0, 6.0, 2.0);

    Point3<double> A2(2.0, 0.0, 0.0);
    Point3<double> B2(2.0, 0.0, 2.0);
    Point3<double> C2(2.0, 0.0, 4.0);

    Triangle3 triangle_1(A1, B1, C1);

    Triangle3 triangle_2(A2, B2, C2);

    EXPECT_EQ(intersects3(triangle_1, triangle_2), true);
}

// треугольник(-2.4|-0.9|10.7 1.1|0.9|18.4 -11.4|-9.0|18.1)
// треугольник(-10.0|0.6|17.6 -1.3|-5.8|13.9 -16.5|-9.4|19.7)
TEST(three_dimentional, basic_6)
{
    Point3<double> A1(-2.4, -0.9, 10.7);
    Point3<double> B1(1.1, 0.9, 18.4);
    Point3<double> C1(-11.4, -9.0, 18.1);

    Point3<double> A2(-10.0, 0.6, 17.6);
    Point3<double> B2(-1.3, -5.8, 13.9);
    Point3<double> C2(-16.5, -9.4, 19.7);

    Triangle3 triangle_1(A1, B1, C1);

    Triangle3 triangle_2(A2, B2, C2);

    EXPECT_EQ(intersects3(triangle_1, triangle_2), true);
}

// треугольник(-2.4|-0.9|10.7 1.1|0.9|18.4 -11.4|-9.0|18.1)
// треугольник(-10.0|0.6|17.6 -1.3|-5.8|13.9 -16.5|-9.4|19.7)
TEST(three_dimentional, basic_7)
{
    Point3<double> A1(-2.4, -0.9, 10.7);
    Point3<double> B1(1.1, 0.9, 18.4);
    Point3<double> C1(-11.4, -9.0, 18.1);

    Point3<double> A2(-10.0, 0.6, 17.6);
    Point3<double> B2(-1.3, -5.8, 13.9);
    Point3<double> C2(-16.5, -9.4, 19.7);

    Triangle3 triangle_1(A2, B2, C2);

    Triangle3 triangle_2(A1, B1, C1);

    EXPECT_EQ(intersects3(triangle_1, triangle_2), true);
}

// треугольник(9|9|9 9|9|9 9|9|9)
// треугольник(8|8|8 8|8|8 -10|8|8)
TEST(three_dimentional, degen_and_superdegen)
{
    Point3<double> A1(9.0, 9.0, 9.0);
    Point3<double> B1(9.0, 9.0, 9.0);
    Point3<double> C1(9.0, 9.0, 9.0);

    Point3<double> A2(8.0, 8.0, 8.0);
    Point3<double> B2(8.0, 8.0, 8.0);
    Point3<double> C2(-10.0, 8.0, 8.0);

    Triangle3 triangle_1(A2, B2, C2);

    Triangle3 triangle_2(A1, B1, C1);

    EXPECT_EQ(intersects3(triangle_1, triangle_2), false);
}

TEST(common, basic_1) { test_utils::run_test("/common/basic_1"); }

TEST(common, basic_2) { test_utils::run_test("/common/basic_2"); }

TEST(common, basic_3) { test_utils::run_test("/common/basic_3"); }

#ifdef BD_TESTS

TEST(bd_tests, amount_100) { test_utils::run_test("/bd_tests/amount-100"); }

TEST(bd_tests, amount_10000) { test_utils::run_test("/bd_tests/amount-100000"); }

#endif
