// TODO faire une description de chaque classe


//TODO : Les questions à romain de type technique

/*
 *   Le centre de la camera fonctionne pas en MNT , comment marche exactement la camera ?
 *   Comment savoir si mes normals sont bonne ?
 *
 *
 *
 *
 */





#include <qapplication.h>
#include <QString>

#include "viewer.h"


int main(int argc,char** argv)
{
    QApplication application(argc,argv);

    QGLFormat fmt;
    fmt.setVersion(3,3);
    fmt.setProfile(QGLFormat::CoreProfile);
    fmt.setSampleBuffers(true);

    Viewer viewer(fmt);
    viewer.setWindowTitle("Rendu style Novat");
    viewer.show();

    return application.exec();
}

