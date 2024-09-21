#ifndef PLANE_H
#define PLANE_H

#include "vec3.h"
#include "triangle.h"

class Plane3
{
  private:
	Vec3 	normal_;
	double 	origin_;

  public:
	Plane3(const Vec3& normal, const Vec3& origin):
		normal_(normal), origin_(origin) {}

	Plane3(const Point3& pnt_1, const Point3& pnt_2, const Point3& pnt_3):
		normal_(cross(pnt_2 - pnt_1, pnt_3 - pnt_1))
		, origin_(-dot(normal_, pnt_1)) {}

	Plane3(const Triangle& triangle):
		normal_(cross(triangle.pnt_2 - triangle.pnt_1, triangle.pnt_3 - triangle.pnt_1))
		, origin_(-dot(normal_, triangle.pnt_1)) {}

	const Vec3& normal() const
	{
		return normal_;
	}

	double origin() const
	{
		return origin_;
	}

}

#endif // PLANE_H
