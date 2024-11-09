#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <algorithm> // for sort
#include <array>     // for array
#include <cmath>     // for atan2
#include <utility>   // for swap

#include "cell.h"
#include "distances.h" // for Distances
#include "log.h"       // for MSG, LOG
#include "status.h"
#include "utils.h" // for sign, cmp_double, Axis, get_max_axis
#include "vec.h"   // for Point3, Vec3, operator-, Vec2, dot, operator+

namespace t_inter
{

namespace detail
{

template <typename FltPnt>
status_t sort_on_plane(	detail::utils::Axis dominant_axis,
								std::array<Point3<FltPnt>, 3> &points,
								const Point3<FltPnt>& center)
{
	switch (dominant_axis)
	{
		case detail::utils::Axis::z:
			// projecting on XY
			std::sort(points.begin(), points.end(),
						[&center](const Point3<FltPnt> &p1,
								const Point3<FltPnt> &p2)
						{
							double angle1 =
								atan2(p1.y - center.y, p1.x - center.x);
							double angle2 =
								atan2(p2.y - center.y, p2.x - center.x);
							return angle1 < angle2;
						});
			break;
		case detail::utils::Axis::x:
			// projecting on YZ
			std::sort(points.begin(), points.end(),
						[&center](const Point3<FltPnt> &p1,
								const Point3<FltPnt> &p2)
						{
							double angle1 =
								atan2(p1.z - center.z, p1.y - center.y);
							double angle2 =
								atan2(p2.z - center.z, p2.y - center.y);
							return angle1 < angle2;
						});
			break;
		case detail::utils::Axis::y:
			// projecting on XZ
			std::sort(points.begin(), points.end(),
						[&center](const Point3<FltPnt> &p1,
								const Point3<FltPnt> &p2)
						{
							double angle1 =
								atan2(p1.z - center.z, p1.x - center.x);
							double angle2 =
								atan2(p2.z - center.z, p2.x - center.x);
							return angle1 < angle2;
						});
			break;
		default:
		{
			return status_t::invalid_axis;
		}
	}

	return status_t::all_good;
}

};

template <typename Point> class Triangle_Base
{
  public:
    Point pnt_1;
    Point pnt_2;
    Point pnt_3;

  public:
    Triangle_Base() = default;

    Triangle_Base(const Point &_pnt_1, const Point &_pnt_2, const Point &_pnt_3)
        : pnt_1(_pnt_1)
        , pnt_2(_pnt_2)
        , pnt_3(_pnt_3)
    {}

    Triangle_Base(const Triangle_Base &other)
        : pnt_1(other.pnt_1)
        , pnt_2(other.pnt_2)
        , pnt_3(other.pnt_3)
    {}

    const Point &operator[](size_t pnt_id) const
    {
        switch (pnt_id)
        {
            case 0:
                return pnt_1;
            case 1:
                return pnt_2;
            case 2:
                return pnt_3;
            default:
                throw std::logic_error("Invalid point index");
        }
    }

    Triangle_Base &operator=(const Triangle_Base &other)
    {
        pnt_1 = other.pnt_1;
        pnt_2 = other.pnt_2;
        pnt_3 = other.pnt_3;

        return *this;
    }
};

template <typename Point>
std::istream &operator>>(std::istream &is, Triangle_Base<Point> &triangle)
{
    is >> triangle.pnt_1 >> triangle.pnt_2 >> triangle.pnt_3;

    return is;
}

template <typename FltPnt>
class Triangle3 final : private Triangle_Base<Point3<FltPnt>>
{
  public:
    using Triangle_Base<Point3<FltPnt>>::pnt_1;
    using Triangle_Base<Point3<FltPnt>>::pnt_2;
    using Triangle_Base<Point3<FltPnt>>::pnt_3;

  private:
    detail::Cell min_cell_;
    detail::Cell max_cell_;

