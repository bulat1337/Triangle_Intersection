#ifndef VEC_H
#define VEC_H

#include <cmath>
#include <iostream>

namespace t_inter
{

// ------------------ Vec3 ------------------

template <typename FltPnt> class Vec3
{
  public:
    FltPnt x = 0.0;
    FltPnt y = 0.0;
    FltPnt z = 0.0;

  public:
    Vec3(FltPnt _x = 0.0, FltPnt _y = 0.0, FltPnt _z = 0.0)
        : x(_x)
        , y(_y)
        , z(_z)
    {}

    Vec3 &operator+=(const Vec3 &other)
    {
        x += other.x;
        y += other.y;
        z += other.z;

        return *this;
    }

    Vec3 &operator*=(FltPnt scalar)
    {
        x *= scalar;
        y *= scalar;
        z *= scalar;

        return *this;
    }

    Vec3 &operator/=(FltPnt scalar) { return *this *= (1 / scalar); }

    Vec3 operator-() const { return Vec3(-x, -y, -z); }

    FltPnt sq_length() const { return x * x + y * y + z * z; }

    FltPnt length() const { return std::sqrt(sq_length()); }

    bool near_zero() const
    {
        return (std::fabs(x) < 1e-9) && (std::fabs(y) < 1e-9) &&
               (std::fabs(z) < 1e-9);
    }
};

template <typename FltPnt>
Vec3<FltPnt> operator+(const Vec3<FltPnt> &lhs, const Vec3<FltPnt> &rhs)
{
    return Vec3(lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z);
}

template <typename FltPnt>
Vec3<FltPnt> operator-(const Vec3<FltPnt> &lhs, const Vec3<FltPnt> &rhs)
{
    return Vec3(lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z);
}

template <typename FltPnt>
Vec3<FltPnt> operator*(const Vec3<FltPnt> &lhs, FltPnt scalar)
{
    return Vec3(lhs.x * scalar, lhs.y * scalar, lhs.z * scalar);
}

template <typename FltPnt>
Vec3<FltPnt> operator/(const Vec3<FltPnt> &vec, FltPnt scalar)
{
    return vec * (1 / scalar);
}

template <typename FltPnt>
std::ostream &operator<<(std::ostream &out, const Vec3<FltPnt> &vec)
{
    out << vec.x << ' ' << vec.y << ' ' << vec.z;
    return out;
}

template <typename FltPnt>
std::istream &operator>>(std::istream &in, Vec3<FltPnt> &vec)
{
    in >> vec.x >> vec.y >> vec.z;

    return in;
}

template <typename FltPnt>
double dot(const Vec3<FltPnt> &lhs, const Vec3<FltPnt> &rhs)
{
    return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z;
}

template <typename FltPnt>
Vec3<FltPnt> cross(const Vec3<FltPnt> &lhs, const Vec3<FltPnt> &rhs)
{
    return Vec3(lhs.y * rhs.z - lhs.z * rhs.y, lhs.z * rhs.x - lhs.x * rhs.z,
                lhs.x * rhs.y - lhs.y * rhs.x);
}

template <typename FltPnt>
Vec3<FltPnt> unit_vector(const Vec3<FltPnt> &vector)
{
    return vector / vector.length();
}

template <typename FltPnt> using Point3 = Vec3<FltPnt>;

// ------------------ Vec2 ------------------

template <typename FltPnt> class Vec2
{
  public:
    FltPnt x = 0.0;
    FltPnt y = 0.0;

  public:
    Vec2()
        : x(0.0)
        , y(0.0)
    {}

    Vec2(FltPnt _x, FltPnt _y)
        : x(_x)
        , y(_y)
    {}

    Vec2 &operator+=(const Vec2 &other)
    {
        x += other.x;
        y += other.y;
        return *this;
    }

    Vec2 operator-() const { return Vec2(-x, -y); }

    FltPnt sq_length() const { return x * x + y * y; }

    FltPnt length() const { return std::sqrt(sq_length()); }

    bool near_zero() const
    {
        return (std::fabs(x) < 1e-9) && (std::fabs(y) < 1e-9);
    }

    Vec2 clockwise_normal() const { return Vec2(y, -x); }
};

template <typename FltPnt>
Vec2<FltPnt> operator+(const Vec2<FltPnt> &lhs, const Vec2<FltPnt> &rhs)
{
    return Vec2(lhs.x + rhs.x, lhs.y + rhs.y);
}

template <typename FltPnt>
Vec2<FltPnt> operator-(const Vec2<FltPnt> &lhs, const Vec2<FltPnt> &rhs)
{
    return Vec2(lhs.x - rhs.x, lhs.y - rhs.y);
}

template <typename FltPnt>
FltPnt dot(const Vec2<FltPnt> &lhs, const Vec2<FltPnt> &rhs)
{
    return lhs.x * rhs.x + lhs.y * rhs.y;
}

template <typename FltPnt> using Point2 = Vec2<FltPnt>;

}; // namespace t_inter

#endif // VEC_H
