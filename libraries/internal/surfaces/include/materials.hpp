#ifndef MATERIAL_H
#define MATERIAL_H

#include "hittable.hpp"
#include <color.hpp>

class material {
  public:
    virtual ~material() = default;

    virtual bool scatter(
        const ray& ray_in, const hit_record& rec, color& attenuation, ray& scattered
    ) const;
};

class lambertian : public material {
  public:
    lambertian(const color& albedo);

    bool scatter(const ray& ray_in, const hit_record& rec, color& attenuation, ray& scattered)
    const override;

  private:
    color albedo;
};


class metal : public material {
  public:
    metal(const color& albedo, double fuzz);

    bool scatter(const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered) const override;

  private:
    color albedo;
    double fuzz;
};

class dielectric : public material {
  public:
    dielectric(double refraction_index);

    bool scatter(const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered) const override;

  private:
    // Refractive index in vacuum or air, or the ratio of the material's refractive index over
    // the refractive index of the enclosing media

    static double reflectance(double cosine, double refraction_index);
    double refraction_index;
};

#endif