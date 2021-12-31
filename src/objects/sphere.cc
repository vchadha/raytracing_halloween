#include "objects/sphere.h"

sphere::sphere() {}

sphere::sphere( point3 center, float radius, std::shared_ptr<material> mat_ptr ) : 
    m_center( center ), m_radius( radius ), m_mat_ptr( mat_ptr ) {}

bool sphere::hit( const ray &r, float t_min, float t_max, hit_record &record ) const
{
    bool is_hit = false;

    vector3f oc = r.origin() - m_center;
    float a = r.direction().length_squared();
    float half_b = oc.dot( r.direction() );
    float c = oc.length_squared() - m_radius * m_radius;

    float discriminant = half_b * half_b - a * c;
    
    // We hit something
    if ( discriminant >=0 )
    {
        float discriminant_sqrt = std::sqrt( discriminant );

        // Find nearest root in range [tmin, tmax]
        float root = ( -half_b - discriminant_sqrt ) / a;
        if ( root < t_min || root > t_max )
        {
            // Try other root
            root = ( -half_b + discriminant_sqrt ) / a;
        }

        // If valid
        if ( root >= t_min && root <= t_max )
        {
            record.t = root;
            record.p = r.at( root );
            vector3f outward_normal = ( record.p - m_center ) / m_radius;
            record.set_face_normal( r, outward_normal );
            record.mat_ptr = m_mat_ptr;

            is_hit = true;
        }
    }

    return ( is_hit );
}
