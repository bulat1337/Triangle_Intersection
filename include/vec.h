#ifndef VEC_H
#define VEC_H

#include <cmath>
#include <iostream>

// ------------------ Vec3 ------------------

template <typename FltPnt> class Vec3
{
  private:
    FltPnt x_ = 0.0;
    FltPnt y_ = 0.0;
    FltPnt z_ = 0.0;

  public:
    Vec3()
        : x_(0.0)
        , y_(0.0)
        , z_(0.0)
    {}

    Vec3(FltPnt x, FltPnt y, FltPnt z)
        : x_(x)
        , y_(y)
        , z_(z)
    {}

    Vec3(const Vec3 &other) = default;

    FltPnt x() const { return x_; }
    FltPnt y() const { return y_; }
    FltPnt z() const { return z_; }

    void set_x(FltPnt value) { x_ = value; }
    void set_y(FltPnt value) { y_ = value; }
    void set_z(FltPnt value) { z_ = value; }

    Vec3 &operator=(const Vec3 &other)
    {
        x_ = other.x_;
        y_ = other.y_;
        z_ = other.z_;
        return *this;
    }

    Vec3 &operator+=(const Vec3 &other)
    {
        x_ += other.x_;
        y_ += other.y_;
        z_ += other.z_;
        return *this;
    }

    Vec3 &operator*=(FltPnt scalar)
    {
        x_ *= scalar;
        y_ *= scalar;
        z_ *= scalar;
        return *this;
    }

    Vec3 &operator/=(FltPnt scalar) { return *this *= (1 / scalar); }

    Vec3 operator-() const { return Vec3(-x_, -y_, -z_); }

    bool operator==(const Vec3 &other) const
    {
        return (std::fabs(x_ - other.x_) < 1e-9) &&
               (std::fabs(y_ - other.y_) < 1e-9) &&
               (std::fabs(z_ - other.z_) < 1e-9);
    }

    FltPnt sq_length() const { return x_ * x_ + y_ * y_ + z_ * z_; }

    FltPnt length() const { return std::sqrt(sq_length()); }

    bool near_zero() const
    {
        return (std::fabs(x_) < 1e-9) && (std::fabs(y_) < 1e-9) &&
               (std::fabs(z_) < 1e-9);
    }
};

template <typename FltPnt>
inline Vec3<FltPnt> operator+(const Vec3<FltPnt> &lhs, const Vec3<FltPnt> &rhs)
{
    return Vec3(lhs.x() + rhs.x(), lhs.y() + rhs.y(), lhs.z() + rhs.z());
}

template <typename FltPnt>
inline Vec3<FltPnt> operator-(const Vec3<FltPnt> &lhs, const Vec3<FltPnt> &rhs)
{
    return Vec3(lhs.x() - rhs.x(), lhs.y() - rhs.y(), lhs.z() - rhs.z());
}
template <typename FltPnt>
inline Vec3<FltPnt> operator*(const Vec3<FltPnt> &lhs, const Vec3<FltPnt> &rhs)
{
    return Vec3(lhs.x() * rhs.x(), lhs.y() * rhs.y(), lhs.z() * rhs.z());
}

template <typename FltPnt>
inline Vec3<FltPnt> operator*(const Vec3<FltPnt> &lhs, double scalar)
{
    return Vec3(lhs.x() * scalar, lhs.y() * scalar, lhs.z() * scalar);
}

template <typename FltPnt>
inline Vec3<FltPnt> operator*(double scalar, const Vec3<FltPnt> &vec)
{
    return vec * scalar;
}

template <typename FltPnt>
inline Vec3<FltPnt> operator/(const Vec3<FltPnt> &vec, double scalar)
{
    return vec * (1 / scalar);
}

template <typename FltPnt>
inline std::ostream &operator<<(std::ostream &out, const Vec3<FltPnt> &vec)
{
    out << vec.x() << ' ' << vec.y() << ' ' << vec.z();
    return out;
}

template <typename FltPnt>
inline std::istream &operator>>(std::istream &in, Vec3<FltPnt> &vec)
{
    double x, y, z;
    if (in >> x >> y >> z)
    {
        vec.set_x(x);
        vec.set_y(y);
        vec.set_z(z);
    }
    return in;
}

