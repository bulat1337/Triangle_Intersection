#ifndef STATUS_H
#define STATUS_H

#include <iostream>

namespace t_inter
{

enum class status_t
{
    all_good,
    invalid_amount,
    invalid_coordinate,
    invalid_open,
    invalid_axis
};

inline bool check_status(status_t status)
{
    if (status == status_t::all_good)
        return false;

    switch (status)
    {
        case status_t::all_good:
            return true;
        case status_t::invalid_amount:
            std::cerr << "ERROR: Invalid amount: "
                         "please enter non negative number\n";
            break;
        case status_t::invalid_coordinate:
            std::cerr << "ERROR: Please enter floating point as the triangle "
                         "coordinate\n";
            break;
        case status_t::invalid_open:
            std::cerr << "ERROR: Can not open file\n";
            break;
        case status_t::invalid_axis:
            std::cerr << "ERROR: Invalid axis. Please check if dimentions are "
                         "mathing\n";
            break;
        default:
            std::cerr << "ERROR: Unknown\n";
    }

    return true;
}

}; // namespace t_inter

#endif // STATUS_H
