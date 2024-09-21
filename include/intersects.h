#ifndef INTERSECTION_H
#define INTERSECTION_H

#include "vec.h"
#include "triangle.h"

bool intersects3(const Triangle<Point3>& lhs, const Triangle<Point3>& rhs);

#endif // INTERSECTION_H
