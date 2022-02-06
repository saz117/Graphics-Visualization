#include "VirtualWorldReader.h"


VirtualWorldReader::VirtualWorldReader(shared_ptr<Scene> s)
{
    scene = s;
}

void VirtualWorldReader::readFile(QString fileName, shared_ptr<Mapping> map) {

    mapping = map;
    std::cout << fileName.toStdString()<<std::endl;

    QFile file(fileName);

    if(!file.open(QIODevice::ReadOnly)) {
        std::cerr << "Error opening the file" << std::endl;
        return;
    }

    QTextStream in(&file);
    while(!in.atEnd()) {
        QString line = in.readLine();
        fileLineRead(line);
    }

    file.close();
}

// TODO: Fase 1: Cal afegir més tipus d'objectes
void VirtualWorldReader::fileLineRead (QString lineReaded) {
    QStringList fields = lineReaded.split(",");
    if (QString::compare("sphere", fields[0], Qt::CaseInsensitive) == 0)
        sphereFound(fields);
    else if (QString::compare("brobject", fields[0], Qt::CaseInsensitive) == 0)
        brObjectFound(fields);
    /*else if (QString::compare("triangle", fields[0], Qt::CaseInsensitive) == 0)
        triangleFound(fields);
    else if (QString::compare("plane", fields[0], Qt::CaseInsensitive) == 0)
        plaFound(fields);
    else if (QString::compare("cylinder", fields[0], Qt::CaseInsensitive) == 0)
        cylinderFound(fields);*/
    else
        std::cerr << "Element unknown" << std::endl;
}


void VirtualWorldReader::sphereFound(QStringList fields) {
    // En el fitxer de dades tindràs
    // sphere, centre.x, centre.y, centre.z, radi, propietats del material, textura
    // sphere, centro (3), radi(1), ambient (3), difus (3), especular (3), coef. esp (1)
    // POR AHORA SIN TEXTURA
    if (fields.size() != 15 ) {
        std::cerr << "Wrong sphere format" << std::endl;
        return;
    }

    QString filename = "://resources/models/sphere0.obj";
    vec3 centre = vec3(fields[1].toDouble(), fields[2].toDouble(), fields[3].toDouble());

    shared_ptr<Object> o;
    //CREACIÓN DEL OBJETO
    o = ObjectFactory::getInstance().createObject(mapping->mapeigPunt(centre),
                                                  mapping->mapeigValor(fields[4].toDouble()),
                                                  filename,
                                                  ObjectFactory::OBJECT_TYPES::SPHERE);
    //PONER MATERIAL
    vec3 ambient = vec3(fields[5].toDouble(),fields[6].toDouble(),fields[7].toDouble());
    vec3 difus = vec3(fields[8].toDouble(),fields[9].toDouble(),fields[10].toDouble());
    vec3 especular = vec3(fields[11].toDouble(),fields[12].toDouble(),fields[13].toDouble());
    auto mat = make_shared<Material>(ambient, difus, especular, fields[14].toDouble());
    o->setMaterial(mat);

    scene->addObject(o);
}

void VirtualWorldReader::brObjectFound(QStringList fields) {

    // TODO Fase 1: Per incloure BrObjecte
    //  Es suposa que serà una linia del fitxer de l'estil
    // brobject, centro (3), filename (1), ambient (3), difus (3), especular (3), coef. esp (1)
    // POR AHORA SIN TEXTURA
    if (fields.size() != 15 ) {
        std::cerr << "Wrong brObject format" << std::endl;
        return;
    }

    vec3 centre = vec3(fields[1].toDouble(), fields[2].toDouble(), fields[3].toDouble());
    //QString filename = fields[4];
    QString filename = QFileDialog::getOpenFileName();

    shared_ptr<Object> o;
    //CREACIÓN DEL OBJETO
    o = ObjectFactory::getInstance().createObject(mapping->mapeigPunt(centre),
                                                  -1.0f,
                                                  filename,
                                                  ObjectFactory::OBJECT_TYPES::BROBJECT);
    //PONER MATERIAL
    vec3 ambient = vec3(fields[5].toDouble(),fields[6].toDouble(),fields[7].toDouble());
    vec3 difus = vec3(fields[8].toDouble(),fields[9].toDouble(),fields[10].toDouble());
    vec3 especular = vec3(fields[11].toDouble(),fields[12].toDouble(),fields[13].toDouble());
    auto mat = make_shared<Material>(ambient, difus, especular, fields[14].toDouble());
    o->setMaterial(mat);

    scene->addObject(o);
}

