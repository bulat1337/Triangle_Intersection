#include <gtest/gtest.h>  // for Test, Message, TestInfo (ptr only), CmpHelp...
#include <string>         // for basic_string
#include "intersects.h"   // for intersects3
#include "status.h"       // for status_t
#include "test_utils.h"   // for run_test
#include "triangle.h"     // for Triangle3
#include "vec.h"          // for Point3

TEST(two_dimentional, basic_1)
{
    t_inter::Point3<double> A1(2.0, 2.0, 0.0);
    t_inter::Point3<double> B1(8.0, 2.0, 0.0);
    t_inter::Point3<double> C1(2.0, 10.0, 0.0);

    t_inter::Point3<double> A2(4.0, 4.0, 0.0);
    t_inter::Point3<double> B2(8.0, 4.0, 0.0);
    t_inter::Point3<double> C2(8.0, 7.0, 0.0);

    t_inter::Triangle3 triangle_1(A1, B1, C1);
    t_inter::Triangle3 triangle_2(A2, B2, C2);

    t_inter::status_t status = t_inter::status_t::all_good;
    EXPECT_EQ(t_inter::detail::intersects3(triangle_1, triangle_2, status),
              true);
    EXPECT_EQ(status, t_inter::status_t::all_good);
}

TEST(two_dimentional, basic_2)
{
    t_inter::Triangle3 triangle_1(t_inter::Point3<double>(2.0, 2.0, 0.0),
                                  t_inter::Point3<double>(2.0, 10.0, 0.0),
                                  t_inter::Point3<double>(8.0, 2.0, 0.0));

    t_inter::Triangle3 triangle_2(t_inter::Point3<double>(7.0, 4.0, 0.0),
                                  t_inter::Point3<double>(8.0, 7.0, 0.0),
                                  t_inter::Point3<double>(8.0, 4.0, 0.0));

    t_inter::status_t status = t_inter::status_t::all_good;
    EXPECT_EQ(t_inter::detail::intersects3(triangle_1, triangle_2, status),
              false);
    EXPECT_EQ(status, t_inter::status_t::all_good);
}

TEST(two_dimentional, basic_3)
{
    t_inter::Triangle3 triangle_1(t_inter::Point3<double>(2.0, 2.0, 0.0),
                                  t_inter::Point3<double>(8.0, 2.0, 0.0),
                                  t_inter::Point3<double>(2.0, 10.0, 0.0));

    t_inter::Triangle3 triangle_2(t_inter::Point3<double>(5.0, 6.0, 0.0),
                                  t_inter::Point3<double>(8.0, 4.0, 0.0),
                                  t_inter::Point3<double>(8.0, 7.0, 0.0));

    t_inter::status_t status = t_inter::status_t::all_good;
    EXPECT_EQ(t_inter::detail::intersects3(triangle_1, triangle_2, status),
              true);
    EXPECT_EQ(status, t_inter::status_t::all_good);
}

TEST(two_dimentional, basic_4)
{
    t_inter::Point3<double> A1(2.0, 2.0, 0.0);
    t_inter::Point3<double> B1(8.0, 2.0, 0.0);
    t_inter::Point3<double> C1(2.0, 10.0, 0.0);

    t_inter::Point3<double> A2(3.0, 3.0, 0.0);
    t_inter::Point3<double> B2(5.0, 3.0, 0.0);
    t_inter::Point3<double> C2(5.0, 5.0, 0.0);

    t_inter::Triangle3 triangle_1(A1, B1, C1);
    t_inter::Triangle3 triangle_2(A2, B2, C2);

    t_inter::status_t status = t_inter::status_t::all_good;
    EXPECT_EQ(t_inter::detail::intersects3(triangle_1, triangle_2, status),
              true);
    EXPECT_EQ(status, t_inter::status_t::all_good);
}

TEST(two_dimentional, one_point_intersection)
{
    t_inter::Point3<double> A1(2.0, 0.0, 0.0);
    t_inter::Point3<double> B1(1.0, 1.0, 0.0);
    t_inter::Point3<double> C1(4.0, 1.0, 0.0);

    t_inter::Point3<double> A2(3.0, 1.0, 0.0);
    t_inter::Point3<double> B2(4.0, 4.0, 0.0);
    t_inter::Point3<double> C2(2.0, 4.0, 0.0);

    t_inter::Triangle3 triangle_1(A1, B1, C1);

    t_inter::Triangle3 triangle_2(A2, B2, C2);

    t_inter::status_t status = t_inter::status_t::all_good;
    EXPECT_EQ(t_inter::detail::intersects3(triangle_1, triangle_2, status),
              true);
    EXPECT_EQ(status, t_inter::status_t::all_good);
}

