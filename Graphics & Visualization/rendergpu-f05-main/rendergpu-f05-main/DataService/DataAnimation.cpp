#include "DataAnimation.h"

DataAnimation::DataAnimation(shared_ptr<Scene> s)
{
    scene = s;
}

void DataAnimation::config(shared_ptr<Mapping> map){
    mapping = map;
    construirEscena();
}

void DataAnimation::construirEscena(){
    QString filename = "://resources/models/sphere0.obj";
    vec3 centreSol = vec3(0.0);
    float dist = 10.0;
    vec3 centreTerra = vec3(dist, 0.0, 0.0);

    vec3 ambient = vec3(0.0,0.0,0.0);
    vec3 difusSol = vec3(1.0,0.0,0.0);
    vec3 difusTerra = vec3(0.0,0.0,1.0);
    vec3 especular = vec3(0.0,0.0,0.0);

    double radiSol = 3.0;
    double radiTerra = 1.0;

    shared_ptr<Object> sol, terra;

    sol = ObjectFactory::getInstance().createObject(mapping->mapeigPunt(centreSol),
                                                  mapping->mapeigValor(radiSol),
                                                  filename,
                                                  ObjectFactory::OBJECT_TYPES::SPHERE);

    terra = ObjectFactory::getInstance().createObject(mapping->mapeigPunt(centreTerra),
                                                  mapping->mapeigValor(radiTerra),
                                                  filename,
                                                  ObjectFactory::OBJECT_TYPES::SPHERE);

    auto matSol = make_shared<Material>(ambient, difusSol, especular, 1.0);
    auto matTerra = make_shared<Material>(ambient, difusTerra, especular, 1.0);
    sol->setMaterial(matSol);
    terra->setMaterial(matTerra);

    shared_ptr<Animation> animSol1 = make_shared<Animation>();
    shared_ptr<Animation> animSol2 = make_shared<Animation>();
    shared_ptr<Animation> animTerra = make_shared<Animation>();
    shared_ptr<Animation> animTerra2 = make_shared<Animation>();

    animTerra->transf =  make_shared<TranslateTG>(vec3(-0.15, 0.0, 0.0));
    animTerra->frameFinal = 58;
    terra->addAnimation(animTerra);
    animTerra2->transf =  make_shared<TranslateTG>(vec3(0.2, 0.0, 0.0));
    animTerra2->frameIni = 58;
    animTerra2->frameFinal = 100;
    terra->addAnimation(animTerra2);

    animSol1->transf =  make_shared<TranslateTG>(vec3(0.0, 0.0, 0.0));
    animSol2->transf =  make_shared<TranslateTG>(vec3(-0.15, 0.0, 0.0));
    animSol1->frameFinal = 58;
    animSol2->frameIni = 58;
    animSol2->frameFinal = 100;
    sol->addAnimation(animSol1);
    sol->addAnimation(animSol2);

    scene->addObject(sol);
    scene->addObject(terra);
}
