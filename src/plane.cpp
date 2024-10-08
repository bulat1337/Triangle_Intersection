#include "plane.h"

#include "triangle.h"

Plane3::Plane3(const Triangle3& triangle):
	normal_(cross(triangle.pnt_2() - triangle.pnt_1(), triangle.pnt_3() - triangle.pnt_1()))
	, origin_(-dot(normal_, triangle.pnt_1())) {}

Plane3::Plane3(const Point3& pnt_1, const Point3& pnt_2, const Point3& pnt_3):
	normal_(cross(pnt_2 - pnt_1, pnt_3 - pnt_1))
	, origin_(-dot(normal_, pnt_1)) {}