template <typename FltPnt>
inline double dot(const Vec3<FltPnt> &lhs, const Vec3<FltPnt> &rhs)
{
    return lhs.x() * rhs.x() + lhs.y() * rhs.y() + lhs.z() * rhs.z();
}

template <typename FltPnt>
inline Vec3<FltPnt> cross(const Vec3<FltPnt> &lhs, const Vec3<FltPnt> &rhs)
{
    return Vec3(lhs.y() * rhs.z() - lhs.z() * rhs.y(),
                lhs.z() * rhs.x() - lhs.x() * rhs.z(),
                lhs.x() * rhs.y() - lhs.y() * rhs.x());
}

template <typename FltPnt>
inline Vec3<FltPnt> unit_vector(const Vec3<FltPnt> &vector)
{
    return vector / vector.length();
}

template <typename FltPnt> using Point3 = Vec3<FltPnt>;

// ------------------ Vec2 ------------------

template <typename FltPnt> class Vec2
{
  private:
    FltPnt x_ = 0.0;
    FltPnt y_ = 0.0;

  public:
    Vec2()
        : x_(0.0)
        , y_(0.0)
    {}

    Vec2(FltPnt x, FltPnt y)
        : x_(x)
        , y_(y)
    {}

    FltPnt x() const { return x_; }
    FltPnt y() const { return y_; }

    void set_x(FltPnt value) { x_ = value; }
    void set_y(FltPnt value) { y_ = value; }

    Vec2 &operator+=(const Vec2 &other)
    {
        x_ += other.x_;
        y_ += other.y_;
        return *this;
    }

    Vec2 &operator*=(FltPnt scalar)
    {
        x_ *= scalar;
        y_ *= scalar;
        return *this;
    }

    Vec2 &operator/=(FltPnt scalar) { return *this *= (1 / scalar); }

    Vec2 operator-() const { return Vec2(-x_, -y_); }

    FltPnt sq_length() const { return x_ * x_ + y_ * y_; }

    FltPnt length() const { return std::sqrt(sq_length()); }

    bool near_zero() const
    {
        return (std::fabs(x_) < 1e-9) && (std::fabs(y_) < 1e-9);
    }

    Vec2 clockwise_normal() const { return Vec2(y_, -x_); }
};

template <typename FltPnt>
inline Vec2<FltPnt> operator+(const Vec2<FltPnt> &lhs, const Vec2<FltPnt> &rhs)
{
    return Vec2(lhs.x() + rhs.x(), lhs.y() + rhs.y());
}

template <typename FltPnt>
inline Vec2<FltPnt> operator-(const Vec2<FltPnt> &lhs, const Vec2<FltPnt> &rhs)
{
    return Vec2(lhs.x() - rhs.x(), lhs.y() - rhs.y());
}

template <typename FltPnt>
inline Vec2<FltPnt> operator*(const Vec2<FltPnt> &lhs, const Vec2<FltPnt> &rhs)
{
    return Vec2(lhs.x() * rhs.x(), lhs.y() * rhs.y());
}

template <typename FltPnt>
inline Vec2<FltPnt> operator*(const Vec2<FltPnt> &lhs, double scalar)
{
    return Vec2(lhs.x() * scalar, lhs.y() * scalar);
}

template <typename FltPnt>
inline Vec2<FltPnt> operator*(double scalar, const Vec2<FltPnt> &vec)
{
    return vec * scalar;
}

template <typename FltPnt>
inline Vec2<FltPnt> operator/(const Vec2<FltPnt> &vec, double scalar)
{
    return vec * (1 / scalar);
}

template <typename FltPnt>
inline std::ostream &operator<<(std::ostream &out, const Vec2<FltPnt> &vec)
{
    out << vec.x() << ' ' << vec.y();
    return out;
}

template <typename FltPnt>
inline FltPnt dot(const Vec2<FltPnt> &lhs, const Vec2<FltPnt> &rhs)
{
    return lhs.x() * rhs.x() + lhs.y() * rhs.y();
}

template <typename FltPnt> using Point2 = Vec2<FltPnt>;

#endif // VEC_H
