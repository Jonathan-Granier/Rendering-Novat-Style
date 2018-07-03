
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
    _currentMapsSelector = new QButtonGroup();

    ui->settingsLayout->addWidget(createNewPanel(0,true));
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
    QStringList fileNames = browser.getOpenFileNames(this, tr("Open Models"), QDir::currentPath()+"/models",tr("Models (*.asc *.obj)"));
    browser.close(); // FIXME , don't always work
    if(!fileNames.isEmpty())
    {

        if(!_viewer->loadSceneFromFile(fileNames)){
            QMessageBox::warning(this,tr("MainWindow"),tr("unknow type file !"),QMessageBox::Ok);
        }
    }

}

void MainWindow::generateModel(){
    _viewer->generateScene();
}

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
     ui->mainWidget->setFocus();
}

void MainWindow::updateShadowLightPosition(int angle)
{
    _viewer->setPitchShadowLight((float)angle);
     ui->mainWidget->setFocus();
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
    ui->mainWidget->setFocus();
}

void MainWindow::updateDrawMode(int d)
{
    _viewer->setDrawMode(d);
    refreshInformationPanel();
    ui->mainWidget->setFocus();
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
    _id++;
    ui->settingsLayout->addWidget(createNewPanel(_id,false));
    _viewer->addGaussMaps(_id);

}

void MainWindow::setShadowEnabled(int b)
{
    if(b==0)
        _viewer->setShadowEnabled(false);
    else
        _viewer->setShadowEnabled(true);
     ui->mainWidget->setFocus();
}

void MainWindow::setShadowEnabledMorpho(int b)
{

    if(b==0)
        _viewer->setShadowEnabledMorpho(false);
    else
        _viewer->setShadowEnabledMorpho(true);

    ui->mainWidget->setFocus();
}

void MainWindow::setShadowEnabledLightDir(int b)
{

    if(b==0)
        _viewer->setShadowEnabledLightDir(false);
    else
        _viewer->setShadowEnabledLightDir(true);

    ui->mainWidget->setFocus();
}

void MainWindow::setShadeEnabledLightDir(int b)
{
    if(b==0)
        _viewer->setShadeEnabledLightDir(false);
    else
        _viewer->setShadeEnabledLightDir(true);
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
    QString fileName = browser.getOpenFileName(this, tr("Charger une texture"), QDir::currentPath()+"/textures",tr("Textures (*.png)"));
    browser.close();
    return fileName;
}




/************************************************
 *              Private Functions               *
 ************************************************/

void MainWindow::setupMenu(){

    //const QIcon openIcon = QIcon::fromTheme("document-open"); //TODO Image
    connect(ui->loadModelAction,&QAction::triggered,this,&MainWindow::open);
    connect(ui->generateModelAction,&QAction::triggered,this,&MainWindow::generateModel);
    connect(ui->screenshotAction,&QAction::triggered,this,&MainWindow::saveScreenshot);
    connect(ui->exitAction,&QAction::triggered,this,&QWidget::close);
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
    connect(ui->reloadButton,&QPushButton::clicked,this,&MainWindow::reloadGaussHeightMap);
}


void MainWindow::refreshInformationPanel(){

    ui->drawMode->setText(QString::fromStdString(_viewer->getCurrentDrawMode()));
    //ui->currentMaps->setText(QStringLiteral("%1").arg(_viewer->getCurrentMapsIndex()));
    //ui->lightMode->setText(QStringLiteral("%1").arg(_viewer->getLightSelector()));
}


QGroupBox* MainWindow::createNewPanel(int id, bool firstPanel){

    QString title = QString("Maps ID : %1").arg(id);


    QGroupBox *mainGroupBox = new QGroupBox(title);
    QVBoxLayout *mainLayout = new QVBoxLayout();
    mainGroupBox->setCheckable(true);



    QHBoxLayout *lightLayout = new QHBoxLayout();
    QHBoxLayout *gaussLayout = new QHBoxLayout();
   // QHBoxLayout *settingsLayout = new QHBoxLayout();


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


    QLabel *lightInfoLabel  = new QLabel("Angle max:(PI/(t/10)) t=");
    QLabel *lightValueLabel = new QLabel();
    lightValueLabel->setNum(30);
    connect(lightSlider,&QSlider::valueChanged,lightValueLabel,qOverload<int>(&QLabel::setNum));

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

        QLabel *gaussInfoLabel  = new QLabel("Niveau de flou :");
        QLabel *gaussValueLabel = new QLabel();
        gaussValueLabel->setNum(0);
        connect(gaussSlider,&QSlider::valueChanged,gaussValueLabel,qOverload<int>(&QLabel::setNum));

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
                this->_viewer->setEnabledMaps(id,b);
                this->ui->mainWidget->setFocus();
            }
    );


    mainLayout->addLayout(lightLayout);
    mainLayout->addLayout(gaussLayout);
   // mainLayout->addLayout(settingsLayout);




    QRadioButton *selectCurrent = new QRadioButton;
    if(firstPanel){
        selectCurrent->setChecked(true);
    }

    connect(selectCurrent, &QRadioButton::toggled,
            [this,id](){
                this->_viewer->selectCurrentMaps(id);
                this->ui->mainWidget->setFocus();
            }
    );


    _currentMapsSelector->addButton(selectCurrent);
    QGridLayout *gridLayout = new QGridLayout;
    gridLayout->addWidget(selectCurrent,0,0,1,1);
    gridLayout->addLayout(mainLayout,0,1,1,9);

    mainGroupBox->setLayout(gridLayout);

    return mainGroupBox;


}


