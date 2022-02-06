#include "Geometry/Scene.h"

/**
 * @brief Scene::Scene
 */
Scene::Scene() {
    // Inicialització de la capsa minima
    capsaMinima.pmin = vec3(-1.0, -1.0,-1.0);
    capsaMinima.a = 2;
    capsaMinima.h = 2;
    capsaMinima.p = 2;
    lightAmbientGlobal = vec3(0.3, 0.3, 0.3);

    light = make_shared<Light>(Puntual, vec3(10,10,20), vec3(0.2, 0.2, 0.2), vec3(0.8, 0.8, 0.8),vec3(1.0, 1.0, 1.0), vec3(1.0, 1.0, 1.0));
    addLight(light);

    //light = make_shared<Light>(Puntual, vec3(-20,-20,10), vec3(0.2, 0.2, 0.2), vec3(0.8, 0.8, 0.8),vec3(1.0, 1.0, 1.0), vec3(1.0, 1.0, 1.0));
    //addLight(light);

    //light = make_shared<Light>(Direccional, vec3(10,10,20), vec3(0.2, 0.2, 0.2), vec3(0.2, 0.2, 0.2), vec3(0.8, 0.8, 0.8),vec3(1.0, 1.0, 1.0), vec3(1.0, 1.0, 1.0));
    //addLight(light);

    //light = make_shared<Light>(Direccional, vec3(-20,-20,10), vec3(0.2, 0.2, 0.2), vec3(0.2, 0.2, 0.2), vec3(0.8, 0.8, 0.8),vec3(1.0, 1.0, 1.0), vec3(1.0, 1.0, 1.0));
    //addLight(light);

    //light = make_shared<Light>(Spot, vec3(10,10,20), vec3(0.2, 0.2, 0.2), 45.0,vec3(0.2, 0.2, 0.2), vec3(0.8, 0.8, 0.8),vec3(1.0, 1.0, 1.0), vec3(1.0, 1.0, 1.0));
    //addLight(light);

}

/**
 * @brief Scene::~Scene
 */
Scene::~Scene() {
    objects.clear();
    lights.clear();
}

/**
 * @brief Scene::addObject
 * @param obj
 */
void Scene::addObject(shared_ptr<Object> obj) {
    objects.push_back(obj);
    calculCapsaMinCont3DEscena();
}

/**
 * @brief Scene::toGPU
 */
void Scene::toGPU(shared_ptr<QGLShaderProgram> p) {

    lightsToGPU(p);
    setAmbientGlobalToGPU(p);

    for(unsigned int i=0; i < objects.size(); i++){
        objects.at(i)->toGPU(p);
    }
}

/**
 * @brief Scene::draw
 */
void Scene::draw() {
    for(unsigned int i=0; i < objects.size(); i++){
        objects.at(i)->draw();
    }
}

/**
 * @brief Scene::drawTexture
 */
void Scene::drawTexture() {
    for(unsigned int i=0; i < objects.size(); i++){
        objects.at(i)->drawTexture();
    }
}

/**
 * @brief Scene::getLightActual
 * @return
 */
shared_ptr<Light> Scene::getLightActual() {
    // TO DO OPCIONAL: A modificar si es vol canviar el comportament de la GUI
    // Ara per ara dona com a Light actual la darrera que s'ha inserit
    return (lights[lights.size()-1]);
}

/**
 * @brief Scene::setLightActual
 * @param l
 */
void Scene::setLightActual(shared_ptr<Light> l){
    lights[lights.size()-1]=l;
}



/**
 * @brief Scene::lightsToGPU
 * @param program
 */
