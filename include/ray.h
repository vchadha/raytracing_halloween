#ifndef RAY_H
#define RAY_H

#include "utilities/vector3f.h"

class ray
{
    public:
        ray();
        ray( const point3 &origin, const vector3f &direction );

        point3 origin() const;
        vector3f direction() const;

        point3 at( float t ) const;

    private:
        point3 m_origin;
        vector3f m_direction;
};

#endif

