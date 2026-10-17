#ifndef CAMERA_H
#define CAMERA_H

#include "hittable.hpp"
#include "rtweekend.hpp"

class camera {
  public:
    /* Public Camera Parameters Here */
    double aspect_ratio;
    std::int32_t    image_height;   // Rendered image height
    std::int32_t    image_width;  // Rendered image width in pixel count
    point3 camera_center;         // Camera center
    point3 pixel00_loc;    // Location of pixel 0, 0
    vec3   pixel_delta_u;  // Offset to pixel to the right
    vec3   pixel_delta_v;  // Offset to pixel below
    std::int32_t    samples_per_pixel;
    double pixel_samples_scale;
    std::uint8_t max_depth;
    double vfov;
    point3 lookfrom = point3(0,0,0);   // Point camera is looking from
    point3 lookat   = point3(0,0,-1);  // Point camera is looking at
    vec3   vup      = vec3(0,1,0);     // Camera-relative "up" direction
    vec3   u, v, w;              // Camera frame basis vectors

    double defocus_angle = 0;  // Variation angle of rays through each pixel
    double focus_dist = 10;    // Distance from camera lookfrom point to plane of perfect focus
    vec3   defocus_disk_u;       // Defocus disk horizontal radius
    vec3   defocus_disk_v;       // Defocus disk vertical radius

    camera(
      double aspect_ratio,
      std::int32_t image_width,
      std::int32_t samples_per_pixel,
      std::uint8_t max_depth,
      double vfov,
      point3 lookfrom,
      point3 lookat,
      vec3 vup,
      double defocus_angle,
      double focus_dist
    );


    std::string render(const hittable& i_world);
    static color ray_color(const ray& r, std::uint8_t depth, const hittable& i_world);
    ray get_ray(int i, int j) const;
    vec3 sample_square() const;
    point3 defocus_disk_sample() const;

  private:
    /* Private Camera Variables Here */

    void initialize();

};

#endif