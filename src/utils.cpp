#include "utils.h"

#include <cmath>

int utils::cmp_double(double lhs, double rhs)
{
    if(isnan(lhs) && isnan(rhs))
    {
        return 0;
    }
    if (fabs(lhs - rhs) < fp_tolerance)
    {
        return 0;
    }
    else if ((lhs - rhs) > fp_tolerance)
    {
        return 1;
    }
    else
    {
        return -1;
    }
}
