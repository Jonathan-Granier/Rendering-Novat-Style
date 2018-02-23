

#include "mainwindow.h"
#include <QMenu>
#include <QMenuBar>
#include <QMessageBox>
#include <QToolBar>
#include <QAction>
#include <QFileDialog>
#include <QErrorMessage>

MainWindow::MainWindow()
{

    this->setFixedSize(1200,800);
    // TODO set Icon
    // TODO window->setWorkingDirectory(appPath, sceneName, textureName, envMapName);

    _viewer = new Viewer();
    setCentralWidget(_viewer);


    setupMenu();

}

MainWindow::~MainWindow()
{
    delete _viewer;
}



void MainWindow::open()
{
    QString fileName = QFileDialog::getOpenFileName(this);
    if(!fileName.isEmpty())
    {
        if(!_viewer->loadModelFromFile(fileName)){
            QErrorMessage errorMessageDialog(this);
            errorMessageDialog.showMessage(tr("Error , unknow type file !"));
        }
    }
}
//TODO
void MainWindow::saveScreenshot()
{
    QErrorMessage errorMessageDialog(this);
    errorMessageDialog.showMessage(tr("Not Implemented!"));
}

void MainWindow::help()
{
    QErrorMessage errorMessageDialog(this);
    errorMessageDialog.showMessage(tr("Not Implemented!"));
}

void MainWindow::about()
{
    QMessageBox::about(this, tr("A propos Rendu Style Novat"),
                tr("Application ayant pour objectif d'automatiser "
                   "le rendu de panorama dans le style du peintre "
                   "<b>Pierre Novat</b>"));
}






void MainWindow::setupMenu(){



    QMenu *fileMenu = menuBar()->addMenu(menuBar()->tr("&File"));
    //QToolBar *fileToolBar = addToolBar(tr("File"));


    //Load new Model
    const QIcon openIcon = QIcon::fromTheme("document_open"); //TODO Image
    QAction *OpenModelAct = new QAction(openIcon,tr("&Charger un model"),this);
    OpenModelAct->setShortcut(QKeySequence::Open);
    OpenModelAct->setStatusTip(menuBar()->tr("&Charger un model existant (.obj ou .mnt)"));
    connect(OpenModelAct,&QAction::triggered,this,&MainWindow::open);
    fileMenu->addAction(OpenModelAct);
    //fileToolBar->addAction(OpenModelAct);

    const QIcon saveIcon = QIcon::fromTheme("document-save-as"); //TODO Image
    QAction *SaveScreenshotAct = new QAction(saveIcon,tr("&Capture d'ecran"),this);
    SaveScreenshotAct->setShortcut(QKeySequence::Print);
    SaveScreenshotAct->setStatusTip(menuBar()->tr("&Sauvegarder une capture d'ecran dans un fichier "));
    connect(SaveScreenshotAct,&QAction::triggered,this,&MainWindow::saveScreenshot);
    fileMenu->addAction(SaveScreenshotAct);
    //fileToolBar->addAction(SaveScreenshotAct);

    fileMenu->addSeparator();

    // Exit
    const QIcon exitIcon = QIcon::fromTheme("application-exit");
    QAction *exitAct = fileMenu->addAction(exitIcon,tr("Quitter"),this,&QWidget::close);
    exitAct->setShortcut(QKeySequence::Quit);
    exitAct->setStatusTip(menuBar()->tr("&Quitter l'application"));


    QMenu *helpMenu = menuBar()->addMenu(tr("&Help"));

    QAction *helpAct = helpMenu->addAction(tr("&Help"), this, &MainWindow::help);
    helpAct->setStatusTip(tr("Show the application's help"));
    QAction *aboutAct = helpMenu->addAction(tr("&About"), this, &MainWindow::about);
    aboutAct->setStatusTip(tr("Show the application's About box"));



}



