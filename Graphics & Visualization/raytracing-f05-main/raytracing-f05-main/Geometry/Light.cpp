#include "Light.h"

Light::Light(vec3 punto, vec3 ambient, vec3 diffuse, vec3 specular, vec3 atenuacion)
{

    this->origen = punto;
    //this->origen = punto; //lo leemos desde ConfigVista y lo pasamos a Light
    this->ambient = ambient;
    this->diffuse = diffuse;
    this->specular = specular;
    this->a = atenuacion.x;
    this->b = atenuacion.y;
    this->c = atenuacion.z;

    /*
    this->origen = vec3(2,8,10);
    this->ambient = vec3(0.3, 0.3, 0.3);
    this->diffuse = vec3(0.7, 0.7, 0.7);
    this->specular = vec3(1.0, 1.0, 1.0);
    this->atenuacion = 0.5;
    */

}
