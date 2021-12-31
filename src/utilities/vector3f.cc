#include "utilities/vector3f.h"

vector3f::vector3f() : e{0, 0, 0} {}

vector3f::vector3f( float e0, float e1, float e2 ): e{e0, e1, e2} {}

float vector3f::x() const
{
    return ( e[0] );
}

float vector3f::y() const
{
    return ( e[1] );
}

float vector3f::z() const
{
    return ( e[2] );
}

vector3f vector3f::operator-() const
{
    return ( vector3f( -e[0], -e[1], -e[2] ) );
}

float vector3f::operator[]( uint8_t i ) const
{
    return ( e[i] );
}

float& vector3f::operator[]( uint8_t i )
{
    return ( e[i] );
}

vector3f& vector3f::operator+=( const vector3f &v )
{
    e[0] += v.e[0];
    e[1] += v.e[1];
    e[2] += v.e[2];

    return ( *this );
}

vector3f& vector3f::operator*=( const float t )
{
    e[0] *= t;
    e[1] *= t;
    e[2] *= t;

    return ( *this );
}

vector3f& vector3f::operator/=( const float t )
{
    return ( *this *= ( 1 / t ) );
}

vector3f operator+( const vector3f &u, const vector3f &v )
{
    return ( vector3f( u.e[0] + v.e[0], u.e[1] + v.e[1], u.e[2] + v.e[2] ) );
}

vector3f operator-( const vector3f &u, const vector3f &v )
{
    return ( vector3f( u.e[0] - v.e[0], u.e[1] - v.e[1], u.e[2] - v.e[2] ) );
}

vector3f operator*( const vector3f &u, const vector3f &v )
{
    return ( vector3f( u.e[0] * v.e[0], u.e[1] * v.e[1], u.e[2] * v.e[2] ) );
}

vector3f operator*( float t, const vector3f &v )
{
    return ( vector3f( t * v.e[0], t * v.e[1], t * v.e[2] ) );
}

vector3f operator*( const vector3f &v, float t )
{
    return ( t * v );
}

vector3f operator/( const vector3f &v, float t )
{
    return ( ( 1 / t ) * v );
}

float vector3f::length() const
{
    return std::sqrt( length_squared() );
}

float vector3f::length_squared() const
{
    return ( e[0] * e[0] + e[1] * e[1] + e[2] * e[2] );
}

vector3f vector3f::unit_vector()
{
    return ( *this / this->length() );
}

float vector3f::dot( const vector3f &v ) const
{
    return ( e[0] * v.e[0] 
        + e[1] * v.e[1]
        + e[2] * v.e[2]
    );
}

vector3f vector3f::cross( const vector3f &v ) const
{
    return ( vector3f( 
            e[1] * v.e[2] - e[2] * v.e[1],
            e[2] * v.e[0] - e[0] * v.e[2],
            e[0] * v.e[1] - e[1] * v.e[0]
        ) 
    );
}

std::ostream& operator<<( std::ostream &out, const vector3f &v )
{
    return ( out << '<' << v.e[0] << ' ' << v.e[1] << ' ' << v.e[2] << '>' );
}
