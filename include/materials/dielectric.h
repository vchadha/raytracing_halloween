#ifndef DIELECTRIC_H
#define DIELECTRIC_H

#include "materials/material.h"
#include "surface.h"
#include "ray.h"
#include "utilities/vector3f.h"

class dielectric : public material
{
    public:
        dielectric( float ior );

        virtual bool scatter(
            const ray &r_in,
            const hit_record &record,
            color &attenuation,
            ray &scattered
        ) const override;

    private:
        static float reflectance( float cos, float ref_idx );

    private:
        float m_ior;
};

#endif
