#############################################################################
# Makefile for building: bin/debugz/Rendu-Style-Novat
# Generated by qmake (3.0) (Qt 5.7.1)
# Project:  Rendu-Style-Novat.pro
# Template: app
# Command: /usr/lib/x86_64-linux-gnu/qt5/bin/qmake -spec linux-g++-64 CONFIG+=debug CONFIG+=qml_debug -o Makefile Rendu-Style-Novat.pro
#############################################################################

MAKEFILE      = Makefile

####### Compiler, tools and options

CC            = gcc
CXX           = g++
DEFINES       = -DQT_DEPRECATED_WARNINGS -DQT_QML_DEBUG -DQT_OPENGL_LIB -DQT_WIDGETS_LIB -DQT_GUI_LIB -DQT_CORE_LIB
CFLAGS        = -m64 -pipe -g -Wall -W -D_REENTRANT -fPIC $(DEFINES)
CXXFLAGS      = -m64 -pipe -g -Wall -W -D_REENTRANT -fPIC $(DEFINES)
INCPATH       = -I. -isystem /usr/include/x86_64-linux-gnu/qt5 -isystem /usr/include/x86_64-linux-gnu/qt5/QtOpenGL -isystem /usr/include/x86_64-linux-gnu/qt5/QtWidgets -isystem /usr/include/x86_64-linux-gnu/qt5/QtGui -isystem /usr/include/x86_64-linux-gnu/qt5/QtCore -I. -I. -I/usr/lib/x86_64-linux-gnu/qt5/mkspecs/linux-g++-64
QMAKE         = /usr/lib/x86_64-linux-gnu/qt5/bin/qmake
DEL_FILE      = rm -f
CHK_DIR_EXISTS= test -d
MKDIR         = mkdir -p
COPY          = cp -f
COPY_FILE     = cp -f
COPY_DIR      = cp -f -R
INSTALL_FILE  = install -m 644 -p
INSTALL_PROGRAM = install -m 755 -p
INSTALL_DIR   = cp -f -R
DEL_FILE      = rm -f
SYMLINK       = ln -f -s
DEL_DIR       = rmdir
MOVE          = mv -f
TAR           = tar -cf
COMPRESS      = gzip -9f
DISTNAME      = Rendu-Style-Novat1.0.0
DISTDIR = /disc/jgranier/source_code/Rendu-Style-Novat/bin/debug/Rendu-Style-Novat1.0.0
LINK          = g++
LFLAGS        = -m64
LIBS          = $(SUBLIBS) -L/usr/X11R6/lib64 -lGLEW -lglfw -lX11 -lXi -lXrandr -lXxf86vm -lXinerama -lXcursor -lrt -lm -pthread -ldl -lQt5OpenGL -lQt5Widgets -lQt5Gui -lQt5Core -lGL -lpthread 
AR            = ar cqs
RANLIB        = 
SED           = sed
STRIP         = strip

####### Output directory

OBJECTS_DIR   = bin/debug/

####### Files

SOURCES       = src/MainWindow/main.cpp \
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
		src/OpenGl/caller.cpp moc_viewer.cpp
OBJECTS       = bin/debug/main.o \
		bin/debug/viewer.o \
		bin/debug/mainwindow.o \
		bin/debug/shader.o \
		bin/debug/mesh.o \
		bin/debug/vertex.o \
		bin/debug/meshloader.o \
		bin/debug/texture.o \
		bin/debug/light.o \
		bin/debug/camera.o \
		bin/debug/trackball.o \
		bin/debug/glad.o \
		bin/debug/stb_image.o \
		bin/debug/glm_add.o \
		bin/debug/loadtexture.o \
		bin/debug/generatedtexture.o \
		bin/debug/scene.o \
		bin/debug/heightmap.o \
		bin/debug/maps.o \
		bin/debug/caller.o \
		bin/debug/moc_viewer.o
