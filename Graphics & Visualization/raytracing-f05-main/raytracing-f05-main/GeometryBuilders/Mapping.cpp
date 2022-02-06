#include "Mapping.h"

Mapping::Mapping(shared_ptr<ConfigMappingReader> mr)
{
   setup = mr;
}
//////////////

//cuando llamas de RealDataReader
vec3 Mapping::mapeigTraslacion(vec3 puntMonReal) {
    vec3 puntMonVirtual=puntMonReal;

    puntMonVirtual[0] = (puntMonReal[0] - getPunt_Rmin(0)) * (getPunt_Vmax(0) - getPunt_Vmin(0)) / (getPunt_Rmax(0) - getPunt_Rmin(0)) + getPunt_Vmin(0);
    puntMonVirtual[2] = -((puntMonReal[2] - getPunt_Rmin(2)) * (getPunt_Vmax(2) - getPunt_Vmin(2)) / (getPunt_Rmax(2) - getPunt_Rmin(2))+getPunt_Vmin(2));

    return puntMonVirtual;
}

float Mapping::mapeigEscala(float valorMonReal) {
    float valorMonVirtual;
    float A,B,a,b;

    A = getPropLimits(0);
    B = getPropLimits(1);
    a = 0.0;//Valor minimo del mundo virtual, probado que queda bien
    b = (getPunt_Vmax(0) - getPunt_Vmin(0))/30.0;//Valor maximo del mundo virtual, probado que queda bien. Juega con el tamaño del mapa para ser coherente

    /*
    A = 1925.0;//Valor minimo del fichero dataBCN
    B = 382703.0;//Valor maximo del fichero dataBCN
    a = 0.01;//Valor minimo del mundo virtual, probado que queda bien
    b = 0.1;//Valor maximo del mundo virtual, probado que queda bien
    */

    valorMonVirtual = (valorMonReal-A)*(b-a)/(B-A)+a;
    //return 0.03;
    return valorMonVirtual;
    //////////////
    //float dim = setup->Rxmax - setup->Rxmin, newdim = setup->Vxmax - setup->Vxmin;
    // Cal canviar la següent línia
    //valorMonVirtual = valorMonReal*newdim/dim;
    //////////////
    //valorMonVirtual = setup->Vxmax / setup->Rxmin;
    ////////////////////
    //valorMonVirtual = (valorMonReal - setup->propLimits[0].first) /(setup ->propLimits[0].second - setup->propLimits[0].first);
    //return valorMonVirtual = 0.03;
}
////////////////
//cuando llamas desde VirtualWorldReader

vec3 Mapping::mapeigPunt(vec3 puntMonReal) {
    // TO DO Fase 1:
    // Mapeig del punt en coordenades reals a coordenades de mon virtual
    vec3 puntMonVirtual=puntMonReal;


    for(int i=0;i<3;i++){
        float dim = getPunt_Rmax(i)-getPunt_Rmin(i), newdim = getPunt_Vmax(i)-getPunt_Vmin(i);
        if(dim!=0){
            puntMonVirtual[i]=(newdim/dim)*(puntMonReal[i]-getPunt_Rmin(i))+getPunt_Vmin(i);
        }else{
            puntMonVirtual[i]=getPunt_Vmin(i);
        }
    }



    return puntMonVirtual;
}

float Mapping::mapeigValor(float valorMonReal) {
    // TO DO Fase 1:
    // Mapeig del valor en dimensions reals a dimensions de mon virtual
   float valorMonVirtual = valorMonReal;

   float dim = setup->Rxmax - setup->Rxmin, newdim = setup->Vxmax - setup->Vxmin;
   // Cal canviar la següent línia
   valorMonVirtual = valorMonReal*newdim/dim;


   return valorMonVirtual;
}


float Mapping::getPunt_Rmin(int i){
    if(i == 0){ //estamos con la X
        return setup ->Rxmin;
    }
    else if(i == 2){ //estamos en Z
        return setup ->Rzmin;
    }
    else return setup ->Rymin; //estamos en Y, que no cambia, retornamos 1, para que no de error al dividir
}

float Mapping::getPunt_Rmax(int i){
    if(i == 0){ //estamos con la X
        return setup ->Rxmax;
    }
    else if(i == 2){ //estamos en Z
        return setup ->Rzmax;
    }
    else return setup ->Rymax;
}

float Mapping::getPunt_Vmin(int i){
    if(i == 0){ //estamos con la X
        return setup ->Vxmin;
    }
    else if(i == 2){ //estamos en Z
        return setup ->Vzmin;
    }
    else return setup -> Vymin;
}

float Mapping::getPunt_Vmax(int i){
    if(i == 0){ //estamos con la X
        return setup ->Vxmax;
    }
    else if(i == 2){ //estamos en Z
        return setup ->Vzmax;
    }
    else return setup -> Vymax;
}

double Mapping::getPropLimits(int i){
    if(i == 0){
        return setup->propLimits[0].first;
    }
    else if(i==1){
        return setup->propLimits[0].second;
    }else{
        return -1;
    }
}

shared_ptr<ColorMap> Mapping::getColorMap(ColorMapStatic::COLOR_MAP_TYPES tCM) {
   auto cm = make_shared<ColorMapStatic>(ColorMapStatic::COLOR_MAP_TYPE_PLASMA);
   return cm;
}

shared_ptr<Material> Mapping::mapeigMaterial(int i, ColorMapStatic::COLOR_MAP_TYPES tCM, double valorMonReal) {

    // TO DO Fase 2: Cal mapejar el color difus al color de la paleta o ColorMap segons el valorMonReal i
    // els valors minims i maxims de les propietats
    // Tens els valors minims i maxim de cada propietat a l'estructura de setup d'aquesta classe

    auto cm = getColorMap(tCM);
    int idx = int(255*(valorMonReal/(setup->propLimits[i].second-setup->propLimits[i].first)));

    return make_shared<Metal>(cm->getColor(idx));
}
