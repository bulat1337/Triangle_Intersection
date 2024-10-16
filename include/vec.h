#ifndef VEC_3_H
#define VEC_3_H

#include <iostream>

// ------------------ Vec3 ------------------

class Vec3
{
  private:
	double x_ = 0.0;
	double y_ = 0.0;
	double z_ = 0.0;

  public:
	Vec3();

	Vec3(double x, double y, double z);

	Vec3(const Vec3& other) = default;

	const double &x() const;

	const double &y() const;

	const double &z() const;

	double &x() ;

	double &y() ;

	double &z() ;

	Vec3& operator =(const Vec3& other);

	Vec3& operator +=(const Vec3& other);

	Vec3& operator *=(double scalar);

	Vec3& operator /=(double scalar);

	Vec3 operator - () const;

	bool operator ==(const Vec3& other) const;

	double sq_length() const;

	double length() const;

	bool near_zero() const;
};

Vec3 operator + (const Vec3 &lhs, const Vec3 &rhs);
Vec3 operator - (const Vec3 &lhs, const Vec3 &rhs);
Vec3 operator * (const Vec3 &lhs, const Vec3 &rhs);
Vec3 operator * (const Vec3 &lhs, double scalar);
Vec3 operator * (double scalar, const Vec3 &vec3);
Vec3 operator / (const Vec3 &vec3, double scalar);

std::ostream&	operator << (std::ostream &out, const Vec3 &vec3);
std::istream&   operator >> (std::istream& is, Vec3& vec);

double 			dot		(const Vec3 &lhs, const Vec3 &rhs);
Vec3 			cross 	(const Vec3& lhs, const Vec3& rhs);

using Point3 = Vec3;

// ------------------ Vec2 ------------------

class Vec2
{
  private:
	double x_ = 0.0;
	double y_ = 0.0;

  public:
	Vec2();

	Vec2(double x, double y);

	const double &x() const;

	const double &y() const;

	double &x() ;

	double &y() ;
	Vec2 &operator +=(const Vec2 &other);

	Vec2 &operator *=(double scalar);

	Vec2 &operator /=(double scalar);

	Vec2 operator - () const;

	Vec2 clockwise_normal() const;

	double sq_length() const;

	double length() const;

	bool near_zero() const;
};

Vec2 operator + (const Vec2 &lhs, const Vec2 &rhs);
Vec2 operator - (const Vec2 &lhs, const Vec2 &rhs);
Vec2 operator * (const Vec2 &lhs, const Vec2 &rhs);
Vec2 operator * (const Vec2 &lhs, double scalar);
Vec2 operator * (double scalar, const Vec2 &vec3);
Vec2 operator / (const Vec2 &vec3, double scalar);

std::ostream& operator << (std::ostream &out, const Vec2 &vec3);

double dot(const Vec2 &lhs, const Vec2 &rhs);

Vec3 unit_vector(const Vec3 &vector);

using Point2 = Vec2;




#endif
