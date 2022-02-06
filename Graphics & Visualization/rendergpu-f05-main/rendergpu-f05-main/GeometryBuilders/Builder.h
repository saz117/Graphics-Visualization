#ifndef BUILDER_H
#define BUILDER_H

#include <QtWidgets>
#include <Renders/GLWidget.h>
#include "GeometryBuilders/SceneFactoryVirtual.h"
#include "GeometryBuilders/SceneFactoryData.h"
#include "GeometryBuilders/SceneFactory.h"


class Builder : public QObject {
        Q_OBJECT

    shared_ptr<Scene> scene;
    GLWidget *glWidget;

public:
    Builder(GLWidget *glWid);
    shared_ptr<SceneFactory> getFactory(shared_ptr<ConfigMappingReader> cf);

public slots:
    void newObjFromFile();
    void newVirtualScene();
    void newDataScene();
    void newVirtualAnimation();

signals:
    void newObj(shared_ptr<Object> o);
    void newScene(shared_ptr<Scene> sc);
};

#endif // BUILDER_H