DIST          = shaders/drawtexture.frag \
		shaders/drawtexture.vert \
		shaders/computelight.vert \
		shaders/computelight.frag \
		shaders/gaussBlur.frag \
		shaders/gaussBlur.vert \
		shaders/slant.frag \
		shaders/slant.vert \
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
		shaders/mergeshadow.vert \
		shaders/shadowmap.frag \
		shaders/shadowmap.vert \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/spec_pre.prf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/common/unix.conf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/common/linux.conf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/common/sanitize.conf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/common/gcc-base.conf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/common/gcc-base-unix.conf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/common/g++-base.conf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/common/g++-unix.conf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/qconfig.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_bootstrap_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_concurrent.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_concurrent_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_core.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_core_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_dbus.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_dbus_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_eglfs_device_lib_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_eglfs_kms_support_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_gui.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_gui_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_network.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_network_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_opengl.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_opengl_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_openglextensions.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_openglextensions_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_platformsupport_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_printsupport.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_printsupport_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_qml.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_qmltest.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_quick.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_quickwidgets.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_sql.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_sql_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_testlib.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_testlib_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_widgets.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_widgets_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_xcb_qpa_lib_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_xml.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_xml_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/qt_functions.prf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/qt_config.prf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/linux-g++-64/qmake.conf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/spec_post.prf \
		.qmake.stash \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/exclusive_builds.prf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/toolchain.prf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/default_pre.prf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/resolve_config.prf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/default_post.prf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/qml_debug.prf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/warn_on.prf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/qt.prf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/resources.prf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/moc.prf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/unix/opengl.prf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/uic.prf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/unix/thread.prf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/file_copies.prf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/testcase_targets.prf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/exceptions.prf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/yacc.prf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/lex.prf \
		Rendu-Style-Novat.pro src/MainWindow/mainwindow.h \
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
		src/OpenGl/caller.h src/MainWindow/main.cpp \
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
		src/OpenGl/caller.cpp
QMAKE_TARGET  = Rendu-Style-Novat
DESTDIR       = bin/debugz/
TARGET        = bin/debugz/Rendu-Style-Novat


first: all
####### Build rules

$(TARGET): ui_mainwindow.h $(OBJECTS)  
	@test -d bin/debugz/ || mkdir -p bin/debugz/
	$(LINK) $(LFLAGS) -o $(TARGET) $(OBJECTS) $(OBJCOMP) $(LIBS)

Makefile: Rendu-Style-Novat.pro /usr/lib/x86_64-linux-gnu/qt5/mkspecs/linux-g++-64/qmake.conf /usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/spec_pre.prf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/common/unix.conf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/common/linux.conf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/common/sanitize.conf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/common/gcc-base.conf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/common/gcc-base-unix.conf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/common/g++-base.conf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/common/g++-unix.conf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/qconfig.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_bootstrap_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_concurrent.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_concurrent_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_core.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_core_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_dbus.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_dbus_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_eglfs_device_lib_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_eglfs_kms_support_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_gui.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_gui_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_network.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_network_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_opengl.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_opengl_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_openglextensions.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_openglextensions_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_platformsupport_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_printsupport.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_printsupport_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_qml.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_qmltest.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_quick.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_quickwidgets.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_sql.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_sql_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_testlib.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_testlib_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_widgets.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_widgets_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_xcb_qpa_lib_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_xml.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_xml_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/qt_functions.prf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/qt_config.prf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/linux-g++-64/qmake.conf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/spec_post.prf \
		.qmake.stash \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/exclusive_builds.prf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/toolchain.prf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/default_pre.prf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/resolve_config.prf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/default_post.prf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/qml_debug.prf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/warn_on.prf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/qt.prf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/resources.prf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/moc.prf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/unix/opengl.prf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/uic.prf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/unix/thread.prf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/file_copies.prf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/testcase_targets.prf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/exceptions.prf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/yacc.prf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/lex.prf \
		Rendu-Style-Novat.pro \
		/usr/lib/x86_64-linux-gnu/libQt5OpenGL.prl \
		/usr/lib/x86_64-linux-gnu/libQt5Widgets.prl \
		/usr/lib/x86_64-linux-gnu/libQt5Gui.prl \
		/usr/lib/x86_64-linux-gnu/libQt5Core.prl
	$(QMAKE) -spec linux-g++-64 CONFIG+=debug CONFIG+=qml_debug -o Makefile Rendu-Style-Novat.pro
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/spec_pre.prf:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/common/unix.conf:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/common/linux.conf:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/common/sanitize.conf:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/common/gcc-base.conf:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/common/gcc-base-unix.conf:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/common/g++-base.conf:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/common/g++-unix.conf:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/qconfig.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_bootstrap_private.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_concurrent.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_concurrent_private.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_core.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_core_private.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_dbus.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_dbus_private.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_eglfs_device_lib_private.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_eglfs_kms_support_private.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_gui.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_gui_private.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_network.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_network_private.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_opengl.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_opengl_private.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_openglextensions.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_openglextensions_private.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_platformsupport_private.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_printsupport.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_printsupport_private.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_qml.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_qmltest.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_quick.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_quickwidgets.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_sql.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_sql_private.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_testlib.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_testlib_private.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_widgets.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_widgets_private.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_xcb_qpa_lib_private.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_xml.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_xml_private.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/qt_functions.prf:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/qt_config.prf:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/linux-g++-64/qmake.conf:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/spec_post.prf:
.qmake.stash:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/exclusive_builds.prf:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/toolchain.prf:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/default_pre.prf:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/resolve_config.prf:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/default_post.prf:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/qml_debug.prf:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/warn_on.prf:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/qt.prf:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/resources.prf:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/moc.prf:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/unix/opengl.prf:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/uic.prf:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/unix/thread.prf:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/file_copies.prf:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/testcase_targets.prf:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/exceptions.prf:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/yacc.prf:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/lex.prf:
Rendu-Style-Novat.pro:
/usr/lib/x86_64-linux-gnu/libQt5OpenGL.prl:
/usr/lib/x86_64-linux-gnu/libQt5Widgets.prl:
/usr/lib/x86_64-linux-gnu/libQt5Gui.prl:
/usr/lib/x86_64-linux-gnu/libQt5Core.prl:
qmake: FORCE
	@$(QMAKE) -spec linux-g++-64 CONFIG+=debug CONFIG+=qml_debug -o Makefile Rendu-Style-Novat.pro

