#include "Triangle.h"

Triangle::Triangle(vec3 A, vec3 B,vec3 C, float data): Plane(cross(B - A,C - A), A, data)
{
    this->vertex[0] = A;
    this->vertex[1] = B;
    this->vertex[2] = C;
    normal = normalize(cross(B - A,C - A));
}

bool Triangle::hit(const Ray& raig, float t_min, float t_max, HitInfo& info) const {

        vec3 puntoA,puntoB,puntoC;

        puntoA=vertex[0];
        puntoB=vertex[1];
        puntoC=vertex[2];

        vec3 normal = normalize(cross(puntoB - puntoA,puntoC - puntoA));

        float umbral = dot(raig.dirVector(), normal);

        if(umbral != 0){

            float d = dot(puntoA, normal) * -1;

            float t = -(dot(normal,raig.initialPoint())+d)/dot(normal,raig.dirVector());

            vec3 I = raig.pointAtParameter(t);

            float s1=dot(cross((puntoB-puntoA),I-puntoA),normal);
            float s2=dot(cross((puntoC-puntoB),I-puntoB),normal);
            float s3=dot(cross((puntoA-puntoC),I-puntoC),normal);

            if((s1>0 && s2>0 && s3>0) || (s1<0 && s2<0 && s3<0)){
                if(t_min<t && t<t_max){
                    info.t = t;
                    info.p = I;
                    if(umbral < 0)
                        info.normal = normal;
                    else
                        info.normal = -normal;
                    info.mat_ptr = material.get();
                    return true;
                }
            }
        }

        return false; //false porque el rayo y el triangulo inician en el mismo lado, porque lo tengo en la cara.

}

void Triangle::aplicaTG(shared_ptr<TG> tg) {    
    vec4 v1(vertex[0], 1.0);
    vec4 v2(vertex[1], 1.0);
    vec4 v3(vertex[2], 1.0);

    if (dynamic_pointer_cast<TranslateTG>(tg)) {//desplacem vertexs

        v1 = tg->getTG() * v1;
        v2 = tg->getTG() * v2;
        v3 = tg->getTG() * v3;

        vertex[0].x = vertex[0].x; vertex[0].y = v1.y; vertex[0].z = v1.z;
        vertex[1].x = vertex[1].x; vertex[1].y = vertex[1].y; vertex[1].z = v2.z;
        vertex[2].x = vertex[2].x; vertex[2].y = v3.y; vertex[2].z = v3.z;

    }
}

void Triangle::setVertex(const vec3& vertex1, const vec3& vertex2, const vec3& vertex3) {
    this->vertex[0] = vertex1;
    this->vertex[1] = vertex2;
    this->vertex[2] = vertex3;
}

const vec3 *Triangle::getVertex() const {
    return vertex;
}

vec3 Triangle::getNormal() const {
    return this->normal;
}

void Triangle::setNormal(const vec3 &normal) {
    this->normal = normal;
}

vec3 Triangle::obteNormal() {

    return normalize(cross(this->vertex[1] - this->vertex[0],this->vertex[2] - this->vertex[0]));

}

float Triangle::getData1() const {
    return data;
}

void Triangle::setData(float data) {
    Triangle::data = data;
}

void Triangle::situar(float x_new, float z_new) {
    //Nota: this->vertex[1].x es la longitud del costat
    float costat = this->vertex[1].x;
    this->vertex[0] = vec3(x_new-costat/2.0,0,z_new);
    this->vertex[1] = vec3(x_new+costat/2.0,0,z_new);
    this->vertex[2] = vec3(x_new,0,z_new+costat);
}


void Triangle::rescalar(float c) {
    this->vertex[1] = vec3(this->vertex[1].x*c,this->vertex[1].y*c,this->vertex[1].z*c);
    this->vertex[2] = vec3(this->vertex[2].x*c,this->vertex[2].y*c,this->vertex[2].z*c);
}



