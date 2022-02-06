#ifndef RAYDATA_FITTEDPLANE_H
#define RAYDATA_FITTEDPLANE_H


#include "Ray.h"
#include "TG.h"
#include "Hitable.h"
#include "Plane.h"
#include <QString>
#include "MaterialTextura.h"

class FittedPlane: public Plane {
    public:
        FittedPlane(vec3 normal, float d, QString fileTextura);
        virtual void setMinMax(vec3 pmin, vec3 pmax);
        virtual ~FittedPlane(){}
        virtual bool hit(const Ray& r, float t_min, float t_max, HitInfo& info) const override;
        virtual void aplicaTG(shared_ptr<TG> t) override;

    private:
        vec3 normal;
        vec3 point;
        vec3 minpoint;
        vec3 maxpoint;

};


#endif //RAYDATA_FITTEDPLANE_H
