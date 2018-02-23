// TODO faire une description de chaque classe
// TODO Descendre le maximum d'include dans les cpp


//TODO : Les questions à romain de type technique

/*
 *   Prevenir romain que ça camera pu.
 *
 */







#include "mainwindow.h"
#include <qapplication.h>









int main(int argc,char** argv)
{
    QApplication application(argc,argv);
    application.setWindowIcon(QIcon("Images/RSN.ico"));
    application.setApplicationName("Rendu Style Novat");

    MainWindow window;
    window.show();
    return application.exec();
}

