
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
    application.setWindowIcon(QIcon("images/RSN.ico"));
    application.setApplicationName("Rendu Style Novat");

    MainWindow window;
    window.show();
    return application.exec();
}
