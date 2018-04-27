
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
#include <QCheckBox>

using namespace std;
MainWindow::MainWindow() :
    ui(new Ui::MainWindow),
    _ID(0)
{

     ui->setupUi(this);
     setupMenu();
     setupControlePanel();

     _viewer = make_unique<Viewer>();
     QObject::connect(_viewer.get(),&Viewer::initializeDone,this,&MainWindow::setupInformationPanelSlot);

     QVBoxLayout *centralLayout = new QVBoxLayout();
     centralLayout->addWidget(_viewer.get());
     ui->mainWidget->setLayout(centralLayout);

    setButtons();

    ui->settingsLayout->addWidget(createNewPanel(0,false));
}

MainWindow::~MainWindow()
{

}

void MainWindow::closeEvent(QCloseEvent *event)
{
    //_settingsWindow->close();
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
/*
    if(ke->key()==Qt::Key_A){
        _viewer->previousLight();
    }
    if(ke->key()==Qt::Key_Z){
        _viewer->nextLight();
    }*/
    if(ke->key()==Qt::Key_Space){
        _viewer->nextMaps();
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
/*
void MainWindow::updateSigma(int sigma)
{
    _viewer->setSigma((float)sigma/10.0);
}

void MainWindow::updateLightThreshold(int t){
    _viewer->setLightThreshold((float)M_PI/((float)t/10.0));
}
*/
void MainWindow::setupInformationPanelSlot(){
    refreshInformationPanel();
}

void MainWindow::updateDrawMode(int d)
{
    _viewer->setDrawMode(d);
    refreshInformationPanel();
}
/*
void MainWindow::updateGaussBlurFactor(int g){
    _viewer->setGaussBlurFactor(g);
}*/

void MainWindow::reloadGaussHeightMap(){
    _viewer->reloadGaussHeightMap();
    ui->mainWidget->setFocus();
}

void MainWindow::addNewPanel()
{
    _ID++;
    ui->settingsLayout->addWidget(createNewPanel(_ID,true));
    _viewer->addGaussMaps(_ID);

}




/************************************************
 *              Private Functions               *
 ************************************************/

void MainWindow::setupMenu(){

    //const QIcon openIcon = QIcon::fromTheme("document-open"); //TODO Image
    connect(ui->loadModelAction,&QAction::triggered,this,&MainWindow::open);
    connect(ui->screenshotAction,&QAction::triggered,this,&MainWindow::saveScreenshot);
    connect(ui->exitAction,&QAction::triggered,this,&QWidget::close);
}

void MainWindow::setupControlePanel()
{
    ui->sigmaSlider->setSliderPosition(10);
    //connect(ui->sigmaSlider,&QSlider::valueChanged,this,&MainWindow::updateSigma);
    ui->lightSlider->setSliderPosition(45);
    connect(ui->lightSlider,&QSlider::valueChanged,this,&MainWindow::updateLightPosition);
    ui->lightThresholdSlider->setSliderPosition(30);
    //connect(ui->lightThresholdSlider,&QSlider::valueChanged,this,&MainWindow::updateLightThreshold);
    ui->gaussBlurSlider->setSliderPosition(3);
    //connect(ui->gaussBlurSlider,&QSlider::valueChanged,this,&MainWindow::updateGaussBlurFactor);

   // connect(ui->GaussBlurButton,&QPushButton::clicked,this,&MainWindow::reloadGaussHeightMap);
    connect(ui->drawModeSlider,&QSlider::valueChanged,this,&MainWindow::updateDrawMode);
}


void MainWindow::refreshInformationPanel(){

    ui->drawMode->setText(QString::fromStdString(_viewer->getCurrentDrawMode()));
    ui->shader->setText(QString::fromStdString(_viewer->getCurrentShader()));
    ui->currentMaps->setText(QStringLiteral("%1").arg(_viewer->getCurrentMapsIndex()));
    //ui->lightMode->setText(QStringLiteral("%1").arg(_viewer->getLightSelector()));
}


QGroupBox* MainWindow::createNewPanel(int id, bool doDeleteButtons){

    QString title = QString("Gauss ID : %1").arg(id);

    QGroupBox *mainGroupBox = new QGroupBox(title);
    QVBoxLayout *mainLayout = new QVBoxLayout();




    QHBoxLayout *lightLayout = new QHBoxLayout();
    QHBoxLayout *gaussLayout = new QHBoxLayout();
    QHBoxLayout *settingsLayout = new QHBoxLayout();


    QSlider *lightSlider = new QSlider(Qt::Horizontal);
    lightSlider->setMinimum(20);
    lightSlider->setMaximum(100);
    lightSlider->setSliderPosition(30);

    connect(lightSlider, &QSlider::valueChanged,
            [this,id](int t){
                this->_viewer->setLightThreshold(id,(float)M_PI/((float)t/10.0));
            }
    );


    QLabel *lightInfoLabel  = new QLabel("Angle max:(PI/(t/10)) t=");
    QLabel *lightValueLabel = new QLabel();
    connect(lightSlider,&QSlider::valueChanged,lightValueLabel,qOverload<int>(&QLabel::setNum));

    lightLayout->addWidget(lightInfoLabel);
    lightLayout->addWidget(lightValueLabel);
    lightLayout->addWidget(lightSlider);



    QSlider *gaussSlider = new QSlider(Qt::Horizontal);
    gaussSlider->setMinimum(0);
    gaussSlider->setMaximum(100);
    gaussSlider->setSliderPosition(0);

    connect(gaussSlider, &QSlider::valueChanged,
            [this,id](int value){



                this->_viewer->setGaussBlurFactor(id,value);
            }
    );

    QLabel *gaussInfoLabel  = new QLabel("Gauss Blur Facteur :");
    QLabel *gaussValueLabel = new QLabel();
    connect(gaussSlider,&QSlider::valueChanged,gaussValueLabel,qOverload<int>(&QLabel::setNum));

    gaussLayout->addWidget(gaussInfoLabel);
    gaussLayout->addWidget(gaussValueLabel);
    gaussLayout->addWidget(gaussSlider);


    QLabel *enabledLabel = new QLabel("Activer ");
    QCheckBox *enabledBox = new QCheckBox();
    connect(enabledBox, &QCheckBox::stateChanged,
            [this,id](int value){
                bool b=true;
                if(value==0) b=false ;
                this->_viewer->setEnabledMaps(id,b);
                this->ui->mainWidget->setFocus();
            }
    );


    settingsLayout->addWidget(enabledLabel);
    settingsLayout->addWidget(enabledBox);

    if(doDeleteButtons){
        QPushButton *deleteButton = new QPushButton("Supprimer");
        settingsLayout->addWidget(deleteButton);
    }


    mainLayout->addLayout(lightLayout);
    mainLayout->addLayout(gaussLayout);
    mainLayout->addLayout(settingsLayout);

    mainGroupBox->setLayout(mainLayout);

    return mainGroupBox;


}
void MainWindow::setButtons(){
    connect(ui->addButton,&QPushButton::clicked,this,&MainWindow::addNewPanel);
    connect(ui->reloadButton,&QPushButton::clicked,this,&MainWindow::reloadGaussHeightMap);
}

