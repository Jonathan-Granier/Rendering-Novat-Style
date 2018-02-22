// TODO faire une description de chaque classe
// TODO Descendre le maximum d'include dans les cpp


//TODO : Les questions à romain de type technique

/*
 *   Prevenir romain que ça camera pu.
 *
 */





#include <qapplication.h>
#include <QString>
#include <QMenuBar>
#include <QMenu>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include "mainwindow.h"




void setupMenu(QMenuBar *menuBar,MainWindow *window, QApplication *app){
    QMenu *fileMenu = menuBar->addMenu(menuBar->tr("&File"));

    //Load new Model
    QAction *actionLoadNewModel = new QAction(menuBar->tr("&Load New Model"),fileMenu);
    actionLoadNewModel->setShortcut(QKeySequence::Open);
    actionLoadNewModel->setStatusTip(menuBar->tr("&Load an existing file (obj or mnt)"));
    //window->connect(actionLoadNewModel,SIGNAL(triggered()),window,SLOT(loadNewModel()));
    fileMenu->addAction(actionLoadNewModel);

    //Save screenshot
    QAction *actionSaveScreenshot = new QAction(menuBar->tr("&Save Screenshot"),fileMenu);
    actionSaveScreenshot->setShortcut(QKeySequence::Print);
    actionSaveScreenshot->setStatusTip(menuBar->tr("&Saves a copy of the screen to a file"));
    //window->connect(actionSaveScreenshot,SIGNAL(triggered()),window,SLOT(saveScreenshot()));
    fileMenu->addAction(actionSaveScreenshot);



    //Quit
    QAction *actionQuit = new QAction(menuBar->tr("&Quit"),fileMenu);
    actionQuit->setShortcut(QKeySequence::Quit);
    actionQuit->setStatusTip(menuBar->tr("&Quit program"));
    //window->connect(actionQuit,SIGNAL(triggered()),app,SLOT(quit()));
    fileMenu->addAction(actionQuit);
}






int main(int argc,char** argv)
{
    QApplication application(argc,argv);

    MainWindow *window = new MainWindow();
    window->setWindowTitle("Rendu Style Novat");
    // TODO set Icon
    // TODO window->setWorkingDirectory(appPath, sceneName, textureName, envMapName);
    window->setMinimumSize(640,480);
    window->setFocusPolicy(Qt::TabFocus);

    QMenuBar *menuBar = new QMenuBar();
    menuBar->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    setupMenu(menuBar,window,&application);

    QHBoxLayout *hb = new QHBoxLayout();
    hb->addWidget(window);

    QVBoxLayout *vb = new QVBoxLayout;
    vb->addWidget(menuBar);
    vb->addLayout(hb);

    QWidget *w = new QWidget;
    w->move(200,100);
    w->setLayout(vb);
    w->show();

    return application.exec();
}

