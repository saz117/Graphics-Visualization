#include "Ray.h"
#include "Hitable.h"
#include "Cylinder.h"
//#include "Circle.h"

/*
 * Constructor amb paramentres crea un cercle centrat en l'origen
 * amb radi i altura = 1
 */
Cylinder::Cylinder(vec3 center, float radius, float height):Object(height){
    this->center = center;
    this->radius = radius;
    this->height = height;
    this->n1 = vec3(0.0,1,0.0);//Vector normal de la tapa superior
    this->n2 = vec3(0.0,-1,0.0);//Vector normal de la tapa inferior, a on esta el centre, per al pla Y=0
    //tapes cilindre new Circle
    top1 = make_shared<Circle>(n1,vec3(this->center.x, this->center.y+height,this->center.z), this->radius);//Cercle de la tapa superior
    top2 = make_shared<Circle>(n2,this->center,this->radius);//Cercle de la tapa inferior

}

Cylinder::~Cylinder() {
  delete this;
}

bool Cylinder::hitCylinder(const Ray &r, float t_min, float t_max, HitInfo &info) const{
    float a = (r.dirVector().x * r.dirVector().x) + (r.dirVector().z * r.dirVector().z);
    float b = 2*(r.initialPoint().x*r.dirVector().x+r.initialPoint().z*r.dirVector().z);
    float c = (r.initialPoint().x*r.initialPoint().x)+(r.initialPoint().z*r.initialPoint().z)-1;
    float disc = b*b - 4*a*c;

    if ((a!=0) && (disc>=0)){
        float int1, int2, final=INFINITY;
        int1 = (-b+sqrt(disc))/2*a;
        int2 = (-b-sqrt(disc))/2*a;
        if(int1 <= int2 && int1 >= 0){final = int1;}
        if(int2 < int1 && int2 >= 0){final = int2;}

        if(final < t_max && final > t_min){
            vec3 inter = r.pointAtParameter(final);
            if((inter.y < (center.y+height)) && (inter.y > center.y)){
                info.t = final;
                info.p = r.pointAtParameter(info.t);
                info.normal = (info.p - center)/radius;
                info.mat_ptr = material.get();
                return true;
            }
        }
    }

    return false;
}

bool Cylinder::hit(const Ray& r, float t_min, float t_max, HitInfo& info) const {
    bool retorn = false;
    float intCylinder = INFINITY, intBase = INFINITY, intCorona = INFINITY;

    //CALCUL INTERSECCIÓ AMB CILINDRE (t_cilindre)
    if(hitCylinder(r,t_min,t_max,info)){
        intCylinder = info.t;
        retorn = true;
    }
    //CALCUL INTERSECCIÓ AMB TOP2 (t_top2)
    if(top2->hit(r,t_min,t_max,info)){
        intBase = info.t;
        retorn = true;
    }
    //CALCUL INTERSECCIÓ AMB TOP1 (t_top1)
    if(top1->hit(r,t_min,t_max,info)){
        intCorona = info.t;
        retorn = true;
    }
    if(retorn){
        if(intBase < intCylinder){
            intCylinder = intBase;
        }
        if(intCorona < intCylinder){
            intCylinder = intCorona;
        }

        info.t = intCylinder;
        info.p = r.pointAtParameter(info.t);
        info.normal = vec3(info.p.x,0,info.p.z);
        info.mat_ptr = material.get();
    }
    return retorn;
}

void Cylinder::trasladaTG(float x_new,float y_new, float z_new) {
    this->center = vec3(x_new,y_new,z_new);
    this->top2->center = vec3(x_new,y_new,z_new);
    this->top1->center = vec3(x_new,y_new+this->height,z_new);
}

void Cylinder::escalaTG(float c) {
    this->height = this->height*c;
    this->top1->setCenterY(this->top1->getCenterY()*c);
}


void Cylinder::aplicaTG(shared_ptr<TG> tg) {

}

float Cylinder::getRadius() const {
    return radius;
}

void Cylinder::setRadius(float radius) {
    Cylinder::radius = radius;
}

float Cylinder::getHeight() const {
    return height;
}

void Cylinder::setHeight(float height) {
    Cylinder::height = height;
}

void Cylinder::situar(float x_new, float z_new) {
    this->center = vec3(x_new,0.0,z_new);

    //canviem les tapes per al cilindre reescalat i situat
    //this->top1 = make_shared<Circle>(n1,vec3(this->center.x,this->center.y+this->height,this->center.z), this->radius);//Cercle de la tapa superior
    //this->top2 = make_shared<Circle>(n2,this->center,this->radius);//Cercle de la tapa inferior
}

void Cylinder::rescalar(float c) {
    this->height = c;
    this->radius = 1.0;//Tots tindran el mateix radi = 1
}
