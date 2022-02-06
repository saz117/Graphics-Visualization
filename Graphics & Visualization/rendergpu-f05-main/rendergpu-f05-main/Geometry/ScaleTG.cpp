#include "Geometry/ScaleTG.h"

ScaleTG::ScaleTG(vec3 scal): scalation(scal)
{
    //Find scale function in mat.h
    matTG = Scale(scal);
}

ScaleTG::~ScaleTG()
{

}
