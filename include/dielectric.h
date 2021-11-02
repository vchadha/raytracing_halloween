#ifndef DIELECTRIC_H
#define DIELECTRIC_H

#include "material.h"
#include "vec3.h"

#include <cmath>

class dielectric : public material
{
    public:
        dielectric( float ior ) : m_ior( ior ) {}

        virtual bool scatter(
            const ray &r_in, const hit_record &record, color &attenuation, ray &scattered
        ) const override
        {
            attenuation = color( 1.0, 1.0, 1.0 );
            float refraction_ratio = record.front_face ? ( 1.0 / m_ior ) : m_ior;

            vec3 unit_direction = unit_vector( r_in.direction() );
            float cos_theta = fmin( dot( -unit_direction, record.normal ), 1.0 );
            float sin_theta = std::sqrt( 1.0 - cos_theta * cos_theta );

            bool cannot_refract = refraction_ratio * sin_theta > 1.0;
            vec3 direction;

            if ( cannot_refract || reflectance( cos_theta, refraction_ratio ) > random_float() )
            {
                direction = reflect( unit_direction, record.normal );
            }
            else
            {
                direction = refract( unit_direction, record.normal, refraction_ratio );
            }

            scattered = ray( record.p, direction );

            return ( true );
        }
    
    private:
        static float reflectance( float cos, float ref_idx )
        {
            // Schlick's approximation for reflectance
            float r0 = ( 1.0 - ref_idx ) / ( 1.0 + ref_idx );
            r0 = r0 * r0;

            return ( r0 + ( 1 - r0 ) * pow( 1 - cos, 5 ) );
        }

    private:
        float m_ior;
};

#endif
