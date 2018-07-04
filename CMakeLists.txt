#Demandez à vincent pour INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/includela version
cmake_minimum_required(VERSION 3.1)

project(Rendu_Style_Novat)

include(CMakeDependentOption)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)

file( 
    GLOB_RECURSE
    SOURCE_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/MainWindow/mainwindow.ui
)

#set(FORMS ${CMAKE_CURRENT_SOURCE_DIR}/src/MainWindow/mainwindow.ui)

#qt5_wrap_ui(FORMS_HEADERS ${FORMS})

#add_library()(CONFIG  ${FORMS_HEADERS})

add_executable(Rendu_Style_Novat ${SOURCE_FILES})# ${CONFIG})

find_package(Qt5Widgets REQUIRED)
find_package(Qt5Core REQUIRED)
find_package(Qt5Gui REQUIRED)
find_package(Qt5OpenGL)
find_package(glfw3 REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(glm REQUIRED)


target_include_directories(
    Rendu_Style_Novat PRIVATE
    ${CMAKE_BINARY_DIR}
   # ${QT5WIDGETS_INCLUDE_DIRS}
   # ${QT5CORE_INCLUDE_DIRS}
   # ${QT5GUI_INCLUDE_DIRS}
   # ${QT5OPENGL_INCLUDE_DIRS}
    ${GLFW_INCLUDE_DIRS}
    ${OPENGL_INCLUDE_DIRS}
    ${GLEW_INCLUDE_DIRS}
    ${GLM_INCLUDE_DIRS}
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

qt5_use_modules(Rendu_Style_Novat Core Gui Widgets OpenGL)

target_link_libraries(
    Rendu_Style_Novat
   # ${QT5WIDGETS_LIBRARIES}
   # ${QT5CORE_LIBRARIES}
   # ${QT5GUI_LIBRARIES}
   # ${QT5OPENGL_LIBRARIES}
    glfw
    ${OPENGL_LIBRARIES}
    ${GLEW_LIBRARIES}
    ${GLM_LIBRARIES}
)

