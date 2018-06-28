
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
 *

 * Final :
 *  Faire marcher sur une distribution neuve
 *  Faire CMake au lieu de .pro
 *
 * Doc :
 *      Faire la doc
 *      Faire le document résumé du code pour le prochain
 *      Faire le readme
 *
 * Nettoyage:
 *      Transferet l'info du viewPort afin d'aléger l'appelle des fonctions
 *      Enlever shadow map (done)
 *      Texture -> merge
 *      Enlever stack shader -> faire une fonction pour le lambertien
 *      Virer toutes les fonctions qui sont obselette
 *      Normaliser les noms des variables Viewer + scene
 *      Essayer de passer tout les input dans une autre class ou au moins dans main windows
 *      Virer les shader intuiles
 *      Nettoyer les shaders
 *      Faire point avec joelle de ce qui sert à rien de garder sur l'interface
 *      Virer angles map + et lighttexture
 *      Normaliser Get-Set name
 *      Gestion error , voir si on arrive à faire fonctionner le caller.
 *      Rajouter bouton lambertien
 *
 * Recherche :
 *      Morphomath : taille dépendant, orientation pente
 *      Multi echelle : Vérifier creation et fusion --> doit respecter la pyraide laplacienne
 *      Ombre portée : Si le temps faire un essai en fonction de l'elevation
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 * /



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

