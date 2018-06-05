/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *loadModelAction;
    QAction *screenshotAction;
    QAction *actionAide;
    QAction *actionA_propos;
    QAction *exitAction;
    QAction *actionMesh;
    QAction *actionHeight_Map;
    QAction *actionNormal_Map;
    QAction *actionCurvature_Map;
    QAction *actionLight_Map;
    QAction *generateModelAction;
    QWidget *centralwidget;
    QWidget *mainWidget;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout_8;
    QPushButton *reloadButton;
    QPushButton *addButton;
    QGroupBox *multiScaleGroupeBox;
    QWidget *verticalLayoutWidget_4;
    QVBoxLayout *settingsLayout;
    QFrame *line;
    QWidget *horizontalLayoutWidget_3;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_6;
    QLabel *shader;
    QWidget *verticalLayoutWidget_3;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout;
    QLabel *informationTitle;
    QLabel *drawMode;
    QSpacerItem *horizontalSpacer_3;
    QSlider *drawModeSlider;
    QGroupBox *colorGroupeBox;
    QWidget *gridLayoutWidget;
    QGridLayout *colorGridLayout;
    QRadioButton *colorRadio2;
    QRadioButton *colorRadio3;
    QRadioButton *colorRadio0;
    QRadioButton *colorRadio1;
    QPushButton *colorButton0;
    QPushButton *colorButton1;
    QPushButton *colorButton2;
    QPushButton *colorButton3;
    QGroupBox *shadowGroupBox;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *shadowVerticalLayout;
    QCheckBox *shadowCheckBoxLightDir;
    QCheckBox *shadowCheckBoxMorpho;
    QVBoxLayout *verticalLayout_7;
    QHBoxLayout *horizontalLayout_7;
    QLabel *lightShadowPosLabel;
    QLabel *lightShadowPosValue;
    QSpacerItem *horizontalSpacer_4;
    QSlider *lightShadowSlider;
    QGroupBox *shadingGroupeBox;
    QWidget *verticalLayoutWidget_5;
    QVBoxLayout *verticalLayout_5;
    QCheckBox *shadeCheckBoxLightDir;
    QHBoxLayout *horizontalLayout_4;
    QRadioButton *shadeRadio0;
    QRadioButton *shadeRadio1;
    QRadioButton *shadeRadio2;
    QRadioButton *shadeRadio3;
    QVBoxLayout *verticalLayout_4;
    QHBoxLayout *horizontalLayout_3;
    QLabel *lightShadingPosLabel;
    QLabel *lightShadingPosValue;
    QSpacerItem *horizontalSpacer_2;
    QSlider *lightShadingSlider;
    QMenuBar *menubar;
    QMenu *menuFile;
    QMenu *menuAide;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->setWindowModality(Qt::WindowModal);
        MainWindow->resize(1586, 1011);
        MainWindow->setBaseSize(QSize(1220, 1010));
        QIcon icon;
        icon.addFile(QStringLiteral("../../../../../../../../../../../../../../images/RSN.ico"), QSize(), QIcon::Normal, QIcon::Off);
        MainWindow->setWindowIcon(icon);
        loadModelAction = new QAction(MainWindow);
        loadModelAction->setObjectName(QStringLiteral("loadModelAction"));
        screenshotAction = new QAction(MainWindow);
        screenshotAction->setObjectName(QStringLiteral("screenshotAction"));
        actionAide = new QAction(MainWindow);
        actionAide->setObjectName(QStringLiteral("actionAide"));
        actionA_propos = new QAction(MainWindow);
        actionA_propos->setObjectName(QStringLiteral("actionA_propos"));
        exitAction = new QAction(MainWindow);
        exitAction->setObjectName(QStringLiteral("exitAction"));
        actionMesh = new QAction(MainWindow);
        actionMesh->setObjectName(QStringLiteral("actionMesh"));
        actionMesh->setCheckable(true);
        actionHeight_Map = new QAction(MainWindow);
        actionHeight_Map->setObjectName(QStringLiteral("actionHeight_Map"));
        actionNormal_Map = new QAction(MainWindow);
        actionNormal_Map->setObjectName(QStringLiteral("actionNormal_Map"));
        actionCurvature_Map = new QAction(MainWindow);
        actionCurvature_Map->setObjectName(QStringLiteral("actionCurvature_Map"));
        actionLight_Map = new QAction(MainWindow);
        actionLight_Map->setObjectName(QStringLiteral("actionLight_Map"));
        generateModelAction = new QAction(MainWindow);
        generateModelAction->setObjectName(QStringLiteral("generateModelAction"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        mainWidget = new QWidget(centralwidget);
        mainWidget->setObjectName(QStringLiteral("mainWidget"));
        mainWidget->setGeometry(QRect(10, 10, 1201, 781));
        horizontalLayoutWidget = new QWidget(centralwidget);
        horizontalLayoutWidget->setObjectName(QStringLiteral("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(1370, 740, 201, 31));
        horizontalLayout_8 = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout_8->setObjectName(QStringLiteral("horizontalLayout_8"));
        horizontalLayout_8->setContentsMargins(0, 0, 0, 0);
        reloadButton = new QPushButton(horizontalLayoutWidget);
        reloadButton->setObjectName(QStringLiteral("reloadButton"));

        horizontalLayout_8->addWidget(reloadButton);

        addButton = new QPushButton(horizontalLayoutWidget);
        addButton->setObjectName(QStringLiteral("addButton"));

        horizontalLayout_8->addWidget(addButton);

        multiScaleGroupeBox = new QGroupBox(centralwidget);
        multiScaleGroupeBox->setObjectName(QStringLiteral("multiScaleGroupeBox"));
        multiScaleGroupeBox->setGeometry(QRect(1220, 10, 361, 721));
        verticalLayoutWidget_4 = new QWidget(multiScaleGroupeBox);
        verticalLayoutWidget_4->setObjectName(QStringLiteral("verticalLayoutWidget_4"));
        verticalLayoutWidget_4->setGeometry(QRect(0, 30, 361, 121));
        settingsLayout = new QVBoxLayout(verticalLayoutWidget_4);
        settingsLayout->setObjectName(QStringLiteral("settingsLayout"));
        settingsLayout->setSizeConstraint(QLayout::SetMinimumSize);
        settingsLayout->setContentsMargins(0, 0, 0, 0);
        line = new QFrame(centralwidget);
        line->setObjectName(QStringLiteral("line"));
        line->setGeometry(QRect(1200, 770, 371, 21));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);
        horizontalLayoutWidget_3 = new QWidget(centralwidget);
        horizontalLayoutWidget_3->setObjectName(QStringLiteral("horizontalLayoutWidget_3"));
        horizontalLayoutWidget_3->setGeometry(QRect(10, 900, 201, 22));
        horizontalLayout_5 = new QHBoxLayout(horizontalLayoutWidget_3);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        horizontalLayout_5->setContentsMargins(0, 0, 0, 0);
        label_6 = new QLabel(horizontalLayoutWidget_3);
        label_6->setObjectName(QStringLiteral("label_6"));

        horizontalLayout_5->addWidget(label_6);

        shader = new QLabel(horizontalLayoutWidget_3);
        shader->setObjectName(QStringLiteral("shader"));
        shader->setStyleSheet(QStringLiteral(""));
        shader->setAlignment(Qt::AlignCenter);

        horizontalLayout_5->addWidget(shader);

        verticalLayoutWidget_3 = new QWidget(centralwidget);
        verticalLayoutWidget_3->setObjectName(QStringLiteral("verticalLayoutWidget_3"));
        verticalLayoutWidget_3->setGeometry(QRect(10, 810, 311, 81));
        verticalLayout_3 = new QVBoxLayout(verticalLayoutWidget_3);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        informationTitle = new QLabel(verticalLayoutWidget_3);
        informationTitle->setObjectName(QStringLiteral("informationTitle"));
        informationTitle->setStyleSheet(QStringLiteral(""));
        informationTitle->setAlignment(Qt::AlignCenter);

        horizontalLayout->addWidget(informationTitle);

        drawMode = new QLabel(verticalLayoutWidget_3);
        drawMode->setObjectName(QStringLiteral("drawMode"));
        drawMode->setStyleSheet(QStringLiteral("font: 9pt \"Sans Serif\";"));
        drawMode->setAlignment(Qt::AlignCenter);

        horizontalLayout->addWidget(drawMode);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_3);


        verticalLayout_3->addLayout(horizontalLayout);

        drawModeSlider = new QSlider(verticalLayoutWidget_3);
        drawModeSlider->setObjectName(QStringLiteral("drawModeSlider"));
        drawModeSlider->setMinimum(0);
        drawModeSlider->setMaximum(13);
        drawModeSlider->setValue(13);
        drawModeSlider->setOrientation(Qt::Horizontal);
        drawModeSlider->setTickPosition(QSlider::TicksBelow);

        verticalLayout_3->addWidget(drawModeSlider);

        colorGroupeBox = new QGroupBox(centralwidget);
        colorGroupeBox->setObjectName(QStringLiteral("colorGroupeBox"));
        colorGroupeBox->setGeometry(QRect(1070, 800, 511, 151));
        gridLayoutWidget = new QWidget(colorGroupeBox);
        gridLayoutWidget->setObjectName(QStringLiteral("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(10, 30, 491, 101));
        colorGridLayout = new QGridLayout(gridLayoutWidget);
        colorGridLayout->setObjectName(QStringLiteral("colorGridLayout"));
        colorGridLayout->setContentsMargins(0, 0, 0, 0);
        colorRadio2 = new QRadioButton(gridLayoutWidget);
        colorRadio2->setObjectName(QStringLiteral("colorRadio2"));

        colorGridLayout->addWidget(colorRadio2, 0, 2, 1, 1);

        colorRadio3 = new QRadioButton(gridLayoutWidget);
        colorRadio3->setObjectName(QStringLiteral("colorRadio3"));

        colorGridLayout->addWidget(colorRadio3, 0, 3, 1, 1);

        colorRadio0 = new QRadioButton(gridLayoutWidget);
        colorRadio0->setObjectName(QStringLiteral("colorRadio0"));
        colorRadio0->setChecked(true);

        colorGridLayout->addWidget(colorRadio0, 0, 0, 1, 1);

        colorRadio1 = new QRadioButton(gridLayoutWidget);
        colorRadio1->setObjectName(QStringLiteral("colorRadio1"));

        colorGridLayout->addWidget(colorRadio1, 0, 1, 1, 1);

        colorButton0 = new QPushButton(gridLayoutWidget);
        colorButton0->setObjectName(QStringLiteral("colorButton0"));

        colorGridLayout->addWidget(colorButton0, 1, 0, 1, 1);

        colorButton1 = new QPushButton(gridLayoutWidget);
        colorButton1->setObjectName(QStringLiteral("colorButton1"));

        colorGridLayout->addWidget(colorButton1, 1, 1, 1, 1);

        colorButton2 = new QPushButton(gridLayoutWidget);
        colorButton2->setObjectName(QStringLiteral("colorButton2"));

        colorGridLayout->addWidget(colorButton2, 1, 2, 1, 1);

        colorButton3 = new QPushButton(gridLayoutWidget);
        colorButton3->setObjectName(QStringLiteral("colorButton3"));

        colorGridLayout->addWidget(colorButton3, 1, 3, 1, 1);

        shadowGroupBox = new QGroupBox(centralwidget);
        shadowGroupBox->setObjectName(QStringLiteral("shadowGroupBox"));
        shadowGroupBox->setGeometry(QRect(330, 800, 361, 151));
        shadowGroupBox->setCheckable(true);
        shadowGroupBox->setChecked(false);
        verticalLayoutWidget = new QWidget(shadowGroupBox);
        verticalLayoutWidget->setObjectName(QStringLiteral("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(10, 30, 341, 111));
        shadowVerticalLayout = new QVBoxLayout(verticalLayoutWidget);
        shadowVerticalLayout->setObjectName(QStringLiteral("shadowVerticalLayout"));
        shadowVerticalLayout->setContentsMargins(0, 0, 0, 0);
        shadowCheckBoxLightDir = new QCheckBox(verticalLayoutWidget);
        shadowCheckBoxLightDir->setObjectName(QStringLiteral("shadowCheckBoxLightDir"));
        shadowCheckBoxLightDir->setChecked(true);

        shadowVerticalLayout->addWidget(shadowCheckBoxLightDir);

        shadowCheckBoxMorpho = new QCheckBox(verticalLayoutWidget);
        shadowCheckBoxMorpho->setObjectName(QStringLiteral("shadowCheckBoxMorpho"));
        shadowCheckBoxMorpho->setChecked(true);

        shadowVerticalLayout->addWidget(shadowCheckBoxMorpho);

        verticalLayout_7 = new QVBoxLayout();
        verticalLayout_7->setObjectName(QStringLiteral("verticalLayout_7"));
        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));
        lightShadowPosLabel = new QLabel(verticalLayoutWidget);
        lightShadowPosLabel->setObjectName(QStringLiteral("lightShadowPosLabel"));

        horizontalLayout_7->addWidget(lightShadowPosLabel);

        lightShadowPosValue = new QLabel(verticalLayoutWidget);
        lightShadowPosValue->setObjectName(QStringLiteral("lightShadowPosValue"));

        horizontalLayout_7->addWidget(lightShadowPosValue);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer_4);


        verticalLayout_7->addLayout(horizontalLayout_7);

        lightShadowSlider = new QSlider(verticalLayoutWidget);
        lightShadowSlider->setObjectName(QStringLiteral("lightShadowSlider"));
        lightShadowSlider->setMaximum(89);
        lightShadowSlider->setValue(45);
        lightShadowSlider->setOrientation(Qt::Horizontal);

        verticalLayout_7->addWidget(lightShadowSlider);


        shadowVerticalLayout->addLayout(verticalLayout_7);

        shadingGroupeBox = new QGroupBox(centralwidget);
        shadingGroupeBox->setObjectName(QStringLiteral("shadingGroupeBox"));
        shadingGroupeBox->setGeometry(QRect(700, 800, 361, 151));
        verticalLayoutWidget_5 = new QWidget(shadingGroupeBox);
        verticalLayoutWidget_5->setObjectName(QStringLiteral("verticalLayoutWidget_5"));
        verticalLayoutWidget_5->setGeometry(QRect(10, 30, 341, 113));
        verticalLayout_5 = new QVBoxLayout(verticalLayoutWidget_5);
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        verticalLayout_5->setContentsMargins(0, 0, 0, 0);
        shadeCheckBoxLightDir = new QCheckBox(verticalLayoutWidget_5);
        shadeCheckBoxLightDir->setObjectName(QStringLiteral("shadeCheckBoxLightDir"));
        shadeCheckBoxLightDir->setChecked(true);
        shadeCheckBoxLightDir->setTristate(false);

        verticalLayout_5->addWidget(shadeCheckBoxLightDir);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        shadeRadio0 = new QRadioButton(verticalLayoutWidget_5);
        shadeRadio0->setObjectName(QStringLiteral("shadeRadio0"));
        shadeRadio0->setChecked(false);

        horizontalLayout_4->addWidget(shadeRadio0);

        shadeRadio1 = new QRadioButton(verticalLayoutWidget_5);
        shadeRadio1->setObjectName(QStringLiteral("shadeRadio1"));

        horizontalLayout_4->addWidget(shadeRadio1);

        shadeRadio2 = new QRadioButton(verticalLayoutWidget_5);
        shadeRadio2->setObjectName(QStringLiteral("shadeRadio2"));

        horizontalLayout_4->addWidget(shadeRadio2);

        shadeRadio3 = new QRadioButton(verticalLayoutWidget_5);
        shadeRadio3->setObjectName(QStringLiteral("shadeRadio3"));
        shadeRadio3->setChecked(true);

        horizontalLayout_4->addWidget(shadeRadio3);


        verticalLayout_5->addLayout(horizontalLayout_4);

        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        lightShadingPosLabel = new QLabel(verticalLayoutWidget_5);
        lightShadingPosLabel->setObjectName(QStringLiteral("lightShadingPosLabel"));

        horizontalLayout_3->addWidget(lightShadingPosLabel);

        lightShadingPosValue = new QLabel(verticalLayoutWidget_5);
        lightShadingPosValue->setObjectName(QStringLiteral("lightShadingPosValue"));

        horizontalLayout_3->addWidget(lightShadingPosValue);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_2);


        verticalLayout_4->addLayout(horizontalLayout_3);

        lightShadingSlider = new QSlider(verticalLayoutWidget_5);
        lightShadingSlider->setObjectName(QStringLiteral("lightShadingSlider"));
        lightShadingSlider->setMaximum(89);
        lightShadingSlider->setValue(45);
        lightShadingSlider->setOrientation(Qt::Horizontal);

        verticalLayout_4->addWidget(lightShadingSlider);


        verticalLayout_5->addLayout(verticalLayout_4);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 1586, 25));
        menuFile = new QMenu(menubar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        menuAide = new QMenu(menubar);
        menuAide->setObjectName(QStringLiteral("menuAide"));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        statusbar->setEnabled(false);
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menuFile->menuAction());
        menubar->addAction(menuAide->menuAction());
        menuFile->addAction(loadModelAction);
        menuFile->addAction(generateModelAction);
        menuFile->addAction(screenshotAction);
        menuFile->addSeparator();
        menuFile->addAction(exitAction);
        menuAide->addAction(actionAide);
        menuAide->addAction(actionA_propos);

        retranslateUi(MainWindow);
        QObject::connect(lightShadingSlider, SIGNAL(valueChanged(int)), lightShadingPosValue, SLOT(setNum(int)));
        QObject::connect(lightShadowSlider, SIGNAL(valueChanged(int)), lightShadowPosValue, SLOT(setNum(int)));

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Rendu Style Nova", Q_NULLPTR));
        loadModelAction->setText(QApplication::translate("MainWindow", "Charger un model", Q_NULLPTR));
