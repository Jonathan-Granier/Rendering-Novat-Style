
#include "mainwindow.h"
#include "src/OpenGl/progressinfo.h"
#include <QMenu>
#include <QMenuBar>
#include <QMessageBox>
#include <QToolBar>
#include <QAction>
#include <QFileDialog>
#include <QErrorMessage>
#include <QGuiApplication>
#include <QScreen>
#include <QPixmap>
#include <QObject>
#include <QStatusBar>
#include <QApplication>

using namespace std;
MainWindow::MainWindow()
{

    this->setFixedSize(1200,800);
    // TODO set Icon
    // TODO window->setWorkingDirectory(appPath, sceneName, textureName, envMapName);

    _viewer = new Viewer();



    setupMenu();
    setupLoadingBar();
    setCentralWidget(_viewer);

}

MainWindow::~MainWindow()
{
    //deleteLoadingBar();
    delete _viewer;
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    this->disconnect();
    _viewer->progressInfo()->disconnect();
    deleteLoadingBar();
    event->accept();
}

void MainWindow::keyPressEvent(QKeyEvent *ke)
{


    // key i: init camera
    if(ke->key()==Qt::Key_I) {
      _viewer->resetTheCameraPosition();

    }
    //key r : reload shader
    if(ke->key()==Qt::Key_R){
       _viewer->reloadShader();

    }

    if(ke->key()==Qt::Key_P){
        _viewer->printCamAndLight();
    }

    if(ke->key()==Qt::Key_D){
        _viewer->fixeCamAndLight();
    }
    if(ke->key()==Qt::Key_Q){
        QString currentShader=QString::fromStdString(_viewer->previousShader());
        statusBar()->showMessage(currentShader);
    }
    if(ke->key()==Qt::Key_S){
        QString currentShader=QString::fromStdString(_viewer->nextShader());
        statusBar()->showMessage(currentShader);
    }
}


void MainWindow::open()
{
    QFileDialog browser;
    QStringList fileNames = browser.getOpenFileNames(this, tr("Open Models"), QDir::currentPath()+"/models",tr("Models (*.asc *.obj)"));
    browser.close(); // FIXME , don't always work
    if(!fileNames.isEmpty())
    {

        if(!_viewer->loadModelFromFile(fileNames)){
            QMessageBox::warning(this,tr("MainWindow"),tr("unknow type file !"),QMessageBox::Ok);
        }
    }

}
//TODO
void MainWindow::saveScreenshot()
{

    QImage screenshot =_viewer->grabFramebuffer();
    QFileDialog dialog(this, "Sauvegarder la capture d'ecran", QDir::currentPath()+"/screenshots","*.png *.jpg");
    dialog.setAcceptMode(QFileDialog::AcceptSave);
    QString filename;
    int ret = dialog.exec();
    if(ret == QDialog::Accepted){
        filename = dialog.selectedFiles()[0];
        if(!screenshot.save(filename)){
            QMessageBox::warning(0,tr("MainWindow"),tr("Impossible de sauvegarder la capture d'ecran :") + filename, QMessageBox::Ok);
        }
    }


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
                   "le rendu de panorama de montagne dans le style du peintre "
                   "<b>Pierre Novat</b>"));
}

void MainWindow::showLoadingBar()
{
    /*_loadingBar->setMinimum(0);
    _loadingBar->setMaximum(_viewer->progressInfo()->mark());
    _loadingBar->setVisible(true);
    //_loadingBar->show();
    statusBar()->setVisible(true);
*/
}

void MainWindow::updateLoadingBar()
{
    //_loadingBar->setValue(_viewer->progressInfo()->progress());

}

void MainWindow::hideLoadingBar()
{
    //_loadingBar->hide();
    //statusBar()->setVisible(false);

}






void MainWindow::setupMenu(){



    QMenu *fileMenu = menuBar()->addMenu(menuBar()->tr("&Fichier"));
    //QToolBar *fileToolBar = addToolBar(tr("Fichier"));


    //Load new Model
    const QIcon openIcon = QIcon::fromTheme("document-open"); //TODO Image
    QAction *OpenModelAct = new QAction(openIcon,tr("&Charger un model"),this);
    OpenModelAct->setShortcut(QKeySequence::Open);
    OpenModelAct->setStatusTip(menuBar()->tr("&Charger un model existant (.obj ou .mnt)"));
    connect(OpenModelAct,&QAction::triggered,this,&MainWindow::open);
    fileMenu->addAction(OpenModelAct);
    //fileToolBar->addAction(OpenModelAct);

    const QIcon saveIcon = QIcon::fromTheme("document-print"); //TODO Image
    QAction *SaveScreenshotAct = new QAction(saveIcon,tr("&Capture d'ecran"),this);
    SaveScreenshotAct->setShortcut(QKeySequence::Print);
    SaveScreenshotAct->setStatusTip(menuBar()->tr("&Sauvegarder une capture d'ecran dans un fichier "));
    connect(SaveScreenshotAct,&QAction::triggered,this,&MainWindow::saveScreenshot);
    fileMenu->addAction(SaveScreenshotAct);
    //fileToolBar->addAction(SaveScreenshotAct);

    fileMenu->addSeparator();

    // Exit
    const QIcon exitIcon = QIcon::fromTheme("application-exit");
    QAction *exitAct = fileMenu->addAction(exitIcon,tr("&Quitter"),this,&QWidget::close);
    exitAct->setShortcut(QKeySequence::Quit);
    exitAct->setStatusTip(menuBar()->tr("&Quitter l'application"));

    QMenu *helpMenu = menuBar()->addMenu(tr("&Help"));

    QAction *helpAct = helpMenu->addAction(tr("&Help"), this, &MainWindow::help);
    helpAct->setStatusTip(tr("Show the application's help"));
    QAction *aboutAct = helpMenu->addAction(tr("&About"), this, &MainWindow::about);
    aboutAct->setStatusTip(tr("Show the application's About box"));



}

void MainWindow::setupLoadingBar()
{
   /* _loadingBar = new QProgressBar(this);
    connect(_viewer->progressInfo(),&ProgressInfo::progressBegin,this,&MainWindow::showLoadingBar);
    connect(_viewer->progressInfo(),&ProgressInfo::progressUpdate,this,&MainWindow::updateLoadingBar);
    connect(_viewer->progressInfo(),&ProgressInfo::progressEnd,this,&MainWindow::hideLoadingBar);
    statusBar()->addPermanentWidget(_loadingBar,1);
    _loadingBar->setVisible(true);
    statusBar()->setVisible(true);
    _application->processEvents();
    */
}

void MainWindow::deleteLoadingBar(){
    /*
    disconnect(_viewer->progressInfo(),&ProgressInfo::progressBegin,this,&MainWindow::showLoadingBar);
    disconnect(_viewer->progressInfo(),&ProgressInfo::progressUpdate,this,&MainWindow::updateLoadingBar);
    disconnect(_viewer->progressInfo(),&ProgressInfo::progressEnd,this,&MainWindow::hideLoadingBar);
    delete _loadingBar;
    */
}

