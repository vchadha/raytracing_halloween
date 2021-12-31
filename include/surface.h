#ifndef SURFACE_H
#define SURFACE_H

#include "materials/material.h"
#include "ray.h"
#include "utilities/vector3f.h"

#include <memory>

class material;

struct hit_record
{
    public:
        void set_face_normal( const ray &r, const vector3f &outward_normal );

    public:
        point3 p;
        vector3f normal;
        std::shared_ptr<material> mat_ptr;
        float t;
        bool front_face;
};

class surface
{
    public:
        virtual bool hit( const ray &r, float t_min, float t_max, hit_record &rec ) const = 0;
};

#endif

