#ifndef vector3f_H
#define vector3f_H

#include <cmath>
#include <iostream>

class vector3f
{
    public:
        vector3f();
        vector3f( float e0, float e1, float e2 );

        float x() const;
        float y() const;
        float z() const;

        vector3f operator-() const;

        float operator[]( uint8_t i ) const;
        float& operator[]( uint8_t i );

        vector3f& operator+=( const vector3f &v );
        vector3f& operator*=( const float t );
        vector3f& operator/=( const float t );

        friend vector3f operator+( const vector3f &u, const vector3f &v );
        friend vector3f operator-( const vector3f &u, const vector3f &v );
        friend vector3f operator*( const vector3f &u, const vector3f &v );
        friend vector3f operator*( float t, const vector3f &v );
        friend vector3f operator*( const vector3f &v, float t );
        friend vector3f operator/( const vector3f &v, float t );

        float length() const;
        float length_squared() const;

        vector3f unit_vector();

        float dot( const vector3f &v ) const;
        vector3f cross( const vector3f &v ) const;

        friend std::ostream& operator<<( std::ostream &out, const vector3f &v );

    private:
        float e[3];
};

// Type aliases
using point3 = vector3f;
using color = vector3f;

#endif