qmake_all: FORCE


all: Makefile $(TARGET)

dist: distdir FORCE
	(cd `dirname $(DISTDIR)` && $(TAR) $(DISTNAME).tar $(DISTNAME) && $(COMPRESS) $(DISTNAME).tar) && $(MOVE) `dirname $(DISTDIR)`/$(DISTNAME).tar.gz . && $(DEL_FILE) -r $(DISTDIR)

distdir: FORCE
	@test -d $(DISTDIR) || mkdir -p $(DISTDIR)
	$(COPY_FILE) --parents $(DIST) $(DISTDIR)/
	$(COPY_FILE) --parents src/MainWindow/mainwindow.h src/MainWindow/viewer.h src/OpenGl/shader.h src/OpenGl/mesh.h src/OpenGl/vertex.h src/OpenGl/meshloader.h src/OpenGl/texture.h src/Light_Camera/light.h src/Light_Camera/camera.h src/Light_Camera/trackball.h lib/stb_image.h lib/glm_add.h src/OpenGl/loadtexture.h src/OpenGl/generatedtexture.h src/OpenGl/scene.h src/OpenGl/heightmap.h src/OpenGl/maps.h src/OpenGl/caller.h $(DISTDIR)/
	$(COPY_FILE) --parents src/MainWindow/main.cpp src/MainWindow/viewer.cpp src/MainWindow/mainwindow.cpp src/OpenGl/shader.cpp src/OpenGl/mesh.cpp src/OpenGl/vertex.cpp src/OpenGl/meshloader.cpp src/OpenGl/texture.cpp src/Light_Camera/light.cpp src/Light_Camera/camera.cpp src/Light_Camera/trackball.cpp lib/glad.c lib/stb_image.cpp lib/glm_add.cpp src/OpenGl/loadtexture.cpp src/OpenGl/generatedtexture.cpp src/OpenGl/scene.cpp src/OpenGl/heightmap.cpp src/OpenGl/maps.cpp src/OpenGl/caller.cpp $(DISTDIR)/
	$(COPY_FILE) --parents src/MainWindow/mainwindow.ui $(DISTDIR)/


clean: compiler_clean 
	-$(DEL_FILE) $(OBJECTS)
	-$(DEL_FILE) *~ core *.core


distclean: clean 
	-$(DEL_FILE) $(TARGET) 
	-$(DEL_FILE) .qmake.stash
	-$(DEL_FILE) Makefile


####### Sub-libraries

mocclean: compiler_moc_header_clean compiler_moc_source_clean

mocables: compiler_moc_header_make_all compiler_moc_source_make_all

check: first

benchmark: first

compiler_rcc_make_all:
compiler_rcc_clean:
compiler_moc_header_make_all: moc_viewer.cpp
compiler_moc_header_clean:
	-$(DEL_FILE) moc_viewer.cpp