#ifndef QT_NO_STATUSTIP
        loadModelAction->setStatusTip(QApplication::translate("MainWindow", "Charger un model existant (.obj ou .mnt)", Q_NULLPTR));
#endif // QT_NO_STATUSTIP
        loadModelAction->setShortcut(QApplication::translate("MainWindow", "Ctrl+O", Q_NULLPTR));
        screenshotAction->setText(QApplication::translate("MainWindow", "Capture d'ecran", Q_NULLPTR));
#ifndef QT_NO_STATUSTIP
        screenshotAction->setStatusTip(QApplication::translate("MainWindow", "Sauvegarder une capture d'ecran dans un fichier", Q_NULLPTR));
#endif // QT_NO_STATUSTIP
        screenshotAction->setShortcut(QApplication::translate("MainWindow", "Ctrl+P", Q_NULLPTR));
        actionAide->setText(QApplication::translate("MainWindow", "Aide", Q_NULLPTR));
        actionA_propos->setText(QApplication::translate("MainWindow", "A propos", Q_NULLPTR));
        exitAction->setText(QApplication::translate("MainWindow", "Quitter", Q_NULLPTR));
#ifndef QT_NO_STATUSTIP
        exitAction->setStatusTip(QApplication::translate("MainWindow", "Quitter l'application", Q_NULLPTR));
