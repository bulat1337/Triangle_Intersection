#include "vec.h"

#include <cmath>

#include <iostream>

#include "utils.h"


// ------------------ Vec3 ------------------


Vec3::Vec3(): x_(0.0), y_(0.0), z_(0.0) {}

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
	x_ += other.x_;
	y_ += other.y_;
	z_ += other.z_;

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
	return 	(std::fabs(x_) < utils::fp_tolerance) &&
			(std::fabs(y_) < utils::fp_tolerance) &&
			(std::fabs(z_) < utils::fp_tolerance);
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


// ------------------ Vec2 ------------------

Vec2::Vec2(): x_(0.0), y_(0.0) {}

Vec2::Vec2(double x, double y):
	x_(x), y_(y) {}

const double &Vec2::x() const
{
	return x_;
}

const double &Vec2::y() const
{
	return y_;
}

double &Vec2::x()
{
	return x_;
}

double &Vec2::y()
{
	return y_;
}

Vec2 &Vec2::operator += (const Vec2 &other)
{
	x_ += other.x_;
	y_ += other.y_;
	return *this;
}

Vec2 &Vec2::operator *= (double scalar)
{
	x_ *= scalar;
	y_ *= scalar;

	return *this;
}

Vec2 &Vec2::operator /= (double scalar)
{
	return *this *= (1 / scalar);
}

Vec2 Vec2::operator - () const
{
	return Vec2(-x_, -y_);
}

double Vec2::sq_length() const
{
	return 	x_ * x_
			+ y_ * y_;
}

double Vec2::length() const
{
	return std::sqrt(sq_length());
}

bool Vec2::near_zero() const
{
	return 	(std::fabs(x_) < utils::fp_tolerance) &&
			(std::fabs(y_) < utils::fp_tolerance);
}

Vec2 Vec2::clockwise_normal() const
{
	return Vec2(y_, -x_);
}


Vec2 operator + (const Vec2 &lhs, const Vec2 &rhs)
{
	return Vec2(lhs.x() + rhs.x(),
				lhs.y() + rhs.y());
}

Vec2 operator - (const Vec2 &lhs, const Vec2 &rhs)
{
	return Vec2(lhs.x() - rhs.x(),
				lhs.y() - rhs.y());
}

Vec2 operator * (const Vec2 &lhs, const Vec2 &rhs)
{
	return Vec2(lhs.x() * rhs.x(),
				lhs.y() * rhs.y());
}

Vec2 operator * (const Vec2 &lhs, double scalar)
{
	return Vec2(lhs.x() * scalar,
				lhs.y() * scalar);
}

Vec2 operator * (double scalar, const Vec2 &vec3)
{
	return vec3 * scalar;
}

Vec2 operator / (const Vec2 &vec3, double scalar)
{
	return vec3 * (1 / scalar);
}

std::ostream &operator << (std::ostream &out, const Vec2 &vec3)
{
	out << vec3.x() << ' ' << vec3.y();

	return out;
}

double dot(const Vec2 &lhs, const Vec2 &rhs)
{
	return 	lhs.x() * rhs.x() +
			lhs.y() * rhs.y();
}

Vec3 unit_vector(const Vec3 &vector)
{
	return vector / vector.length();
}
