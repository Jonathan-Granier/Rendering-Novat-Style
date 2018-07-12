/**
*   @file main.cpp
*   @author Jonathan Granier
*   @version 1.0
*   @date 07/2018
*   @brief Prototype to generate the shading of the panorama in the style of Pierre Novat
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
    application.setApplicationName("Rendering in Novat style");

    MainWindow window;
    window.show();
    return application.exec();
}
