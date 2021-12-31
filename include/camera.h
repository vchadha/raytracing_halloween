#ifndef CAMERA_H
#define CAMERA_H

#include "ray.h"
#include "utilities/vector3f.h"

class camera
{
    public:
        // TODO: change from lookfrom lookat to direction vector
        camera(
            point3 lookfrom, 
            point3 lookat, 
            vector3f vup, 
            float vfov_deg, 
            float aspect_ratio,
            float aperture,
            float focus_dist
        );

        ray get_ray( float s, float t ) const;

    private:
        point3 origin;
        point3 lower_left_corner;
        
        vector3f horizontal;
        vector3f vertical;
        vector3f u, v, w;
        float lens_radius;
};

#endif

