#ifndef TRIANGLE2_H
#define TRIANGLE2_H

#include "Object.h"
#include "Plane.h"
#include "Animation.h"
#include "Translate.h"

class Triangle2: public Object {

    public:
    Triangle2(vec3 all_vectors[3], float data);
    virtual bool hit(const Ray &r, float t_min, float t_max, HitInfo &info) const override;
    virtual void aplicaTG(shared_ptr<TG> tg) override;

    private:

    vec3 puntoA;
    vec3 puntoB;
    vec3 puntoC;
};

#endif // TRIANGLE2_H
