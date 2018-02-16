// TODO faire une description de chaque classe

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

