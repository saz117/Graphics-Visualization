#pragma once

#include "Ray.h"


using namespace std;
class Material;


class HitInfo
{
public:
    float     t;         // t del raig on s'ha intersecat
    vec3      p;         // punt del raig on hi ha la intersecciÃ³
    vec3      normal;    // normal en el punt d'intersecciÃ³
    Material *mat_ptr;   // material de l'objecte que s'ha intersectat
    vec2      uv=vec2(-1,-1);//Coordenades (u,v) en (0,1)x(0,1) per a aplicar textura. negativas para materiales sin textura

    HitInfo():
        t(std::numeric_limits<float>::infinity()),
        p(0.0f),
        normal(0.0f),
        mat_ptr(NULL)
        {}

    //  "operator =" per la classe  IntersectionInfo
    HitInfo &operator =(const HitInfo &rhs) {
      p = rhs.p;
      mat_ptr = rhs.mat_ptr;
      normal = rhs.normal;
      t = rhs.t;
      return *this;
    }
};

class Hitable
{
public:
    Hitable();
    ~Hitable();
    // S'obliga a implementar-lo en les classes filles: es un metode abstracte
    virtual bool hit(const Ray& r, float t_min, float t_max, HitInfo& info) const = 0;
};