TEST(two_dimentional, degen_triangle_1)
{
    t_inter::Point3<double> A1(2.0, 0.0, 0.0);
    t_inter::Point3<double> B1(1.0, 1.0, 0.0);
    t_inter::Point3<double> C1(4.0, 1.0, 0.0);

    t_inter::Point3<double> A2(2.0, -2.0, 0.0);
    t_inter::Point3<double> B2(4.0, 4.0, 0.0);
    t_inter::Point3<double> C2(5.0, 7.0, 0.0);

    t_inter::Triangle3 triangle_1(A1, B1, C1);

    t_inter::Triangle3 triangle_2(A2, B2, C2);

    t_inter::status_t status = t_inter::status_t::all_good;
    EXPECT_EQ(t_inter::detail::intersects3(triangle_1, triangle_2, status),
              true);
    EXPECT_EQ(status, t_inter::status_t::all_good);
}

TEST(two_dimentional, degen_triangle_2)
{
    t_inter::Point3<double> A1(2.0, 0.0, 0.0);
    t_inter::Point3<double> B1(1.0, 1.0, 0.0);
    t_inter::Point3<double> C1(4.0, 1.0, 0.0);

    t_inter::Point3<double> A2(-1.0, -2.0, 0.0);
    t_inter::Point3<double> B2(-3.0, -4.0, 0.0);
    t_inter::Point3<double> C2(-4.0, -5.0, 0.0);

    t_inter::Triangle3 triangle_1(A1, B1, C1);

    t_inter::Triangle3 triangle_2(A2, B2, C2);

    t_inter::status_t status = t_inter::status_t::all_good;
    EXPECT_EQ(t_inter::detail::intersects3(triangle_1, triangle_2, status),
              false);
    EXPECT_EQ(status, t_inter::status_t::all_good);
}

TEST(two_dimentional, degen_triangle_one_point_intersection)
{
    t_inter::Point3<double> A1(2.0, 0.0, 0.0);
    t_inter::Point3<double> B1(1.0, 1.0, 0.0);
    t_inter::Point3<double> C1(4.0, 1.0, 0.0);

    t_inter::Point3<double> A2(3.0, 1.0, 0.0);
    t_inter::Point3<double> B2(4.0, 4.0, 0.0);
    t_inter::Point3<double> C2(5.0, 7.0, 0.0);

    t_inter::Triangle3 triangle_1(A1, B1, C1);

    t_inter::Triangle3 triangle_2(A2, B2, C2);

    t_inter::status_t status = t_inter::status_t::all_good;
    EXPECT_EQ(t_inter::detail::intersects3(triangle_1, triangle_2, status),
              true);
    EXPECT_EQ(status, t_inter::status_t::all_good);
}

TEST(two_dimentional, contained_superdegen)
{
    t_inter::Point3<double> A1(2.0, 0.0, 0.0);
    t_inter::Point3<double> B1(1.0, 1.0, 0.0);
    t_inter::Point3<double> C1(4.0, 1.0, 0.0);

    t_inter::Point3<double> A2(2.0, 0.5, 0.0);
    t_inter::Point3<double> B2(2.0, 0.5, 0.0);
    t_inter::Point3<double> C2(2.0, 0.5, 0.0);

    t_inter::Triangle3 triangle_1(A1, B1, C1);

    t_inter::Triangle3 triangle_2(A2, B2, C2);

    t_inter::status_t status = t_inter::status_t::all_good;
    EXPECT_EQ(t_inter::detail::intersects3(triangle_1, triangle_2, status),
              true);
    EXPECT_EQ(status, t_inter::status_t::all_good);
}

TEST(two_dimentional, superdegen_on_vert)
{
    t_inter::Point3<double> A1(2.0, 0.0, 0.0);
    t_inter::Point3<double> B1(1.0, 1.0, 0.0);
    t_inter::Point3<double> C1(4.0, 1.0, 0.0);

    t_inter::Point3<double> A2(2.0, 0.0, 0.0);
    t_inter::Point3<double> B2(2.0, 0.0, 0.0);
    t_inter::Point3<double> C2(2.0, 0.0, 0.0);

    t_inter::Triangle3 triangle_1(A1, B1, C1);

    t_inter::Triangle3 triangle_2(A2, B2, C2);

    t_inter::status_t status = t_inter::status_t::all_good;
    EXPECT_EQ(t_inter::detail::intersects3(triangle_1, triangle_2, status),
              true);
    EXPECT_EQ(status, t_inter::status_t::all_good);
}

