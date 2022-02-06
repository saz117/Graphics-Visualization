#include "FittedPlane.h"


FittedPlane::FittedPlane(vec3 normal, float d, QString fileTextura) : Plane(normal, d, 1){//pasamos aux=1 al constructor de Plane, no se usa
    this->minpoint = vec3(0,0,0);//Valores por defecto, se establecen despues
    this->maxpoint = vec3(0,0,0);

    if(QString::compare("", fileTextura, Qt::CaseInsensitive) == 0){//No tiene textura
        auto mat = make_shared<Lambertian>(vec3(0.7, 0.4, 0.4));
        this->setMaterial(mat);
    }else{
        auto mat = make_shared<MaterialTextura>(fileTextura);
        this->setMaterial(mat);
    }
}

void FittedPlane::setMinMax(vec3 pmin, vec3 pmax){
    this->minpoint = pmin;
    this->maxpoint = pmax;
}

bool FittedPlane::hit(const Ray& r, float t_min, float t_max, HitInfo& info) const{

    if(Plane::hit(r,t_min,t_max, info)){
        if(info.p.x <= maxpoint.x && info.p.x >= minpoint.x && info.p.z <= maxpoint.z && info.p.z >= minpoint.z){
            vec2 uv;
            double h,w,x,z;
            vec3 point;

            //Obtenemos divisores para normalizar al intervalo (0,1) las (x,z)
            w = maxpoint.x-minpoint.x;
            h = maxpoint.z-minpoint.z;

            //Calculamos coordenadas (x,z) con origen en el cero, ya que pmin no tiene por que ser (0,0,0)
            //de la siguiente forma para los pmin y pmax, solo que el programa solamente lo necesita en el punto de intersec:
            //  new_p_min = vec2(0,0);//en realidad es minpoint.x-minpoint.x,minpoint.z-minpoint.z, que siempre sera 0,0
            //  new_p_max = vec2(maxpoint.x-minpoint.x,maxpoint.z-minpoint.z);
            //Y=0.0, por tanto no la consideramos
            point = r.pointAtParameter(info.t);
            x = point.x -minpoint.x;
            z = point.z -minpoint.z;

            uv = vec2(x/w,z/h);//Calculamos uv con coordenadas entre (0,1)x(0,1)

            info.uv = uv;

            return true;
        }
    }
    return false;
}

void FittedPlane::aplicaTG(shared_ptr<TG> t){
    if (dynamic_pointer_cast<shared_ptr<TranslateTG>>(t)) {
        //movemos el punt de paso del plano
        vec4 c(point, 1.0);
        c = t->getTG() * c;
        point.x = c.x; point.y = c.y; point.z = c.z;
    }
}
