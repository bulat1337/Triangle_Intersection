#include "segment.h"

#include "vec.h"
#include "utils.h"
#include "log.h"

bool Segment2::point_on_segment(const Point2& pnt, const Segment2& sgm) const
{
	Vec2 ab = sgm.pnt_2() - sgm.pnt_1();
	Vec2 ap = pnt - sgm.pnt_1();

	double proj_on_norm = dot(ab, ap.clockwise_normal());

	if (utils::cmp_double(std::abs(proj_on_norm), 0) != 0)
	{
		return false;
	}

	double dot_product = dot(ap, ab);

	return dot_product >= 0 && dot_product <= ab.sq_length();
}

bool Segment2::intersects(const Segment2& other) const
{
	Vec2 direc_1 = pnt_2_ - pnt_1_;
	Point2 origin_1 = pnt_1_;

	Vec2 direc_2 = other.pnt_2() - other.pnt_1();
	Point2 origin_2 = other.pnt_1();

	Vec2 orig_to_orig = origin_2 - origin_1;

	double dir_1_proj = dot(direc_1, direc_2.clockwise_normal());

	double oo_proj_1 = dot(orig_to_orig, direc_1.clockwise_normal());
	double oo_proj_2 = dot(orig_to_orig, direc_2.clockwise_normal());

	bool first_is_point = is_point(direc_1);
	bool second_is_point = is_point(direc_2);

	if (first_is_point && second_is_point)
	{
		MSG("They are both points\n");
		return orig_to_orig.near_zero();
	}

	if (first_is_point)
	{
		MSG("First one is point\n");
		return point_on_segment(pnt_1_, other);
	}

	if (second_is_point)
	{
		MSG("Second one is point\n");
		return point_on_segment(other.pnt_1(), *this);
	}

	if (utils::cmp_double(dir_1_proj, 0) == 0)
	{
		MSG("Direrction 1 projection is 0\n");
		if (utils::cmp_double(oo_proj_1, 0) == 0)
		{
			double t_0 = dot(orig_to_orig, direc_1) / dot(direc_1, direc_1);

			double t_1 = t_0 + dot(direc_2, direc_1) / dot(direc_1, direc_1);

			if (std::max(t_0, t_1) <= 0 || std::min(t_0, t_1) >= 1) return false;
			else return true;
		}
		else return false;
	}

	double t = oo_proj_2 / dir_1_proj;

	double u = oo_proj_1 / dir_1_proj;


	LOG("t coeff: {}\n", t);
	LOG("u coeff: {}\n", u);

	if(0 <= t && t <= 1 && 0 <= u && u <= 1) return true;

	return false;
}

std::ostream& operator << (std::ostream& out, const Segment2& sgm)
{
	out << sgm.pnt_1() << ' ' << sgm.pnt_2();

	return out;
}
