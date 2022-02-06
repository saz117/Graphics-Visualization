#version 330

in vec4 Position_v;
in vec4 Normal_v;
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
    vec4 spotLightAngle;
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

    //color = vec4(0.0,0.0,0.0,1.0);
    color = vec4(luzAmbientGlobal, 1.0);
    vec4 n = Normal_v;
    vec4 vPosition = Position_v;

    for (int i=0; i < numl; i++){
        //gl tiene su libreria que permite usar normalize y otras funciones sin necesidad de include
        //todo-colocar un if-else aqui dependiendo de la luz.
        if(conjunto[i].lightType == 1) { //si es luz direccional
            //en la luz direccional hay que invertir la posicion de la luz
            L = normalize(conjunto[i].direction * -1);

        }else if(conjunto[i].lightType == 2){ //si es luz spotlight
            L = normalize(conjunto[i].direction * -1);

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

        //color += vec4(ambient + (diffuse + specular),1.0);
        color += vec4(ambient + (diffuse + specular) / atenuacion,1.0);
    }

}
