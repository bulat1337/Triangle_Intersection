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

  	Triangle_Base(const Point& pnt_1, const Point& pnt_2, const Point& pnt_3):
		pnt_1_(pnt_1), pnt_2_(pnt_2), pnt_3_(pnt_3) {}


	Triangle_Base(const Triangle_Base& other):
		pnt_1_(other.pnt_1_), pnt_2_(other.pnt_2_), pnt_3_(other.pnt_3_) {}


  	const Point& pnt_1() const { return pnt_1_; }
	const Point& pnt_2() const { return pnt_2_; }
	const Point& pnt_3() const { return pnt_3_; }

  	Point& pnt_1() { return pnt_1_; }
	Point& pnt_2() { return pnt_2_; }
	Point& pnt_3() { return pnt_3_; }

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

template <typename Point>
std::istream& operator >> (std::istream& is, Triangle_Base<Point>& triangle)
{
    Point pnt_1, pnt_2, pnt_3;

    if (is >> pnt_1 >> pnt_2 >> pnt_3)
    {
        triangle.pnt_1() = pnt_1;
        triangle.pnt_2() = pnt_2;
        triangle.pnt_3() = pnt_3;
    }

    return is;
}


class Triangle3 : public Triangle_Base<Point3>
{
  private:
	Point3 min_cell_;
	Point3 max_cell_;

	static void sort_vertices(std::array<Point3, 3>& points);

  public:
	// разбить на функции
	Triangle3(	const Point3& pnt_1
				, const Point3& pnt_2
				, const Point3& pnt_3);

	void distance_sort(Distances& dists);

	Point3&       min_cell();
	const Point3& min_cell() const;
	Point3&       max_cell();
	const Point3& max_cell() const;
};

class Triangle2 : public Triangle_Base<Point2>
{
  public:
	Triangle2(const Point2& pnt_1, const Point2& pnt_2, const Point2& pnt_3);

	bool contains(const Triangle2& other) const;
};

#endif // TRIANGLE_H
