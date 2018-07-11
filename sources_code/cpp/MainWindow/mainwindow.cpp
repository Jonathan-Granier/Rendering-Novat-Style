/**
* @file mainwindow.cpp
* @author Jonathan Granier
* @copyright  This code was writen for the research project
*             "Rendering panorama maps in the "atelier Novat" style.
*             Performed at Inria Grenoble Rhöne-Alpes, Maverick Team.
*             Univ.Grenoble Alpes, LJK, INRIA.
*             Under the supervision of : Joelle THOLLOT and Romain VERGNE.
*/


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
#include <QInputDialog>
#include <QRadioButton>
#include <QGridLayout>
#include <QColorDialog>

using namespace std;
MainWindow::MainWindow() :
    ui(new Ui::MainWindow),
    _id(0)
{

     ui->setupUi(this);
     setupMenu();
     setupControlePanel();
     setupShadeSettings();
     setupShadowSettings();
     setupColorSettings();

     _viewer = make_unique<Viewer>();
     QObject::connect(_viewer.get(),&Viewer::initializeDone,this,&MainWindow::setupInformationPanelSlot);

     QVBoxLayout *centralLayout = new QVBoxLayout();
     centralLayout->addWidget(_viewer.get());
     ui->mainWidget->setLayout(centralLayout);

    setupButtons();
    _currentScaleSelector = new QButtonGroup();

    ui->settingsLayout->addWidget(createNewPanel(0,true));
}

MainWindow::~MainWindow()
{

}

void MainWindow::closeEvent(QCloseEvent *event)
{
    this->disconnect();
    event->accept();
}

void MainWindow::keyPressEvent(QKeyEvent *ke)
{
    if(ke->key()==Qt::Key_I) {
      _viewer->resetTheCameraPosition();

    }

    if(ke->key()==Qt::Key_R){
       _viewer->reloadShader();

   }

    if(ke->key()==Qt::Key_P){
        _viewer->printCamAndLight();
    }

    if(ke->key()==Qt::Key_D){
        _viewer->fixeCamAndLight();
    }

    if(ke->key()==Qt::Key_W){
        _viewer->previousDrawMode();
        int value = ui->drawModeSlider->value();
        ui->drawModeSlider->setValue((value-1+12)%12);
    }
    if(ke->key()==Qt::Key_X){
        _viewer->nextDrawMode();
        int value = ui->drawModeSlider->value();
        ui->drawModeSlider->setValue((value+1)%12);
    }

    refreshInformationPanel();
}


void MainWindow::open()
{

    QFileDialog browser;
    QStringList fileNames = browser.getOpenFileNames(this, tr("Open DEM(s) (.asc)"), QDir::currentPath()+"/../ressources/models",tr("DEM (*.asc)"));
    browser.close();
    if(!fileNames.isEmpty())
    {

        if(!_viewer->loadSceneFromFile(fileNames)){
            QMessageBox::warning(this,tr("MainWindow"),tr("unknow type file !"),QMessageBox::Ok);
        }
    }

}

void MainWindow::generateScene(){
    _viewer->generateScene();
}

void MainWindow::saveScreenshot()
{

    QImage screenshot =_viewer->grabFramebuffer();
    QFileDialog dialog(this, "Save the screenshot", QDir::currentPath()+"/../ressources/screenshots","*.png *.jpg");
    dialog.setAcceptMode(QFileDialog::AcceptSave);
    QString filename;
    int ret = dialog.exec();
    if(ret == QDialog::Accepted){
        filename = dialog.selectedFiles()[0];
        if(!screenshot.save(filename)){
            QMessageBox::warning(0,tr("MainWindow"),tr("Can not save screenshot :") + filename, QMessageBox::Ok);
        }
    }


}

void MainWindow::help()
{
    QErrorMessage errorMessageDialog(this);
    errorMessageDialog.showMessage(tr("Not Implemented! See the report (in french) and the documentation"));
}

void MainWindow::about()
{
    QMessageBox::about(this, tr("About Rendering in Novat style"),
                tr("Prototype of a shadow rendering software \n"
                "in the style of the mountain panoramas of the painters \n "
                "Pierre Novat and Arthur Novat. \n"
                "Create by Jonathan Granier\n"
                "In the MAVERICK Team (LJK,INRIA)\n"));
}

void MainWindow::updateLightPosition(int angle)
{
    _viewer->setHeightLight((float)angle);
     ui->mainWidget->setFocus();
}

void MainWindow::updateShadowLightPosition(int angle)
{
    _viewer->setPitchShadowLight((float)angle);
     ui->mainWidget->setFocus();
}


void MainWindow::setupInformationPanelSlot(){
    refreshInformationPanel();
    ui->mainWidget->setFocus();
}

void MainWindow::updateDrawMode(int d)
{
    _viewer->setDrawMode(d);
    refreshInformationPanel();
    ui->mainWidget->setFocus();
}


