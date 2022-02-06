#include "SceneFactoryData.h"

SceneFactoryData::SceneFactoryData(shared_ptr<ConfigMappingReader> mr):SceneFactory()
{
    map = make_shared<Mapping>(mr);
}


shared_ptr<Scene>  SceneFactoryData::createScene(QString filename, shared_ptr<Camera> camera) {

    auto scene = make_shared<Scene>();
    scene->setCamera(camera);
    auto rdr = make_shared<RealDataReader>(scene);
    // TODO: Fase 1: construccio de l'escena dins de dataReader
    rdr->readFile(filename, map);
    return scene;
}

shared_ptr<Scene> SceneFactoryData::createScene(shared_ptr<Camera> camera) {
    auto scene= make_shared<Scene>();
    scene->setCamera(camera);
    //  TODO: Només si voleu provar manualment algunes dades posades
    //  hardcoded aqui
    /*shared_ptr<Plane> p = make_shared<Plane>(vec3(0.0,1.0,0.0),-0.5,1);

    // Afegir objecte a l'escena
    scene->objects.push_back(p);*/

    return scene;
}
