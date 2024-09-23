#include "plane.h"

#include "triangle.h"

Plane3::Plane3(const Triangle<Point3>& triangle):
	normal_(cross(triangle.pnt_2() - triangle.pnt_1(), triangle.pnt_3() - triangle.pnt_1()))
	, origin_(-dot(normal_, triangle.pnt_1())) {}