void Scene::lightsToGPU(shared_ptr<QGLShaderProgram> program){
// TO DO: A implementar a la fase 1 de la practica 2

    //para pasar el size y usarlo en la GPU
    numl = lights.size();

    GLuint numl2 = program->uniformLocation("numl");
    glUniform1i(numl2, this->numl);

    //para pasar el observador
    vec4 lookfrom = camera->origin;
    GLuint lookfromGPU = program->uniformLocation("lookfrom");
    glUniform4fv(lookfromGPU,1, lookfrom);

    //pasar luz ambient
    GLuint luzAmbientGLobal = program->uniformLocation("luzAmbientGlobal");
    glUniform3fv(luzAmbientGLobal,1, this->lightAmbientGlobal);

    struct gl_Light{

        GLuint diffuse;
        GLuint ambient;
        GLuint specular;
        GLuint lightType;
        GLuint origen;
        GLuint direction;
        GLuint spotLightAngle;
        GLuint atenuacion;
    };

    gl_Light gl_components[lights.size()];

    for(int i = 0; i < lights.size();i++){

        shared_ptr<Light> light = lights.at(i);

        gl_components[i].diffuse = program->uniformLocation(QString("conjunto[%1].diffuse").arg(i));
        gl_components[i].ambient = program->uniformLocation(QString("conjunto[%1].ambient").arg(i));
        gl_components[i].specular = program->uniformLocation(QString("conjunto[%1].specular").arg(i));
        gl_components[i].lightType = program->uniformLocation(QString("conjunto[%1].lightType").arg(i));
        gl_components[i].origen = program->uniformLocation(QString("conjunto[%1].origen").arg(i));
        gl_components[i].direction = program->uniformLocation(QString("conjunto[%1].direction").arg(i));
        gl_components[i].spotLightAngle = program->uniformLocation(QString("conjunto[%1].spotLightAngle").arg(i));
        gl_components[i].atenuacion = program->uniformLocation(QString("conjunto[%1].atenuacion").arg(i));

        glUniform3fv(gl_components[i].diffuse,1, light->getId());
        glUniform3fv(gl_components[i].ambient,1, light->getIa());
        glUniform3fv(gl_components[i].specular,1, light->getIs());
        glUniform1i(gl_components[i].lightType, light->getTipusLight()); //TODO da problemas si uso int y no LightType?
        glUniform4fv(gl_components[i].origen,1, light->getLightPosition());
        glUniform4fv(gl_components[i].direction,1, light->getLightDirection());
        glUniform1f(gl_components[i].spotLightAngle, light->getSpotLight());
        glUniform3fv(gl_components[i].atenuacion,1, light->getCoeficients());

    }

}

/**
 * @brief Scene::setAmbientGlobalToGPU
 * @param program
 */
void Scene::setAmbientGlobalToGPU(shared_ptr<QGLShaderProgram> program){
    //TODO revisar esto, tenemos de agregarlo tambien en el struct en vshader1
    GLuint luzAmbientGlobal = program->uniformLocation("luzAmbientGlobal");
    glUniform3fv(luzAmbientGlobal,1, lightAmbientGlobal);

}

void Scene::addLight(shared_ptr<Light> l) {
    lights.push_back(l);
}

/**
 * @brief Scene::setAmbientToGPU
 * @param program
 */
void Scene::setAmbientToGPU(shared_ptr<QGLShaderProgram> program){
    // TO DO: A implementar a la fase 1 de la practica 2
    //NOTA: agregue la funcion nueva mas arriba

}

/**
 * @brief Scene::setCamera
 * @param Camera *
 */
void Scene::setCamera(shared_ptr<Camera> c) {
    camera = c;
}
/**
 * @brief Scene::calculCapsaMinCont3DEscena
 */

void Scene::calculCapsaMinCont3DEscena()
{
    Capsa3D c;
    vec3 pmax;

    if (objects.size()==1) {
        capsaMinima = objects[0]->calculCapsa3D();
        pmax[0] = capsaMinima.pmin[0]+capsaMinima.a;
        pmax[1] = capsaMinima.pmin[1]+capsaMinima.h;
        pmax[2] = capsaMinima.pmin[2]+capsaMinima.p;
    } else {
        capsaMinima.pmin[0]=200;
        capsaMinima.pmin[1]=200;
        capsaMinima.pmin[2]=200;
        pmax[0] = -200;
        pmax[1] = -200;
        pmax[2] = -200;
    }

    for (unsigned int i=0; i<objects.size(); i++) {
       c = objects[i]->calculCapsa3D();

       if (capsaMinima.pmin[0]>c.pmin[0]) capsaMinima.pmin[0] = c.pmin[0];
       if (capsaMinima.pmin[1]>c.pmin[1]) capsaMinima.pmin[1] = c.pmin[1];
       if (capsaMinima.pmin[2]>c.pmin[2]) capsaMinima.pmin[2] = c.pmin[2];
       if (pmax[0]<c.pmin[0]+c.a) pmax[0] = c.pmin[0]+c.a;
       if (pmax[1]<c.pmin[1]+c.h) pmax[1] = c.pmin[1]+c.h;
       if (pmax[2]<c.pmin[2]+c.p) pmax[2] = c.pmin[2]+c.p;
    }
    capsaMinima.a = pmax[0]-capsaMinima.pmin[0];
    capsaMinima.h = pmax[1]-capsaMinima.pmin[1];
    capsaMinima.p = pmax[2]-capsaMinima.pmin[2];
}

void Scene::update(int nframe) {
    for (unsigned int i = 0; i< objects.size(); i++) {
        if (dynamic_pointer_cast<Animable>(objects[i]) ){
            objects[i]->update(nframe);
        }
    }
}

void Scene::setGround(vec3 normal, float d, QString fileTextura){
    this->ground = make_shared<Plane>();
    //groundNotNull = true;
}

