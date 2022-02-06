#pragma once
#include <QString>
#include "Geometry/Object.h"
#include "Geometry/Sphere.h"
#include "Geometry/Plane.h"
#include "Geometry/Triangle.h"
#include "Geometry/triangle2.h"
#include "Geometry/Cylinder.h"
#include "Geometry/BoundaryObject.h"

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


    shared_ptr<Object> createObject(vec3 v, double aux, float data, vec3 all_vectors[3], QString filename, OBJECT_TYPES t);
    shared_ptr<Object> createObject_REAL(vec3 v, double aux, float data, QString filename, OBJECT_TYPES t);
    static shared_ptr<Object> getObject(const vec3& vertex,
            const vec3& vertexAux1,
            const vec3& vertexAux2,
            float aux,
            float data,
            QString fileName,
            OBJECT_TYPES t);
};
