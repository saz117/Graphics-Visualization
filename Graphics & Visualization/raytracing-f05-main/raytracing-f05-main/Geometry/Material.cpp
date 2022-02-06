#include "Material.h"
#include "Texture.h"



Material::Material():
    diffuse(1.0f)
  {}

Material::~Material()
{}

Material::Material(vec3 d){
    diffuse = d;
}

Material::Material(vec3 a, vec3 d, vec3 s, vec3 k, float beta, float dmax){
    //tipo = 0 es Lambertian, tipo = 1 es metal
    // TO DO: Fase 2
    //propiedades que definen un material
    ///////////////////
    //NOTA: hacer el calculo aqui puede traer problemas si tenemos mas luces?!
    ///////////////////
    diffuse = d; //componente difusa Kd
    ambient = a; //componente ambiente Ka
    specular = s; //componente specular Ks
    shineness = beta; //que es el componente alfa (shininess)
    transparent = k;
    this->dmax=dmax;

    /*
    diffuse = d; //componente difusa Kd
    ambient = vec3(0.2,0.2, 0.2); //componente ambiente Ka
    specular = vec3(1.0, 1.0, 1.0); //componente specular Ks
    opacidad = 10; //que es el componente alfa (shininess)
    */

}

vec3 Material::RandomInSphere() const {
    vec3 p;
    do {
        p = 2.0f*vec3(double(rand())/RAND_MAX, double(rand())/RAND_MAX,double(rand())/RAND_MAX) - vec3(1,1,1);
    } while (glm::length(p) >=  1.0f);
    return p;
}

vec3 Material::getDiffuse(vec2 uv) const{
        return diffuse;//Para los Material que no hagan override de este metodo, se ejecutara este
}

