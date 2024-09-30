#ifndef SEGMENT_H
#define SEGMENT_H

#include "vec.h"
#include "utils.h"

class Segment2
{
  private:
	Point2 pnt_1_;
	Point2 pnt_2_;

	bool is_point(const Vec2& direc) const
	{
		return utils::cmp_double(direc.x(), 0) == 0 && utils::cmp_double(direc.y(), 0) == 0;
	}

	bool point_on_segment(const Point2& pnt, const Segment2& sgm) const
	{
		Vec2 ab = sgm.pnt_2() - sgm.pnt_1();
		Vec2 ap = pnt - sgm.pnt_1();
		
		double proj_on_norm = dot(ab, ap.clockwise_normal());

		if (utils::cmp_double(std::abs(proj_on_norm), 0) > 0)
		{
			return false;
		}

		double dot_product = dot(ap, ab);
		double squared_length_ab = dot(ab, ab);

		return dot_product >= 0 && dot_product <= squared_length_ab;
	}


  public:
	Segment2(const Point2& pnt_1, const Point2& pnt_2):
		pnt_1_(pnt_1), pnt_2_(pnt_2) {}

	const Point2& pnt_1() const
	{
		return pnt_1_;
	}

	const Point2& pnt_2() const
	{
		return pnt_2_;
	}

	bool intersects(const Segment2& other) const
	{
		Vec2 direc_1 = pnt_2_ - pnt_1_;
		Point2 origin_1 = pnt_1_;

		Vec2 direc_2 = other.pnt_2() - other.pnt_1();
		Point2 origin_2 = other.pnt_1();

		// q - p
		Vec2 orig_to_orig = origin_2 - origin_1;

		// r × s
		double dir_1_proj = dot(direc_1, direc_2.clockwise_normal());

		double oo_proj_1 = dot(orig_to_orig, direc_1.clockwise_normal());
		double oo_proj_2 = dot(orig_to_orig, direc_2.clockwise_normal());

		if (is_point(direc_1))
		{
			return point_on_segment(pnt_1_, other);
		}

		if (is_point(direc_2))
		{
			return point_on_segment(other.pnt_1(), *this);
		}


		// r × s = 0
		if (utils::cmp_double(dir_1_proj, 0) == 0)
		{
			std::clog << "(q - p) x r = 0\n";
			if (utils::cmp_double(oo_proj_1, 0) == 0)
			{
				// t0 = (q − p) · r / (r · r)
				double t_0 = dot(orig_to_orig, direc_1) / dot(direc_1, direc_1);

				// t1 = (q + s − p) · r / (r · r) = t0 + s · r / (r · r)
				double t_1 = t_0 + dot(direc_2, direc_1) / dot(direc_1, direc_1);

				if (std::max(t_0, t_1) <= 0 || std::min(t_0, t_1) >= 1) return false;
				else return true;
			}
			// (q − p) × r != 0
			else return false;
		}

		// t = (q − p) × s / (r × s)
		double t = oo_proj_2 / dir_1_proj;

		// u = (q − p) × r / (r × s)
		double u = oo_proj_1 / dir_1_proj;


		std::clog << "t: " << t << '\n';
		std::clog << "u: " << u << '\n';

		// r × s ≠ 0 and 0 ≤ t ≤ 1 and 0 ≤ u ≤ 1
		if(0 <= t && t <= 1 && 0 <= u && u <= 1) return true;

		return false;
	}

};

#endif // SEGMENT_H
