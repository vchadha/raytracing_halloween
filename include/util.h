#ifndef UTIL_H
#define UTIL_H

// TODO: split these files and includes into h and cc plz
#include "vec3.h"

#include <cmath>
#include <cstdlib>
#include <limits>
#include <memory>

//Constants
const float pos_infinity = std::numeric_limits<float>::infinity();
const float PI = 3.1415926535897932385;

// Utility functions
inline float deg2rad( float deg )
{
    return ( deg * PI / 180.0 );
}

inline float random_float()
{
    // Returns random real in [0. 1)
    return ( rand() / ( RAND_MAX + 1.0 ) );
}

inline float random_float( float min, float max )
{
    // Returns random real in [min, max)
    return ( min + ( max - min ) * random_float() );
}

inline float clamp( float x, float min, float max )
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

inline vec3 random_vec3()
{
    return ( vec3( random_float(), random_float(), random_float() ) );
}

inline vec3 random_vec3( float min, float max )
{
    float v1 = random_float( min, max );
    float v2 = random_float( min, max );
    float v3 = random_float( min, max );

    return ( vec3( v1, v2, v3 ) );
}

vec3 random_vec3_in_unit_sphere()
{
    vec3 p = random_vec3( -1.0, 1.0 );
    bool is_valid = p.length_squared() < 1;

    while( !is_valid )
    {
        p = random_vec3( -1.0, 1.0 );
        is_valid = p.length_squared() < 1;
    }

    return ( p );
}

vec3 random_unit_vector()
{
    return ( unit_vector( random_vec3_in_unit_sphere() ) );
}

vec3 random_vec3_in_hemisphere( const vec3 &normal )
{
    vec3 in_unit_sphere = random_vec3_in_unit_sphere();

    if ( dot( in_unit_sphere, normal ) <= 0.0 )
    {
        in_unit_sphere = -in_unit_sphere;
    }

    return ( in_unit_sphere );
}

vec3 random_vec3_in_unit_disc()
{
    vec3 p = vec3( random_float( -1.0, 1.0 ), random_float( -1.0, 1.0 ), 0.0 );
    bool is_valid = p.length_squared() < 1;

    while( !is_valid )
    {
        p = vec3( random_float( -1.0, 1.0 ), random_float( -1.0, 1.0 ), 0.0 ); 
        is_valid = p.length_squared() < 1;
    }

    return ( p );
}

#endif

