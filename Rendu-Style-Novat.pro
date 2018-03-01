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
  DESTDIR = bin/debug
}




# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

#LIBS += -lglfw3 -lGL -lX11 -lpthread -lXrandr -lXi -ldl
LIBS += -lGLEW -lglfw3 -lGL -lX11 -lXi -lXrandr -lXxf86vm -lXinerama -lXcursor -lrt -lm -pthread -ldl
# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0




SOURCES += \
    src/main.cpp \
    lib/glad.c \
    src/shader.cpp \
    src/viewer.cpp \
    lib/stb_image.cpp \
    lib/glm_add.cpp \
    src/mesh.cpp \
    src/vertex.cpp \
    src/model.cpp \
    src/camera.cpp \
    src/trackball.cpp \
    src/mainwindow.cpp \
    src/progressinfo.cpp \
    src/meshloader.cpp \
    src/texture.cpp


HEADERS += \
    src/shader.h \
    src/viewer.h \
    lib/stb_image.h \
    lib/glm_add.h \
    src/mesh.h \
    src/vertex.h \
    src/model.h \
    src/camera.h \
    src/trackball.h \
    src/mainwindow.h \
    src/progressinfo.h \
    src/meshloader.h \
    src/texture.h

DISTFILES += \
    shaders/fragmentshader.frag \
    shaders/vertexshader.vert
