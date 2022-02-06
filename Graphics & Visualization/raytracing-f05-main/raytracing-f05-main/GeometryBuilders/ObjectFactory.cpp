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
//ESTE ES PARA VIRTUA WORLD READER
shared_ptr<Object> ObjectFactory::createObject(vec3 v, double aux, float data, vec3 all_vectors[3], QString filename, OBJECT_TYPES t)
{
    //cuando es con datos reales:
    shared_ptr<Object> o;

    // TODO Fase 1:
    // Quan es creen els objectes cal que les coordenades
    // es mapegin a mon virtual aquí
    // TODO Fase 1:
    // Incloure diferents objectes: CILINDRES, TRIANGLES, BR_OBJECTES, PRISMES POLIGONALS
    switch (t) {
    case SPHERE: //colocar breakpoint aqui
        o = make_shared<Sphere>(v, aux, data); //poner en centro 000, y el aux sera 1(radio)

        break;
    case CYLINDER:
        o = make_shared<Cylinder>(v, 1.0, aux);
        break;
    case PLANE:
        o = make_shared<Plane>(v, aux, data);
        break;
    case TRIANGLE:
        //Considerem la creacio a una projeccio en el pla XZ, es a dir, y=v.y constant
        //Triangle de centre (x,y,z) de manera que aquest punt sigui el centre entre les coordenades del primer vertex i el segon, de tamany "aux"
        //Base i alcada = "aux"
        //o = make_shared<Triangle>(vec3(v.x-aux/2, v.y, v.z), vec3(v.x+aux/2, v.y, v.z), vec3(v.x, v.y, v.z+aux), data);

        o = make_shared<Triangle>(all_vectors[0],all_vectors[1], all_vectors[2], data);

        break;
    case BROBJECT:
        o = make_shared<BoundaryObject>(filename,data);
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
    case SPHERE: //colocar breakpoint aqui
        o = make_shared<Sphere>(vec3(0,0,0), 1, data); //poner en centro 000, y el aux sera 1(radio)
        dynamic_pointer_cast<Sphere>(o)->escalaTG(aux);
        dynamic_pointer_cast<Sphere>(o)->trasladaTG(v[0],v[1],v[2]);
        break;
    case CYLINDER: //colocar breakpoint aqui
        o = make_shared<Cylinder>(vec3(0,0,0), 1, 1); //poner en centro 000, y el aux sera 1(radio)
        dynamic_pointer_cast<Cylinder>(o)->escalaTG(aux);
        dynamic_pointer_cast<Cylinder>(o)->trasladaTG(v[0],v[1],v[2]);
        break;
    case PLANE:
        o = make_shared<Plane>(v, aux, data);
        break;
    case TRIANGLE:
        //Considerem la creacio a una projeccio en el pla XZ, es a dir, y=v.y constant
        //Triangle de centre (x,y,z) de manera que aquest punt sigui el centre entre les coordenades del primer vertex i el segon, de tamany "aux"
        //Base i alcada = "aux"

        o = make_shared<Triangle>(vec3(v.x-aux/2, v.y, v.z), vec3(v.x+aux/2, v.y, v.z), vec3(v.x, v.y, v.z+aux), data);

        break;
    case BROBJECT:
        o = make_shared<BoundaryObject>(filename,data);
        break;
    default:
        break;
    }

    //TO-DO llamar a aplicaTG?
    //llamar a escala y despues a traslacion
    //aplica tg escala y aplicatg translate

    return o;
}

