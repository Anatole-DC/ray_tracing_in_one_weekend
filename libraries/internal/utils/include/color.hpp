#ifndef COLOR_H
#define COLOR_H

#include "vector3.hpp"

#include <iostream>

using color = vec3;

double linear_to_gamma(double linear_component);
void write_color(std::ostream& out, const color& pixel_color);


#endif