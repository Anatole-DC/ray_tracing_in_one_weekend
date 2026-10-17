#ifndef RTWEEKEND_H
#define RTWEEKEND_H

#include <stdio.h>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <unistd.h>
#include <cmath>
#include <memory>

#include "constants.h"

// Utility Functions

inline double degrees_to_radians(double degrees) {
    return degrees * pi / 180.0;
}

inline double random_double() {
    // Returns a random real in [0,1).
    return std::rand() / (RAND_MAX + 1.0);
}

inline double random_double(double min, double max) {
    // Returns a random real in [min,max).
    return min + (max-min)*random_double();
}

// Common Headers

#include "interval.hpp"
#include "color.hpp"
#include "ray.hpp"
#include "vector3.hpp"

#endif