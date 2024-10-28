#ifndef INTERSECTION_H
#define INTERSECTION_H

#include "intersects.h"

#include <optional>
#include <stddef.h> // for size_t

#include "distances.h" // for Distances
#include "interval.h"  // for Interval
#include "log.h"       // for MSG, LOG
#include "plane.h"     // for Plane3
#include "segment.h"   // for Segment2
#include "status.h"
#include "triangle.h" // for Triangle3, Triangle2, Triangle_Base
#include "utils.h"    // for Axis, get_max_axis
#include "vec.h"      // for Vec3, Point2, cross

namespace t_inter
{

namespace detail
{

template <typename FltPnt>
std::optional<Triangle2<FltPnt>>
project(const Triangle3<FltPnt> &triangle, utils::Axis max_normal_axis,
        [[maybe_unused]] status_t status = status_t::all_good)
{
    switch (max_normal_axis)
    {
        case utils::Axis::x:
            MSG("Projecting on Oyz\n");

            return Triangle2<FltPnt>(
                Point2<FltPnt>(triangle.pnt_1.y, triangle.pnt_1.z),
                Point2<FltPnt>(triangle.pnt_2.y, triangle.pnt_2.z),
                Point2<FltPnt>(triangle.pnt_3.y, triangle.pnt_3.z));
        case utils::Axis::y:
            MSG("Projecting on Oxz\n");

            return Triangle2<FltPnt>(
                Point2<FltPnt>(triangle.pnt_1.x, triangle.pnt_1.z),
                Point2<FltPnt>(triangle.pnt_2.x, triangle.pnt_2.z),
                Point2<FltPnt>(triangle.pnt_3.x, triangle.pnt_3.z));
        case utils::Axis::z:
            MSG("Projecting on Oxy\n");

            return Triangle2<FltPnt>(
                Point2<FltPnt>(triangle.pnt_1.x, triangle.pnt_1.y),
                Point2<FltPnt>(triangle.pnt_2.x, triangle.pnt_2.y),
                Point2<FltPnt>(triangle.pnt_3.x, triangle.pnt_3.y));
        default:
        {
            status = status_t::invalid_axis;
            return std::nullopt;
        }
    }
}

template <typename FltPnt>
bool intersects2(const Triangle2<FltPnt> &lhs, const Triangle2<FltPnt> &rhs)
{
    for (size_t lhs_side_id = 0; lhs_side_id < 3; ++lhs_side_id)
    {
        Segment2<FltPnt> lhs_side(lhs[lhs_side_id],
                                  lhs[lhs_side_id >= 2 ? 0 : lhs_side_id + 1]);

        for (size_t rhs_side_id = 0; rhs_side_id < 3; ++rhs_side_id)
        {
            Segment2<FltPnt> rhs_side(
                rhs[rhs_side_id], rhs[rhs_side_id >= 2 ? 0 : rhs_side_id + 1]);

            LOG("Testing if side {} intersects {}\n", lhs_side_id, rhs_side_id);

            if (lhs_side.intersects(rhs_side))
            {
                MSG("Yes they do\n");
                return true;
            }
            MSG("No they are not\n");
        }
    }

    MSG("Checking if rhs is in lhs\n");
    if (lhs.contains(rhs))
        return true;
    MSG("No it's not\n");

    MSG("Checking if lhs is in rhs\n");
    if (rhs.contains(lhs))
        return true;
    MSG("No it's not\n");

    return false;
}

template <typename FltPnt>
std::optional<Interval>
compute_interval(Triangle3<FltPnt> triangle, Distances<FltPnt> &triangle_dists,
                 const utils::Axis &max_axis, status_t &status)
{
    triangle.distance_sort(triangle_dists);

    double min = 0.0;
    double max = 0.0;

    auto get_coord =
        [max_axis, &status](const Point3<FltPnt> &pnt) -> std::optional<double>
    {
        switch (max_axis)
        {
            case utils::Axis::x:
                return pnt.x;
            case utils::Axis::y:
                return pnt.y;
            case utils::Axis::z:
                return pnt.z;
            default:
            {
                status = status_t::invalid_axis;
                return std::nullopt;
            }
        }
    };

    auto coord1 = get_coord(triangle.pnt_1);
    auto coord2 = get_coord(triangle.pnt_2);
    auto coord3 = get_coord(triangle.pnt_3);

    if (!coord1 || !coord2 || !coord3)
        return std::nullopt;

    double sim_coeff =
        triangle_dists.first / (triangle_dists.first - triangle_dists.second);

    min = *coord1 + (*coord2 - *coord1) * sim_coeff;

    sim_coeff =
        triangle_dists.third / (triangle_dists.third - triangle_dists.second);

    max = *coord3 + (*coord2 - *coord3) * sim_coeff;

    return Interval(min, max);
}

template <typename FltPnt>
std::optional<bool> intersects3(const Triangle3<FltPnt> &lhs,
                                const Triangle3<FltPnt> &rhs, status_t &status)
{
    Plane3<FltPnt> rhs_plane(rhs.pnt_1, rhs.pnt_2, rhs.pnt_3);

    Distances lhs_dists(lhs.pnt_1, lhs.pnt_2, lhs.pnt_3, rhs_plane);

    if (lhs_dists.same_sign())
    {
        MSG("All points of lhs triangle are on same side\n");
        return false;
    }

    Plane3 lhs_plane(lhs.pnt_1, lhs.pnt_2, lhs.pnt_3);

    Distances rhs_dists(rhs.pnt_1, rhs.pnt_2, rhs.pnt_3, lhs_plane);

    if (rhs_dists.same_sign())
    {
        MSG("All points of rhs triangle are on same side\n");
        return false;
    }

    if (lhs_dists.are_trivial() || rhs_dists.are_trivial())
    {
        MSG("It's 2D case.\n");

        utils::Axis max_normal_axis = utils::get_max_axis(lhs_plane.normal());

        auto lhs_projection = project(lhs, max_normal_axis, status);
        auto rhs_projection = project(rhs, max_normal_axis, status);

        if (check_status(status))
            return std::nullopt;

        return intersects2(lhs_projection.value(), rhs_projection.value());
    }

    Vec3 intersection_line = cross(lhs_plane.normal(), rhs_plane.normal());

    utils::Axis max_axis = utils::get_max_axis(intersection_line);

    auto lhs_interval = compute_interval(lhs, lhs_dists, max_axis, status);
    auto rhs_interval = compute_interval(rhs, rhs_dists, max_axis, status);

    if (t_inter::check_status(status) || !lhs_interval.has_value() ||
        !rhs_interval.has_value())
        return std::nullopt;

    LOG("lhs interval: [{} , {}]\n", lhs_interval.value().min(),
        lhs_interval.value().max());
    LOG("rhs interval: [{} , {}]\n", rhs_interval.value().min(),
        rhs_interval.value().max());

    if (lhs_interval.value().max() < rhs_interval.value().min())
        return false;
    if (rhs_interval.value().max() < lhs_interval.value().min())
        return false;

    return true;
}

}; // namespace detail

}; // namespace t_inter

#endif // INTERSECTION_H
