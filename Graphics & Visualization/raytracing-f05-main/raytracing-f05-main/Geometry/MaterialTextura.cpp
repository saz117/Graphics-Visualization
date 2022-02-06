#include "MaterialTextura.h"

MaterialTextura::MaterialTextura(QString fileTextura):Material(vec3(0.1,0.1,0.1),vec3(0.7,0.4,0.4),vec3(0.0,0.0,0.0),vec3(0.0,0.0,0.0),500.0,0.0)
{
    textura = make_shared<Texture>(fileTextura);

}

bool MaterialTextura::scatter(const Ray& r_in, const HitInfo& rec, vec3& color, vector<Ray>& r_out) const  {

    return false;
}

vec3 MaterialTextura::getDiffuse(vec2 uv) const {
    return textura->getColorPixel(uv);
}
