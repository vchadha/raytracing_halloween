#include "utilities/util.h"

#include <cmath>
#include <cstdlib>
#include <iostream>

float util::deg2rad( float deg )
{
    return ( deg * PI / 180.0 );
}

float util::random_float()
{
    // Returns random real in [0. 1)
    return ( rand() / ( RAND_MAX + 1.0 ) );
}

float util::random_float( float min, float max )
{
    // Returns random real in [min, max)
    return ( min + ( max - min ) * random_float() );
}

float util::clamp( float x, float min, float max )
{
    float return_val = x;

    if ( x < min )
    {
        return_val = min;
    }

    if( x > max )
    {
        return_val = max;
    }

    return ( return_val );
}

vector3f util::random_vector3f()
{
    return ( vector3f( random_float(), random_float(), random_float() ) );
}

vector3f util::random_vector3f( float min, float max )
{
    float v1 = random_float( min, max );
    float v2 = random_float( min, max );
    float v3 = random_float( min, max );

    return ( vector3f( v1, v2, v3 ) );
}

vector3f util::random_vector3f_in_unit_sphere()
{
    vector3f p = random_vector3f( -1.0, 1.0 );
    bool is_valid = p.length_squared() < 1;

    while( !is_valid )
    {
        p = random_vector3f( -1.0, 1.0 );
        is_valid = p.length_squared() < 1;
    }

    return ( p );
}

vector3f util::random_unit_vector()
{
    return ( random_vector3f_in_unit_sphere().unit_vector() );
}

vector3f util::random_vector3f_in_hemisphere( const vector3f &normal )
{
    vector3f in_unit_sphere = random_vector3f_in_unit_sphere();

    if ( in_unit_sphere.dot( normal ) <= 0.0 )
    {
        in_unit_sphere = -in_unit_sphere;
    }

    return ( in_unit_sphere );
}

vector3f util::random_vector3f_in_unit_disc()
{
    vector3f p = vector3f( random_float( -1.0, 1.0 ), random_float( -1.0, 1.0 ), 0.0 );
    bool is_valid = p.length_squared() < 1;

    while( !is_valid )
    {
        p = vector3f( random_float( -1.0, 1.0 ), random_float( -1.0, 1.0 ), 0.0 ); 
        is_valid = p.length_squared() < 1;
    }

    return ( p );
}

bool util::near_zero( const vector3f &v )
{
    // Return true if vector is close to zero in all dim
    const float s = 1e-8;
    return ( fabs( v[0] ) < s && fabs( v[1] ) < s && fabs( v[2] < s ) );
}

vector3f util::reflect( const vector3f &v, const vector3f &n )
{
    return ( v - 2 * v.dot( n ) * n );
}

vector3f util::refract( const vector3f &uv, const vector3f &n, float eta_ratio )
{
    float cos_theta = fmin( ( -uv ).dot( n ), 1.0 );
    vector3f r_perp = eta_ratio * ( uv + cos_theta * n );
    vector3f r_parallel = -std::sqrt( fabs( 1.0 - r_perp.length_squared() ) ) * n;

    return ( r_perp + r_parallel );
}

void util::write_color( std::ostream &out, color pixel_color, uint16_t num_samples )
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
