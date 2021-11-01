#ifndef COLOR_H
#define COLOR_H

#include "vec3.h"

#include <iostream>

void write_color( std::ostream &out, color pixel_color )
{
    out << '(' 
        << static_cast<uint16_t>( 255.999 * pixel_color.x() ) << ", "
        << static_cast<uint16_t>( 255.999 * pixel_color.y() ) << ", "
        << static_cast<uint16_t>( 255.999 * pixel_color.z() ) << ")\n";
}

void write_ppm_color( std::ostream &out, color pixel_color )
{
    out << static_cast<uint16_t>( 255.999 * pixel_color.x() ) << ' '
        << static_cast<uint16_t>( 255.999 * pixel_color.y() ) << ' '
        << static_cast<uint16_t>( 255.999 * pixel_color.z() ) << '\n';
}

#endif

