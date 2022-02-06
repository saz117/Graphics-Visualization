#include "Sphere.h"

/*Sphere::Sphere(vec3 cen, float r, float data, QString fileTextura) :Object(data) {
    center = cen;
    radius = r;

    if(QString::compare("", fileTextura, Qt::CaseInsensitive) == 0){//No tiene textura
        auto mat = make_shared<Lambertian>(vec3(0.7, 0.4, 0.4));
        this->setMaterial(mat);
        tieneTextura = false;
    }else{
        auto mat = make_shared<MaterialTextura>(fileTextura);
        this->setMaterial(mat);
        tieneTextura = true;
    }
}

bool Sphere::hit(const Ray& raig, float t_min, float t_max, HitInfo& info) const {
    vec3 oc = raig.initialPoint() - center;
    float a = dot(raig.dirVector(), raig.dirVector());
    float b = dot(oc, raig.dirVector());
    float c = dot(oc, oc) - radius*radius;
    float discriminant = b*b - a*c;
    if (discriminant > 0) {
        float temp = (-b - sqrt(discriminant))/a;
        if (temp < t_max && temp > t_min) {
            info.t = temp;
            info.p = raig.pointAtParameter(info.t);
            info.normal = (info.p - center) / radius;
            info.mat_ptr = material.get();

            if(tieneTextura){
                this->computeUV(info);
            }else{
                info.uv = vec2(-1,-1);
            }

            return true;
        }
        temp = (-b + sqrt(discriminant)) / a;
        if (temp < t_max && temp > t_min) {
            info.t = temp;
            info.p = raig.pointAtParameter(info.t);
            info.normal = (info.p - center) / radius;
            info.mat_ptr = material.get();

            if(tieneTextura){
                this->computeUV(info);
            }else{
                info.uv = vec2(-1,-1);
            }


            return true;
        }
    }
    return false;
}

void Sphere::computeUV(HitInfo& info) const {
    vec3 point_norm = (info.p -center)/radius;//Obtenemos coordenadas para centro de la esfera en (0,0,0)
    float u = 0.5 + atan2(point_norm.z,point_norm.x)/(2*3.141592653589793);//Si invertimos a una resta da la textura al reves
    float v = 0.5 + asin(point_norm.y)/(3.141592653589793);
    info.uv = vec2(u,v);
    //Falta comprobar el singo de la atan2 de la u para ver si es la textura normal o invertida
}*/

Sphere::Sphere(vec3 cen, float r, float data) :Object(data) {
    center = cen;
    radius = r;
}

bool Sphere::hit(const Ray& raig, float t_min, float t_max, HitInfo& info) const {
    vec3 oc = raig.initialPoint() - center;
    float a = dot(raig.dirVector(), raig.dirVector());
    float b = dot(oc, raig.dirVector());
    float c = dot(oc, oc) - radius*radius;
    float discriminant = b*b - a*c;
    if (discriminant > 0) {
        float temp = (-b - sqrt(discriminant))/a;
        if (temp < t_max && temp > t_min) {
            info.t = temp;
            info.p = raig.pointAtParameter(info.t);
            info.normal = (info.p - center) / radius;
            info.mat_ptr = material.get();

            return true;
        }
        temp = (-b + sqrt(discriminant)) / a;
        if (temp < t_max && temp > t_min) {
            info.t = temp;
            info.p = raig.pointAtParameter(info.t);
            info.normal = (info.p - center) / radius;
            info.mat_ptr = material.get();
            return true;
        }
    }
    return false;
}

void Sphere::aplicaTG(shared_ptr<TG> t) {
    if (dynamic_pointer_cast<TranslateTG>(t)) {
        // Per ara només es preveuen translacions
        vec4 c(center, 1.0);
        c = t->getTG() * c;
        center.x = c.x; center.y = c.y; center.z = c.z;
    }
    //hacer else de si es escalado, (radio por escala) en este caso
}

void Sphere::trasladaTG(float x_new,float y_new, float z_new) {
    this->center = vec3(x_new,y_new,z_new);
}

void Sphere::escalaTG(float c) {
    this->radius = this->radius*c;
}
