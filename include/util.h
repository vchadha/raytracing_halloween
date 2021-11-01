#ifndef UTIL_H
#define UTIL_H

#include <cmath>
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

#endif

