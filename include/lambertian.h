#ifndef LAMBERTIAN_H
#define LAMBERTIAN_H

#include "material.h"
#include "surface.h"
#include "util.h"
#include "vec3.h"

class lambertian : public material
{
    public:
        lambertian( const color &albedo ) : m_albedo( albedo ) {}
        
        virtual bool scatter(
            const ray &r_in, const hit_record &record, color &attenuation, ray &scattered
        ) const override
        {
            UNUSED( r_in );
            vec3 scatter_direction = record.normal + random_unit_vector();

            // Catch degenerate scatter direction
            if ( scatter_direction.near_zero() )
            {
                scatter_direction = record.normal;
            }

            scattered = ray( record.p, scatter_direction );
            attenuation = m_albedo;

            return ( true );
        }

    private:
        color m_albedo;
};

#endif

