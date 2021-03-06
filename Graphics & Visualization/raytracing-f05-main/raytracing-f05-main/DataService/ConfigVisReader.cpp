#include "ConfigVisReader.h"



ConfigVisReader::ConfigVisReader(QString filename)
{
    readFile(filename);
}

RayTracingFactory::RENDER_TYPES ConfigVisReader::getRenderType() {
    return renderingType;
}


shared_ptr<Camera> ConfigVisReader::getCamera() {
    return(make_shared<Camera>(lookfrom, lookat, vup, vfov, aspect_ratio, width));
}

QString ConfigVisReader::getOutputFile() {
    return outputFile;
}

void ConfigVisReader::readFile(QString fileName) {
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


// TODO: Fase 2: Cal ampliar llegint les llums

void ConfigVisReader::fileLineRead (QString lineReaded) {

    QStringList fields = lineReaded.split(",");
    if (QString::compare("renderType", fields[0], Qt::CaseInsensitive) == 0)
        renderTypeFound(fields);
    else if (QString::compare("lookFrom", fields[0], Qt::CaseInsensitive) == 0)
        lookFromFound(fields);
    else if (QString::compare("lookAt", fields[0], Qt::CaseInsensitive) == 0)
        lookAtFound(fields);
    else if (QString::compare("vup", fields[0], Qt::CaseInsensitive) == 0)
        vupFound(fields);
    else if (QString::compare("vfov", fields[0], Qt::CaseInsensitive) == 0)
        vfovFound(fields);
    else if (QString::compare("aspectRatio", fields[0], Qt::CaseInsensitive) == 0)
        aspectRatioFound(fields);
    else if (QString::compare("pixelsX", fields[0], Qt::CaseInsensitive) == 0)
        widthFound(fields);
    else if (QString::compare("pixelsY", fields[0], Qt::CaseInsensitive) == 0)
        heightFound(fields);
    else if (QString::compare("output", fields[0], Qt::CaseInsensitive) == 0)
        fitxerFound(fields);
    else if (QString::compare("globalLight", fields[0], Qt::CaseInsensitive) == 0)
        globalLightFound(fields);
    else if (QString::compare("light", fields[0], Qt::CaseInsensitive) == 0)
        lightFound(fields);
    else
        std::cerr << "Element unknown" << std::endl;
}


void ConfigVisReader::renderTypeFound(QStringList fields) {
    //rendertype IMAGE, ONLINE, TEMPORAL
    if (fields.size() != 2) {
        std::cerr << "Wrong propietat format" << std::endl;
        return;
    }
    if (QString::compare("ONLINE", fields[1], Qt::CaseInsensitive) == 0)
        renderingType = RayTracingFactory::RENDER_TYPES::ONLINE;
    else if (QString::compare("IMAGE", fields[1], Qt::CaseInsensitive) == 0)
        renderingType = RayTracingFactory::RENDER_TYPES::IMAGE;
    else if (QString::compare("TEMPORAL", fields[1], Qt::CaseInsensitive) == 0)
        renderingType = RayTracingFactory::RENDER_TYPES::TEMPORAL;
    else std::cerr << "Error de sintaxi en el tipus de rendering" << std::endl;
}


void ConfigVisReader::lookFromFound(QStringList fields) {
    //lookFrom x, y, z
    if (fields.size() != 4) {
        std::cerr << "Wrong data format" << std::endl;
        return;
    }
    lookfrom = vec3(fields[1].toDouble(), fields[2].toDouble(), fields[3].toDouble());
}

void ConfigVisReader::lookAtFound(QStringList fields) {
    //lookAt x, y, z
    if (fields.size() != 4) {
        std::cerr << "Wrong data format" << std::endl;
        return;
    }
    lookat = vec3(fields[1].toDouble(), fields[2].toDouble(), fields[3].toDouble());
}

void ConfigVisReader::vupFound(QStringList fields) {
    //vup x, y, z
    if (fields.size() != 4) {
        std::cerr << "Wrong data format" << std::endl;
        return;
    }
    vup = vec3(fields[1].toDouble(), fields[2].toDouble(), fields[3].toDouble());
}

void ConfigVisReader::vfovFound(QStringList fields) {
    //vfov float
    if (fields.size() != 2) {
        std::cerr << "Wrong data format" << std::endl;
        return;
    }
    vfov = fields[1].toDouble();
}

void ConfigVisReader::aspectRatioFound(QStringList fields) {
    //aspectRatio float
    if (fields.size() != 2) {
        std::cerr << "Wrong data format" << std::endl;
        return;
    }
    aspect_ratio = fields[1].toDouble();
}

void ConfigVisReader::widthFound(QStringList fields) {
    //width integer in pixels(PixelsX)
    if (fields.size() != 2) {
        std::cerr << "Wrong data format" << std::endl;
        return;
    }
    width = fields[1].toInt();
}

void ConfigVisReader::heightFound(QStringList fields) {
    //height integer in pixels(PixelsY)
    if (fields.size() != 2) {
        std::cerr << "Wrong data format" << std::endl;
        return;
    }
    height = fields[1].toInt();
}

void ConfigVisReader::fitxerFound(QStringList fields) {
    //output nomFitxer
    if (fields.size() != 2) {
        std::cerr << "Wrong data format" << std::endl;
        return;
    }
    outputFile = fields[1];
}

void ConfigVisReader::globalLightFound(QStringList fields) {
    //output nomFitxer
    if (fields.size() != 4) {
        std::cerr << "Wrong data format" << std::endl;
        return;
    }
    globalLight = vec3(fields[1].toDouble(),fields[2].toDouble(),fields[3].toDouble());
}

void ConfigVisReader::lightFound(QStringList fields) {
    //output nomFitxer
    if (fields.size() != 17) {
        std::cerr << "Wrong data format" << std::endl;
        return;
    }

    if (QString::compare("POINTLIGHT", fields[1], Qt::CaseInsensitive) == 0){
        vec3 ambient = vec3(fields[2].toDouble(),fields[3].toDouble(),fields[4].toDouble());
        vec3 diffuse = vec3(fields[5].toDouble(),fields[6].toDouble(),fields[7].toDouble());
        vec3 specular = vec3(fields[8].toDouble(),fields[9].toDouble(),fields[10].toDouble());
        vec3 atenuacion = vec3(fields[11].toDouble(),fields[12].toDouble(),fields[13].toDouble());
        vec3 origen = vec3(fields[14].toDouble(),fields[15].toDouble(),fields[16].toDouble());
        luces.push_back(new Light(origen, ambient, diffuse, specular, atenuacion));
    }
}
