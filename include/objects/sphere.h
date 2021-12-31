#ifndef SPHERE_H
#define SPHERE_H

#include "materials/material.h"
#include "surface.h"
#include "ray.h"
#include "utilities/vector3f.h"

#include <memory>

class sphere : public surface
{
    public:
        sphere();
        sphere( point3 center, float radius, std::shared_ptr<material> mat_ptr );

        virtual bool hit(
            const ray &r, float t_min, float t_max, hit_record &record ) const override;

        private:
            point3 m_center;
            float m_radius;
            std::shared_ptr<material> m_mat_ptr;
};

#endif
