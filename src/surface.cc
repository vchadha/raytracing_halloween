#include "surface.h"

void hit_record::set_face_normal( const ray &r, const vector3f &outward_normal )
{
    front_face = r.direction().dot( outward_normal ) < 0.0;
    normal = front_face ? outward_normal : -outward_normal;
}
