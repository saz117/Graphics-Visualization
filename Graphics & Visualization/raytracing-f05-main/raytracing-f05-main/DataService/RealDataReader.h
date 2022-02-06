#pragma once


#include <QFile>
#include <QTextStream>
#include <iostream>
#include <sstream>
#include <QObject>
#include <QString>
#include <QStringList>
#include <vector>
#include "glm/glm.hpp"
#include "Geometry/Scene.h"
#include "GeometryBuilders/ObjectFactory.h"
#include "GeometryBuilders/Mapping.h"

class RealDataReader {
public:
    explicit RealDataReader();

    RealDataReader(shared_ptr<Scene> s);

    void readFile (QString fileName, shared_ptr<Mapping> map);

private:

    virtual void fileLineRead (QString lineReaded);

    shared_ptr<Scene> scene;
    shared_ptr<Mapping> mapping;

    void baseFound(QStringList list);

    void limitsFound(QStringList list);

    void propFound(QStringList list);

    void dataFound(QStringList list);

    int numProp;
    vector<ObjectFactory::OBJECT_TYPES> props;
    float xmin;
    float xmax;
    float zmin;
    float zmax;
    float escalaSphere;
    float escalaTriangle;
    float escalaCylinder;
    float escalaBrObject;

};
