#ifndef INTERVAL_H
#define INTERVAL_H

#include "constants.h"

class interval {
  public:
    double min, max;

    interval(); // Default interval is empty

    interval(double min, double max);

    double size() const;

    bool contains(double x) const;

    bool surrounds(double x) const;

    double clamp(double x) const;

    static const interval empty, universe;
};



#endif