#ifndef VEC3_H
#define VEC3_H

#include <cmath>
#include <iostream>

class vec3
{
    public:
        vec3() : e{0, 0, 0} {}
        vec3( float e0, float e1, float e2 ): e{e0, e1, e2} {}

        float x() const { return ( e[0] ); }
        float y() const { return ( e[1] ); }
        float z() const { return ( e[2] ); } 

        vec3 operator-() const { return ( vec3( -e[0], -e[1], -e[2] ) ); }
        float operator[]( uint8_t i ) const { return ( e[i] ); }
        float& operator[]( uint8_t i ) { return( e[i] ); }

        vec3& operator+=( const vec3 &v )
        {
            e[0] += v.e[0];
            e[1] += v.e[1];
            e[2] += v.e[2];

            return ( *this );
        }

        vec3& operator*=( const float t )
        {
            e[0] *= t;
            e[1] *= t;
            e[2] *= t;

            return ( *this );
        }

        vec3& operator/=( const float t )
        {
            return ( *this *= ( 1 / t ) );
        }

        float length() const
        {
            return std::sqrt( length_squared() );
        }

        float length_squared() const
        {
            return ( e[0] * e[0] + e[1] * e[1] + e[2] * e[2] );
        }

        // TODO: move to util plz
        bool near_zero() const
        {
            // Return true if vector is close to zero in all dim
            const float s = 1e-8;
            return ( fabs( e[0] ) < s && fabs( e[1] ) < s && fabs( e[2] < s ) );
        }

    public:
        float e[3];
};

// Type aliases
using point3 = vec3;
using color = vec3;

// Utility functions
inline std::ostream& operator<<( std::ostream &out, const vec3 &v )
{
    return ( out << '<' << v.e[0] << ' ' << v.e[1] << ' ' << v.e[2] << '>' );
}

inline vec3 operator+( const vec3 &u, const vec3 &v )
{
    return ( vec3( u.e[0] + v.e[0], u.e[1] + v.e[1], u.e[2] + v.e[2] ) );
}

inline vec3 operator-( const vec3 &u, const vec3 &v )
{
    return ( vec3( u.e[0] - v.e[0], u.e[1] - v.e[1], u.e[2] - v.e[2] ) );
}

inline vec3 operator*( const vec3 &u, const vec3 &v )
{
    return ( vec3( u.e[0] * v.e[0], u.e[1] * v.e[1], u.e[2] * v.e[2] ) );
}

inline vec3 operator*( float t, const vec3 &v )
{
    return ( vec3( t * v.e[0], t * v.e[1], t * v.e[2] ) );
}

inline vec3 operator*( const vec3 &v, float t )
{
    return ( t * v );
}

inline vec3 operator/( const vec3 &v, float t )
{
    return ( ( 1 / t ) * v );
}

inline float dot( const vec3 &u, const vec3 &v )
{
    return ( u.e[0] * v.e[0] 
        + u.e[1] * v.e[1]
        + u.e[2] * v.e[2]
    );
}

inline vec3 cross( const vec3 &u, const vec3 &v )
{
    return ( vec3( 
            u.e[1] * v.e[2] - u.e[2] * v.e[1],
            u.e[2] * v.e[0] - u.e[0] * v.e[2],
            u.e[0] * v.e[1] - u.e[1] * v.e[0]
        ) 
    );
}

inline vec3 unit_vector( const vec3 &v )
{
    return ( v / v.length() );
}

vec3 reflect( const vec3 &v, const vec3 &n )
{
    return ( v - 2 * dot( v, n ) * n );
}

vec3 refract( const vec3 &uv, const vec3 &n, float eta_ratio )
{
    float cos_theta = fmin( dot( -uv, n ), 1.0 );
    vec3 r_perp = eta_ratio * ( uv + cos_theta * n );
    vec3 r_parallel = -std::sqrt( fabs( 1.0 - r_perp.length_squared() ) ) * n;

    return ( r_perp + r_parallel );
}

#endif

