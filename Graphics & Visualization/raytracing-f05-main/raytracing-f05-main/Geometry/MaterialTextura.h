#ifndef MATERIALTEXTURA_H
#define MATERIALTEXTURA_H

#pragma once
#include <vector>
#include "Ray.h"
#include "Hitable.h"
#include "Material.h"
#include "Texture.h"

class MaterialTextura: public Material
{
public:

    shared_ptr<Texture> textura;

    MaterialTextura(QString fileTextura);

    virtual bool scatter(const Ray& r_in, const HitInfo& rec, vec3& color, vector<Ray>& r_out) const override;
    vec3 getDiffuse(vec2 uv) const override;
};

#endif // MATERIALTEXTURA_H
