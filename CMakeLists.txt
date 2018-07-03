cmake_minimum_required(VERSION 3.1)

find_package(Qt5Widgets)
find_package(Qt5Core REQUIRED)
find_package(Qt5gui REQUIRED)
find_package(OpenGl REQUIRED)


set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -std=c++0x")

set(SOURCES
	src/MainWindow/main.cpp 
    src/MainWindow/viewer.cpp 
    src/MainWindow/mainwindow.cpp 
    src/OpenGl/shader.cpp 
    src/OpenGl/mesh.cpp 
    src/OpenGl/vertex.cpp 
    src/OpenGl/meshloader.cpp 
    src/OpenGl/texture.cpp
    src/Light_Camera/light.cpp 
    src/Light_Camera/camera.cpp 
    src/Light_Camera/trackball.cpp 
    lib/stb_image.cpp 
    lib/glm_add.cpp 
    src/OpenGl/loadtexture.cpp 
    src/OpenGl/generatedtexture.cpp 
    src/OpenGl/scene.cpp 
    src/OpenGl/heightmap.cpp 
    src/OpenGl/maps.cpp 
    src/OpenGl/caller.cpp
)

set(HEADERS
	src/MainWindow/mainwindow.h 
    src/MainWindow/viewer.h 
    src/OpenGl/shader.h 
    src/OpenGl/mesh.h 
    src/OpenGl/vertex.h 
    src/OpenGl/meshloader.h 
    src/OpenGl/texture.h 
    src/Light_Camera/light.h 
    src/Light_Camera/camera.h 
    src/Light_Camera/trackball.h 
    lib/stb_image.h 
    lib/glm_add.h 
    src/OpenGl/loadtexture.h 
    src/OpenGl/generatedtexture.h 
    src/OpenGl/scene.h 
    src/OpenGl/heightmap.h 
    src/OpenGl/maps.h 
    src/OpenGl/caller.h
)

set(UI src/MainWindow/mainWindow.ui)
qt5_wrap_ui(UI_HDRS ${UI})

add_executable(Rendu_Style_Novat ${SOURCES} ${HEADERS} ${UI_HDRS})
