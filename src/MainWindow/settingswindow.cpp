#include "settingswindow.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QSlider>
#include <QLabel>
#include <QSpacerItem>
#include <QPushButton>
#include <QCheckBox>


SettingsWindow::SettingsWindow():
    ui(new Ui::SettingsWindow)
{

    _ID = 0;
    ui->setupUi(this);


    setButtons();



}

SettingsWindow::~SettingsWindow()
{

}

void SettingsWindow::closeEvent(QCloseEvent *event){
    this->disconnect();
    event->accept();
}

void SettingsWindow::addPanel()
{
    ui->centralLayout->addWidget(creatNewPanel(_ID));
    // Create map in viewer;
    _ID++;
}

void SettingsWindow::reload()
{
    //reload in viewer;
}







void SettingsWindow::setButtons(){
    connect(ui->addButton,&QPushButton::clicked,this,&SettingsWindow::addPanel);
    connect(ui->reloadButton,&QPushButton::clicked,this,&SettingsWindow::reload);
}


QGroupBox* SettingsWindow::creatNewPanel(int id){

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
            [this,id](int value){
                //this->_viewer.setLightThreshold(id,value);
            }
    );


    QLabel *lightInfoLabel  = new QLabel("Limite d'angle de la lumière : (PI/) *(10): ");
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
               // this->_viewer->setGaussBlurFactor(id,value);
            }
    );

    QLabel *gaussInfoLabel  = new QLabel("Gauss Blur Facteur :");
    QLabel *gaussValueLabel = new QLabel();
    connect(gaussSlider,&QSlider::valueChanged,gaussValueLabel,qOverload<int>(&QLabel::setNum));

    gaussLayout->addWidget(gaussInfoLabel);
    gaussLayout->addWidget(gaussValueLabel);
    gaussLayout->addWidget(gaussSlider);

    QCheckBox *enabledBox = new QCheckBox();
    QPushButton *deleteButton = new QPushButton("Supprimer");
    QLabel *enabledLabel = new QLabel("Activer ");

    settingsLayout->addWidget(enabledLabel);
    settingsLayout->addWidget(enabledBox);
    settingsLayout->addWidget(deleteButton);


    mainLayout->addLayout(lightLayout);
    mainLayout->addLayout(gaussLayout);
    mainLayout->addLayout(settingsLayout);

    mainGroupBox->setLayout(mainLayout);

    return mainGroupBox;


}



