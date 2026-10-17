#include "rtweekend.hpp"

#include "hittable.hpp"
#include "hittable_list.hpp"
#include "sphere.hpp"
#include "camera.hpp"
#include "materials.hpp"

// Writes a PPM string to a file. Returns true on success.
bool exportPPMImage(const std::string& i_ppm_content, const std::string& i_file_path) {
    std::ofstream file(i_file_path, std::ios::out | std::ios::trunc);
    if (!file.is_open()) {
        std::cerr << "Error: could not open '" << i_file_path << "' for writing.\n";
        return false;
    }

    file << i_ppm_content;
    file.close();

    if (file.fail()) {
        std::cerr << "Error: failed while writing to '" << i_file_path << "'.\n";
        return false;
    }

    std::clog << "Image exported to " << i_file_path << "\n";
    return true;
}


std::int32_t main(std::int32_t argc, char** argv) {
    std::string output_path = (argc > 1) ? argv[1] : "image.ppm";
    hittable_list world;

    auto ground_material = std::make_shared<lambertian>(color(0.5, 0.5, 0.5));
    world.add(std::make_shared<sphere>(point3(0,-1000,0), 1000, ground_material));

    for (int a = -11; a < 11; a++) {
        for (int b = -11; b < 11; b++) {
            auto choose_mat = random_double();
            point3 center(a + 0.9*random_double(), 0.2, b + 0.9*random_double());

            if ((center - point3(4, 0.2, 0)).length() > 0.9) {
                std::shared_ptr<material> sphere_material;

                if (choose_mat < 0.8) {
                    // diffuse
                    auto albedo = color::random() * color::random();
                    sphere_material = std::make_shared<lambertian>(albedo);
                    world.add(std::make_shared<sphere>(center, 0.2, sphere_material));
                } else if (choose_mat < 0.95) {
                    // metal
                    auto albedo = color::random(0.5, 1);
                    auto fuzz = random_double(0, 0.5);
                    sphere_material = std::make_shared<metal>(albedo, fuzz);
                    world.add(std::make_shared<sphere>(center, 0.2, sphere_material));
                } else {
                    // glass
                    sphere_material = std::make_shared<dielectric>(1.5);
                    world.add(std::make_shared<sphere>(center, 0.2, sphere_material));
                }
            }
        }
    }

    auto material1 = std::make_shared<dielectric>(1.5);
    world.add(std::make_shared<sphere>(point3(0, 1, 0), 1.0, material1));

    auto material2 = std::make_shared<lambertian>(color(0.4, 0.2, 0.1));
    world.add(std::make_shared<sphere>(point3(-4, 1, 0), 1.0, material2));

    auto material3 = std::make_shared<metal>(color(0.7, 0.6, 0.5), 0.0);
    world.add(std::make_shared<sphere>(point3(4, 1, 0), 1.0, material3));

    camera* cam = new camera(
        16.0 / 9.0,
        1200,
        500,
        50,
        20,
        point3(13,2,3),
        point3(0,0,0),
        vec3(0,1,0),
        0.6,
        10.0
    );

    const std::string ppm = cam->render(world);

    return exportPPMImage(ppm, output_path) ? 0 : 1;
}