#ifndef PLANE_H
#define PLANE_H

#include "vec.h"

template <typename FltPnt> class Plane3
{
  private:
    Vec3<FltPnt> normal_;
    FltPnt origin_ = 0.0;

  public:
    Plane3(const Vec3<FltPnt> &normal, FltPnt origin)
        : normal_(normal)
        , origin_(origin)
    {}

    Plane3(const Point3<FltPnt> &pnt_1, const Point3<FltPnt> &pnt_2,
           const Point3<FltPnt> &pnt_3)
        : normal_(cross(pnt_2 - pnt_1, pnt_3 - pnt_1))
        , origin_(-dot(normal_, pnt_1))
    {}

    const Vec3<FltPnt> &normal() const { return normal_; }
    FltPnt origin() const { return origin_; }
};

#endif // PLANE_H