  private:
    status_t sort_vertices(std::array<Point3<FltPnt>, 3> &points)
    {
        Vec3 normal = cross(points[1] - points[0], points[2] - points[0]);

        if (detail::utils::cmp_double(normal.sq_length(), 0) != 0)
            normal = unit_vector(normal);
		else
			MSG("Normal vector is null-sized\n");

        Point3<FltPnt> center =
            (points[0] + points[1] + points[2]) / static_cast<FltPnt>(3.0);

		detail::utils::Axis dominant_axis = detail::utils::get_max_axis(normal);

		status_t status = detail::sort_on_plane(dominant_axis, points, center);
		if (check_status(status)) return status;

        MSG("After sorting:\n");
        for ([[maybe_unused]] const auto &point : points)
        {
            LOG("{} {} {}\n", point.x, point.y, point.z);
        }

        return status_t::all_good;
    }

  public:
    Triangle3(const Point3<FltPnt> &_pnt_1, const Point3<FltPnt> &_pnt_2,
              const Point3<FltPnt> &_pnt_3)
    {
        std::array<Point3<FltPnt>, 3> points = {_pnt_1, _pnt_2, _pnt_3};

        sort_vertices(points);

        pnt_1 = points[0];
        pnt_2 = points[1];
        pnt_3 = points[2];
    }

    void distance_sort(detail::Distances<FltPnt> &dists)
    {
        if (detail::utils::sign(dists.second) !=
                detail::utils::sign(dists.first) &&
            detail::utils::sign(dists.second) !=
                detail::utils::sign(dists.third))
        {
            MSG("Already sorted\n");
            return;
        }

        if (detail::utils::sign(dists.second) ==
            detail::utils::sign(dists.first))
        {
            std::swap(dists.first, dists.second);
            std::swap(dists.second, dists.third);

            std::swap(pnt_1, pnt_2);
            std::swap(pnt_2, pnt_3);
        }
        else
        {
            std::swap(dists.second, dists.third);
            std::swap(dists.first, dists.second);

            std::swap(pnt_2, pnt_3);
            std::swap(pnt_1, pnt_2);
        }
    }

    const detail::Cell &min_cell() const { return min_cell_; }
    const detail::Cell &max_cell() const { return max_cell_; }
    void set_min_cell(const detail::Cell &value) { min_cell_ = value; }
    void set_max_cell(const detail::Cell &value) { max_cell_ = value; }
};

template <typename FltPnt>
class Triangle2 final : private Triangle_Base<Point2<FltPnt>>
{
  public:
    using Triangle_Base<Point2<FltPnt>>::pnt_1;
    using Triangle_Base<Point2<FltPnt>>::pnt_2;
    using Triangle_Base<Point2<FltPnt>>::pnt_3;
	using Triangle_Base<Point2<FltPnt>>::operator[];

  public:
    Triangle2(const Point2<FltPnt> &_pnt_1, const Point2<FltPnt> &_pnt_2,
              const Point2<FltPnt> &_pnt_3)
        : Triangle_Base<Point2<FltPnt>>(_pnt_1, _pnt_2, _pnt_3)
    {}

    bool contains(const Triangle2 &other) const
    {
        Vec2 a_to_pnt = other.pnt_1 - pnt_1;

        Vec2 a_to_b = pnt_2 - pnt_1;
        Vec2 a_to_c = pnt_3 - pnt_1;

        double ab_norm_proj = dot(a_to_pnt, a_to_b.clockwise_normal());
        LOG("ab_norm_proj = {}\n", ab_norm_proj);

        double ac_norm_proj = dot(a_to_pnt, a_to_c.clockwise_normal());
        LOG("ac_norm_proj = {}\n", ab_norm_proj);

        bool ab_proj_sign = detail::utils::cmp_double(ab_norm_proj, 0) > 0;
        bool ac_proj_sign = detail::utils::cmp_double(ac_norm_proj, 0) > 0;

        if (ab_proj_sign == ac_proj_sign)
        {
            MSG("ab_proj_sign == ac_proj_sign\n");
            return false;
        }

        Vec2 b_to_c = pnt_3 - pnt_2;
        Vec2 b_to_pnt = other.pnt_1 - pnt_2;

        double bc_norm_proj = dot(b_to_pnt, b_to_c.clockwise_normal());

        bool bc_proj_sign = detail::utils::cmp_double(bc_norm_proj, 0) > 0;

        if (bc_proj_sign != ab_proj_sign)
        {
            MSG("bc_proj_sign != ab_proj_sign\n");
            return false;
        }

        return true;
    }
};

}; // namespace t_inter

#endif // TRIANGLE_H