TEST(two_dimentional, superdegen_on_side)
{
    t_inter::Point3<double> A1(2.0, 0.0, 0.0);
    t_inter::Point3<double> B1(1.0, 1.0, 0.0);
    t_inter::Point3<double> C1(4.0, 1.0, 0.0);

    t_inter::Point3<double> A2(2.0, 1.0, 0.0);
    t_inter::Point3<double> B2(2.0, 1.0, 0.0);
    t_inter::Point3<double> C2(2.0, 1.0, 0.0);

    t_inter::Triangle3 triangle_1(A1, B1, C1);

    t_inter::Triangle3 triangle_2(A2, B2, C2);

    t_inter::status_t status = t_inter::status_t::all_good;
    EXPECT_EQ(t_inter::detail::intersects3(triangle_1, triangle_2, status),
              true);
    EXPECT_EQ(status, t_inter::status_t::all_good);
}

TEST(two_dimentional, not_contained_superdegen)
{
    t_inter::Point3<double> A1(2.0, 0.0, 0.0);
    t_inter::Point3<double> B1(1.0, 1.0, 0.0);
    t_inter::Point3<double> C1(4.0, 1.0, 0.0);

    t_inter::Point3<double> A2(5.0, 5.0, 0.0);
    t_inter::Point3<double> B2(5.0, 5.0, 0.0);
    t_inter::Point3<double> C2(5.0, 5.0, 0.0);

    t_inter::Triangle3 triangle_1(A1, B1, C1);

    t_inter::Triangle3 triangle_2(A2, B2, C2);

    t_inter::status_t status = t_inter::status_t::all_good;
    EXPECT_EQ(t_inter::detail::intersects3(triangle_1, triangle_2, status),
              false);
    EXPECT_EQ(status, t_inter::status_t::all_good);
}

TEST(three_dimentional, basic_1)
{
    t_inter::Point3<double> A1(1.0, 4.0, 1.0);
    t_inter::Point3<double> B1(-4.0, 2.0, 3.0);
    t_inter::Point3<double> C1(1.0, 1.0, 1.0);

    t_inter::Point3<double> A2(1.0, 4.0, 3.0);
    t_inter::Point3<double> B2(-4.0, 2.0, 1.0);
    t_inter::Point3<double> C2(1.0, 1.0, 3.0);

    t_inter::Triangle3 triangle_1(A1, B1, C1);

    t_inter::Triangle3 triangle_2(A2, B2, C2);

    t_inter::status_t status = t_inter::status_t::all_good;
    EXPECT_EQ(t_inter::detail::intersects3(triangle_1, triangle_2, status),
              true);
    EXPECT_EQ(status, t_inter::status_t::all_good);
}

TEST(three_dimentional, basic_2)
{
    t_inter::Point3<double> A1(1.0, -4.0, 1.0);
    t_inter::Point3<double> B1(-4.0, -2.0, 3.0);
    t_inter::Point3<double> C1(0.5, -1.0, 1.0);

    t_inter::Point3<double> A2(1.0, -4.0, 3.0);
    t_inter::Point3<double> B2(-4.0, -2.0, 1.0);
    t_inter::Point3<double> C2(1.0, -1.0, 3.0);

    t_inter::Triangle3 triangle_1(A1, B1, C1);

    t_inter::Triangle3 triangle_2(A2, B2, C2);

    t_inter::status_t status = t_inter::status_t::all_good;
    EXPECT_EQ(t_inter::detail::intersects3(triangle_1, triangle_2, status),
              true);
    EXPECT_EQ(status, t_inter::status_t::all_good);
}

TEST(three_dimentional, basic_3)
{
    t_inter::Point3<double> A1(1.0, 4.0, 1.0);
    t_inter::Point3<double> B1(-4.0, 2.0, 3.0);
    t_inter::Point3<double> C1(1.0, 1.0, 1.0);

    t_inter::Point3<double> A2(1.0, 2.5, 3.0);
    t_inter::Point3<double> B2(-4.0, 0.0, 1.0);
    t_inter::Point3<double> C2(-4.0, 4.0, 1.0);

    t_inter::Triangle3 triangle_1(C1, B1, A1);

    t_inter::Triangle3 triangle_2(A2, C2, B2);

    t_inter::status_t status = t_inter::status_t::all_good;
    EXPECT_EQ(t_inter::detail::intersects3(triangle_1, triangle_2, status),
              true);
    EXPECT_EQ(status, t_inter::status_t::all_good);
}

