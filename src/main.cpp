// TODO faire une description de chaque classe
// TODO Descendre le maximum d'include dans les cpp


//TODO : Les questions à romain de type technique

/*
 *   Prevenir romain que ça camera pu.
 *
 */


//TODO
/*
 * Bar de progression
 * Save screenshot
*/

/**
*   \file main.cpp
*   \author Jonathan Granier
*   \version 1.0
*   \date 26/02/2018
*   \brief Application to generate a mountain panorama in the style of Pierre Novat
*
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
    application.setWindowIcon(QIcon("Images/RSN.ico"));
    application.setApplicationName("Rendu Style Novat");

    MainWindow window;
    window.show();
    return application.exec();
}

