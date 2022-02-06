#version 330

layout (location = 0) in vec4 vPosition;
layout (location = 1) in vec4 vColor;
layout (location = 2) in vec4 normal;
layout (location = 3) in vec2 vCoordTexture;

uniform mat4 model_view;
uniform mat4 projection;

out vec4 color;

struct Material{
    vec3 diffuse;
    vec3 ambient;
    vec3 specular;
    vec3 shineness;
};

uniform Material material;

uniform int numl;

struct Light{
    vec3 diffuse;
    vec3 ambient;
    vec3 specular;
    int lightType;
    vec4 origen;
    vec4 direction;
    vec4 spotLightAngle;
    //para la atenuacion
    vec3 atenuacion;
};

uniform Light conjunto[5];

//aparte
vec3 luzAmbientGlobal;

void main()
{
    gl_Position = projection*model_view*vPosition;
    gl_Position = gl_Position/gl_Position.w;
    color = vColor;
}