TEST(three_dimentional, basic_4)
{
    t_inter::Point3<double> A1(1.0, 4.0, 3.0);
    t_inter::Point3<double> B1(2.0, 2.0, 2.0);
    t_inter::Point3<double> C1(-3.0, 2.0, 1.5);

    t_inter::Point3<double> A2(-1.0, -4.0, -2.5);
    t_inter::Point3<double> B2(2.0, -2.0, 4.0);
    t_inter::Point3<double> C2(-2.5, -2.5, 3.5);

    t_inter::Triangle3 triangle_1(A1, B1, C1);

    t_inter::Triangle3 triangle_2(A2, B2, C2);

    t_inter::status_t status = t_inter::status_t::all_good;
    EXPECT_EQ(t_inter::detail::intersects3(triangle_1, triangle_2, status),
              false);
    EXPECT_EQ(status, t_inter::status_t::all_good);
}

TEST(three_dimentional, basic_5)
{
    t_inter::Point3<double> A1(1.0, 4.0, 3.0);
    t_inter::Point3<double> B1(2.0, 2.0, 2.0);
    t_inter::Point3<double> C1(-3.0, 2.0, 1.5);

    t_inter::Point3<double> A2(5.0, 4.0, -2.5);
    t_inter::Point3<double> B2(8.0, 2.0, 4.0);
    t_inter::Point3<double> C2(3.5, 2.5, 3.5);

    t_inter::Triangle3 triangle_1(A1, B1, C1);

    t_inter::Triangle3 triangle_2(A2, B2, C2);

    t_inter::status_t status = t_inter::status_t::all_good;
    EXPECT_EQ(t_inter::detail::intersects3(triangle_1, triangle_2, status),
              false);
    EXPECT_EQ(status, t_inter::status_t::all_good);
}

TEST(three_dimentional, one_point_intersection)
{
    t_inter::Point3<double> A1(2.0, 0.0, 0.0);
    t_inter::Point3<double> B1(1.0, 1.0, 0.0);
    t_inter::Point3<double> C1(4.0, 1.0, 0.0);

    t_inter::Point3<double> A2(3.0, 1.0, 0.0);
    t_inter::Point3<double> B2(4.0, 4.0, 4.0);
    t_inter::Point3<double> C2(2.0, 4.0, 4.0);

    t_inter::Triangle3 triangle_1(A1, B1, C1);

    t_inter::Triangle3 triangle_2(A2, B2, C2);

    t_inter::status_t status = t_inter::status_t::all_good;
    EXPECT_EQ(t_inter::detail::intersects3(triangle_1, triangle_2, status),
              true);
    EXPECT_EQ(status, t_inter::status_t::all_good);
}

TEST(three_dimentional, degen_triangle_1)
{
    t_inter::Point3<double> A1(2.0, 0.0, 1.0);
    t_inter::Point3<double> B1(3.0, 4.0, 3.0);
    t_inter::Point3<double> C1(7.0, 1.0, 2.0);

    t_inter::Point3<double> A2(-1.0, -2.0, 0.0);
    t_inter::Point3<double> B2(-3.0, -4.0, 0.0);
    t_inter::Point3<double> C2(-4.0, -5.0, 0.0);

    t_inter::Triangle3 triangle_1(A1, B1, C1);

    t_inter::Triangle3 triangle_2(A2, B2, C2);

    t_inter::status_t status = t_inter::status_t::all_good;
    EXPECT_EQ(t_inter::detail::intersects3(triangle_1, triangle_2, status),
              false);
    EXPECT_EQ(status, t_inter::status_t::all_good);
}

TEST(three_dimentional, degen_triangle_2)
{
    t_inter::Point3<double> A1(2.0, 0.0, 1.0);
    t_inter::Point3<double> B1(3.0, 8.0, 3.0);
    t_inter::Point3<double> C1(7.0, 6.0, 2.0);

    t_inter::Point3<double> A2(4.0, 2.0, 0.0);
    t_inter::Point3<double> B2(4.0, 4.0, 2.0);
    t_inter::Point3<double> C2(4.0, 6.0, 4.0);

    t_inter::Triangle3 triangle_1(A1, B1, C1);

    t_inter::Triangle3 triangle_2(A2, B2, C2);

    t_inter::status_t status = t_inter::status_t::all_good;
    EXPECT_EQ(t_inter::detail::intersects3(triangle_1, triangle_2, status),
              true);
    EXPECT_EQ(status, t_inter::status_t::all_good);
}

