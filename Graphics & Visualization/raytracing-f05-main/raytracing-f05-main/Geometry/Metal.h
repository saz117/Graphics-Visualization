#ifndef METAL_H
#define METAL_H

#pragma once
#include <vector>
#include "Ray.h"
#include "Hitable.h"
#include "Material.h"

class Metal: public Material
{
public:
    Metal(const vec3& color);
    Metal(const vec3& d, const vec3& a,const vec3& s, float sh);
    virtual bool scatter(const Ray& r_in, const HitInfo& rec, vec3& color, vector<Ray>& r_out) const override;
};

#endif // METAL_H
