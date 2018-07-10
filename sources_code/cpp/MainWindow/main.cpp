
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
 *  [DONE] Faire marcher sur une distribution neuve
 *  [DONE] Faire CMake au lieu de .pro
 *
 * Doc :
 *      Faire la doc
 *      Faire le document résumé du code pour le prochain
 *      Faire le readme
 * Nettoyage:
 *      [DONE] Transferet l'info du viewPort afin d'aléger l'appelle des fonctions
 *      [DONE] Enlever shadow map
 *      [DONE] Enlever stack shader ->
 *      [DONE] faire une fonction pour le lambertien
 *      [DONE] Virer toutes les fonctions qui sont obselette
 *      [DONE] Normaliser les noms des variables Viewer + scene
 *      [DONE] Normaliser Get-Set name
 *      Essayer de passer tout les input dans une autre class ou au moins dans main windows
 *      [DONE]Virer les shader intuiles
 *      Nettoyer les shaders et les rennomer correctement.
 *      [DONE] Virer angles map + et lighttexture
 *      [AVOID] Gestion error , voir si on arrive à faire fonctionner le caller.
 *      [AVOID] Factoriser maps et faire une stack de maps --> voir si possible et plus simple
 *      Gestion Memoire --> verifier les fuites possibles
 *      Verifier le bug texture qu'on avait avec une petite MNT et voir comment le résoudre
 *      Shader -> Normaliser les axes
 *      [DONE] Shader -> verifier les input
 *      [DONE] Swith Erosion/Dilatation
 *      [DONE] Rename Paralax to shadow
 *      [DONE] Interface en anglais.
 *
 *      Commentaire Shader ++.
* Recherche :
 *
 *      [AVOID] Multi echelle : Vérifier creation et fusion --> doit respecter la pyramide laplacienne
 *      [DONE]Couleur en fonction de l'altitude.
 *      [AVOID] Voir le fichier recherche si on peut le nettoyer et le rendre plus propre.
 *
 *
 *
 * Transfert :
 *      [DONE] Donner le rapport + soutenance , avec les sources (.tex et schema).
 *
 *
 * Divers :
 *      [DONE] Faire fonctionner sur mon pc pour le rdv avec Renaud , vendredi 6 juillet.
 *
 *      [DONE] Mail Arthur
 *
 *      Corriger coquille (un schema + ; et imprimer le rapport )
 *
 *      Faire un Best of paper
 *
 *
 *      [DONE] Rapport file transfert.
 */



/*
 *
 * Les truc à installer :
 * QT5 (qt5-default + qt5-qmake + qtdeclarative5-dev
 * Glew : (libglew-dev sous debian)
 * glm :  libglm-dev
 * glfw : libglfw3-dev
 * cmd : sudo apt-get install qt5-default qt5-qmake qtdeclarative5-dev libglew-dev libglm-dev libglfw3-dev pkg-config
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
    application.setWindowIcon(QIcon("images/RSN.ico"));
    application.setApplicationName("Rendu Style Novat");

    MainWindow window;
    window.show();
    return application.exec();
}
