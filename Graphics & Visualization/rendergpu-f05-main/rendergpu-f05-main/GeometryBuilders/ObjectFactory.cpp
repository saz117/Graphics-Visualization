#include "ObjectFactory.h"

//! createObject
/*!
  \sa testMe()
  \param v.x coordenada x on cal colocar el centre de l'objecte en el món virtual
  \param v.y coordenada x on cal colocar el centre de l'objecte en el món virtual.
  \param v.z coordenada x on cal colocar el centre de l'objecte en el món virtual.
  \param aux paràmetre addicional per codificar el radi de l'esfera o la d del pla.
  \param data valor d'escalaque cal aplicar a l'objecte
  \param t tipus d'objecte a construir: SPHERE, PLANE, ....
*/
//ESTE ES PARA VIRTUAL WORLD READER
shared_ptr<Object> ObjectFactory::createObject(vec3 v, double aux, QString filename, OBJECT_TYPES t)
{
    //cuando es con datos reales:
    shared_ptr<Object> o;
    o = make_shared<Object>(1000000, filename);
    // TODO Fase 1:
    // Quan es creen els objectes cal que les coordenades
    // es mapegin a mon virtual aquí
    // TODO Fase 1:
    // Incloure diferents objectes: CILINDRES, TRIANGLES, BR_OBJECTES, PRISMES POLIGONALS
    switch (t) {
    case SPHERE:
        o->aplicaTG(make_shared<ScaleTG>(vec3(aux)));
        o->aplicaTG(make_shared<TranslateTG>(v));
        break;
    case BROBJECT:
        o->aplicaTG(make_shared<TranslateTG>(v));
        break;
    default:
        break;
    }

    //TO-DO llamar a aplicaTG?
    //llamar a escala y despues a traslacion
    //aplica tg escala y aplicatg translate
    return o;
}

//ESTE ES PARA REAL DATA READER
shared_ptr<Object> ObjectFactory::createObject_REAL(vec3 v, double aux, float data, QString filename, OBJECT_TYPES t)
{
    //cuando es con datos reales:
    shared_ptr<Object> o;
    // TODO Fase 1:
    // Quan es creen els objectes cal que les coordenades
    // es mapegin a mon virtual aquí
    // TODO Fase 1:
    // Incloure diferents objectes: CILINDRES, TRIANGLES, BR_OBJECTES, PRISMES POLIGONALS
    switch (t) {

    case BROBJECT:
        o = make_shared<Object>(1000000,filename);
        break;
    default:
        break;
    }

    //TO-DO llamar a aplicaTG?
    //llamar a escala y despues a traslacion
    //aplica tg escala y aplicatg translate

    return o;
}
