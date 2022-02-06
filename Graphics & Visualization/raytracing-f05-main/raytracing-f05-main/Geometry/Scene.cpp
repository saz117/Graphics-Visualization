#include "Scene.h"
#include "FittedPlane.h"

Scene::Scene()
{
    pmin.x = -0.5f;  pmin.y = -0.5f; pmin.z = -0.5f;
    pmax.x = 0.5f;  pmax.y = 0.5f; pmax.z = 0.5f;

    //camera = new Camera(vec3(13,2,10),vec3(0,0,0),vec3(0, 1, 0),double(20),double(600/300),double(600));
    //Light *luz;

    //luz = new Light(vec3(2, 8, 10),vec3(0.3, 0.3, 0.3),vec3(0.7, 0.7, 0.7),vec3(1.0, 1.0, 1.0),vec3(0.01,0,0.5));
    //luces.push_back(luz);

    groundNotNull = false;

    //ground = new FittedPlane(vec3(0,1,0), -0.5, vec2(this->pmin.x,this->pmin.z), vec2(this->pmax.x, this->pmax.z),0.0f);
}


/*
** TODO: FASE 1: Metode que testeja la interseccio contra tots els objectes de l'escena
**
** Si un objecte es intersecat pel raig, el parametre  de tipus IntersectInfo conte
** la informació sobre la interesccio.
** El metode retorna true si algun objecte es intersecat o false en cas contrari.
**
*/
bool Scene::hit(const Ray& raig, float t_min, float t_max, HitInfo& info) const {
    // TODO FASE 0 i FASE 1: Heu de codificar la vostra solucio per aquest metode substituint el 'return true'
    // Una possible solucio es cridar el mètode intersection per a tots els objectes i quedar-se amb la interseccio
    // mes propera a l'observador, en el cas que n'hi hagi més d'una.
    // Cada vegada que s'intersecta un objecte s'ha d'actualitzar el IntersectionInfo del raig,
    // pero no en aquesta funcio.

    bool hitObject=false,hit=false;
    HitInfo minIntersection;



    float actualT = t_max;
    for(auto object: objects){
        hit = object->hit(raig,t_min,t_max,info);
        if(info.t < actualT){
            actualT = info.t;
            //t_max = actualT;
            minIntersection = info;
        }
        if(hit){
            hitObject = true;
        }
    }

    //Repetimos hit para el ground y comparamos
    if(groundNotNull==true){
        hit = ground->hit(raig,t_min,t_max,info);
        if(info.t < actualT){
            actualT = info.t;
            //t_max = actualT;
            minIntersection = info;
        }
        if(hit){
            hitObject = true;
        }
    }


    info = minIntersection;

    return hitObject;
}

/*
** TODO: Funcio ComputeColorRay es la funcio recursiva del RayTracing.
** TODO: FASE 0 per a fer el degradat del fons
** TODO: FASE 1 per a cridar a la intersecció amb l'escena i posar el color de l'objecte
** TODO: Fase 2 de l'enunciat per incloure Blinn-Phong  i ombres
** TODO: Fase 2 per a tractar reflexions i transparències
**
*/
vec3 Scene::ComputeColor (Ray &ray, int depth ) {
    vec3 color(0.0f);
    vec3 ray2;
    HitInfo info;

    ray2 = normalize(ray.direction);
    vec3 color1,color2;
    float k=0.5f*(1+ray2.y);
    color1=vec3(0,0.3,0.7);
    color2=vec3(0.5,0.5,0.5);

    if(hit(ray,0.01f,INFINITY,info)){
        color+= (1.0f-info.mat_ptr->transparent)*BlinnPhong(info.p,info.normal,info.mat_ptr, info.uv);
        vector<Ray> ray_scatter;
        vec3 newColor = vec3(0.0);
        if (MAXDEPTH > depth) {
            //a este nuevo color se le asigna el componente diffuse en scatter
            if (info.mat_ptr->scatter(ray, info, newColor, ray_scatter)) { //la de lambertian siempre retorna true
                color += newColor * ComputeColor(ray_scatter[0], depth+1);

            }
        }
        color+= luzAmbienteGlobal * info.mat_ptr->ambient;
    }else{
        color = k*color1+(1-k)*color2;
    }
    return color;
}

vec3 Scene::BlinnPhong(vec3 p, vec3 n, Material* m, vec2 uv){

    vec3 iluminacion;// = vec3(0.0f);

    for (Light *l: luces){
        iluminacion += Luces(p, n, m, l,uv);
    }

    return iluminacion;
}

vec3 Scene::Luces(vec3 p, vec3 n, Material *m, Light *l,vec2 uv){
    vec3 L = normalize(l->origen - p);//vector entre el orgiden de la luz y el punto actual
    vec3 V = normalize(camera->vistaCamara - p); //vector entre lookfrom y el punto actual
    vec3 H = normalize(L + V);

    Ray ray(p,L);
    HitInfo info,info2;
    float dist = distance(l->origen, p); //distancia
    float atenuacion = 1 / (l->c + l->b*dist + l->a*(dist * dist));
    vec3 ambient = l->ambient * m->ambient;
    vec3 diffuse = l->diffuse * m->getDiffuse(uv) * glm::max(dot(L, n), 0.0f);//m->getDiffuse(uv) * glm::max(dot(L, n), 0.0f);
    vec3 specular = l->specular * m->specular * vec3(pow(glm::max(dot(n, H), 0.0f), m->shineness));

    vec3 factorSombra=vec3(1.0f,1.0f,1.0f);
    if(hit(Ray(p,L),0.01f,dist,info)){
        factorSombra=factorSombra*vec3(0.0f,0.0f,0.0f);
        if(info.mat_ptr->transparent!=vec3(0.0f,0.0f,0.0f)){            
            vec3 primero=info.p;
            if(hit(Ray(primero,L),0.01f,dist,info2)){                
                //SOMBRA MÁS CLARITA
                float dista=distance(info2.p,primero);
                factorSombra+=vec3(1.0f,1.0f,1.0f)-dista/info.mat_ptr->dmax;
                //DESCOMENTAR PARA SOMBRA FUERTE PERO COLORIDA SEGÚN EL DIFFUSE
                /**/
                vec3 difuTrans = l->diffuse * info2.mat_ptr->diffuse;
                //vec3 difuSpecu = (1.0f-l->specular)*info2.mat_ptr->transparent;
                return ambient + difuTrans*factorSombra;//(difuTrans + difuSpecu) * factorSombra;
                /**/
            }
        }
    }

    return ambient + (diffuse + specular) * atenuacion * factorSombra;
}

void Scene::update(int nframe) {
    for (unsigned int i = 0; i< objects.size(); i++) {
        objects[i]->update(nframe);
    }
}

void Scene::setDimensions(vec3 p1, vec3 p2) {
    this->pmin = p1;
    this->pmax = p2;
}

void Scene::setGround(vec3 normal, float d, QString fileTextura){
    this->ground = make_shared<FittedPlane>(normal, d, fileTextura);
    groundNotNull = true;
}

void Scene::setGroundMinMax(){
    this->ground->setMinMax(pmin, pmax);
}

bool Scene::getGroundNotNull(){
    return this->groundNotNull;
}

void Scene::setCamera(shared_ptr<Camera> camera){
    //vec3 lookFrom, vec3 lookAt, vec3 vup, double vfov, int width, int height
    //camera = new Camera(lookFrom,lookAt,vup,vfov,double(width)/double(height),double(width));
    this->camera = camera;
}

void Scene::setLights(vector<Light*> llums, vec3 llum_global){
    this->luzAmbienteGlobal = llum_global;
    this->luces = llums;
}


