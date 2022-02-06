#include "escala.h"

EscalaTG::EscalaTG(glm::vec3 escala): escalado(escala)
{
    matTG = glm::scale(glm::mat4(1.0f), escalado);
}

//NOTA: hacer otro para la esfera? que utilice float en lugar de vector.
