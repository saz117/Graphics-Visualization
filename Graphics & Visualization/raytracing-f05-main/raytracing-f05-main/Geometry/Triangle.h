#ifndef RAYDATA_TRIANGLE_H
#define RAYDATA_TRIANGLE_H

#include "Plane.h"
#include "Translate.h"

class Triangle : public Plane {
private:
    vec3 vertex[3];
    vec3 normal;
    vec3 obteNormal();
    //EPSILON
    float const EPSILON = 0.001;

public:

    //Triangle(vec3 cord,float r, float d);
    Triangle(vec3 A,vec3 B, vec3 C, float data);


    virtual bool hit(const Ray &r, float t_min, float t_max, HitInfo &info) const override;

    virtual void aplicaTG(shared_ptr<TG> tg) override;

    vec3 getNormal() const;
    const vec3 *getVertex() const;

    void setNormal(const vec3 &normal);
    void setVertex(const vec3& vertex1, const vec3& vertex2, const vec3& vertex3);

    float getData1() const;

    void setData(float data);

    void situar(float x_new, float z_new);

    void rescalar(float c);
};


#endif //RAYDATA_TRIANGLE_H
