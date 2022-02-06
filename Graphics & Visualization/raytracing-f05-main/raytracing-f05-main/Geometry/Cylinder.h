#ifndef RAYDATA_CYLINDER_H
#define RAYDATA_CYLINDER_H

#include "math.h"
#include "Object.h"
#include "Circle.h"
#include "Translate.h"

class Cylinder : public Object{
private:
    vec3 center;
    float radius;
    float height;
    //tapa superior cilindre
    shared_ptr<Circle> top1;
    //tapa inferior cilindre
    shared_ptr<Circle> top2;
    //normal top1
    vec3 n1;
    //normal top2
    vec3 n2;
    //EPSILON
    double const EPSILON = 0.0000000000001;

public:
    //constructor amb parametres
    Cylinder(vec3 center, float radi, float height);

    virtual ~Cylinder() override;
    virtual bool hit(const Ray &r, float t_min, float t_max, HitInfo &info) const override;
    virtual bool hitCylinder(const Ray &r, float t_min, float t_max, HitInfo &info)const;
    virtual void aplicaTG(shared_ptr<TG> tg) override;
    void trasladaTG(float x_new, float y_new, float z_new);
    void escalaTG(float c);

    //obteNormal '

    /* getters and setters */
    float getRadius() const;
    void setRadius(float radius);
    float getHeight() const;
    void setHeight(float height);

    void situar(float x_new, float z_new);
    void rescalar(float c);

};

#endif //RAYDATA_CYLINDER_H
