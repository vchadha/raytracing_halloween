#include "camera.h"
#include "utilities/util.h"

#include <cmath>

camera::camera(
    point3 lookfrom, 
    point3 lookat, 
    vector3f vup, 
    float vfov_deg, 
    float aspect_ratio,
    float aperture,
    float focus_dist
)
{
    float theta = util::deg2rad( vfov_deg );
    float h = tan( theta / 2.0 );

    float viewport_height = 2.0 * h;
    float viewport_width = aspect_ratio * viewport_height;

    w = ( lookfrom - lookat ).unit_vector();
    u = vup.cross( w ).unit_vector();
    v = w.cross( u );

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

ray camera::get_ray( float s, float t ) const
{
    vector3f rd = lens_radius * util::random_vector3f_in_unit_disc();
    vector3f offset = u * rd.x() + v * rd.y();

    ray r(
        origin + offset,
        lower_left_corner + s * horizontal + t * vertical - origin - offset
    );

    return ( r );
}
