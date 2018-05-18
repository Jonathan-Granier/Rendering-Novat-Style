
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
        bool ok;
        int numText = QInputDialog::getInt(this,tr("Numero du test"),tr("Numero du test :"),0,0,1000,1,&ok);
        if(ok){
            _viewer->makeATest(numText);
        }

    }
    if(ke->key()==Qt::Key_B){
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
    _ID++;
    ui->settingsLayout->addWidget(createNewPanel(_ID,false));
    _viewer->addGaussMaps(_ID);

}


void MainWindow::updateShadow(int s){
    if(s==0)
        _viewer->setDoShadow(false);
    else
        _viewer->setDoShadow(true);
     ui->mainWidget->setFocus();
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
    ui->lightSlider->setSliderPosition(45);
    connect(ui->lightSlider,&QSlider::valueChanged,this,&MainWindow::updateLightPosition);


    connect(ui->typeShading0,&QRadioButton::pressed,this, [this](){
            this->_viewer->setTypeShading(0);

        }
    );
    connect(ui->typeShading1,&QRadioButton::pressed,this, [this](){
            this->_viewer->setTypeShading(1);
        }
    );
    connect(ui->typeShading2,&QRadioButton::pressed,this, [this](){
            this->_viewer->setTypeShading(2);
        }
    );

    connect(ui->typeMerge0,&QRadioButton::pressed,this, [this](){
            this->_viewer->setTypeMerge(0);

        }
    );
    connect(ui->typeMerge1,&QRadioButton::pressed,this, [this](){
            this->_viewer->setTypeMerge(1);

        }
    );
    connect(ui->typeMerge2,&QRadioButton::pressed,this, [this](){
            this->_viewer->setTypeMerge(2);
        }
    );

    connect(ui->shade0,&QRadioButton::pressed,this, [this](){
            this->_viewer->setShadeSelector(0);

        }
    );
    connect(ui->shade1,&QRadioButton::pressed,this, [this](){
            this->_viewer->setShadeSelector(1);

        }
    );

    connect(ui->shade2,&QRadioButton::pressed,this, [this](){
            this->_viewer->setShadeSelector(2);

        }
    );

    connect(ui->shade3,&QRadioButton::pressed,this, [this](){
            this->_viewer->setShadeSelector(3);

        }
    );


    connect(ui->shadowCheckBox,&QCheckBox::stateChanged,this,&MainWindow::updateShadow);

   // connect(ui->GaussBlurButton,&QPushButton::clicked,this,&MainWindow::reloadGaussHeightMap);

}


void MainWindow::refreshInformationPanel(){

    ui->drawMode->setText(QString::fromStdString(_viewer->getCurrentDrawMode()));
    ui->shader->setText(QString::fromStdString(_viewer->getCurrentShader()));
    ui->currentMaps->setText(QStringLiteral("%1").arg(_viewer->getCurrentMapsIndex()));
    //ui->lightMode->setText(QStringLiteral("%1").arg(_viewer->getLightSelector()));
}


QGroupBox* MainWindow::createNewPanel(int id, bool firstPanel){

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

        QLabel *gaussInfoLabel  = new QLabel("Gauss Blur Facteur :");
        QLabel *gaussValueLabel = new QLabel();
        gaussValueLabel->setNum(0);
        connect(gaussSlider,&QSlider::valueChanged,gaussValueLabel,qOverload<int>(&QLabel::setNum));

        gaussLayout->addWidget(gaussInfoLabel);
        gaussLayout->addWidget(gaussValueLabel);
        gaussLayout->addWidget(gaussSlider);
    }

    QLabel *enabledLabel = new QLabel("Activer ");
    QCheckBox *enabledBox = new QCheckBox();

    if(firstPanel){
        enabledBox->setChecked(true);
    }

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

    if(!firstPanel){
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

