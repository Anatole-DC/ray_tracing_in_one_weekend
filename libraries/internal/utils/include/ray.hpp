#ifndef RAY_H
#define RAY_H

#include "vector3.hpp"

class ray {
  public:
    ray();

    ray(const point3& origin, const vec3& direction);

    const point3& origin() const;
    const vec3& direction() const;

    point3 at(double t) const;

  private:
    point3 orig;
    vec3 dir;
};

#endif