#pragma once

#include <string.h>

#include "DataService/ConfigMappingReader.h"
#include "Geometry/ColorMap.h"
#include "Geometry/ColorMapStatic.h"
#include "Geometry/Material.h"
#include "GeometryBuilders/ObjectFactory.h"

#include <QString>

using namespace std;



class Mapping
{
public:

    Mapping();
    Mapping(const shared_ptr<ConfigMappingReader> configMapping);

    vec3  mapeigTraslacion(vec3 puntMonReal);
    float mapeigEscala(float valorMonReal);
    vec3  mapeigPunt(vec3 puntMonReal);
    float mapeigValor(float valorMonReal);
    float getPunt_Rmin(int i);
    float getPunt_Rmax(int i);
    float getPunt_Vmin(int i);
    float getPunt_Vmax(int i);
    double getPropLimits(int i);

    shared_ptr<Material> mapeigMaterial(int i, ColorMapStatic::ColorMapType tCM, double valorReal);

    int getNumProps() { return setup->numProp; };


    ObjectFactory::OBJECT_TYPES getObjectTypeProp(int i) {
        return setup->props[i].first;
    }

    ColorMapStatic::ColorMapType getColorMapProp(int i) {
        return setup->props[i].second;
    }

    shared_ptr<ColorMap> getColorMap(ColorMapStatic::ColorMapType tCM);


private:
    shared_ptr<ConfigMappingReader> setup;
};

