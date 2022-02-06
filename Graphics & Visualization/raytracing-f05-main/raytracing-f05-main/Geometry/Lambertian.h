#pragma once

#include "Material.h"

class Lambertian : public Material
{

public:
    Lambertian(const vec3& color);
    Lambertian(const vec3& d, const vec3& a,const vec3& s, float sh);

    virtual bool scatter(const Ray& r_in, const HitInfo& rec, vec3& color, std::vector<Ray>& r_out) const;
};