#endif // QT_NO_STATUSTIP
        exitAction->setShortcut(QApplication::translate("MainWindow", "Ctrl+Q", Q_NULLPTR));
        actionMesh->setText(QApplication::translate("MainWindow", "Mesh", Q_NULLPTR));
        actionHeight_Map->setText(QApplication::translate("MainWindow", "Height Map", Q_NULLPTR));
        actionNormal_Map->setText(QApplication::translate("MainWindow", "Normal Map", Q_NULLPTR));
        actionCurvature_Map->setText(QApplication::translate("MainWindow", "Curvature Map", Q_NULLPTR));
        actionLight_Map->setText(QApplication::translate("MainWindow", "Light Map", Q_NULLPTR));
        generateModelAction->setText(QApplication::translate("MainWindow", "Generer un model", Q_NULLPTR));
        reloadButton->setText(QApplication::translate("MainWindow", "Recharger", Q_NULLPTR));
        addButton->setText(QApplication::translate("MainWindow", "Ajouter", Q_NULLPTR));
        multiScaleGroupeBox->setTitle(QApplication::translate("MainWindow", "Multi-Echelle", Q_NULLPTR));
        label_6->setText(QApplication::translate("MainWindow", "<html><head/><body><p><span style=\" text-decoration: underline;\">Mode de dessin :</span></p></body></html>", Q_NULLPTR));
        shader->setText(QApplication::translate("MainWindow", "TextLabel", Q_NULLPTR));
        informationTitle->setText(QApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-weight:600; text-decoration: underline;\">Shader courant :</span></p></body></html>", Q_NULLPTR));
        drawMode->setText(QApplication::translate("MainWindow", "TextLabel", Q_NULLPTR));
        colorGroupeBox->setTitle(QApplication::translate("MainWindow", "Couleur", Q_NULLPTR));
        colorRadio2->setText(QApplication::translate("MainWindow", "Carte de couleur", Q_NULLPTR));
        colorRadio3->setText(QApplication::translate("MainWindow", "Cel-shading", Q_NULLPTR));
        colorRadio0->setText(QApplication::translate("MainWindow", "Couleur Unique", Q_NULLPTR));
        colorRadio1->setText(QApplication::translate("MainWindow", "Aquarelle", Q_NULLPTR));
        colorButton0->setText(QApplication::translate("MainWindow", "Choisir couleur", Q_NULLPTR));
        colorButton1->setText(QApplication::translate("MainWindow", "Choisir couleur", Q_NULLPTR));
        colorButton2->setText(QApplication::translate("MainWindow", "Charger Texture", Q_NULLPTR));
        colorButton3->setText(QApplication::translate("MainWindow", "Charger Texture", Q_NULLPTR));
        shadowGroupBox->setTitle(QApplication::translate("MainWindow", "Ombres Port\303\251es", Q_NULLPTR));
        shadowCheckBoxLightDir->setText(QApplication::translate("MainWindow", "Orienter la lumi\303\250re", Q_NULLPTR));
        shadowCheckBoxMorpho->setText(QApplication::translate("MainWindow", "Faire la Morphologie", Q_NULLPTR));
        lightShadowPosLabel->setText(QApplication::translate("MainWindow", "<html><head/><body><p>Position vertical de la lumi\303\250re :</p></body></html>", Q_NULLPTR));
        lightShadowPosValue->setText(QApplication::translate("MainWindow", "<html><head/><body><p>45</p></body></html>", Q_NULLPTR));
        shadingGroupeBox->setTitle(QApplication::translate("MainWindow", " Ombrage", Q_NULLPTR));
        shadeCheckBoxLightDir->setText(QApplication::translate("MainWindow", "Orienter la lumi\303\250re ", Q_NULLPTR));
        shadeRadio0->setText(QApplication::translate("MainWindow", "Flou", Q_NULLPTR));
        shadeRadio1->setText(QApplication::translate("MainWindow", "Details", Q_NULLPTR));
        shadeRadio2->setText(QApplication::translate("MainWindow", "Overlay", Q_NULLPTR));
        shadeRadio3->setText(QApplication::translate("MainWindow", "Wartercolor", Q_NULLPTR));
        lightShadingPosLabel->setText(QApplication::translate("MainWindow", "<html><head/><body><p>Position vertical de la lumi\303\250re :</p></body></html>", Q_NULLPTR));
        lightShadingPosValue->setText(QApplication::translate("MainWindow", "<html><head/><body><p>45</p></body></html>", Q_NULLPTR));
        menuFile->setTitle(QApplication::translate("MainWindow", "Fichier", Q_NULLPTR));
        menuAide->setTitle(QApplication::translate("MainWindow", "Aide", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
