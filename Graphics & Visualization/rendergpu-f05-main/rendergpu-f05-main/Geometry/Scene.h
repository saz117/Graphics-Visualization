#pragma once

#include <cmath>
#include <iostream>
#include <stdlib.h>

#include <list>
#include <vector>
#include <string>
#include <stdio.h>

#include <library/Common.h>
#include <library/vec.h>

#include <Geometry/Object.h>
#include <Geometry/Light.h>
#include <Renders/Camera.h>

using namespace std;
using namespace Common;

#include <Geometry/Plane.h>

// Scene: contains all objects, lights to visualize the scene
// the viewer is placed in the z+ axis

class Scene {

public:
    typedef enum
    {
           VIRTUALWORLD,
           REALDATA,
           TEMPORALVW,
           TEMPORALDATA
    } DATA_TYPES;

    typedef enum
    {
        MATERIAL,
        COLORMAP
    } MATERIAL_TYPES;

    vector<shared_ptr<Object>> objects;
    vector<shared_ptr<Light>>  lights;
    int numl;

    vec3    lightAmbientGlobal;
    shared_ptr<Light> light;

    shared_ptr<Camera> camera;
    // Capsa contenedora de l'escena
    Capsa3D capsaMinima;

    Scene();
    ~Scene();

    void   addObject(shared_ptr<Object> obj);
    void   addLight(shared_ptr<Light> l);
    shared_ptr<Light> getLightActual();
    void   setLightActual(shared_ptr<Light> l);

    void setCamera(shared_ptr<Camera> c);

    void toGPU(shared_ptr<QGLShaderProgram> p);
    void draw();
    void drawTexture();


    void lightsToGPU(shared_ptr<QGLShaderProgram> program);
    void setAmbientToGPU(shared_ptr<QGLShaderProgram> program);
    void setAmbientGlobalToGPU(shared_ptr<QGLShaderProgram> program);

    void calculCapsaMinCont3DEscena();
    void update(int nframe);
    virtual void setGround(vec3 normal, float d, QString fileTextura);

    //ground
    shared_ptr<Plane> ground;

};

