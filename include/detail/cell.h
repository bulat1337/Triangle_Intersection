#ifndef CELL_H
#define CELL_H

namespace t_inter
{

namespace detail
{

struct Cell final
{
    long long x;
    long long y;
    long long z;

    Cell(long long _x = 0, long long _y = 0, long long _z = 0)
        : x(_x)
        , y(_y)
        , z(_z)
    {}

    bool operator <=>(const Cell &other) const = default;
};

}; // namespace detail

}; // namespace t_inter

#endif
