#include "materials/metal.h"
#include "utilities/util.h"

metal::metal( const color &albedo, float fuzz ) : 
    m_albedo( albedo ), m_fuzz( fuzz < 1 ? fuzz : 1 ) {}

bool metal::scatter(
    const ray &r_in,
    const hit_record &record,
    color&attenuation,
    ray &scattered
) const
{
    vector3f reflected = util::reflect( r_in.direction().unit_vector(), record.normal );
    scattered = ray( record.p, reflected + m_fuzz * util::random_vector3f_in_unit_sphere() );
    attenuation = m_albedo;

    return ( scattered.direction().dot( record.normal ) > 0 );
}
