
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
MainWindow::MainWindow() :
    ui(new Ui::MainWindow)
{

     ui->setupUi(this);
     setupMenu();
     setupControlePanel();

     _viewer = make_unique<Viewer>();
     QObject::connect(_viewer.get(),&Viewer::initializeDone,this,&MainWindow::setupInformationPanelSlot);

     QVBoxLayout *centralLayout = new QVBoxLayout();
     centralLayout->addWidget(_viewer.get());
     ui->mainWidget->setLayout(centralLayout);



    /*this->setFixedSize(1200,1000);
    // TODO set Icon
    // TODO window->setWorkingDirectory(appPath, sceneName, textureName, envMapName);

    //Allocation
    _viewer = make_unique<Viewer>();




     // _viewer->setFixedSize(1200, 700);
   // setupMenu();
    QWidget *controlePanel = setupControlePanel();
   // QWidget *controlePanel = new QWidget();
    controlePanel->setMaximumHeight(100);
    QWidget *centralWidget = new QWidget();
    QVBoxLayout *centralLayout = new QVBoxLayout();
    centralLayout->addWidget(_viewer.get());
    centralLayout->addWidget(controlePanel);

    centralWidget->setLayout(centralLayout);


   // setCentralWidget(centralWidget);
    */
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
    refreshInformationPanel();
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

void MainWindow::setupInformationPanelSlot(){
    refreshInformationPanel();
}



void MainWindow::setupMenu(){

    //const QIcon openIcon = QIcon::fromTheme("document-open"); //TODO Image
    connect(ui->loadModelAction,&QAction::triggered,this,&MainWindow::open);
    connect(ui->screenshotAction,&QAction::triggered,this,&MainWindow::saveScreenshot);
    connect(ui->exitAction,&QAction::triggered,this,&QWidget::close);
}

void MainWindow::setupControlePanel()
{
    ui->sigmaSlider->setSliderPosition(10);
    connect(ui->sigmaSlider,&QSlider::valueChanged,this,&MainWindow::updateSigma);
    ui->lightSlider->setSliderPosition(45);
    connect(ui->lightSlider,&QSlider::valueChanged,this,&MainWindow::updateLightPosition);
}



void MainWindow::refreshInformationPanel(){

    ui->drawMode->setText(QString::fromStdString(_viewer->getCurrentDrawMode()));
    ui->shader->setText(QString::fromStdString(_viewer->getCurrentShader()));
    ui->lightMode->setText(QStringLiteral("%1").arg(_viewer->getLightSelector()));
}

/*
void MainWindow::refreshStatusBar(){
    QString currentDrawMode=QString::fromStdString(_viewer->getDrawMode());
    QString currentLight = QStringLiteral(" Light Mode : %1").arg(_viewer->getLightSelector());
    statusBar()->showMessage(currentDrawMode + currentLight);
}
*/
