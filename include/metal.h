#ifndef METAL_H
#define METAL_H

#include "material.h"
#include "surface.h"
#include "util.h"
#include "vec3.h"

class metal : public material
{
    public:
        metal( const color &albedo, float fuzz ) : m_albedo( albedo ), m_fuzz( fuzz < 1 ? fuzz : 1 ) {}

        virtual bool scatter(
            const ray &r_in, const hit_record &record, color&attenuation, ray &scattered
        ) const override
        {
            vec3 reflected = reflect( unit_vector( r_in.direction() ), record.normal );
            scattered = ray( record.p, reflected + m_fuzz * random_vec3_in_unit_sphere() );
            attenuation = m_albedo;

            return ( dot( scattered.direction(), record.normal ) > 0 );
        }

    private:
        color m_albedo;
        float m_fuzz;
};

#endif

