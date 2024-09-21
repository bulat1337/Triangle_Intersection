#ifndef VEC_3_HPP
#define VEC_3_HPP

#include <cmath>
#include <iostream>

class Vec3
{
  private:
	double x_ = 0.0;
	double y_ = 0.0;
	double z_ = 0.0;

  public:
	Vec3();

	Vec3(double x, double y, double z);

	const double &x() const;

	const double &y() const;

	const double &z() const;

	double &x() ;

	double &y() ;

	double &z() ;

	Vec3 &operator +=(const Vec3 &other);

	Vec3 &operator *=(double scalar);

	Vec3 &operator /=(double scalar);

	Vec3 operator - () const;

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

double 			dot		(const Vec3 &lhs, const Vec3 &rhs);
Vec3 			cross 	(const Vec3& lhs, const Vec3& rhs);

using Point3 = Vec3;



#endif
