#ifndef UTIL_H
#define UTIL_H

#include "vector3f.h"

#include <limits>

// Macros
#define UNUSED(x) (void)(x)

class util
{
    public:
        static float deg2rad( float deg );

        static float random_float();
        static float random_float( float min, float max );

        static float clamp( float x, float min, float max );

        static vector3f random_vector3f();
        static vector3f random_vector3f( float min, float max );

        static vector3f random_vector3f_in_unit_sphere();
        static vector3f random_unit_vector();
        static vector3f random_vector3f_in_hemisphere( const vector3f &normal );
        static vector3f random_vector3f_in_unit_disc();

        static bool near_zero( const vector3f &v );

        static vector3f reflect( const vector3f &v, const vector3f &n );
        static vector3f refract( const vector3f &uv, const vector3f &n, float eta_ratio );

        static void write_color( std::ostream &out, color pixel_color, uint16_t num_samples );

    public:
        //Constants
        constexpr static float const pos_infinity = std::numeric_limits<float>::infinity();
        constexpr static float const PI = 3.1415926535897932385;
};

#endif
