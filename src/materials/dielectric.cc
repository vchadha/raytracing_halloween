#include "materials/dielectric.h"

#include <cmath>

dielectric::dielectric( float ior ) : m_ior( ior ) {}

bool dielectric::scatter(
    const ray &r_in,
    const hit_record &record,
    color &attenuation, 
    ray &scattered
) const
{
    attenuation = color( 1.0, 1.0, 1.0 );
    float refraction_ratio = record.front_face ? ( 1.0 / m_ior ) : m_ior;

    vector3f unit_direction = r_in.direction().unit_vector();
    float cos_theta = fmin( ( -unit_direction ).dot( record.normal ), 1.0 );
    float sin_theta = std::sqrt( 1.0 - cos_theta * cos_theta );

    bool cannot_refract = refraction_ratio * sin_theta > 1.0;
    vector3f direction;

    if ( cannot_refract || reflectance( cos_theta, refraction_ratio ) > util::random_float() )
    {
        direction = util::reflect( unit_direction, record.normal );
    }
    else
    {
        direction = util::refract( unit_direction, record.normal, refraction_ratio );
    }

    scattered = ray( record.p, direction );

    return ( true );
}

float dielectric::reflectance( float cos, float ref_idx )
{
    // Schlick's approximation for reflectance
    float r0 = ( 1.0 - ref_idx ) / ( 1.0 + ref_idx );
    r0 = r0 * r0;

    return ( r0 + ( 1 - r0 ) * pow( 1 - cos, 5 ) );
}
