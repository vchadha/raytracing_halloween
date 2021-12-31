#ifndef SURFACES_H
#define SURFACES_H

#include "surface.h"

#include <memory>
#include <vector>

class surfaces : public surface
{
    public:
        surfaces();
        surfaces( std::shared_ptr<surface> object );

        void clear();
        void add( std::shared_ptr<surface> object );

        virtual bool hit(
            const ray &r, float t_min, float t_max, hit_record &record ) const override;

    private:
        std::vector<std::shared_ptr<surface>> objects;
};

#endif

