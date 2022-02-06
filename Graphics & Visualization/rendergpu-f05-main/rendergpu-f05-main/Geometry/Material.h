#pragma once

#include "library/Common.h"
#include <QGLShaderProgram>
#include <memory>


using namespace std;
// TO DO: A canviar a la fase 1 de la practica 2
// Classe que representa els materials d'un objecte
class Material {


public:
    Material(vec3 a, vec3 d, vec3 s, vec3 k, float beta);
    Material(vec3 a, vec3 d, vec3 s, float beta);

    void toGPU(shared_ptr<QGLShaderProgram> program);

    vec3 diffuse;
    vec3 ambient;
    vec3 specular;
    vec3 transparent;
    float shineness,dmax;
};

