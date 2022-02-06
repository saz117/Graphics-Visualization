#ifndef DATAANIMATION_H
#define DATAANIMATION_H

#pragma once

#include <QObject>
#include <QString>
#include <QStringList>
#include <QFile>
#include <QTextStream>

#include <vector>
#include <iostream>
#include <sstream>

#include "Geometry/Scene.h"
#include "GeometryBuilders/ObjectFactory.h"
#include "GeometryBuilders/Mapping.h"


class DataAnimation
{
public:
    explicit DataAnimation();

    DataAnimation(shared_ptr<Scene> s);

    void config(shared_ptr<Mapping> map);

private:
    shared_ptr<Scene> scene;
    shared_ptr<Mapping> mapping;

    void construirEscena();
};

#endif // DATAANIMATION_H
