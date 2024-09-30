#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <iostream>

#include "vec.h"

class Distances;

template <typename Point>
class Triangle_Base
{
  protected:
	Point pnt_1_;
	Point pnt_2_;
	Point pnt_3_;


  public:
  	Triangle_Base() = default;

  	Triangle_Base(const Point2& pnt_1, const Point2& pnt_2, const Point2& pnt_3):
		pnt_1_(pnt_1), pnt_2_(pnt_2), pnt_3_(pnt_3) {}

  	const Point& pnt_1() const { return pnt_1_; }
	const Point& pnt_2() const { return pnt_2_; }
	const Point& pnt_3() const { return pnt_3_; }

	const Point& operator [] (size_t pnt_id) const
	{
		switch (pnt_id)
		{
			case 0: return pnt_1_;
			case 1: return pnt_2_;
			case 2: return pnt_3_;
			default: throw std::logic_error("Invalid point index");
		}
	}

	Triangle_Base& operator = (const Triangle_Base& other)
	{
		pnt_1_ = other.pnt_1();
		pnt_2_ = other.pnt_2();
		pnt_3_ = other.pnt_3();

		return *this;
	}
};

class Triangle3 : public Triangle_Base<Point3>
{
  private:
	static void sort_vertices(std::array<Point3, 3>& points);
  public:
	// разбить на функции
	Triangle3(	const Point3& pnt_1
				, const Point3& pnt_2
				, const Point3& pnt_3);

	void distance_sort(Distances& dists);
};

class Triangle2 : public Triangle_Base<Point2>
{
  public:
	Triangle2(const Point2& pnt_1, const Point2& pnt_2, const Point2& pnt_3);

	bool contains(const Triangle2& other) const;
};

#endif // TRIANGLE_H
