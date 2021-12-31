#include "surfaces.h"

surfaces::surfaces() {}

surfaces::surfaces( std::shared_ptr<surface> object )
{ 
    add( object );
}

void surfaces::clear()
{
    objects.clear();
}

void surfaces::add( std::shared_ptr<surface> object )
{
    objects.push_back( object );
}

bool surfaces::hit( const ray &r, float t_min, float t_max, hit_record &record ) const
{
    hit_record temp_record;
    bool hit_anything = false;
    float closest_hit = t_max;

    for ( const auto& object : objects )
    {
        if ( object->hit( r, t_min, closest_hit, temp_record ) )
        {
            hit_anything = true;
            closest_hit = temp_record.t;
            record = temp_record;
        }
    }

    return ( hit_anything );
}
