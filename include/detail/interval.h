#ifndef INTERVAL_H
#define INTERVAL_H

namespace t_inter
{

namespace detail
{

class Interval
{
  private:
    double min_ = 0.0;
    double max_ = 0.0;

  public:
    Interval() = default;

    Interval(double min, double max)
        : min_(std::min(min, max))
        , max_(std::max(min, max))
    {}

    double min() const { return min_; }

    double max() const { return max_; }

    void set_min(double value) { min_ = value; }

    void set_max(double value) { max_ = value; }
};

}; // namespace detail

}; // namespace t_inter

#endif
