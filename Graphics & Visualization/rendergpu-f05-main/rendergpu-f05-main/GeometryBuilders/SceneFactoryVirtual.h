#pragma once

#include "DataService/VirtualWorldReader.h"
#include "DataService/DataAnimation.h"
#include "SceneFactory.h"
#include "Mapping.h"

class SceneFactoryVirtual : public SceneFactory
{
public:
    SceneFactoryVirtual(shared_ptr<ConfigMappingReader> mapping);

    virtual shared_ptr<Scene>  createScene(QString nomFitxer, shared_ptr<Camera> camera);
    virtual shared_ptr<Scene>  createScene(shared_ptr<Camera> camera);

private:
    void OneSphere(shared_ptr<Scene> s);
};


