#ifndef RAYDATA_CIRCLE_H
#define RAYDATA_CIRCLE_H

#include "math.h"
#include "Plane.h"
#include "Translate.h"

class Circle: public Plane {
public:
    Circle(vec3 normal, vec3 passPoint, float d);
    virtual ~Circle() override;
    virtual bool hit(const Ray& r, float t_min, float t_max, HitInfo& info ) const override;
    virtual void aplicaTG(shared_ptr<TG> tg) override;
    float getCenterY();
    void setCenterY(float center_y);
    vec3 center;

private:
    vec3 normal;
    float radius;
    double const EPSILON = 0.0000000000001;

};


#endif //RAYDATA_CIRCLE_H
