#include "sphere.hpp"
#include <cmath>

sphere::sphere(const point3 &center, double radius) : center(center), radius(std::fmax(0, radius)) {}

sphere::sphere(const point3 &center, double radius, std::shared_ptr<material> mat)
    : center(center), radius(std::fmax(0, radius)), mat(mat) {}

bool sphere::hit(const ray &r, interval ray_t, hit_record &record) const
{
    vec3 origin_center = center - r.origin();
    double a = r.direction().length_squared();
    double h = dot(r.direction(), origin_center);
    double c = origin_center.length_squared() - radius * radius;

    double discriminant = h * h - a * c;
    if (discriminant < 0)
        return false;

    double sqrtd = std::sqrt(discriminant);

    // Find the nearest root that lies in the acceptable range.
    double root = (h - sqrtd) / a;
    if (root <= ray_t.min || ray_t.max <= root)
    {
        root = (h + sqrtd) / a;
        if (root <= ray_t.min || ray_t.max <= root)
            return false;
    }

    record.t = root;
    record.point = r.at(record.t);
    vec3 outward_normal = (record.point - center) / radius;
    record.set_face_normal(r, outward_normal);
    record.mat = mat;

    return true;
}