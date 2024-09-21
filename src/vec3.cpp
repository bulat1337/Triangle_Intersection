#include "vec3.h"

#include <cmath>

#include <iostream>

#include "utils.h"


Vec3::Vec3(): coords{0, 0, 0} {}

Vec3::Vec3(double x, double y, double z):
	x_(x), y_(y), z_(z) {}

const double &Vec3::x() const
{
	return x_;
}

const double &Vec3::y() const
{
	return y_;
}

const double &Vec3::z() const
{
	return z_;
}

double &Vec3::x()
{
	return x_;
}

double &Vec3::y()
{
	return y_;
}

double &Vec3::z()
{
	return z_;
}

Vec3 &Vec3::operator += (const Vec3 &other)
{
	x_ += other.x;
	y_ += other.y;
	z_ += other.z;

	return *this;
}

Vec3 &Vec3::operator *= (double scalar)
{
	x_ *= scalar;
	y_ *= scalar;
	z_ *= scalar;

	return *this;
}

Vec3 &Vec3::operator /= (double scalar)
{
	return *this *= (1 / scalar);
}

Vec3 Vec3::operator - () const
{
	return Vec3(-x_, -y_, -z_);
}

double Vec3::sq_length() const
{
	return 	x_ * x_
			+ y_ * y_
			+ z_ * z_;
}

double Vec3::length() const
{
	return std::sqrt(sq_length());
}

bool Vec3::near_zero() const
{
	return 	(std::fabs(coords[0]) < utils::fp_tolerance) &&
			(std::fabs(coords[1]) < utils::fp_tolerance) &&
			(std::fabs(coords[2]) < utils::fp_tolerance);
}


Vec3 operator + (const Vec3 &lhs, const Vec3 &rhs)
{
	return Vec3(lhs.x() + rhs.x(),
				lhs.y() + rhs.y(),
				lhs.z() + rhs.z());
}

Vec3 operator - (const Vec3 &lhs, const Vec3 &rhs)
{
	return Vec3(lhs.x() - rhs.x(),
				lhs.y() - rhs.y(),
				lhs.z() - rhs.z());
}

Vec3 operator * (const Vec3 &lhs, const Vec3 &rhs)
{
	return Vec3(lhs.x() * rhs.x(),
				lhs.y() * rhs.y(),
				lhs.z() * rhs.z());
}

Vec3 operator * (const Vec3 &lhs, double scalar)
{
	return Vec3(lhs.x() * scalar,
				lhs.y() * scalar,
				lhs.z() * scalar);
}

Vec3 operator * (double scalar, const Vec3 &vec3)
{
	return vec3 * scalar;
}

Vec3 operator / (const Vec3 &vec3, double scalar)
{
	return vec3 * (1 / scalar);
}

std::ostream &operator << (std::ostream &out, const Vec3 &vec3)
{
	out << vec3.x() << ' ' << vec3.y() << ' ' << vec3.z();

	return out;
}

double dot(const Vec3 &lhs, const Vec3 &rhs)
{
	return 	lhs.x() * rhs.x() +
			lhs.y() * rhs.y() +
			lhs.z() * rhs.z();
}

Vec3 cross(const Vec3& lhs, const Vec3& rhs)
{
	return Vec3(lhs.y() * rhs.z() - lhs.z() * rhs.y(),
				lhs.z() * rhs.x() - lhs.x() * rhs.z(),
				lhs.x() * rhs.y() - lhs.y() * rhs.x());
}