TEST(three_dimentional, degen_triangle_one_point_intersection)
{
    t_inter::Point3<double> A1(2.0, 0.0, 1.0);
    t_inter::Point3<double> B1(3.0, 8.0, 3.0);
    t_inter::Point3<double> C1(7.0, 6.0, 2.0);

    t_inter::Point3<double> A2(2.0, 0.0, 0.0);
    t_inter::Point3<double> B2(2.0, 0.0, 2.0);
    t_inter::Point3<double> C2(2.0, 0.0, 4.0);

    t_inter::Triangle3 triangle_1(A1, B1, C1);

    t_inter::Triangle3 triangle_2(A2, B2, C2);

    t_inter::status_t status = t_inter::status_t::all_good;
    EXPECT_EQ(t_inter::detail::intersects3(triangle_1, triangle_2, status),
              true);
    EXPECT_EQ(status, t_inter::status_t::all_good);
}

TEST(three_dimentional, basic_6)
{
    t_inter::Point3<double> A1(-2.4, -0.9, 10.7);
    t_inter::Point3<double> B1(1.1, 0.9, 18.4);
    t_inter::Point3<double> C1(-11.4, -9.0, 18.1);

    t_inter::Point3<double> A2(-10.0, 0.6, 17.6);
    t_inter::Point3<double> B2(-1.3, -5.8, 13.9);
    t_inter::Point3<double> C2(-16.5, -9.4, 19.7);

    t_inter::Triangle3 triangle_1(A1, B1, C1);

    t_inter::Triangle3 triangle_2(A2, B2, C2);

    t_inter::status_t status = t_inter::status_t::all_good;
    EXPECT_EQ(t_inter::detail::intersects3(triangle_1, triangle_2, status),
              true);
    EXPECT_EQ(status, t_inter::status_t::all_good);
}

TEST(three_dimentional, basic_7)
{
    t_inter::Point3<double> A1(-2.4, -0.9, 10.7);
    t_inter::Point3<double> B1(1.1, 0.9, 18.4);
    t_inter::Point3<double> C1(-11.4, -9.0, 18.1);

    t_inter::Point3<double> A2(-10.0, 0.6, 17.6);
    t_inter::Point3<double> B2(-1.3, -5.8, 13.9);
    t_inter::Point3<double> C2(-16.5, -9.4, 19.7);

    t_inter::Triangle3 triangle_1(A2, B2, C2);

    t_inter::Triangle3 triangle_2(A1, B1, C1);

    t_inter::status_t status = t_inter::status_t::all_good;
    EXPECT_EQ(t_inter::detail::intersects3(triangle_1, triangle_2, status),
              true);
    EXPECT_EQ(status, t_inter::status_t::all_good);
}

TEST(three_dimentional, degen_and_superdegen)
{
    t_inter::Point3<double> A1(9.0, 9.0, 9.0);
    t_inter::Point3<double> B1(9.0, 9.0, 9.0);
    t_inter::Point3<double> C1(9.0, 9.0, 9.0);

    t_inter::Point3<double> A2(8.0, 8.0, 8.0);
    t_inter::Point3<double> B2(8.0, 8.0, 8.0);
    t_inter::Point3<double> C2(-10.0, 8.0, 8.0);

    t_inter::Triangle3 triangle_1(A2, B2, C2);

    t_inter::Triangle3 triangle_2(A1, B1, C1);

    t_inter::status_t status = t_inter::status_t::all_good;
    EXPECT_EQ(t_inter::detail::intersects3(triangle_1, triangle_2, status),
              false);
    EXPECT_EQ(status, t_inter::status_t::all_good);
}

TEST(common, basic_1) { test_utils::run_test<double>("/common/basic_1"); }

TEST(common, basic_2) { test_utils::run_test<double>("/common/basic_2"); }

TEST(common, basic_1_float) { test_utils::run_test<float>("/common/basic_1"); }

TEST(common, basic_2_float) { test_utils::run_test<float>("/common/basic_2"); }

#ifdef BD_TESTS

TEST(bd_tests, amount_100)
{
    test_utils::run_test<double>("/bd_tests/amount-100");
}

TEST(bd_tests, amount_100000)
{
    test_utils::run_test<double>("/bd_tests/amount-100000");
}

#endif
