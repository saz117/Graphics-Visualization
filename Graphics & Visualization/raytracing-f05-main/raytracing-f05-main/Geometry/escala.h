#ifndef ESCALA_H
#define ESCALA_H

#include "TG.h"

class EscalaTG : public TG
{
public:
    EscalaTG(glm::vec3 escala);
    glm::vec3 escalado;
};

#endif // ESCALA_H
