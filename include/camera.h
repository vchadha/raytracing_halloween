#ifndef CAMERA_H
#define CAMERA_H

#include "ray.h"
#include "util.h"

class camera
{
    public:
        camera()
        {
            float aspect_ratio = 16.0 / 9.0;
            float viewport_height = 2.0;
            float viewport_width = aspect_ratio * viewport_height;
            float focal_length = 1.0;

            //   ^ +y
            //   | / -z
            //   |/
            //   |------> +x
            origin = point3( 0, 0, 0 );
            horizontal = vec3( viewport_width, 0, 0 );
            vertical = vec3( 0, viewport_height, 0 );
            depth = vec3( 0, 0, focal_length );
            lower_left_corner = origin - ( horizontal / 2 ) - ( vertical / 2 ) - depth;
        }

        ray get_ray( float u, float v ) const
        {
            return ( ray( origin, lower_left_corner + u * horizontal + v * vertical - origin) );
        }

    private:
        point3 origin;
        point3 lower_left_corner;
        
        vec3 horizontal;
        vec3 vertical;
        vec3 depth;
};

#endif

