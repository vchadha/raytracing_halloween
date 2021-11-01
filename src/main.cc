#include "camera.h"

#include "color.h"
#include "ray.h"
#include "vec3.h"

#include "sphere.h"
#include "surfaces.h"

#include "util.h"

#include <iostream>

void WriteProgress( float percent )
{
    uint8_t buff_size = 45;
    char output [buff_size];

    const uint8_t bar_width = 35;
    std::string progress_bar = "";

    uint8_t bar_percentage = static_cast<uint8_t>( bar_width * percent );
    for ( uint8_t i = 0; i < bar_percentage; i++ )
    {
        progress_bar.append( "#" );
    }

    uint8_t rounded_percent = static_cast<int>( percent * 100 );
    snprintf( output, buff_size, "%-3u%%: [%s]\n", rounded_percent, progress_bar.c_str() );
    std::cerr << output << std::flush;
}

float hit_sphere( const point3 &center, double radius, const ray &r )
{
    float hit_point = -1.0;

    vec3 oc = r.origin() - center;
    float a = r.direction().length_squared();
    float half_b = dot( oc, r.direction() );
    float c = oc.length_squared() - radius * radius;
    float discriminant = half_b * half_b - a * c;
    
    if ( discriminant >= 0 )
    {
        hit_point = ( -half_b - std::sqrt( discriminant ) ) / a;
    }

    return ( hit_point );
}

color ray_color( const ray &r, const surface &world )
{
    hit_record record;
    color pixel_color = color( 1.0, 1.0, 1.0 );

    if ( world.hit( r, 0, pos_infinity, record ) )
    {
        pixel_color = 0.5 * ( record.normal + color( 1.0, 1.0, 1.0 ) );
    }
    else
    {
        vec3 unit_direction = unit_vector( r.direction() );
        float t = 0.5 * ( unit_direction.y() + 1.0 );
        color c1 = color( 1.0, 1.0, 1.0 );
        color c2 = color( 0.5, 0.7, 1.0 );

        pixel_color = ( 1.0 - t ) * c1 + t * c2;
    }

    return ( pixel_color );
}

int main()
{
    // Image
    const float aspect_ratio = 16.0 / 9.0;
    const uint16_t image_width = 400;
    const uint16_t image_height = static_cast<uint16_t>( image_width / aspect_ratio );
    const uint8_t samples_per_pixel = 100;

    // World
    surfaces world;
    world.add( std::make_shared<sphere>( point3( 0.0, 0.0, -1.0 ), 0.5 ) );
    world.add( std::make_shared<sphere>( point3( 0.0, -100.5, -1.0 ), 100 ) );

    // Camera
    camera cam;

    // Render
    
    // Create image in PPM format
    // Preamble
    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    // Image data
    for ( int16_t j = image_height - 1; j >= 0; j-- )
    {
        // Write progress
        float percent = float( image_height - 1 - j ) / float( image_height - 1 );
        WriteProgress( percent );

        for ( uint16_t i = 0; i < image_width; i++ )
        {
            color pixel_color( 0.0, 0.0, 0.0 );

            // Iter through samples
            for ( uint8_t s = 0; s < samples_per_pixel; s++ )
            {
                float u = ( i + random_float() ) / ( image_width - 1 );
                float v = ( j + random_float() ) / ( image_height - 1 );

                ray r = cam.get_ray( u, v );
                pixel_color += ray_color( r, world );
            }

            write_color( std::cout, pixel_color, samples_per_pixel );
        }
    }

    return ( 0 );
}

