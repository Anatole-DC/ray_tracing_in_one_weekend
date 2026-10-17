#ifndef SPHERE_H
#define SPHERE_H

#include "hittable.hpp"
#include "vector3.hpp"

class sphere : public hittable {
  public:
    sphere(const point3& center, double radius);
    sphere(const point3& center, double radius, std::shared_ptr<material> mat);

    bool hit(const ray& r, interval ray_t, hit_record& rec) const override;

  private:
    point3 center;
    double radius;
    std::shared_ptr<material> mat;
};

#endif