#include "Geometry/Light.h"

/**
 * @brief Light::Light
 * @param t
 */
Light::Light(LightType t) {
    // TO DO: A canviar a la fase 1 de la practica 2

}

//paso 3
//luz puntual
Light::Light(LightType l,vec4 posicio, vec3 ambient, vec3 diffuse, vec3 specular, vec3 atenuacion){
    setTipusLight(l);
    setLightPosition(posicio);
    //this->origen = punto; //lo leemos desde ConfigVista y lo pasamos a Light
    setIa(ambient);
    setId(diffuse);
    setIs(specular);

    setCoeficients(atenuacion);
}

//luz direccional
Light::Light(LightType l,vec4 posicio,vec4 direction, vec3 ambient, vec3 diffuse, vec3 specular, vec3 atenuacion){
    setTipusLight(l);
    setLightPosition(posicio);
    setLightDirection(direction);
    //this->origen = punto; //lo leemos desde ConfigVista y lo pasamos a Light
    setIa(ambient);
    setId(diffuse);
    setIs(specular);

    setCoeficients(atenuacion);
}

//spotLight
Light::Light(LightType l,vec4 posicio,vec4 direction, float angle, vec3 ambient, vec3 diffuse, vec3 specular, vec3 atenuacion)
{
    setTipusLight(l);
    setLightPosition(posicio);
    setLightDirection(direction);
    setSpotLight(angle);
    //this->origen = punto; //lo leemos desde ConfigVista y lo pasamos a Light
    setIa(ambient);
    setId(diffuse);
    setIs(specular);

    setCoeficients(atenuacion);

}

/**
 * @brief Light::getDiffuseIntensity
 * @return
 */
vec3 Light::getId() {
    // TO DO: A canviar a la fase 1 de la practica 2
   //return(vec3(1.0, 1.0, 1.0));
    return this->diffuse;
}

/**
 * @brief Light::setId
 * @param i
 */
void Light::setId(vec3 i) {
    // TO DO: A canviar a la fase 1 de la practica 2
    this->diffuse = i;
}

/**
 * @brief Light::getLightPosition
 */
vec4 Light::getLightPosition() {
    // TO DO: A canviar a la fase 1 de la practica 2
    //return(vec4(0.0, 0.0, 0.0, 0.0));
    return this->origen;
}

/**
 * @brief Light::setLightPosition
 * @param v
 */
void Light::setLightPosition(vec4 v) {
    // TO DO: A canviar a la fase 1 de la practica 2
    this->origen = v;
}

// agregado
/**
 * @brief Light::getLightDirection
 */
vec4 Light::getLightDirection() {
    // TO DO: A canviar a la fase 1 de la practica 2
    //return(vec4(0.0, 0.0, 0.0, 0.0));
    return this->direction;
}
/**
 * @brief Light::setLightDirection
 * @param d
 */
void Light::setLightDirection(vec4 d) {
    // TO DO: A canviar a la fase 1 de la practica 2
    this->direction = d;
}

/**
 * @brief Light::getSpotLight
 */
float Light::getSpotLight() {
    // TO DO: A canviar a la fase 1 de la practica 2
    return this->spotLightAngle;
}

/**
 * @brief Light::setSpotLight
 * @param angle
 */
void Light::setSpotLight(float angle) {
    // TO DO: A canviar a la fase 1 de la practica 2
    this->spotLightAngle = angle * (2 * 3.1416)/360; //TODO-revisar si hace falta pasarlo de grado a un numero o como?
}
//agregado


/**
 * @brief Light::getIa
 * @return
 */
vec3 Light::getIa() const
{
    // TO DO: A canviar a la fase 1 de la practica 2
       //return(vec3(1.0, 1.0, 1.0));
    return this->ambient;
}

/**
 * @brief Light::setIa
 * @param value
 */
void Light::setIa(const vec3 &value)
{
    // TO DO: A canviar a la fase 1 de la practica 2
    this->ambient = value;

}

/**
 * @brief Light::getIs
 * @return
 */
vec3 Light::getIs() const
{
    // TO DO: A canviar a la fase 1 de la practica 2
       //return(vec3(1.0, 1.0, 1.0));
    return this->specular;
}

/**
 * @brief Light::setIs
 * @param value
 */
void Light::setIs(const vec3 &value)
{
    // TO DO: A canviar a la fase 1 de la practica 2
    this->specular = value;

}

/**
 * @brief Light::getCoeficients
 * @return
 */
vec3 Light::getCoeficients() const
{
    // TO DO: A canviar a la fase 1 de la practica 2
       //return(vec3(1.0, 1.0, 1.0));
    return(vec3(this->a, this->b, this->c));
}

/**
 * @brief Light::setCoeficients
 * @param value
 */
void Light::setCoeficients(const vec3 &value)
{
    // TO DO: A canviar a la fase 1 de la practica 2
    //la atenuacion
    this->a = value.x;
    this->b = value.y;
    this->c = value.z;
}


/**
 * @brief Light::getTipusLight
 *
 */
LightType Light::getTipusLight() const
{
    // TO DO: A canviar a la fase 1 de la practica 2
    //return Puntual;
    return this->lightType;
}

/**
 * @brief Light::setTipusLight
 * @param value
 */
void Light::setTipusLight(const LightType &value)
{
    // TO DO: A canviar a la fase 1 de la practica 2
    this->lightType = value;
}
