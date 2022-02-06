#pragma once


#include <vector>
#include "Ray.h"
#include "Hitable.h"
#include "Animation.h"
#include "Object.h"
#include "Sphere.h"
#include "BoundaryObject.h"
#include "Lambertian.h"
#include "ColorMap.h"
#include "Geometry\FittedPlane.h"
#include "Geometry\Light.h"
#include "Geometry\Material.h"
#include "Renders\Camera.h"

class Scene: public Hitable
{
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

    Scene();
    virtual ~Scene() {};

    // Funcio que calcula la interseccio del raig r amb l'escena. Guarda la informacio
    // del punt d'interseccio més proper a t_min, punt que està entre t_min i t_max.
    // Retorna cert si existeix la interseccio, fals, en cas contrari
    virtual bool hit(const Ray& raig, float t_min, float t_max, HitInfo& info) const;

    // Funcio recursiva que calcula el color. Inicialment es
    // es crida a cada pixel. Tambe es crida en calcular les ombres o les reflexions.
    vec3 ComputeColor (Ray &ray, int depth );

    vec3 BlinnPhong(vec3 p, vec3 n, Material* m, vec2 uv);
    vec3 Luces(vec3 p, vec3 n, Material* m, Light *l, vec2 uv);

    void update(int nframe);

    virtual void setDimensions(vec3 p1, vec3 p2);
    virtual void setGround(vec3 normal, float d, QString fileTextura);
    virtual void setGroundMinMax();
    virtual bool getGroundNotNull();
    virtual void setCamera(shared_ptr<Camera> camera);
    virtual void setLights(vector<Light*> llums, vec3 llum_global);

    // dimensions de l'escena virtual
    vec3 pmin, pmax;

    // Vector d'objectes continguts a l'escena
    std::vector<shared_ptr<Object>> objects;

    //ground
    shared_ptr<FittedPlane> ground;

    shared_ptr<Camera> camera;

    // TODO FASE 2: Afegir llums a l'escena
    vector<Light*> luces;

    vec3 luzAmbienteGlobal;
    //Light* llumPuntual;

    int const MAXDEPTH = 10;
    bool groundNotNull;

};