void MainWindow::reloadLaplacienPyramid(){
    _viewer->reloadLaplacienPyramid();
    ui->mainWidget->setFocus();
}

void MainWindow::addNewPanel()
{
    _id++;
    ui->settingsLayout->addWidget(createNewPanel(_id,false));
    _viewer->addScale(_id);

}

void MainWindow::setShadowEnabled(int b)
{
    if(b==0)
        _viewer->setDoShadow(false);
    else
        _viewer->setDoShadow(true);
     ui->mainWidget->setFocus();
}

void MainWindow::setShadowEnabledMorpho(int b)
{

    if(b==0)
        _viewer->setDoShadowMorpho(false);
    else
        _viewer->setDoShadowMorpho(true);

    ui->mainWidget->setFocus();
}

void MainWindow::setShadowEnabledLightDir(int b)
{

    if(b==0)
        _viewer->setDoEditShadowLightDir(false);
    else
        _viewer->setDoEditShadowLightDir(true);

    ui->mainWidget->setFocus();
}

void MainWindow::setShadeEnabledLightDir(int b)
{
    if(b==0)
        _viewer->setDoEditShadeLightDir(false);
    else
        _viewer->setDoEditShadeLightDir(true);
    ui->mainWidget->setFocus();
}

void MainWindow::setDoDefaultShading(int b)
{
    if(b==0)
        _viewer->setDoDefaultShading(false);
    else
        _viewer->setDoDefaultShading(true);
    ui->mainWidget->setFocus();
}

QColor MainWindow::selectColor(QColor currentColor)
{
    return QColorDialog::getColor(currentColor,this);
}

QString MainWindow::loadTexture()
{
    QFileDialog browser;
    QString fileName = browser.getOpenFileName(this, tr("Load a texture"), QDir::currentPath()+"/../ressources/textures",tr("Textures (*.png)"));
    browser.close();
    return fileName;
}




/************************************************
 *              Private Functions               *
 ************************************************/

void MainWindow::setupMenu(){

    connect(ui->loadModelAction,&QAction::triggered,this,&MainWindow::open);
    connect(ui->generateModelAction,&QAction::triggered,this,&MainWindow::generateScene);
    connect(ui->screenshotAction,&QAction::triggered,this,&MainWindow::saveScreenshot);
    connect(ui->exitAction,&QAction::triggered,this,&QWidget::close);

    connect(ui->helpAction,&QAction::triggered,this,&MainWindow::help);
    connect(ui->aboutAction,&QAction::triggered,this,&MainWindow::about);
}

void MainWindow::setupControlePanel()
{
    connect(ui->drawModeSlider,&QSlider::valueChanged,this,&MainWindow::updateDrawMode);
    connect(ui->doDefaultShading,&QCheckBox::toggled,this,&MainWindow::setDoDefaultShading);
}



void MainWindow::setupShadeSettings(){

    connect(ui->shadeRadio0,&QRadioButton::pressed,this, [this](){
            this->_viewer->setShadeSelector(0);

        }
    );
    connect(ui->shadeRadio1,&QRadioButton::pressed,this, [this](){
            this->_viewer->setShadeSelector(1);

        }
    );

    connect(ui->shadeRadio2,&QRadioButton::pressed,this, [this](){
            this->_viewer->setShadeSelector(2);

        }
    );

    connect(ui->shadeRadio3,&QRadioButton::pressed,this, [this](){
            this->_viewer->setShadeSelector(3);

        }
    );

    connect(ui->shadeCheckBoxLightDir,&QRadioButton::toggled,this,&MainWindow::setShadeEnabledLightDir);
        connect(ui->lightShadingSlider,&QSlider::valueChanged,this,&MainWindow::updateLightPosition);
}


void MainWindow::setupShadowSettings(){
    connect(ui->shadowGroupBox,&QGroupBox::toggled,this,&MainWindow::setShadowEnabled);
    connect(ui->shadowCheckBoxMorpho,&QRadioButton::toggled,this,&MainWindow::setShadowEnabledMorpho);
    connect(ui->shadowCheckBoxLightDir,&QRadioButton::toggled,this,&MainWindow::setShadowEnabledLightDir);
    connect(ui->lightShadowSlider,&QSlider::valueChanged,this,&MainWindow::updateShadowLightPosition);
}

void MainWindow::setupColorSettings(){
    connect(ui->colorRadio0,&QRadioButton::pressed,this, [this](){
            this->_viewer->setColorSelector(0);

        }
    );
    connect(ui->colorRadio1,&QRadioButton::pressed,this, [this](){
            this->_viewer->setColorSelector(1);

        }
    );

    connect(ui->colorRadio2,&QRadioButton::pressed,this, [this](){
            this->_viewer->setColorSelector(2);

        }
    );

    connect(ui->colorRadio3,&QRadioButton::pressed,this, [this](){
            this->_viewer->setColorSelector(3);

        }
    );

    connect(ui->colorButton0,&QRadioButton::pressed,this,[this](){
        QColor c = selectColor(_viewer->getPlainColor());
        if(c.isValid())
            _viewer->setPlainColor(c);
    }
    );
    connect(ui->colorButton1,&QRadioButton::pressed,this,[this](){
        QColor c = selectColor(_viewer->getWaterColor());
        if(c.isValid())
            _viewer->setWaterColor(c);
    }
    );

    connect(ui->colorButton2,&QRadioButton::pressed,this,[this](){
        QString s = loadTexture();
        if(!s.isEmpty())
            _viewer->loadColorMapTex(s);
    }
    );

    connect(ui->colorButton3,&QRadioButton::pressed,this,[this](){
        QString s = loadTexture();
        if(!s.isEmpty())
            _viewer->loadCelShadingTex(s);
    }
    );

}

