#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <algorithm> // for sort
#include <array>     // for array
#include <cmath>     // for atan2
#include <utility>   // for swap

#include "cell.h"
#include "distances.h" // for Distances
#include "log.h"       // for MSG, LOG
#include "utils.h"     // for sign, cmp_double, Axis, get_max_axis
#include "vec.h"       // for Point3, Vec3, operator-, Vec2, dot, operator+

namespace t_inter
{

namespace detail
{

template <typename Point> class Triangle_Base
{
  protected:
    Point pnt_1_;
    Point pnt_2_;
    Point pnt_3_;

  public:
    Triangle_Base() = default;

    Triangle_Base(const Point &pnt_1, const Point &pnt_2, const Point &pnt_3)
        : pnt_1_(pnt_1)
        , pnt_2_(pnt_2)
        , pnt_3_(pnt_3)
    {}

    Triangle_Base(const Triangle_Base &other)
        : pnt_1_(other.pnt_1_)
        , pnt_2_(other.pnt_2_)
        , pnt_3_(other.pnt_3_)
    {}

    const Point &pnt_1() const { return pnt_1_; }
    const Point &pnt_2() const { return pnt_2_; }
    const Point &pnt_3() const { return pnt_3_; }

    void set_pnt_1(double value) { pnt_1_ = value; }
    void set_pnt_2(double value) { pnt_2_ = value; }
    void set_pnt_3(double value) { pnt_3_ = value; }

    const Point &operator[](size_t pnt_id) const
    {
        switch (pnt_id)
        {
            case 0:
                return pnt_1_;
            case 1:
                return pnt_2_;
            case 2:
                return pnt_3_;
            default:
                throw std::logic_error("Invalid point index");
        }
    }

    Triangle_Base &operator=(const Triangle_Base &other)
    {
        pnt_1_ = other.pnt_1();
        pnt_2_ = other.pnt_2();
        pnt_3_ = other.pnt_3();

        return *this;
    }
};

template <typename Point>
std::istream &operator>>(std::istream &is, Triangle_Base<Point> &triangle)
{
    Point pnt_1, pnt_2, pnt_3;

    if (is >> pnt_1 >> pnt_2 >> pnt_3)
    {
        triangle.pnt_1() = pnt_1;
        triangle.pnt_2() = pnt_2;
        triangle.pnt_3() = pnt_3;
    }

    return is;
}

template <typename FltPnt>
class Triangle3 : public Triangle_Base<Point3<FltPnt>>
{
  private:
    Cell min_cell_;
    Cell max_cell_;

  private:
    void sort_vertices(std::array<Point3<FltPnt>, 3> &points)
    {
        Vec3 normal = cross(points[1] - points[0], points[2] - points[0]);
        if (utils::cmp_double(normal.sq_length(), 0) != 0)
            normal = unit_vector(normal);

        MSG("Normal vector is null-sized\n");

        Point3<FltPnt> center = (points[0] + points[1] + points[2]) / 3.0;

        utils::Axis dominant_axis = utils::get_max_axis(normal);

        switch (dominant_axis)
        {
            case utils::Axis::z:
                // projecting on XY
                std::sort(points.begin(), points.end(),
                          [&center](const Point3<FltPnt> &p1,
                                    const Point3<FltPnt> &p2)
                          {
                              double angle1 = atan2(p1.y() - center.y(),
                                                    p1.x() - center.x());
                              double angle2 = atan2(p2.y() - center.y(),
                                                    p2.x() - center.x());
                              return angle1 < angle2;
                          });
                break;
            case utils::Axis::x:
                // projecting on YZ
                std::sort(points.begin(), points.end(),
                          [&center](const Point3<FltPnt> &p1,
                                    const Point3<FltPnt> &p2)
                          {
                              double angle1 = atan2(p1.z() - center.z(),
                                                    p1.y() - center.y());
                              double angle2 = atan2(p2.z() - center.z(),
                                                    p2.y() - center.y());
                              return angle1 < angle2;
                          });
                break;
            case utils::Axis::y:
                // projecting on XZ
                std::sort(points.begin(), points.end(),
                          [&center](const Point3<FltPnt> &p1,
                                    const Point3<FltPnt> &p2)
                          {
                              double angle1 = atan2(p1.z() - center.z(),
                                                    p1.x() - center.x());
                              double angle2 = atan2(p2.z() - center.z(),
                                                    p2.x() - center.x());
                              return angle1 < angle2;
                          });
                break;
        }

        MSG("After sorting:\n");
        for ([[maybe_unused]] const auto &point : points)
        {
            LOG("{} {} {}\n", point.x(), point.y(), point.z());
        }
    }

