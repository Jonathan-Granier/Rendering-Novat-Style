
#include "mainwindow.h"
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
#include <QSlider>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>

using namespace std;
MainWindow::MainWindow()
{
    this->setFixedSize(1200,1000);
    // TODO set Icon
    // TODO window->setWorkingDirectory(appPath, sceneName, textureName, envMapName);

    //Allocation
    _viewer = make_unique<Viewer>();

   // _viewer->setFixedSize(1200, 700);
    setupMenu();
    QWidget *controlePanel = setupControlePanel();
   // QWidget *controlePanel = new QWidget();
    controlePanel->setMaximumHeight(100);
    QWidget *centralWidget = new QWidget();
    QVBoxLayout *centralLayout = new QVBoxLayout();
    centralLayout->addWidget(_viewer.get());
    centralLayout->addWidget(controlePanel);

    centralWidget->setLayout(centralLayout);


    setCentralWidget(centralWidget);

}

MainWindow::~MainWindow()
{
    //deleteLoadingBar();
    //delete _viewer;
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    this->disconnect();
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
        _viewer->previousShader();
    }
    if(ke->key()==Qt::Key_S){
        _viewer->nextShader();
    }

    if(ke->key()==Qt::Key_W){
        _viewer->previousDrawMode();
    }
    if(ke->key()==Qt::Key_X){
        _viewer->nextDrawMode();
    }

    if(ke->key()==Qt::Key_A){
        _viewer->previousLight();
    }
    if(ke->key()==Qt::Key_Z){
        _viewer->nextLight();
    }
    if(ke->key()==Qt::Key_Space){
        _viewer->switchScene();
    }
    refreshStatusBar();
}


void MainWindow::open()
{
    QFileDialog browser;
    QStringList fileNames = browser.getOpenFileNames(this, tr("Open Models"), QDir::currentPath()+"/models",tr("Models (*.asc *.obj)"));
    browser.close(); // FIXME , don't always work
    if(!fileNames.isEmpty())
    {

        if(!_viewer->loadSceneFromFile(fileNames)){
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

void MainWindow::updateLightPosition(int angle)
{
    _viewer->setHeightLight((float)angle);
}

void MainWindow::updateSigma(int sigma)
{
    _viewer->setSigma((float)sigma/10.0);
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

    QAction *helpAct = helpMenu->addAction(tr("Help"), this, &MainWindow::help);
    helpAct->setStatusTip(tr("Show the application's help"));
    QAction *aboutAct = helpMenu->addAction(tr("&About"), this, &MainWindow::about);
    aboutAct->setStatusTip(tr("Show the application's About box"));



}

QWidget *MainWindow::setupControlePanel()
{
    QWidget *controlePanel = new QWidget;
    QVBoxLayout *sliderLayout = new QVBoxLayout;

    QSlider* lightSlider = new QSlider(Qt::Horizontal);
    lightSlider->setTickPosition(QSlider::TicksBelow);
    lightSlider->setMinimum(0);
    lightSlider->setMaximum(89);
    lightSlider->setSliderPosition(45);
    connect(lightSlider,&QSlider::valueChanged,this,&MainWindow::updateLightPosition);
    QLabel* lightLabel = new QLabel("Light Height Position = ");
    QLabel* lightLabelValue = new QLabel();
    lightLabelValue->setNum(45);
    connect(lightSlider,SIGNAL(valueChanged(int)),lightLabelValue,SLOT(setNum(int)));
    QHBoxLayout *hboxLight = new QHBoxLayout;
    hboxLight->addWidget(lightLabel);
    hboxLight->addWidget(lightLabelValue);
    hboxLight->addWidget(lightSlider);
    sliderLayout->addLayout(hboxLight);



    QSlider* sigmaSlider = new QSlider(Qt::Horizontal);
    sigmaSlider->setTickPosition(QSlider::TicksBelow);
    sigmaSlider->setMinimum(0);
    sigmaSlider->setMaximum(100);
    sigmaSlider->setSliderPosition(1 * 10);
    connect(sigmaSlider,&QSlider::valueChanged,this,&MainWindow::updateSigma);
    QLabel* sigmaLabel = new QLabel("Sigma (*10) = ");
    QLabel* sigmaLabelValue = new QLabel();
   sigmaLabelValue->setNum(1 * 10);
    connect(sigmaSlider,SIGNAL(valueChanged(int)),sigmaLabelValue,SLOT(setNum(int)));
    QHBoxLayout *hboxSigma = new QHBoxLayout;
    hboxSigma->addWidget(sigmaLabel);
    hboxSigma->addWidget(sigmaLabelValue);
    hboxSigma->addWidget(sigmaSlider);
    sliderLayout->addLayout(hboxSigma);









    controlePanel->setLayout(sliderLayout);

    return controlePanel;
}



void MainWindow::refreshStatusBar(){
    QString currentDrawMode=QString::fromStdString(_viewer->getDrawMode());
    QString currentLight = QStringLiteral(" Light Mode : %1").arg(_viewer->getLightSelector());
    statusBar()->showMessage(currentDrawMode + currentLight);
}

