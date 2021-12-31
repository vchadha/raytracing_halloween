#ifndef METAL_H
#define METAL_H

#include "materials/material.h"
#include "surface.h"
#include "ray.h"
#include "utilities/vector3f.h"

class metal : public material
{
    public:
        metal( const color &albedo, float fuzz );

        virtual bool scatter(
            const ray &r_in,
            const hit_record &record,
            color&attenuation,
            ray &scattered
        ) const override;

    private:
        color m_albedo;
        float m_fuzz;
};

#endif

