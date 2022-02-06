#pragma once


#include "Geometry/ColorMapStatic.h"
#include "DataService/RealDataReader.h"
#include "SceneFactory.h"
#include "Mapping.h"

class SceneFactoryData : public SceneFactory
{
public:
    SceneFactoryData(shared_ptr<ConfigMappingReader> mapping);
    virtual shared_ptr<Scene>  createScene(QString nomFitxer, shared_ptr<Camera> camera);
    virtual shared_ptr<Scene>  createScene(shared_ptr<Camera> camera);
};


