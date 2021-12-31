#include "ray.h"

ray::ray() {}

ray::ray( const point3 &origin, const vector3f &direction ) : 
    m_origin( origin ), m_direction( direction ) {}

point3 ray::origin() const 
{
    return ( m_origin );
}

vector3f ray::direction() const
{
    return ( m_direction );
}

point3 ray::at( float t ) const
{
    return ( m_origin + t * direction() );
}
