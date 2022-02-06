#pragma once

#include <library/vec.h>
using namespace Common;

// Tipus de Lights
enum LightType {Puntual, Direccional, Spot};

// Classe que representa els atributs d'una Light
// TO DO: A la fase 1 has d'incloure els atributs necessaris per codificar una llum

class Light {
    public:
        Light(LightType l);
        //paso 3
        Light(LightType l,vec4 posicio, vec3 ambient, vec3 diffuse, vec3 specular, vec3 atenuacion); //luz puntual
        Light(LightType l,vec4 posicio,vec4 direction, vec3 ambient, vec3 diffuse, vec3 specular, vec3 atenuacion);//luz direccional
        Light(LightType l,vec4 posicio,vec4 direction, float angle, vec3 ambient, vec3 diffuse, vec3 specular, vec3 atenuacion);//spotlight

        LightType lightType;
        vec4 origen, direction;
        float spotLightAngle;
        vec3 diffuse, ambient, specular;
        float a,b,c; //para la atenuacion


        vec4 getLightPosition();
        void setLightPosition(vec4 v);

        vec4 getLightDirection();
        void setLightDirection(vec4 d);

        float getSpotLight();
        void setSpotLight(float angle);

        vec3 getIa() const;
        void setIa(const vec3 &value);

        vec3 getId();
        void setId(vec3 i);

        vec3 getIs() const;
        void setIs(const vec3 &value);

        vec3 getCoeficients() const;
        void setCoeficients(const vec3 &value);

        LightType getTipusLight() const;
        void setTipusLight(const LightType &value);
};

