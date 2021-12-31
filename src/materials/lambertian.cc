#include "materials/lambertian.h"
#include "utilities/util.h"

lambertian::lambertian( const color &albedo ) : m_albedo( albedo ) {}

bool lambertian::scatter(
    const ray &r_in,
    const hit_record &record,
    color &attenuation,
    ray &scattered
) const
{
    UNUSED( r_in );
    vector3f scatter_direction = record.normal + util::random_unit_vector();

    // Catch degenerate scatter direction
    if ( util::near_zero( scatter_direction ) )
    {
        scatter_direction = record.normal;
    }

    scattered = ray( record.p, scatter_direction );
    attenuation = m_albedo;

    return ( true );
}
