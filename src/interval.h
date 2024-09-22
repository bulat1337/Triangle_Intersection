#ifndef INTERVAL_H
#define INTERVAL_H

class Interval
{
  private:
	double min_ = 0.0;
	double max_ = 0.0;

  public:
	Interval() = default;

	Interval(double min, double max):
		min_(min), max_(max) {}

	double min() const
	{
		return min_;
	}

	double max() const
	{
		return max_;
	}

	double& min()
	{
		return min_;
	}

	double& max()
	{
		return max_;
	}
};

#endif
