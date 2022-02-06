#version 330
#define PUNTUAL 0
#define DIRECCIONAL 0
#define SPOTLIGHT 2

layout (location = 0) in vec4 vPosition;
layout (location = 1) in vec4 vColor;
layout (location = 2) in vec4 normal;
layout (location = 3) in vec2 vCoordTexture;

uniform mat4 model_view;
uniform mat4 projection;

out float light_intensity;

uniform int numl;

uniform vec4 lookfrom;

struct Light{
    vec3 diffuse;
    vec3 ambient;
    vec3 specular;
    int lightType;
    vec4 origen;
    vec4 direction;
    vec4 spotLightAngle;
    //para la atenuacion
    vec3 atenuacion; //a,b,c
};

uniform Light conjunto[5];



void main()
{
    gl_Position = projection*model_view*vPosition;
    gl_Position = gl_Position/gl_Position.w;

    vec4 L,V,H;
    float dist,atenuacion;
    vec3 ambient, diffuse, specular;
    float spotLightFactor = 1;

    //color = vColor;
    vec4 color = vec4(0.0,0.0,0.0,1.0);
    //color = vec4(material.diffuse, 1.0);
    //color = vec4((conjunto[0].ambient.x)+0.8,(conjunto[0].ambient.y) +0.8,(conjunto[0].ambient.z)+0.8,1.0);
    vec4 n = normal; //revisar
    vec3 s;
    vec4 D ;
    float spotAngle;
    float light_intensity_acc = 0.0;

    L = normalize(conjunto[0].origen-vPosition);
    light_intensity = dot(n,L);

    /*for (int i=0; i < numl; i++){
        //gl tiene su libreria que permite usar normalize y otras funciones sin necesidad de include
        //todo-colocar un if-else aqui dependiendo de la luz.
        if(conjunto[i].lightType == 1) { //si es luz direccional
            //en la luz direccional hay que invertir la posicion de la luz
            L = normalize(conjunto[i].direction * (-1));
            light_intensity_acc += dot(n,L);

        }else if(conjunto[i].lightType == 2){ //si es luz spotlight
            L =  normalize(conjunto[i].direction -  vPosition);
            if(conjunto[i].spotLightAngle > 0.0){ //verificamos que efectivamente sea spotlight
                D = normalize(conjunto[i].direction);
                spotAngle = dot(D, L * -1);

                if(spotAngle >= conjunto[i].spotLightAngle){ //si esta dentro del spotLIght
                    //el 2 es un exponente que utilizo por defecto
                    spotLightFactor = pow(spotAngle, 2); //creamos un factor para multiplicar a los compoentes
                    light_intensity_acc += dot(n,L);
                }
                else{ //si esta fuera del spotlight no hay color
                    light_intensity_acc += 0.0;
                     //y que ignore el calculo de BLinn-Phong
                }
            }

        }else{ //si es luz Puntual
            L = normalize(conjunto[i].origen - vPosition);
            light_intensity_acc += dot(n,L);
        }
    }
    light_intensity = light_intensity_acc/numl;//Enviamos a fshader la media de las intensidades por si hay mas de una luz
    */
}

