#include "camera.h"
#include "ray.h"
#include "surfaces.h"

#include "objects/sphere.h"

#include "materials/lambertian.h"
#include "materials/metal.h"
#include "materials/dielectric.h"

#include "utilities/util.h"
#include "utilities/vector3f.h"

#include <iostream>
#include <cmath>

void WriteProgress( float percent )
{
    uint8_t buff_size = 45;
    char output [buff_size];

    const uint8_t bar_width = 35;
    std::string progress_bar = "";

    uint8_t bar_percentage = static_cast<uint8_t>( bar_width * percent );
    for ( uint8_t i = 0; i < bar_width; i++ )
    {
        if ( i <= bar_percentage )
        {
            progress_bar.append( "#" );
        }
        else
        {
            progress_bar.append( " " );
        }
    }

    uint8_t rounded_percent = static_cast<int>( percent * 100 );
    snprintf( output, buff_size, "%-3u%%: [%s]\n", rounded_percent, progress_bar.c_str() );
    std::cerr << output << std::flush;
}

float hit_sphere( const point3 &center, double radius, const ray &r )
{
    float hit_point = -1.0;

    vector3f oc = r.origin() - center;
    float a = r.direction().length_squared();
    float half_b = oc.dot( r.direction() );
    float c = oc.length_squared() - radius * radius;
    float discriminant = half_b * half_b - a * c;
    
    if ( discriminant >= 0 )
    {
        hit_point = ( -half_b - std::sqrt( discriminant ) ) / a;
    }

    return ( hit_point );
}

color ray_color( const ray &r, const surface &world, uint8_t depth )
{
    hit_record record;
    color pixel_color = color( 0.0, 0.0, 0.0 );

    // Have not reached ray bounce limit
    if ( depth > 0 )
    {
        if ( world.hit( r, 0.001, util::pos_infinity, record ) )
        {
            ray scattered;
            color attenuation;

            if ( record.mat_ptr->scatter( r, record, attenuation, scattered ) )
            {
                pixel_color = attenuation * ray_color( scattered, world, depth - 1 );
            }
        }
        else
        {
            vector3f unit_direction = r.direction().unit_vector();
            float t = 0.5 * ( unit_direction.y() + 1.0 );
            color c1 = color( 1.0, 1.0, 1.0 );
            color c2 = color( 0.5, 0.7, 1.0 );

            pixel_color = ( 1.0 - t ) * c1 + t * c2;
        }
    }

    return ( pixel_color );
}

surfaces random_scene()
{
    surfaces world;

    auto ground_material = std::make_shared<lambertian>( color( 0.5, 0.5, 0.5 ) );
    world.add(std::make_shared<sphere>( point3( 0, -1000, 0 ), 1000, ground_material ) );

    for ( int a = -11; a < 11; a++ ) {
        for ( int b = -11; b < 11; b++ ) {
            auto choose_mat = util::random_float();
            point3 center( a + 0.9 * util::random_float(), 0.2, b + 0.9 * util::random_float() );

            if ( ( center - point3( 4, 0.2, 0 ) ).length() > 0.9 ) {
                std::shared_ptr<material> sphere_material;

                if ( choose_mat < 0.8 ) {
                    // diffuse
                    auto albedo = util::random_vector3f() * util::random_vector3f();
                    sphere_material = std::make_shared<lambertian>( albedo );
                    world.add( std::make_shared<sphere>( center, 0.2, sphere_material ) );
                } else if ( choose_mat < 0.95 ) {
                    // metal
                    auto albedo = util::random_vector3f( 0.5, 1 );
                    auto fuzz = util::random_float( 0, 0.5 );
                    sphere_material = std::make_shared<metal>( albedo, fuzz );
                    world.add( std::make_shared<sphere>( center, 0.2, sphere_material ) );
                } else {
                    // glass
                    sphere_material = std::make_shared<dielectric>( 1.5 );
                    world.add( std::make_shared<sphere>( center, 0.2, sphere_material ) );
                }
            }
        }
    }

    auto material1 = std::make_shared<dielectric>( 1.5 );
    world.add( std::make_shared<sphere>( point3( 0, 1, 0 ), 1.0, material1 ) );

    auto material2 = std::make_shared<lambertian>( color( 0.4, 0.2, 0.1 ) );
    world.add( std::make_shared<sphere>( point3( -4, 1, 0 ), 1.0, material2 ) );

    auto material3 = std::make_shared<metal>( color( 0.7, 0.6, 0.5 ), 0.0 );
    world.add( std::make_shared<sphere>( point3( 4, 1, 0 ), 1.0, material3 ) );

    return world;
}

int main()
{
    // Image
    const float aspect_ratio = 3.0 / 2.0;
    const uint16_t image_width = 400;
    const uint16_t image_height = static_cast<uint16_t>( image_width / aspect_ratio );
    const uint16_t samples_per_pixel = 10;
    const uint16_t max_depth = 50;

    // World
    surfaces world;
    world = random_scene();

    // Camera
    point3 lookfrom( 13, 2, 3 );
    point3 lookat( 0.0, 0.0, 0.0 );
    vector3f vup( 0.0 , 1.0 , 0.0 );
    float dist_to_focus = 10.0;
    float aperture = 0.1;

    camera cam(lookfrom, lookat, vup, 20, aspect_ratio, aperture, dist_to_focus );

    // Render
    
    // Create image in PPM format
    // Preamble
    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    // Image data
    for ( int16_t j = image_height - 1; j >= 0; j-- )
    {
        // Write progress
        if ( j % 5 == 0 )
        {
            float percent = float( image_height - 1 - j ) / float( image_height - 1 );
            WriteProgress( percent );
        }

        for ( uint16_t i = 0; i < image_width; i++ )
        {
            color pixel_color( 0.0, 0.0, 0.0 );

            // Iter through samples
            for ( uint8_t s = 0; s < samples_per_pixel; s++ )
            {
                float u = ( i + util::random_float() ) / ( image_width - 1 );
                float v = ( j + util::random_float() ) / ( image_height - 1 );

                ray r = cam.get_ray( u, v );
                pixel_color += ray_color( r, world, max_depth );
            }

            util::write_color( std::cout, pixel_color, samples_per_pixel );
        }
    }

    return ( 0 );
}

