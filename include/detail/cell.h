#ifndef CELL_H
#define CELL_H

namespace t_inter
{

namespace detail
{

struct Cell
{
    long long x = 0;
    long long y = 0;
    long long z = 0;

    Cell() = default;

    Cell(long long _x, long long _y, long long _z)
        : x(_x)
        , y(_y)
        , z(_z)
    {}

    bool operator==(const Cell &other) const = default;
};

}; // namespace detail

}; // namespace t_inter

#endif
