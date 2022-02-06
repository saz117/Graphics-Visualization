#include "RealDataReader.h"
#include "Geometry\Scene.h"


RealDataReader::RealDataReader(shared_ptr<Scene> s)
{
    scene = s;
    numProp = 0;
}

void RealDataReader::readFile(QString fileName, shared_ptr<Mapping> map) {
    QFile file(fileName);

    mapping = map;

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
void RealDataReader::fileLineRead (QString lineReaded) {

    QStringList fields = lineReaded.split(",");
    if (QString::compare("data", fields[0], Qt::CaseInsensitive) == 0)
        dataFound(fields);
    else if (QString::compare("base", fields[0], Qt::CaseInsensitive) == 0)
        baseFound(fields);
    else if (QString::compare("prop", fields[0], Qt::CaseInsensitive) == 0)
        propFound(fields);
    else if (QString::compare("limits", fields[0], Qt::CaseInsensitive) == 0)
        limitsFound(fields);

    else
        std::cerr << "Element unknown" << std::endl;

}

void RealDataReader::dataFound(QStringList fields) {
    //data x z valor1 valor2...
    int n = mapping->getNumProps();
    //printf("n = %d\n",n);

    if (fields.size() != (3 + n)) {
        std::cerr << "Wrong data format" << std::endl;
        return;
    }

    for (int i=0; i<n; i++) {

        shared_ptr<Object> o;

        vec3 puntBase = vec3(fields[1].toDouble(), 0.0, fields[2].toDouble());

         // Construccio de l'objecte al Mon Virtual
        //aqui la Y es = 0
        o = ObjectFactory::getInstance().createObject_REAL(mapping->mapeigTraslacion(puntBase),
                                                       mapping->mapeigEscala(fields[3 + i].toDouble()), fields[3 + i].toDouble(),
                QString(),
                                                       mapping->getObjectTypeProp(i));

        // Construccio i assignacio del material
        o->setMaterial(mapping->mapeigMaterial(i, mapping->getColorMapProp(i), fields[3 + i].toDouble()));

        // Afegir objecte a l'escena
        scene->objects.push_back(o);
    }


}

    void RealDataReader::baseFound(QStringList fields) {
        //base plane nx ny nz d textura
        if (fields.size() != 7) {
            std::cerr << "Wrong base format" << std::endl;
            return;
        }

        //Creamos el ground
        if (QString::compare("plane", fields[1], Qt::CaseInsensitive) == 0) {
            scene->setGround(vec3(fields[2].toDouble(),fields[3].toDouble(),fields[4].toDouble()),fields[5].toDouble(),fields[6]);
        }
    }


    void RealDataReader::limitsFound(QStringList fields) {
        if (fields.size() != 5) {
            std::cerr << "Wrong limits format" << std::endl;
            return;
        }
        xmin = fields[1].toDouble();
        xmax = fields[2].toDouble();
        zmin= fields[3].toDouble();
        zmax = fields[4].toDouble();

    }

    void RealDataReader::propFound(QStringList fields) {
        if (fields.size() != 5) {
            std::cerr << "Wrong propietat format" << std::endl;
            return;
        }
        numProp++;

        cout<<fields[4].toStdString()<<endl;
        if (QString::compare("sphere", fields[4], Qt::CaseInsensitive) == 0) {
            props.push_back(ObjectFactory::OBJECT_TYPES::SPHERE);
            escalaSphere = fields[3].toDouble();
        }
        else if (QString::compare("triangle", fields[4], Qt::CaseInsensitive) == 0) {
            props.push_back(ObjectFactory::OBJECT_TYPES::TRIANGLE);
            escalaTriangle = fields[3].toDouble();
        }
        else if (QString::compare("cylinder", fields[4], Qt::CaseInsensitive) == 0) {
            props.push_back(ObjectFactory::OBJECT_TYPES::CYLINDER);
            escalaCylinder = fields[3].toDouble();
        }
        else if (QString::compare("brobject", fields[4], Qt::CaseInsensitive) == 0) {
            props.push_back(ObjectFactory::OBJECT_TYPES::BROBJECT);
            escalaBrObject = fields[3].toDouble();
        }
    }

