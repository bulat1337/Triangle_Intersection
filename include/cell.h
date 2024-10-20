#ifndef CELL_H
#define CELL_H

struct Cell
{
    long long x = 0;
    long long y = 0;
    long long z = 0;

    Cell() = default;

    Cell(long long x, long long y, long long z)
        : x(x)
        , y(y)
        , z(z)
    {}

    bool operator==(const Cell &other) const
    {
        return x == other.x && y == other.y && z == other.z;
    }
};

#endif
