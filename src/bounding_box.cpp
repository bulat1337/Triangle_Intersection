#include "bounding_box.h"

#include <algorithm>   // for max, min

#include "triangle.h"  // for Triangle3

Bounding_box::Bounding_box(const Triangle3& triangle)
{
	min_.set_x(std::min({triangle.pnt_1().x(), triangle.pnt_2().x(), triangle.pnt_3().x()}));
	min_.set_y(std::min({triangle.pnt_1().y(), triangle.pnt_2().y(), triangle.pnt_3().y()}));
	min_.set_z(std::min({triangle.pnt_1().z(), triangle.pnt_2().z(), triangle.pnt_3().z()}));

	max_.set_x(std::max({triangle.pnt_1().x(), triangle.pnt_2().x(), triangle.pnt_3().x()}));
	max_.set_y(std::max({triangle.pnt_1().y(), triangle.pnt_2().y(), triangle.pnt_3().y()}));
	max_.set_z(std::max({triangle.pnt_1().z(), triangle.pnt_2().z(), triangle.pnt_3().z()}));
}
