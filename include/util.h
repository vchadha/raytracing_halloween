#ifndef UTIL_H
#define UTIL_H

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
    return ( rand() / RAND_MAX + 1.0 );
}

inline float random_float( float min, float max )
{
    // Returns random real in [min, max)
    return ( min + ( max - min ) * random_float() );
}

#endif

