#include "triangle2.h"

Triangle2::Triangle2(vec3 all_vectors[3], float data) : Object(data)
{
    //cada punto es enrealidad un vec3
    puntoA = all_vectors[0];
    puntoB = all_vectors[1];
    puntoC = all_vectors[2];

}

bool Triangle2::hit(const Ray &r, float t_min, float t_max, HitInfo &info) const {

////////////////////////////////////////////////
    vec3 puntoA_B = puntoB - puntoA;
    vec3 puntoA_C = puntoC - puntoA;

    //prod vectorial p1p2 amb p1p
    vec3 normal = normalize(cross(puntoA_B, puntoA_C));

    bool hit = false;


    ///////////////////////////////////////////////////////
    return hit;
}

void Triangle2::aplicaTG(shared_ptr<TG> t) {

}