void MainWindow::setupButtons(){
    connect(ui->addButton,&QPushButton::clicked,this,&MainWindow::addNewPanel);
    connect(ui->reloadButton,&QPushButton::clicked,this,&MainWindow::reloadLaplacienPyramid);
}


void MainWindow::refreshInformationPanel(){

    ui->drawMode->setText(QString::fromStdString(_viewer->getCurrentDrawMode()));
}


QGroupBox* MainWindow::createNewPanel(int id, bool firstPanel){

    QString title = QString("Scale ID : %1").arg(id);


    QGroupBox *mainGroupBox = new QGroupBox(title);
    QVBoxLayout *mainLayout = new QVBoxLayout();
    mainGroupBox->setCheckable(true);



    QHBoxLayout *lightLayout = new QHBoxLayout();
    QHBoxLayout *gaussLayout = new QHBoxLayout();


    QSlider *lightSlider = new QSlider(Qt::Horizontal);
    lightSlider->setMinimum(20);
    lightSlider->setMaximum(100);
    lightSlider->setSliderPosition(30);

    connect(lightSlider, &QSlider::valueChanged,
            [this,id](int t){
                this->_viewer->setLightThreshold(id,(float)M_PI/((float)t/10.0));
                this->ui->mainWidget->setFocus();
            }
    );


    QLabel *lightInfoLabel  = new QLabel("Angle limit:(PI/(T/10)) T=");
    QLabel *lightValueLabel = new QLabel();
    lightValueLabel->setNum(30);
    // Version QT5.7 and more
    //connect(lightSlider,&QSlider::valueChanged,lightValueLabel,qOverload<int>(&QLabel::setNum));
    // Version QT5.6 and less
    connect(lightSlider,&QSlider::valueChanged,lightValueLabel,static_cast<void (QLabel::*)(int)>(&QLabel::setNum));



    lightLayout->addWidget(lightInfoLabel);
    lightLayout->addWidget(lightValueLabel);
    lightLayout->addWidget(lightSlider);


    if(!firstPanel){
        QSlider *gaussSlider = new QSlider(Qt::Horizontal);
        gaussSlider->setMinimum(0);
        gaussSlider->setMaximum(100);
        gaussSlider->setSliderPosition(0);

        connect(gaussSlider, &QSlider::valueChanged,
                [this,id](int value){
                    this->_viewer->setGaussBlurFactor(id,value);
                    this->ui->mainWidget->setFocus();
                }
        );

        QLabel *gaussInfoLabel  = new QLabel("Blur (sigma) :");
        QLabel *gaussValueLabel = new QLabel();
        gaussValueLabel->setNum(0);
        // Version QT5.7 and more
        //connect(gaussSlider,&QSlider::valueChanged,gaussValueLabel,qOverload<int>(&QLabel::setNum));
        // Version QT5.6 and less
        connect(gaussSlider,&QSlider::valueChanged,gaussValueLabel,static_cast<void (QLabel::*)(int)>(&QLabel::setNum));

        gaussLayout->addWidget(gaussInfoLabel);
        gaussLayout->addWidget(gaussValueLabel);
        gaussLayout->addWidget(gaussSlider);
    }


    if(!firstPanel){
        mainGroupBox->setChecked(false);
    }


    connect(mainGroupBox, &QGroupBox::toggled,
            [this,id](int value){
                bool b=true;
                if(value==0) b=false ;
                this->_viewer->setEnabledScale(id,b);
                this->ui->mainWidget->setFocus();
            }
    );


    mainLayout->addLayout(lightLayout);
    mainLayout->addLayout(gaussLayout);




    QRadioButton *selectCurrent = new QRadioButton;
    if(firstPanel){
        selectCurrent->setChecked(true);
    }

    connect(selectCurrent, &QRadioButton::toggled,
            [this,id](){
                this->_viewer->selectCurrentScale(id);
                this->ui->mainWidget->setFocus();
            }
    );


    _currentScaleSelector->addButton(selectCurrent);
    QGridLayout *gridLayout = new QGridLayout;
    gridLayout->addWidget(selectCurrent,0,0,1,1);
    gridLayout->addLayout(mainLayout,0,1,1,9);

    mainGroupBox->setLayout(gridLayout);

    return mainGroupBox;


}
