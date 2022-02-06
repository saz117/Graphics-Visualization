#include "GeometryBuilders/Builder.h"

Builder::Builder(GLWidget *glWid)
{
    glWidget = glWid;
    scene = glWidget->getScene();
    /*
    shared_ptr<Object> plane;
    plane = make_shared<Plane>();
    scene->addObject(plane);
    scene->camera->actualitzaCamera(scene->capsaMinima);
    emit newObj(plane);
    */

}

void Builder::newObjFromFile()
{
    QString fileName = QFileDialog::getOpenFileName();
    if (!fileName.isNull()) {
            auto obj = make_shared<Object>(1000000, fileName);
            scene->addObject(obj);
            scene->camera->actualitzaCamera(scene->capsaMinima);
            emit newObj(obj);
    }
}

void Builder::newVirtualScene() {
    // TO DO Fase 1: creació de la nova escena Virtual a partir d'un fitxer
    // de  a partir de les dades
    // del configMapping  i un fitxer .txt de tipus VIRTUALWORLD.
    // Nomes hi hauran fitxers de tipus BoundaryObject.
    // Usa el ConfigMappingReader i la teva SceneFactoryVirtual
    // per a construir l'escena tal i com feies a la practica 1
    QString fileName = QFileDialog::getOpenFileName(); //"://resources/escenes/mapMarino.txt";
    shared_ptr<ConfigMappingReader> mapping = make_shared<ConfigMappingReader>(fileName);
    auto factory = getFactory(mapping);

    QString dataFile = QFileDialog::getOpenFileName(); //"://resources/escenes/marino.txt";
    shared_ptr<Scene> scene;
    scene = factory->createScene(dataFile, this->scene->camera);
    scene->camera->actualitzaCamera(scene->capsaMinima);

    emit newScene(scene);
}

void Builder::newVirtualAnimation() {
    // Crea la escena on es veurà la animació creada, en cas de crear-ne vàries, es podria passar per fitxer controlant-ne els paràmetres
    QString fileName = "://resources/escenes/mapAnime.txt"; //QFileDialog::getOpenFileName();
    shared_ptr<ConfigMappingReader> mapping = make_shared<ConfigMappingReader>(fileName);
    auto factory = getFactory(mapping);

    shared_ptr<Scene> scene;
    scene = factory->createScene(this->scene->camera);
    //scene->capsaMinima.a*=10;
    //scene->capsaMinima.h*=10;
    //scene->capsaMinima.p*=10;
    scene->camera->actualitzaCamera(scene->capsaMinima);

    emit newScene(scene);
}

void Builder::newDataScene()
{
    // TO DO Fase 1: Crear la nova escena a partir de les dades
    // del configMapping i el fitxer .txt que conté les dades
    // Utilitza el ConfigMappingReader i la teva SceneFactoryData per a llegir els fitxers
    // i crear l'escena corresponent.

    // Opcionalment pots crear un dialeg per posar els valors del mapping

    //inicialitzem el ground

    /*if(mapping->plaBaseNotNull){
        scene->setGround(mapping->normalPlaBase,mapping->dPlaBase, mapping->fileTextura);
        scene->setGroundMinMax();//Una vez establecidos los limites en la escena, añadimos el pmin y pmax al fittedplane
    }*/

    emit newScene(scene);
}

shared_ptr<SceneFactory> Builder::getFactory(shared_ptr<ConfigMappingReader> cf) {

    if(cf->dataType == Scene::DATA_TYPES::VIRTUALWORLD)
    {
        return make_shared<SceneFactoryVirtual>(cf);
    }
    else if(cf->dataType == Scene::DATA_TYPES::REALDATA)
    {
        return make_shared<SceneFactoryData>(cf);
    }    
    else if(cf->dataType == Scene::DATA_TYPES::TEMPORALVW)
    {
        return make_shared<SceneFactoryVirtual>(cf);
    }

    //TO DO:  Afegir les factories de dades temporals en les animacions
    return nullptr;
}

