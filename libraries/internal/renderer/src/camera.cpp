#include "camera.hpp"
#include "materials.hpp"

camera::camera(
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
) : aspect_ratio(aspect_ratio),
    image_width(image_width),
    samples_per_pixel(samples_per_pixel),
    max_depth(max_depth),
    vfov(vfov),
    lookfrom(lookfrom),
    lookat(lookat),
    vup(vup),
    defocus_angle(defocus_angle),
    focus_dist(focus_dist)
{
    initialize();
}

void camera::initialize()
{
    pixel_samples_scale = 1.0 / samples_per_pixel;

    // Calculate the image height, and ensure that it's at least 1.
    image_height = std::int32_t(image_width / aspect_ratio);
    image_height = (image_height < 1) ? 1 : image_height;

    // Camera
    camera_center = lookfrom;

    double theta = degrees_to_radians(vfov);
    double h = std::tan(theta/2);
    double viewport_height = 2 * h * focus_dist;
    double viewport_width = viewport_height * (double(image_width) / image_height);

    w = unit_vector(lookfrom - lookat);
    u = unit_vector(cross(vup, w));
    v = cross(w, u);

    // Calculate the vectors across the horizontal and down the vertical viewport edges.
    vec3 viewport_u = viewport_width * u;    // Vector across viewport horizontal edge
    vec3 viewport_v = viewport_height * -v;  // Vector down viewport vertical edge

    // Calculate the horizontal and vertical delta vectors from pixel to pixel.
    pixel_delta_u = viewport_u / image_width;
    pixel_delta_v = viewport_v / image_height;

    // Calculate the location of the upper left pixel.
    point3 viewport_upper_left = camera_center - (focus_dist * w) - viewport_u/2 - viewport_v/2;
    // Calculate the camera defocus disk basis vectors.
    double defocus_radius = focus_dist * std::tan(degrees_to_radians(defocus_angle / 2));
    defocus_disk_u = u * defocus_radius;
    defocus_disk_v = v * defocus_radius;
    pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);
}

color camera::ray_color(const ray &r, std::uint8_t depth, const hittable &i_world)
{
    if (depth <= 0) {
        return color(0,0,0);
    }

    hit_record rec;
    if (i_world.hit(r, interval(0.001, infinity), rec))
    {
        ray scattered;
        color attenuation;
        if (rec.mat->scatter(r, rec, attenuation, scattered)) {
            return attenuation * ray_color(scattered, depth-1, i_world);
        }
        return color(0,0,0);
    }

    vec3 unit_direction = unit_vector(r.direction());
    double a = 0.5 * (unit_direction.y() + 1.0);
    return (1.0 - a) * color(1.0, 1.0, 1.0) + a * color(0.5, 0.7, 1.0);
}

point3 camera::defocus_disk_sample() const {
    // Returns a random point in the camera defocus disk.
    auto p = random_in_unit_disk();
    return camera_center + (p[0] * defocus_disk_u) + (p[1] * defocus_disk_v);
}

ray camera::get_ray(int i, int j) const
{
    // Construct a camera ray originating from the origin and directed at randomly sampled
    // point around the pixel location i, j.

    vec3 offset = sample_square();
    vec3 pixel_sample = pixel00_loc + ((i + offset.x()) * pixel_delta_u) + ((j + offset.y()) * pixel_delta_v);

    point3 ray_origin = (defocus_angle <= 0) ? camera_center : defocus_disk_sample();
    vec3 ray_direction = pixel_sample - ray_origin;

    return ray(ray_origin, ray_direction);
}

vec3 camera::sample_square() const
{
    // Returns the vector to a random point in the [-.5,-.5]-[+.5,+.5] unit square.
    return vec3(random_double() - 0.5, random_double() - 0.5, 0);
}

// Ray traces the scene and returns the image as a PPM string.
std::string createPPMImage(
    const camera &cam,
    const hittable &i_world)
{
    std::ostringstream ppm;
    ppm << "P3\n"
        << cam.image_width << ' ' << cam.image_height << " 255\n";

    for (std::uint16_t j = 0; j < cam.image_height; j++)
    {
        std::clog << "\rScanlines remaining: " << (cam.image_height - j) << " " << std::flush;
        for (std::uint16_t i = 0; i < cam.image_width; i++)
        {
            color pixel_color(0, 0, 0);
            for (std::uint8_t sample = 0; sample < cam.samples_per_pixel; sample++)
            {
                ray r = cam.get_ray(i, j);
                pixel_color += cam.ray_color(r, cam.max_depth, i_world);
            }
            write_color(ppm, cam.pixel_samples_scale * pixel_color);
        }
    }
    std::clog << "\rDone.                 \n";
    return ppm.str();
}

std::string camera::render(const hittable &i_world)
{
    return createPPMImage(
        *this,
        i_world);
}