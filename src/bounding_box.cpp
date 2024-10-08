#include "bounding_box.h"

#include "triangle.h"

#include "cmath"

Bounding_box::Bounding_box(const Triangle3& triangle)
{
	min_.x() = std::min({triangle.pnt_1().x(), triangle.pnt_2().x(), triangle.pnt_3().x()});
	min_.y() = std::min({triangle.pnt_1().y(), triangle.pnt_2().y(), triangle.pnt_3().y()});
	min_.z() = std::min({triangle.pnt_1().z(), triangle.pnt_2().z(), triangle.pnt_3().z()});

	max_.x() = std::max({triangle.pnt_1().x(), triangle.pnt_2().x(), triangle.pnt_3().x()});
	max_.y() = std::max({triangle.pnt_1().y(), triangle.pnt_2().y(), triangle.pnt_3().y()});
	max_.z() = std::max({triangle.pnt_1().z(), triangle.pnt_2().z(), triangle.pnt_3().z()});
}
