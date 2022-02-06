#include "Circle.h"

Circle::Circle(vec3 normal, vec3 passPoint, float radius) : Plane(normal, passPoint, radius) {

  this->normal = normal;
  this->center = passPoint;
  this->radius = radius;

}

Circle::~Circle() {
  delete this;

}

bool Circle::hit(const Ray& r, float t_min, float t_max, HitInfo& info) const {
    if(Plane::hit(r,t_min,t_max,info)){
        vec3 punt = info.p-this->center;
        if(((punt.x*punt.x + punt.z*punt.z) <= this->radius) && ((punt.x + punt.z)>= 0.0f)){
            return true;
        }
    }
    return false;
}



void Circle::setCenterY(float center_y) {

  this->center.y = center_y;

}

float Circle::getCenterY() {

  return this->center.y;

}

void Circle::aplicaTG(shared_ptr<TG> t) {

  //desplaçar centre

  if (dynamic_pointer_cast<shared_ptr<TranslateTG>>(t)) {

    vec4 c(center, 1.0);
    c = t->getTG() * c;
    center.x = c.x;

    center.y = c.y;

    center.z = c.z;

  }

}
