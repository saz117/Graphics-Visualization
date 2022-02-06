#ifndef LIGHT_H
#define LIGHT_H

#include "Ray.h"

class Light
{
public:
    Light(vec3 punto, vec3 ambient, vec3 diffuse, vec3 specular, vec3 atenuacion);
    vec3 origen;
    vec3 diffuse;
    vec3 ambient;
    vec3 specular;
    float a,b,c;
};

#endif // LIGHT_H
