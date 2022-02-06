#ifndef SCALETG_H
#define SCALETG_H

#include "TG.h"

class ScaleTG : public TG
{
public:
    vec3 scalation;
    ScaleTG(vec3 scal);
    ~ScaleTG();
};

#endif // SCALETG_H
