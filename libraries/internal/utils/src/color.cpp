#include "color.hpp"

#include <cstdint>
#include <cmath>

#include "interval.hpp"


double linear_to_gamma(double linear_component)
{
    if (linear_component > 0)
        return std::sqrt(linear_component);

    return 0;
}

void write_color(std::ostream& out, const color& pixel_color) {
    double red = pixel_color.x();
    double green = pixel_color.y();
    double blue = pixel_color.z();

    // Apply a linear to gamma transform for gamma 2
    red = linear_to_gamma(red);
    green = linear_to_gamma(green);
    blue = linear_to_gamma(blue);

    // Translate the [0,1] component values to the byte range [0,255].
    static const interval intensity(0.000, 0.999);
    std::int32_t rbyte = static_cast<std::int32_t>(256 * intensity.clamp(red));
    std::int32_t gbyte = static_cast<std::int32_t>(256 * intensity.clamp(green));
    std::int32_t bbyte = static_cast<std::int32_t>(256 * intensity.clamp(blue));

    // Write out the pixel color components.
    out << rbyte << ' ' << gbyte << ' ' << bbyte << '\n';
}