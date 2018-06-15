
/**
*   \file main.cpp
*   \author Jonathan Granier
*   \version 1.0
*   \date 26/02/2018
*   \brief Application to generate a mountain panorama in the style of Pierre Novat
*
*/



// TODO
/*
 * Faire la morpologie mathématique
 * Rename parallax to shadow
 * Faire la save d'une heightMap en format MNT.
 * Faire le min et max d'une heightMap flouté.
 * Transferet l'info du viewPort afin d'aléger l'appelle des fonctions
 * Faire la doc
 * Virer ce qui ne sert plus à rien
 */



/***
 *
 * Les truc à installer :
 * QT5 (qt5-default + qt5-qmake + qtdeclarative5-dev
 * Glew : (libglew-dev sous debian)
 * glm :  libglm-dev
 * libglfw3-dev
 * libxcursor-dev
 * libxrandr-dev
 * libxi-dev
 * libxinerama-dev
 * */



/**
  TODO : Coloriage
  Difference gradient
  Multi-Echelle.
*/



#include "mainwindow.h"
#include <qapplication.h>

/**
 * @brief main create the app and the mainwindow
 * @param argc Useless
 * @param argv Useless
 * @return Show QApplication.exec() return.
 */
int main(int argc,char** argv)
{
    QApplication application(argc,argv);
    application.setWindowIcon(QIcon("images/RSN.ico"));
    application.setApplicationName("Rendu Style Novat");

    MainWindow window;
    window.show();
    return application.exec();
}

