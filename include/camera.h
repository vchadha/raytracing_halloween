#ifndef CAMERA_H
#define CAMERA_H

#include "ray.h"
#include "util.h"

#include <cmath>

class camera
{
    public:
        // TODO: change from lookfrom lookat to direction vector
        camera(
            point3 lookfrom, 
            point3 lookat, 
            vec3 vup, 
            float vfov_deg, 
            float aspect_ratio,
            float aperture,
            float focus_dist
        )
        {
            float theta = deg2rad( vfov_deg );
            float h = tan( theta / 2.0 );

            float viewport_height = 2.0 * h;
            float viewport_width = aspect_ratio * viewport_height;

            w = unit_vector( lookfrom - lookat );
            u = unit_vector( cross( vup, w ) );
            v = cross( w, u );

            //   ^ +y
            //   | / -z
            //   |/
            //   |------> +x
            origin = lookfrom;
            horizontal = focus_dist * viewport_width * u;
            vertical = focus_dist * viewport_height * v;
            lower_left_corner = origin - horizontal / 2 - vertical / 2 - focus_dist * w;

            lens_radius = aperture / 2;
        }

        ray get_ray( float s, float t ) const
        {
            vec3 rd = lens_radius * random_vec3_in_unit_disc();
            vec3 offset = u * rd.x() + v * rd.y();

            ray r(
                origin + offset,
                lower_left_corner + s * horizontal + t * vertical - origin - offset
            );

            return ( r );
        }

    private:
        point3 origin;
        point3 lower_left_corner;
        
        vec3 horizontal;
        vec3 vertical;
        vec3 u, v, w;
        float lens_radius;
};

#endif

