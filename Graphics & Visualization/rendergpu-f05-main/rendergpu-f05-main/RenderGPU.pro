QT       += core gui opengl

TARGET = RenderGPU
TEMPLATE = app

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    DataService/ConfigMappingReader.cpp \
    DataService/DataAnimation.cpp \
    DataService/ReadObj.cpp \
    DataService/RealDataReader.cpp \
    DataService/VirtualWorldReader.cpp \
    Geometry/Animation.cpp \
    Geometry/Cara.cpp \
    Geometry/ColorMapStatic.cpp \
    Geometry/Lambertian.cpp \
    Geometry/Light.cpp \
    Geometry/Material.cpp \
    Geometry/Object.cpp \
    Geometry/Plane.cpp \
    Geometry/ScaleTG.cpp \
    Geometry/Scene.cpp \
    Geometry/TG.cpp \
    Geometry/TranslateTG.cpp \
    Geometry/Transparente.cpp \
    GeometryBuilders/Builder.cpp \
    GeometryBuilders/Mapping.cpp \
    GeometryBuilders/ObjectFactory.cpp \
    GeometryBuilders/SceneFactory.cpp \
    GeometryBuilders/SceneFactoryData.cpp \
    GeometryBuilders/SceneFactoryVirtual.cpp \
    main.cpp \
    Renders/Camera.cpp \
    Renders/GLWidget.cpp \
    Renders/MainWindow.cpp \
    library/Common.cpp

HEADERS += \
    DataService/ConfigMappingReader.h \
    DataService/DataAnimation.h \
    DataService/ReadObj.h \
    DataService/RealDataReader.h \
    DataService/VirtualWorldReader.h \
    Geometry/Animation.h \
    Geometry/Cara.h \
    Geometry/ColorMap.h \
    Geometry/ColorMapStatic.h \
    Geometry/Lambertian.h \
    Geometry/Light.h \
    Geometry/Material.h \
    Geometry/Object.h \
    Geometry/Plane.h \
    Geometry/ScaleTG.h \
    Geometry/Scene.h \
    Geometry/TG.h \
    Geometry/TranslateTG.h \
    Geometry/Transparente.h \
    GeometryBuilders/Builder.h \
    GeometryBuilders/Mapping.h \
    GeometryBuilders/ObjectFactory.h \
    GeometryBuilders/SceneFactory.h \
    GeometryBuilders/SceneFactoryData.h \
    GeometryBuilders/SceneFactoryVirtual.h \
    IncludeWin32/GL/glut.h \
    Renders/Camera.h \
    Renders/GLWidget.h \
    Renders/MainWindow.h \
    library/Common.h \
    library/mat.h \
    library/vec.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc

DISTFILES += \
    libWin32/glut.dll \
    libWin32/glut.lib \
    libWin32/glut32.dll \
    libWin32/glut32.lib \
    modelsItextures/models/Monkey.mtl \
    modelsItextures/models/MonkeyTex.mtl \
    modelsItextures/models/README.fst \
    modelsItextures/models/common-cockle.mtl \
    modelsItextures/models/cruiser.mtl \
    modelsItextures/models/f16.mtl \
    modelsItextures/models/sphere0.mtl \
    modelsItextures/models/sphere1.mtl \
    modelsItextures/models/teapot2.mtl \
    modelsItextures/textures/2k_earth_clouds.jpg \
    modelsItextures/textures/2k_earth_daymap.jpg \
    modelsItextures/textures/2k_earth_nightmap.jpg \
    modelsItextures/textures/2k_earth_normal_map.tif \
    modelsItextures/textures/2k_earth_specular_map.tif \
    modelsItextures/textures/2k_jupiter.jpg \
    modelsItextures/textures/2k_mars.jpg \
    modelsItextures/textures/2k_mercury.jpg \
    modelsItextures/textures/2k_moon.jpg \
    modelsItextures/textures/2k_saturn.jpg \
    modelsItextures/textures/2k_stars+milky_way.jpg \
    modelsItextures/textures/2k_sun.jpg \
    modelsItextures/textures/2k_uranus.jpg \
    modelsItextures/textures/2k_venus_atmosphere.jpg \
    modelsItextures/textures/2k_venus_surface.jpg \
    modelsItextures/textures/F16s.bmp \
    modelsItextures/textures/F16t.bmp \
    modelsItextures/textures/MonkeyTex.png \
    modelsItextures/textures/basket_weave.bmp \
    modelsItextures/textures/bricks.bmp \
    modelsItextures/textures/bricks.png \
    modelsItextures/textures/capsule0.jpg \
    modelsItextures/textures/common-cockle.mtl \
    modelsItextures/textures/common-cockle_Diffuse.jpg \
    modelsItextures/textures/common-cockle_Normal.png \
    modelsItextures/textures/common-cockle_Roughness.png \
    modelsItextures/textures/common-cockle_Specularity.png \
    modelsItextures/textures/crack.bmp \
    modelsItextures/textures/cruiser.bmp \
    modelsItextures/textures/earth1.png \
    modelsItextures/textures/earth3.png \
    modelsItextures/textures/ennis.png \
    modelsItextures/textures/grace-new.png \
    modelsItextures/textures/head_diffuse.jpg \
    modelsItextures/textures/head_normals.jpg \
    modelsItextures/textures/head_specular.jpg \
    modelsItextures/textures/metal_crosshatch_pattern_6190173.JPG \
    modelsItextures/textures/skybox/back.jpg \
    modelsItextures/textures/skybox/bottom.jpg \
    modelsItextures/textures/skybox/front.jpg \
    modelsItextures/textures/skybox/left.jpg \
    modelsItextures/textures/skybox/right.jpg \
    modelsItextures/textures/skybox/top.jpg \
    modelsItextures/textures/uvtemplate.bmp \
    resources/vGouraudShader.glsl
