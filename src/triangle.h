#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "vec3.h"

class Triangle
{
  private:
	Point3 pnt_1_;
	Point3 pnt_2_;
	Point3 pnt_3_;

  public:
	Triangle(const Point3& pnt_1, const Point3& pnt_2, const Point3& pnt_3):
		pnt_1_(pnt_1), pnt_2_(pnt_2), pnt_3_(pnt_3) {}

	const Point3& pnt_1() const
	{
		return pnt_1_;
	}

	const Point3& pnt_2() const
	{
		return pnt_2_;
	}

	const Point3& pnt_3() const
	{
		return pnt_3_;
	}
};

#endif // TRIANGLE_H
