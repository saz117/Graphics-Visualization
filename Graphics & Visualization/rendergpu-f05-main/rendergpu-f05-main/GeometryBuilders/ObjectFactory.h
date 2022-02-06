#pragma once
#include <QString>
#include <QtWidgets>
#include "Geometry/Object.h"
#include "Geometry/TranslateTG.h"
#include "Geometry/ScaleTG.h"

class ObjectFactory
{
    ObjectFactory(){};

public:
    enum  OBJECT_TYPES{
        SPHERE,
        PLANE,
        TRIANGLE,
        BROBJECT,
        CYLINDER
    };

    static ObjectFactory& getInstance() {
        static ObjectFactory instance;
        return instance;
    }


    shared_ptr<Object> createObject(vec3 v, double aux, QString filename, OBJECT_TYPES t);
    shared_ptr<Object> createObject_REAL(vec3 v, double aux, float data, QString filename, OBJECT_TYPES t);
    static shared_ptr<Object> getObject(const vec3& vertex,
            const vec3& vertexAux1,
            const vec3& vertexAux2,
            float aux,
            float data,
            QString fileName,
            OBJECT_TYPES t);
};
