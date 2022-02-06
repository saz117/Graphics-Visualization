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

out vec4 color;

struct Material{
    vec3 diffuse;
    vec3 ambient;
    vec3 specular;
    float shineness;
};

uniform Material material;

uniform int numl;

uniform vec4 lookfrom;

struct Light{
    vec3 diffuse;
    vec3 ambient;
    vec3 specular;
    int lightType;
    vec4 origen;
    vec4 direction;
    float spotLightAngle;
    //para la atenuacion
    vec3 atenuacion; //a,b,c
};

uniform Light conjunto[5];

//aparte
vec3 luzAmbientGlobal;

void main()
{
    vec4 L,V,H;
    float dist,atenuacion;
    vec3 ambient, diffuse, specular;
    float spotLightFactor = 1;

    gl_Position = projection*model_view*vPosition;
    gl_Position = gl_Position/gl_Position.w;
    //color = vColor;
    //color = vec4(0.0,0.0,0.0,1.0);
    color = vec4(luzAmbientGlobal, 1.0);

    vec4 n = normal; //revisar
    vec3 s;
    vec4 D;
    float spotAngle;

    for (int i=0; i < numl; i++){
        //gl tiene su libreria que permite usar normalize y otras funciones sin necesidad de include
        //todo-colocar un if-else aqui dependiendo de la luz.
        if(conjunto[i].lightType == 1) { //si es luz direccional
            //en la luz direccional hay que invertir la posicion de la luz
            L = normalize(conjunto[i].direction * (-1));

        }else if(conjunto[i].lightType == 2){ //si es luz spotlight
            L =  normalize(conjunto[i].direction -  vPosition);
            if(conjunto[i].spotLightAngle > 0.0){ //verificamos que efectivamente sea spotlight
                D = normalize(conjunto[i].direction);
                spotAngle = dot(D, L * -1);

                if(spotAngle >= conjunto[i].spotLightAngle){ //si esta dentro del spotLIght
                    //el 2 es un exponente que utilizo por defecto
                    spotLightFactor = pow(spotAngle, 2); //creamos un factor para multiplicar a los compoentes
                }
                else{ //si esta fuera del spotlight no hay color
                    color = vec4(0.0,0.0,0.0,0.0);
                     //y que ignore el calculo de BLinn-Phong
                }
            }

        }else{ //si es luz Puntual
            L = normalize(conjunto[i].origen - vPosition);

        }
        V = normalize(lookfrom - vPosition); //vector entre lookfrom y el punto actual
        H = normalize(L + V);

        dist = distance(conjunto[i].origen, vPosition); //distancia
        atenuacion = 1 / (conjunto[i].atenuacion[2] + conjunto[i].atenuacion[1]*dist + conjunto[i].atenuacion[0]*(dist * dist));
        if (atenuacion <= 1){
            atenuacion = 1;
        }else{
            atenuacion = atenuacion;
        }
        ambient = conjunto[i].ambient * material.ambient;
        diffuse = conjunto[i].diffuse * material.diffuse * max(dot(L, n), 0.0f);//m->getDiffuse(uv) * max(dot(L, n), 0.0f);
        specular = conjunto[i].specular * material.specular * vec3(pow(max(dot(n, H), 0.0f), material.shineness));

        ambient *= spotLightFactor;
        diffuse *= spotLightFactor;
        specular *= spotLightFactor;
        //s = ambient + (diffuse + specular) * atenuacion;
        //color = vec4(color.x + s.x, color.y + s.y, color.z + s.z, 1.0);
        color += vec4(ambient + (diffuse + specular) / atenuacion,1.0);
        //color += vec4(ambient + (diffuse + specular),1.0);
    }

}

