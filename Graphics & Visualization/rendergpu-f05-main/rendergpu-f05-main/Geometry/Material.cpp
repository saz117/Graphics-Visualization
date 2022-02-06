#include "Geometry/Material.h"

//NOTA: los componentes son vec3 o vec4, si son vec4 hay que cambiar el toGPU Uniform4fv no 3fv

Material::Material(vec3 a, vec3 d, vec3 s, vec3 k, float beta) {

    diffuse = d; //componente difusa Kd
    ambient = a; //componente ambiente Ka
    specular = s; //componente specular Ks
    shineness = beta; //que es el componente alfa (shininess)
    transparent = k;
}

Material::Material(vec3 a, vec3 d, vec3 s, float beta) {

    diffuse = d; //componente difusa Kd
    ambient = a; //componente ambiente Ka
    specular = s; //componente specular Ks
    shineness = beta; //que es el componente alfa (shininess)
}

/**
 * Passa el material de CPU a GPU
 * @brief Material::toGPU
 * @param program
 */
void Material::toGPU(shared_ptr<QGLShaderProgram> program){

    struct{
        GLuint diffuse;
        GLuint ambient;
        GLuint specular;
        GLuint shineness;
    } propiedades;

    propiedades.diffuse = program->uniformLocation("material.diffuse");
    propiedades.ambient = program->uniformLocation("material.ambient");
    propiedades.specular = program->uniformLocation("material.specular");
    propiedades.shineness = program->uniformLocation("material.shineness");

    glUniform3fv(propiedades.diffuse,1, this->diffuse);
    glUniform3fv(propiedades.ambient,1, this->ambient);
    glUniform3fv(propiedades.specular,1, this->specular);
    glUniform1f(propiedades.shineness, this->shineness);

}