  public:
    Triangle3(const Point3<FltPnt> &pnt_1, const Point3<FltPnt> &pnt_2,
              const Point3<FltPnt> &pnt_3)
    {
        std::array<Point3<FltPnt>, 3> points = {pnt_1, pnt_2, pnt_3};

        sort_vertices(points);

        this->pnt_1_ = points[0];
        this->pnt_2_ = points[1];
        this->pnt_3_ = points[2];
    }

    void distance_sort(Distances<FltPnt> &dists)
    {
        if (utils::sign(dists.second) != utils::sign(dists.first) &&
            utils::sign(dists.second) != utils::sign(dists.third))
        {
            MSG("Already sorted\n");
            return;
        }

        if (utils::sign(dists.second) == utils::sign(dists.first))
        {
            std::swap(dists.first, dists.second);
            std::swap(dists.second, dists.third);

            std::swap(this->pnt_1_, this->pnt_2_);
            std::swap(this->pnt_2_, this->pnt_3_);
        }
        else
        {
            std::swap(dists.second, dists.third);
            std::swap(dists.first, dists.second);

            std::swap(this->pnt_2_, this->pnt_3_);
            std::swap(this->pnt_1_, this->pnt_2_);
        }
    }

    const Cell &min_cell() const { return min_cell_; }
    const Cell &max_cell() const { return max_cell_; }
    void set_min_cell(const Cell &value) { min_cell_ = value; }
    void set_max_cell(const Cell &value) { max_cell_ = value; }
};

template <typename FltPnt>
class Triangle2 : public Triangle_Base<Point2<FltPnt>>
{
  public:
    Triangle2(const Point2<FltPnt> &pnt_1, const Point2<FltPnt> &pnt_2,
              const Point2<FltPnt> &pnt_3)
        : Triangle_Base<Point2<FltPnt>>(pnt_1, pnt_2, pnt_3)
    {}

    bool contains(const Triangle2 &other) const
    {
        Vec2 a_to_pnt = other.pnt_1_ - this->pnt_1_;

        Vec2 a_to_b = this->pnt_2_ - this->pnt_1_;
        Vec2 a_to_c = this->pnt_3_ - this->pnt_1_;

        double ab_norm_proj = dot(a_to_pnt, a_to_b.clockwise_normal());
        LOG("ab_norm_proj = {}\n", ab_norm_proj);

        double ac_norm_proj = dot(a_to_pnt, a_to_c.clockwise_normal());
        LOG("ac_norm_proj = {}\n", ab_norm_proj);

        bool ab_proj_sign = utils::cmp_double(ab_norm_proj, 0) > 0;
        bool ac_proj_sign = utils::cmp_double(ac_norm_proj, 0) > 0;

        if (ab_proj_sign == ac_proj_sign)
        {
            MSG("ab_proj_sign == ac_proj_sign\n");
            return false;
        }

        Vec2 b_to_c = this->pnt_3_ - this->pnt_2_;
        Vec2 b_to_pnt = other.pnt_1_ - this->pnt_2_;

        double bc_norm_proj = dot(b_to_pnt, b_to_c.clockwise_normal());

        bool bc_proj_sign = utils::cmp_double(bc_norm_proj, 0) > 0;

        if (bc_proj_sign != ab_proj_sign)
        {
            MSG("bc_proj_sign != ab_proj_sign\n");
            return false;
        }

        return true;
    }
};

}; // namespace detail

}; // namespace t_inter

#endif // TRIANGLE_H
