#include "Metal.h"

Metal::Metal(const vec3& color): Material(vec3(0.1,0.1, 0.1),color,vec3(1.0,1.0,1.0),vec3(0.0,0.0,0.0),500,0.0)
{

}

Metal::Metal(const vec3& d, const vec3& a,const vec3& s, float sh): Material(a,d,s,vec3(0.0,0.0,0.0),sh,0.0)
{

}
bool Metal::scatter(const Ray& r_in, const HitInfo& rec, vec3& color, vector<Ray>& r_out) const  {

    vec3 v = reflect(normalize(rec.p - r_in.initialPoint()),rec.normal); //vector de reflexion
    vec3 p0 = rec.p + v; //punto de interseccion
    r_out.push_back(Ray(p0, v)); //rayo reflejado
    color = specular;
    return true;
}
