#ifndef TRANSPARENTE_H
#define TRANSPARENTE_H
#pragma once
#include <vector>
#include "Ray.h"
#include "Hitable.h"
#include "Material.h"

class Transparente: public Material
{
public:
    float refraccion;
    Transparente(const vec3& d, const vec3& a,const vec3& s, float sh, float re, float dmax);
    virtual bool scatter(const Ray& r_in, const HitInfo& rec, vec3& color, std::vector<Ray>& r_out) const override;
};

#endif // TRANSPARENTE_H