moc_viewer.cpp: src/OpenGl/shader.h \
		src/OpenGl/scene.h \
		src/OpenGl/mesh.h \
		src/OpenGl/vertex.h \
		src/OpenGl/loadtexture.h \
		src/OpenGl/texture.h \
		src/OpenGl/generatedtexture.h \
		src/OpenGl/meshloader.h \
		src/OpenGl/maps.h \
		src/Light_Camera/camera.h \
		src/Light_Camera/trackball.h \
		lib/glm_add.h \
		src/Light_Camera/light.h \
		src/MainWindow/viewer.h \
		/usr/lib/x86_64-linux-gnu/qt5/bin/moc
	/usr/lib/x86_64-linux-gnu/qt5/bin/moc $(DEFINES) -I/usr/lib/x86_64-linux-gnu/qt5/mkspecs/linux-g++-64 -I/disc/jgranier/source_code/Rendu-Style-Novat -I/usr/include/x86_64-linux-gnu/qt5 -I/usr/include/x86_64-linux-gnu/qt5/QtOpenGL -I/usr/include/x86_64-linux-gnu/qt5/QtWidgets -I/usr/include/x86_64-linux-gnu/qt5/QtGui -I/usr/include/x86_64-linux-gnu/qt5/QtCore -I/usr/include/c++/6 -I/usr/include/x86_64-linux-gnu/c++/6 -I/usr/include/c++/6/backward -I/usr/lib/gcc/x86_64-linux-gnu/6/include -I/usr/local/include -I/usr/lib/gcc/x86_64-linux-gnu/6/include-fixed -I/usr/include/x86_64-linux-gnu -I/usr/include src/MainWindow/viewer.h -o moc_viewer.cpp

compiler_moc_source_make_all:
compiler_moc_source_clean:
compiler_uic_make_all: ui_mainwindow.h
compiler_uic_clean:
	-$(DEL_FILE) ui_mainwindow.h
ui_mainwindow.h: src/MainWindow/mainwindow.ui \
		/usr/lib/x86_64-linux-gnu/qt5/bin/uic
	/usr/lib/x86_64-linux-gnu/qt5/bin/uic src/MainWindow/mainwindow.ui -o ui_mainwindow.h

compiler_yacc_decl_make_all:
compiler_yacc_decl_clean:
compiler_yacc_impl_make_all:
compiler_yacc_impl_clean:
compiler_lex_make_all:
compiler_lex_clean:
compiler_clean: compiler_moc_header_clean compiler_uic_clean 

####### Compile

bin/debug/main.o: src/MainWindow/main.cpp src/MainWindow/mainwindow.h \
		src/MainWindow/viewer.h \
		src/OpenGl/shader.h \
		src/OpenGl/scene.h \
		src/OpenGl/mesh.h \
		src/OpenGl/vertex.h \
		src/OpenGl/loadtexture.h \
		src/OpenGl/texture.h \
		src/OpenGl/generatedtexture.h \
		src/OpenGl/meshloader.h \
		src/OpenGl/maps.h \
		src/Light_Camera/camera.h \
		src/Light_Camera/trackball.h \
		lib/glm_add.h \
		src/Light_Camera/light.h \
		ui_mainwindow.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o bin/debug/main.o src/MainWindow/main.cpp

bin/debug/viewer.o: src/MainWindow/viewer.cpp src/MainWindow/viewer.h \
		src/OpenGl/shader.h \
		src/OpenGl/scene.h \
		src/OpenGl/mesh.h \
		src/OpenGl/vertex.h \
		src/OpenGl/loadtexture.h \
		src/OpenGl/texture.h \
		src/OpenGl/generatedtexture.h \
		src/OpenGl/meshloader.h \
		src/OpenGl/maps.h \
		src/Light_Camera/camera.h \
		src/Light_Camera/trackball.h \
		lib/glm_add.h \
		src/Light_Camera/light.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o bin/debug/viewer.o src/MainWindow/viewer.cpp

bin/debug/mainwindow.o: src/MainWindow/mainwindow.cpp src/MainWindow/mainwindow.h \
		src/MainWindow/viewer.h \
		src/OpenGl/shader.h \
		src/OpenGl/scene.h \
		src/OpenGl/mesh.h \
		src/OpenGl/vertex.h \
		src/OpenGl/loadtexture.h \
		src/OpenGl/texture.h \
		src/OpenGl/generatedtexture.h \
		src/OpenGl/meshloader.h \
		src/OpenGl/maps.h \
		src/Light_Camera/camera.h \
		src/Light_Camera/trackball.h \
		lib/glm_add.h \
		src/Light_Camera/light.h \
		ui_mainwindow.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o bin/debug/mainwindow.o src/MainWindow/mainwindow.cpp

