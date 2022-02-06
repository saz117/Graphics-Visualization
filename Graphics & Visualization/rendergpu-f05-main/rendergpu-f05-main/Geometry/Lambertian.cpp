/*#include "Lambertian.h"

Lambertian::Lambertian(const vec3& color): Material(vec3(0.1,0.1,0.1),color,vec3(0.0,0.0,0.0),vec3(0.0,0.0,0.0),500.0,0.0)
{

}

Lambertian::Lambertian(const vec3& d, const vec3& a,const vec3& s, float sh): Material(a,d,s,vec3(0.0,0.0,0.0),sh,0.0)
{

}

bool Lambertian::scatter(const Ray& r_in, const HitInfo& rec, vec3& color, std::vector<Ray>& r_out) const  {
    vec3 target = rec.p + rec.normal + this->RandomInSphere();
    r_out.push_back(Ray(rec.p, target-rec.p));
    color = diffuse;
    return true;
}
*/
