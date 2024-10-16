#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <stddef.h>   // for size_t
#include <array>      // for array
#include <iostream>   // for istream
#include <stdexcept>  // for logic_error

#include "vec.h"      // for Point3, Point2, operator>>
#include "cell.h"

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

  	void set_pnt_1(double value) { pnt_1_ = value; }
	void set_pnt_2(double value) { pnt_2_ = value; }
	void set_pnt_3(double value) { pnt_3_ = value; }

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
	Cell min_cell_;
	Cell max_cell_;

	static void sort_vertices(std::array<Point3, 3>& points);

  public:
	Triangle3(	  const Point3& pnt_1
				, const Point3& pnt_2
				, const Point3& pnt_3);

	void distance_sort(Distances& dists);

	const Cell& min_cell() const { return min_cell_; }
	const Cell& max_cell() const { return max_cell_; }
	void set_min_cell(const Cell& value) { min_cell_ = value; }
	void set_max_cell(const Cell& value) { max_cell_ = value; }
};

class Triangle2 : public Triangle_Base<Point2>
{
  public:
	Triangle2(const Point2& pnt_1, const Point2& pnt_2, const Point2& pnt_3);

	bool contains(const Triangle2& other) const;
};

#endif // TRIANGLE_H