bin/debug/shader.o: src/OpenGl/shader.cpp src/OpenGl/shader.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o bin/debug/shader.o src/OpenGl/shader.cpp

bin/debug/mesh.o: src/OpenGl/mesh.cpp src/OpenGl/mesh.h \
		src/OpenGl/vertex.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o bin/debug/mesh.o src/OpenGl/mesh.cpp

bin/debug/vertex.o: src/OpenGl/vertex.cpp src/OpenGl/vertex.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o bin/debug/vertex.o src/OpenGl/vertex.cpp

bin/debug/meshloader.o: src/OpenGl/meshloader.cpp src/OpenGl/meshloader.h \
		src/OpenGl/mesh.h \
		src/OpenGl/vertex.h \
		src/OpenGl/loadtexture.h \
		src/OpenGl/shader.h \
		src/OpenGl/texture.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o bin/debug/meshloader.o src/OpenGl/meshloader.cpp

bin/debug/texture.o: src/OpenGl/texture.cpp src/OpenGl/texture.h \
		src/OpenGl/shader.h \
		src/OpenGl/caller.h \
		lib/stb_image.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o bin/debug/texture.o src/OpenGl/texture.cpp

bin/debug/light.o: src/Light_Camera/light.cpp src/Light_Camera/light.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o bin/debug/light.o src/Light_Camera/light.cpp

bin/debug/camera.o: src/Light_Camera/camera.cpp src/Light_Camera/camera.h \
		src/Light_Camera/trackball.h \
		lib/glm_add.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o bin/debug/camera.o src/Light_Camera/camera.cpp

bin/debug/trackball.o: src/Light_Camera/trackball.cpp src/Light_Camera/trackball.h \
		lib/glm_add.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o bin/debug/trackball.o src/Light_Camera/trackball.cpp

bin/debug/glad.o: lib/glad.c 
	$(CC) -c $(CFLAGS) $(INCPATH) -o bin/debug/glad.o lib/glad.c

bin/debug/stb_image.o: lib/stb_image.cpp lib/stb_image.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o bin/debug/stb_image.o lib/stb_image.cpp

bin/debug/glm_add.o: lib/glm_add.cpp lib/glm_add.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o bin/debug/glm_add.o lib/glm_add.cpp

bin/debug/loadtexture.o: src/OpenGl/loadtexture.cpp src/OpenGl/loadtexture.h \
		src/OpenGl/shader.h \
		src/OpenGl/texture.h \
		lib/stb_image.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o bin/debug/loadtexture.o src/OpenGl/loadtexture.cpp

bin/debug/generatedtexture.o: src/OpenGl/generatedtexture.cpp src/OpenGl/generatedtexture.h \
		src/OpenGl/texture.h \
		src/OpenGl/shader.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o bin/debug/generatedtexture.o src/OpenGl/generatedtexture.cpp

bin/debug/scene.o: src/OpenGl/scene.cpp src/OpenGl/scene.h \
		src/OpenGl/mesh.h \
		src/OpenGl/vertex.h \
		src/OpenGl/shader.h \
		src/OpenGl/loadtexture.h \
		src/OpenGl/texture.h \
		src/OpenGl/generatedtexture.h \
		src/OpenGl/meshloader.h \
		src/OpenGl/maps.h \
		src/OpenGl/heightmap.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o bin/debug/scene.o src/OpenGl/scene.cpp

bin/debug/heightmap.o: src/OpenGl/heightmap.cpp src/OpenGl/heightmap.h \
		src/OpenGl/generatedtexture.h \
		src/OpenGl/texture.h \
		src/OpenGl/shader.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o bin/debug/heightmap.o src/OpenGl/heightmap.cpp

bin/debug/maps.o: src/OpenGl/maps.cpp src/OpenGl/maps.h \
		src/OpenGl/loadtexture.h \
		src/OpenGl/shader.h \
		src/OpenGl/texture.h \
		src/OpenGl/generatedtexture.h \
		src/OpenGl/mesh.h \
		src/OpenGl/vertex.h \
		src/OpenGl/meshloader.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o bin/debug/maps.o src/OpenGl/maps.cpp

bin/debug/caller.o: src/OpenGl/caller.cpp src/OpenGl/caller.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o bin/debug/caller.o src/OpenGl/caller.cpp

bin/debug/moc_viewer.o: moc_viewer.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o bin/debug/moc_viewer.o moc_viewer.cpp

####### Install

install:  FORCE

uninstall:  FORCE

FORCE:

