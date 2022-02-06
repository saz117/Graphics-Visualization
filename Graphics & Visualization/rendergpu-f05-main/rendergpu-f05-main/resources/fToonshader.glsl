#version 330
#define PUNTUAL 0
#define DIRECCIONAL 0
#define SPOTLIGHT 2

out vec4 color;
in float light_intensity;

struct Material{
    vec3 diffuse;
    vec3 ambient;
    vec3 specular;
    float shineness;
};

uniform Material material;


void main()
{
    //segun la intensdidad
    if(light_intensity > 0.95){
        color = vec4((material.diffuse),1.0);
    }

    else if(light_intensity > 0.5 && light_intensity <= 0.95){
        color = vec4((material.diffuse * 0.75),1.0);
    }

    else if(light_intensity > 0.25 && light_intensity <= 0.5){
        color = vec4((material.diffuse * 0.5),1.0);
    }
    else{
        color = vec4((material.diffuse * 0.25),1.0);
    }

}
