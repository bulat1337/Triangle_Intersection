#ifndef PLANE_H
#define PLANE_H

#include "vec.h"

namespace t_inter
{

namespace detail
{

template <typename FltPnt> class Plane3 final
{
  private:
    Vec3<FltPnt> normal_;
    FltPnt origin_;

  public:
    Plane3(const Vec3<FltPnt> &normal, FltPnt origin = 0.0)
        : normal_(normal)
        , origin_(origin)
    {}

    Plane3(const Point3<FltPnt> &pnt_1, const Point3<FltPnt> &pnt_2,
           const Point3<FltPnt> &pnt_3)
        : normal_(cross(pnt_2 - pnt_1, pnt_3 - pnt_1))
        , origin_(static_cast<FltPnt>(-dot(normal_, pnt_1)))
    {}

    const Vec3<FltPnt> &normal() const { return normal_; }
    FltPnt origin() const { return origin_; }
};

}; // namespace detail

}; // namespace t_inter

#endif // PLANE_H
