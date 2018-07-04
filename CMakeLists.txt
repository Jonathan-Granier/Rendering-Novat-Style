cmake_minimum_required(VERSION 3.1)

project(Rendu_Style_Novat)

include(CMakeDependentOption)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "-g -O0 -Wall -fprofile-arcs -ftest-coverage")
set(CMAKE_CXX_OUPUT_EXTENSION_REPLACE 1)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)

file(
    GLOB_RECURSE
    SOURCE_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/sources_code/cpp/*.h
    ${CMAKE_CURRENT_SOURCE_DIR}/sources_code/cpp/*.cpp
)


add_executable(Rendu_Style_Novat ${SOURCE_FILES})# ${CONFIG})

find_package(Qt5Widgets REQUIRED)
find_package(Qt5Core REQUIRED)
find_package(Qt5Gui REQUIRED)
find_package(Qt5OpenGL REQUIRED)
find_package(glfw3 REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(glm REQUIRED)


target_include_directories(
    Rendu_Style_Novat PRIVATE
    ${CMAKE_BINARY_DIR}
    ${GLFW_INCLUDE_DIRS}
    ${OPENGL_INCLUDE_DIRS}
    ${GLEW_INCLUDE_DIRS}
    ${GLM_INCLUDE_DIRS}
    ${CMAKE_CURRENT_SOURCE_DIR}/sources_code/cpp
)

qt5_use_modules(Rendu_Style_Novat Core Gui Widgets OpenGL)

target_link_libraries(
    Rendu_Style_Novat
    glfw
    ${OPENGL_LIBRARIES}
    ${GLEW_LIBRARIES}
    ${GLM_LIBRARIES}
)
