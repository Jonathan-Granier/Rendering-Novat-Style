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
LIBS += -lGLEW -lglfw3 -lGL -lX11 -lXi -lXrandr -lXxf86vm -lXinerama -lXcursor -lrt -lm -pthread -ldl
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
    src/OpenGl/model.cpp \
    src/OpenGl/progressinfo.cpp \
    src/OpenGl/meshloader.cpp \
    src/OpenGl/texture.cpp \
    src/Light_Camera/light.cpp \
    src/Light_Camera/camera.cpp \
    src/Light_Camera/trackball.cpp \
    lib/glad.c \
    lib/stb_image.cpp \
    lib/glm_add.cpp \
    src/OpenGl/shadowmap.cpp


HEADERS += \
    src/MainWindow/mainwindow.h \
    src/MainWindow/viewer.h \
    src/OpenGl/shader.h \
    src/OpenGl/mesh.h \
    src/OpenGl/vertex.h \
    src/OpenGl/model.h \
    src/OpenGl/progressinfo.h \
    src/OpenGl/meshloader.h \
    src/OpenGl/texture.h \
    src/Light_Camera/light.h \
    src/Light_Camera/camera.h \
    src/Light_Camera/trackball.h \
    lib/stb_image.h \
    lib/glm_add.h \
    src/OpenGl/shadowmap.h

DISTFILES += \
    shaders/toon1D.frag \
    shaders/toon1D.vert \
    shaders/debug.vert \
    shaders/debug.frag \
    shaders/phong.frag \
    shaders/phong.vert \
    shaders/phongspec.frag \
    shaders/phongspec.vert \
    shaders/shadowmap.frag \
    shaders/shadowmap.vert \
    shaders/shadowmapdebug.frag \
    shaders/shadowmapdebug.vert
