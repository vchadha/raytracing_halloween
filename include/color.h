#ifndef COLOR_H
#define COLOR_H

#include "vec3.h"

#include <cmath>
#include <iostream>

void write_color( std::ostream &out, color pixel_color, uint8_t num_samples )
{
    float r = pixel_color.x();
    float g = pixel_color.y();
    float b = pixel_color.z();

    // Divide by num samples and gamma correct, gamma = 2.0
    float scale = 1.0 / num_samples;
    r = std::sqrt( scale * r );
    g = std::sqrt( scale * g );
    b = std::sqrt( scale * b );

    // Write [0, 255] color components
    out << static_cast<uint16_t>( 256 * clamp( r, 0.0, 0.999 ) ) << ' '
        << static_cast<uint16_t>( 256 * clamp( g, 0.0, 0.999 ) ) << ' '
        << static_cast<uint16_t>( 256 * clamp( b, 0.0, 0.999 ) ) << '\n';
}

#endif

