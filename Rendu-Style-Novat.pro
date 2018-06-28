#-------------------------------------------------
#
# Project created by QtCreator 2018-02-12T16:43:52
#
#-------------------------------------------------

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 5): QT += widgets

TARGET = Rendu-Style-Novat
TEMPLATE = app

CONFIG(release, release|debug) {
  OBJECTS_DIR = bin/release
  DESTDIR = bin/release
} else {
  OBJECTS_DIR = bin/debug
  DESTDIR = bin/debugz
}




# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

#LIBS += -lglfw3 -lGL -lX11 -lpthread -lXrandr -lXi -ldl
LIBS += -lGLEW -lglfw -lGL -lX11 -lXi -lXrandr -lXxf86vm -lXinerama -lXcursor -lrt -lm -pthread -ldl
# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0




SOURCES += \
    src/MainWindow/main.cpp \
    src/MainWindow/viewer.cpp \
    src/MainWindow/mainwindow.cpp \
    src/OpenGl/shader.cpp \
    src/OpenGl/mesh.cpp \
    src/OpenGl/vertex.cpp \
    src/OpenGl/meshloader.cpp \
    src/OpenGl/texture.cpp \
    src/Light_Camera/light.cpp \
    src/Light_Camera/camera.cpp \
    src/Light_Camera/trackball.cpp \
    lib/glad.c \
    lib/stb_image.cpp \
    lib/glm_add.cpp \
    src/OpenGl/loadtexture.cpp \
    src/OpenGl/generatedtexture.cpp \
    src/OpenGl/scene.cpp \
    src/OpenGl/heightmap.cpp \
    src/OpenGl/maps.cpp \
    src/OpenGl/caller.cpp \
    src/OpenGl/lighttextures.cpp


HEADERS += \
    src/MainWindow/mainwindow.h \
    src/MainWindow/viewer.h \
    src/OpenGl/shader.h \
    src/OpenGl/mesh.h \
    src/OpenGl/vertex.h \
    src/OpenGl/meshloader.h \
    src/OpenGl/texture.h \
    src/Light_Camera/light.h \
    src/Light_Camera/camera.h \
    src/Light_Camera/trackball.h \
    lib/stb_image.h \
    lib/glm_add.h \
    src/OpenGl/loadtexture.h \
    src/OpenGl/generatedtexture.h \
    src/OpenGl/scene.h \
    src/OpenGl/heightmap.h \
    src/OpenGl/maps.h \
    src/OpenGl/caller.h \
    src/OpenGl/lighttextures.h

DISTFILES += \
    shaders/debug.vert \
    shaders/debug.frag \
    shaders/phong.frag \
    shaders/phong.vert \
    shaders/phongspec.frag \
    shaders/phongspec.vert \
    shaders/shadowmap.frag \
    shaders/shadowmap.vert \
    shaders/curvature.vert \
    shaders/curvature.frag \
    shaders/drawtexture.frag \
    shaders/drawtexture.vert \
    shaders/curvaturecyril.frag \
    shaders/computelight.vert \
    shaders/computelight.frag \
    shaders/gaussBlur.frag \
    shaders/gaussBlur.vert \
    shaders/correctcurvature.frag \
    shaders/correctcurvature.vert \
    shaders/slant.frag \
    shaders/slant.vert \
    shaders/parallax.frag \
    shaders/parallax.vert \
    shaders/shadelight.vert \
    shaders/shadelight.frag \
    shaders/shadowlight.vert \
    shaders/shadowlight.frag \
    shaders/normalmap.vert \
    shaders/normalmap.frag \
    shaders/editheightmap.frag \
    shaders/editheightmap.vert \
    shaders/genheightmap.frag \
    shaders/genheightmap.vert \
    shaders/shading.frag \
    shaders/shading.vert \
    shaders/morpho.frag \
    shaders/morpho.vert \
    shaders/mergeshadow.frag \
    shaders/mergeshadow.vert

FORMS +=  src/MainWindow/mainwindow.ui
