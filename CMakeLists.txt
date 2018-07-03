#Demandez à vincent pour la version
cmake_minimum_required(VERSION 3.1)

project(Rendu_Style_Novat)

set(CMAKE_CXX_STANDARD 11)


file( 
    GLOB_RECURSE
    SOURCE_FILES
    src/*
    lib/*   
)


set(UI src/MainWindow/mainWindow.ui)
qt5_wrap_ui(UI_HDRS ${UI})


add_executable(Rendu_Style_Novat ${SOURCE_FILES} ${UI_HDRS})


find_package(Qt5Widgets REQUIRED)
find_package(Qt5Core REQUIRED)
find_package(Qt5gui REQUIRED)
find_package(OpenGl REQUIRED)


find_package(glfw REQUIRED)
include_directories(${GLFW_INCLUDE_DIRS})
link_libraries(${GLFW_LIBRARY_DIRS})

find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIRS})

find_package(GLEW REQUIRED)
include_directories(${GLEW_INCLUDE_DIRS})

find_package(glm QUIET)
if (NOT GLM_FOUND)
    # Find GLM using pkg-config
    pkg_search_module(GLM glm)

    if (NOT GLM_FOUND)
        # Find GLM using find_path
        find_path(GLM_INCLUDE_DIRS glm/glm.hpp)

        if (NOT GLM_INCLUDE_DIRS)
            message(FATAL "Could not find GLM using any of CMake, pkg-config or find_path. Please ensure libglm-dev is installed.")
        endif()
    endif()
endif()






set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -std=c++0x")