/*void VirtualWorldReader::plaFound(QStringList fields) {
     // TODO Fase 1: Per incloure pla
    //Es suposa que tindràs una línia en el fitxer
    // plane, nx, ny, nz, d, propietats del material, textura
    if (fields.size() != 7) {
        std::cerr << "Wrong base format" << std::endl;
        return;
    }
    // TODO Fase 1: Donar d'alta el pla com objecte de l'escena. Fixa't en el codi del mètode sphereFound
    // TODO Fase 1: Cal fer un pla acotat i no un pla infinit. Les dimensions del pla acotat seran les dimensions de l'escena en x i z

    vec3 normalPlaBase = vec3(fields[1].toDouble(), fields[2].toDouble(), fields[3].toDouble());
    float dPlaBase = fields[4].toDouble();
    // TODO Fase 1: Crear el pla a l’escena
    // TODO Fase 4: llegir textura i afegir-la a l'objecte. Veure la classe Texture
}

// Exemple de cilindre segons enunciat
// cylinder, x, y, z, radi, alçada, material, textura
void VirtualWorldReader::cylinderFound(QStringList fields) {

    if (fields.size() != 18 ) {
        std::cerr << "Wrong cylinder format" << std::endl;
        return;
    }
    shared_ptr<Object> o;

    vec3 centre = vec3(fields[1].toDouble(), fields[2].toDouble(), fields[3].toDouble());
    vec3 empty[1];
    empty[0] = vec3(0,0,0); //AQUI PROBABLEMENTE SI USEMOS ESTE VECTOR DE VECTORES

    // Construccio de l'objecte al Mon Virtual
    o = ObjectFactory::getInstance().createObject(mapping->mapeigPunt(centre),
                                                   mapping->mapeigValor(fields[4].toDouble()),
                                                   -1.0f, empty,
                                                   QString(),
                                                   ObjectFactory::OBJECT_TYPES::CYLINDER);
    // Construccio i assignacio del material
    //NOTA: implementar para leer un parametro que indique si es lambertian o metal.

    // Afegir objecte a l'escena
    scene->objects.push_back(o);
}

void VirtualWorldReader::triangleFound(QStringList fields) {

    // TODO Fase 1: Per incloure Triangle
    //  Es suposa que serà una linia del fitxer de l'estil
    //  triangle, x1, y1, z1, x2, y2, z2, x3, y3, z3,, propietats del material, textura

    if (fields.size() != 23) { //13 porque son 3 vectores, y 3 elementos para RGB
        std::cerr << "Wrong triangle format" << std::endl;
    } else {
        shared_ptr<Object> o;

        vec3 all_vectors[3];
        vec3 puntoA = vec3(fields[1].toDouble(), fields[2].toDouble(), fields[3].toDouble());
        vec3 puntoB = vec3(fields[4].toDouble(), fields[5].toDouble(), fields[6].toDouble());
        vec3 puntoC = vec3(fields[7].toDouble(), fields[8].toDouble(), fields[9].toDouble());

        mapping ->mapeigPunt(puntoA);
        mapping ->mapeigPunt(puntoB);
        mapping ->mapeigPunt(puntoC);

        all_vectors[0] = puntoA;
        all_vectors[1] = puntoB;
        all_vectors[2] = puntoC; //falta hacer mapeig punt a los 3 mapping->mapeigPunt(puntA)

        //deberiamos hacer mapeig punt a todos, y luego pasar all_vectors
        // Construccio de l'objecte al Mon Virtual

        o = ObjectFactory::getInstance().createObject(vec3(0,0,0),
                                                      -1.0f,
                -1.0f, all_vectors, QString(),
                ObjectFactory::OBJECT_TYPES::TRIANGLE);//Aux i data no s'utilitzen, ni fields[0]

        // Construccio i assignacio del material

        // Afegir objecte a l'escena
        scene->objects.push_back(o);
    }

}*/
