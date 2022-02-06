#include "Transparente.h"

Transparente::Transparente(const vec3& d, const vec3& a,const vec3& s, float sh, float re, float dmax): Material(a,d,s,vec3(1.0f,1.0f,1.0f)-s,sh,dmax)
{
    this->refraccion = re;
}
bool Transparente::scatter(const Ray& r_in, const HitInfo& rec, vec3& color, std::vector<Ray>& r_out) const  {    
    vec3 N = normalize(rec.normal);//Normal a la intersecció
    vec3 V = normalize(r_in.dirVector());//Vector del raig incident
    float cos = dot(N,V);//Cos de la Normal i el raig incident
    float snell = 1.0f/refraccion;// medi2 / medi1
    vec3 p0 = rec.p;//punt d'intersecció
    //Entrando o saliendo?
    if(cos > 0.001){//Contrari
        N = -N;
        snell = 1.f/snell;
    }
    vec3 v_refract = refract(V,N,snell);// vector refractat normalitzat
    //r_out = Ray(p0,v_refract);//raig refractat
    color = transparent;
    //Comprobació reflexió interna
    if(dot(v_refract,v_refract) < 0.001){//No hi ha refracció sinó reflexió
        vec3 v_reflect = reflect(V,N);//vector reflectit normalitzat
        r_out.push_back(Ray(p0,v_reflect));//raig reflectit
        color = specular;
    }else{
        r_out.push_back(Ray(p0,v_refract));
    }

    return true;
}
