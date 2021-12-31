#ifndef LAMBERTIAN_H
#define LAMBERTIAN_H

#include "materials/material.h"
#include "surface.h"
#include "ray.h"
#include "utilities/vector3f.h"

class lambertian : public material
{
    public:
        lambertian( const color &albedo );
        
        virtual bool scatter(
            const ray &r_in,
            const hit_record &record,
            color &attenuation,
            ray &scattered
        ) const override;

    private:
        color m_albedo;
};

#endif

