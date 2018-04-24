/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.10.1
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
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
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
    QWidget *centralwidget;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QLabel *informationTitle;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_6;
    QFrame *line_7;
    QLabel *label_5;
    QFrame *line_8;
    QLabel *label;
    QFrame *lineInfo;
    QHBoxLayout *horizontalLayout;
    QLabel *drawMode;
    QFrame *line_5;
    QLabel *shader;
    QFrame *line_6;
    QLabel *lightMode;
    QWidget *verticalLayoutWidget_2;
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout_4;
    QHBoxLayout *horizontalLayout_3;
    QLabel *lightPosLabel;
    QLabel *lightPosValue;
    QSpacerItem *horizontalSpacer_2;
    QSlider *lightSlider;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_2;
    QLabel *sigmaLabel;
    QLabel *sigmaValue;
    QSpacerItem *horizontalSpacer;
    QSlider *sigmaSlider;
    QVBoxLayout *verticalLayout_5;
    QHBoxLayout *horizontalLayout_4;
    QLabel *lightThresholdLabel;
    QLabel *lightThresholdValue;
    QSpacerItem *horizontalSpacer_3;
    QSlider *lightThresholdSlider;
    QWidget *mainWidget;
    QCheckBox *checkBox;
    QCheckBox *checkBox_2;
    QWidget *verticalLayoutWidget_3;
    QVBoxLayout *GaussBlurLayout;
    QHBoxLayout *horizontalLayout_5;
    QLabel *gaussBlurLabel;
    QLabel *gaussBlurValue;
    QSpacerItem *horizontalSpacer_4;
    QSlider *gaussBlurSlider;
    QPushButton *GaussBlurButton;
    QMenuBar *menubar;
    QMenu *menuFile;
    QMenu *menuAide;
    QMenu *menuSelection_Map;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->setWindowModality(Qt::WindowModal);
        MainWindow->resize(1212, 1002);
        MainWindow->setBaseSize(QSize(1220, 1010));
        QIcon icon;
        icon.addFile(QStringLiteral("../../../../../../../../images/RSN.ico"), QSize(), QIcon::Normal, QIcon::Off);
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
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        verticalLayoutWidget = new QWidget(centralwidget);
        verticalLayoutWidget->setObjectName(QStringLiteral("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(20, 810, 421, 131));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        informationTitle = new QLabel(verticalLayoutWidget);
        informationTitle->setObjectName(QStringLiteral("informationTitle"));

        verticalLayout->addWidget(informationTitle);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        label_6 = new QLabel(verticalLayoutWidget);
        label_6->setObjectName(QStringLiteral("label_6"));

        horizontalLayout_6->addWidget(label_6);

        line_7 = new QFrame(verticalLayoutWidget);
        line_7->setObjectName(QStringLiteral("line_7"));
        line_7->setFrameShape(QFrame::VLine);
        line_7->setFrameShadow(QFrame::Sunken);

        horizontalLayout_6->addWidget(line_7);

        label_5 = new QLabel(verticalLayoutWidget);
        label_5->setObjectName(QStringLiteral("label_5"));

        horizontalLayout_6->addWidget(label_5);

        line_8 = new QFrame(verticalLayoutWidget);
        line_8->setObjectName(QStringLiteral("line_8"));
        line_8->setFrameShape(QFrame::VLine);
        line_8->setFrameShadow(QFrame::Sunken);

        horizontalLayout_6->addWidget(line_8);

        label = new QLabel(verticalLayoutWidget);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout_6->addWidget(label);


        verticalLayout->addLayout(horizontalLayout_6);

        lineInfo = new QFrame(verticalLayoutWidget);
        lineInfo->setObjectName(QStringLiteral("lineInfo"));
        lineInfo->setFrameShape(QFrame::HLine);
        lineInfo->setFrameShadow(QFrame::Sunken);

        verticalLayout->addWidget(lineInfo);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        drawMode = new QLabel(verticalLayoutWidget);
        drawMode->setObjectName(QStringLiteral("drawMode"));

        horizontalLayout->addWidget(drawMode);

        line_5 = new QFrame(verticalLayoutWidget);
        line_5->setObjectName(QStringLiteral("line_5"));
        line_5->setFrameShape(QFrame::VLine);
        line_5->setFrameShadow(QFrame::Sunken);

        horizontalLayout->addWidget(line_5);

        shader = new QLabel(verticalLayoutWidget);
        shader->setObjectName(QStringLiteral("shader"));

        horizontalLayout->addWidget(shader);

        line_6 = new QFrame(verticalLayoutWidget);
        line_6->setObjectName(QStringLiteral("line_6"));
        line_6->setFrameShape(QFrame::VLine);
        line_6->setFrameShadow(QFrame::Sunken);

        horizontalLayout->addWidget(line_6);

        lightMode = new QLabel(verticalLayoutWidget);
        lightMode->setObjectName(QStringLiteral("lightMode"));

        horizontalLayout->addWidget(lightMode);


        verticalLayout->addLayout(horizontalLayout);

        verticalLayoutWidget_2 = new QWidget(centralwidget);
        verticalLayoutWidget_2->setObjectName(QStringLiteral("verticalLayoutWidget_2"));
        verticalLayoutWidget_2->setGeometry(QRect(460, 800, 521, 149));
        verticalLayout_2 = new QVBoxLayout(verticalLayoutWidget_2);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        lightPosLabel = new QLabel(verticalLayoutWidget_2);
        lightPosLabel->setObjectName(QStringLiteral("lightPosLabel"));

        horizontalLayout_3->addWidget(lightPosLabel);

        lightPosValue = new QLabel(verticalLayoutWidget_2);
        lightPosValue->setObjectName(QStringLiteral("lightPosValue"));

        horizontalLayout_3->addWidget(lightPosValue);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_2);


        verticalLayout_4->addLayout(horizontalLayout_3);

        lightSlider = new QSlider(verticalLayoutWidget_2);
        lightSlider->setObjectName(QStringLiteral("lightSlider"));
        lightSlider->setMaximum(89);
        lightSlider->setValue(45);
        lightSlider->setOrientation(Qt::Horizontal);

        verticalLayout_4->addWidget(lightSlider);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        sigmaLabel = new QLabel(verticalLayoutWidget_2);
        sigmaLabel->setObjectName(QStringLiteral("sigmaLabel"));

        horizontalLayout_2->addWidget(sigmaLabel);

        sigmaValue = new QLabel(verticalLayoutWidget_2);
        sigmaValue->setObjectName(QStringLiteral("sigmaValue"));

        horizontalLayout_2->addWidget(sigmaValue);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);


        verticalLayout_3->addLayout(horizontalLayout_2);

        sigmaSlider = new QSlider(verticalLayoutWidget_2);
        sigmaSlider->setObjectName(QStringLiteral("sigmaSlider"));
        sigmaSlider->setMaximum(100);
        sigmaSlider->setValue(10);
        sigmaSlider->setOrientation(Qt::Horizontal);

        verticalLayout_3->addWidget(sigmaSlider);

        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        lightThresholdLabel = new QLabel(verticalLayoutWidget_2);
        lightThresholdLabel->setObjectName(QStringLiteral("lightThresholdLabel"));

        horizontalLayout_4->addWidget(lightThresholdLabel);

        lightThresholdValue = new QLabel(verticalLayoutWidget_2);
        lightThresholdValue->setObjectName(QStringLiteral("lightThresholdValue"));

        horizontalLayout_4->addWidget(lightThresholdValue);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_3);


        verticalLayout_5->addLayout(horizontalLayout_4);

        lightThresholdSlider = new QSlider(verticalLayoutWidget_2);
        lightThresholdSlider->setObjectName(QStringLiteral("lightThresholdSlider"));
        lightThresholdSlider->setMinimum(20);
        lightThresholdSlider->setMaximum(100);
        lightThresholdSlider->setValue(40);
        lightThresholdSlider->setOrientation(Qt::Horizontal);

        verticalLayout_5->addWidget(lightThresholdSlider);


        verticalLayout_3->addLayout(verticalLayout_5);


        verticalLayout_4->addLayout(verticalLayout_3);


        verticalLayout_2->addLayout(verticalLayout_4);

        mainWidget = new QWidget(centralwidget);
        mainWidget->setObjectName(QStringLiteral("mainWidget"));
        mainWidget->setGeometry(QRect(10, 10, 1191, 781));
        checkBox = new QCheckBox(mainWidget);
        checkBox->setObjectName(QStringLiteral("checkBox"));
        checkBox->setGeometry(QRect(220, 240, 85, 21));
        checkBox_2 = new QCheckBox(mainWidget);
        checkBox_2->setObjectName(QStringLiteral("checkBox_2"));
        checkBox_2->setGeometry(QRect(210, 270, 85, 21));
        verticalLayoutWidget_3 = new QWidget(centralwidget);
        verticalLayoutWidget_3->setObjectName(QStringLiteral("verticalLayoutWidget_3"));
        verticalLayoutWidget_3->setGeometry(QRect(990, 830, 207, 91));
        GaussBlurLayout = new QVBoxLayout(verticalLayoutWidget_3);
        GaussBlurLayout->setObjectName(QStringLiteral("GaussBlurLayout"));
        GaussBlurLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        gaussBlurLabel = new QLabel(verticalLayoutWidget_3);
        gaussBlurLabel->setObjectName(QStringLiteral("gaussBlurLabel"));

        horizontalLayout_5->addWidget(gaussBlurLabel);

        gaussBlurValue = new QLabel(verticalLayoutWidget_3);
        gaussBlurValue->setObjectName(QStringLiteral("gaussBlurValue"));

        horizontalLayout_5->addWidget(gaussBlurValue);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_4);


        GaussBlurLayout->addLayout(horizontalLayout_5);

        gaussBlurSlider = new QSlider(verticalLayoutWidget_3);
        gaussBlurSlider->setObjectName(QStringLiteral("gaussBlurSlider"));
        gaussBlurSlider->setOrientation(Qt::Horizontal);

        GaussBlurLayout->addWidget(gaussBlurSlider);

        GaussBlurButton = new QPushButton(verticalLayoutWidget_3);
        GaussBlurButton->setObjectName(QStringLiteral("GaussBlurButton"));
        GaussBlurButton->setAutoDefault(false);

        GaussBlurLayout->addWidget(GaussBlurButton);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 1212, 20));
        menuFile = new QMenu(menubar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        menuAide = new QMenu(menubar);
        menuAide->setObjectName(QStringLiteral("menuAide"));
        menuSelection_Map = new QMenu(menubar);
        menuSelection_Map->setObjectName(QStringLiteral("menuSelection_Map"));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        statusbar->setEnabled(false);
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menuFile->menuAction());
        menubar->addAction(menuAide->menuAction());
        menubar->addAction(menuSelection_Map->menuAction());
        menuFile->addAction(loadModelAction);
        menuFile->addAction(screenshotAction);
        menuFile->addSeparator();
        menuFile->addAction(exitAction);
        menuAide->addAction(actionAide);
        menuAide->addAction(actionA_propos);
        menuSelection_Map->addAction(actionMesh);

        retranslateUi(MainWindow);
        QObject::connect(lightSlider, SIGNAL(valueChanged(int)), lightPosValue, SLOT(setNum(int)));
        QObject::connect(sigmaSlider, SIGNAL(valueChanged(int)), sigmaValue, SLOT(setNum(int)));
        QObject::connect(lightThresholdSlider, SIGNAL(valueChanged(int)), lightThresholdValue, SLOT(setNum(int)));
        QObject::connect(gaussBlurSlider, SIGNAL(valueChanged(int)), gaussBlurValue, SLOT(setNum(int)));

        GaussBlurButton->setDefault(false);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Rendu Style Nova", nullptr));
        loadModelAction->setText(QApplication::translate("MainWindow", "Charger un model", nullptr));
#ifndef QT_NO_STATUSTIP
        loadModelAction->setStatusTip(QApplication::translate("MainWindow", "Charger un model existant (.obj ou .mnt)", nullptr));
#endif // QT_NO_STATUSTIP
#ifndef QT_NO_SHORTCUT
        loadModelAction->setShortcut(QApplication::translate("MainWindow", "Ctrl+O", nullptr));
#endif // QT_NO_SHORTCUT
        screenshotAction->setText(QApplication::translate("MainWindow", "Capture d'ecran", nullptr));
#ifndef QT_NO_STATUSTIP
        screenshotAction->setStatusTip(QApplication::translate("MainWindow", "Sauvegarder une capture d'ecran dans un fichier", nullptr));
#endif // QT_NO_STATUSTIP
#ifndef QT_NO_SHORTCUT
        screenshotAction->setShortcut(QApplication::translate("MainWindow", "Ctrl+P", nullptr));
#endif // QT_NO_SHORTCUT
        actionAide->setText(QApplication::translate("MainWindow", "Aide", nullptr));
        actionA_propos->setText(QApplication::translate("MainWindow", "A propos", nullptr));
        exitAction->setText(QApplication::translate("MainWindow", "Quitter", nullptr));
#ifndef QT_NO_STATUSTIP
        exitAction->setStatusTip(QApplication::translate("MainWindow", "Quitter l'application", nullptr));
#endif // QT_NO_STATUSTIP
#ifndef QT_NO_SHORTCUT
        exitAction->setShortcut(QApplication::translate("MainWindow", "Ctrl+Q", nullptr));
#endif // QT_NO_SHORTCUT
        actionMesh->setText(QApplication::translate("MainWindow", "Mesh", nullptr));
        informationTitle->setText(QApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:16pt; font-weight:600; text-decoration: underline;\">Shading :</span></p></body></html>", nullptr));
        label_6->setText(QApplication::translate("MainWindow", "<html><head/><body><p><span style=\" text-decoration: underline;\">Mode de dessin</span></p></body></html>", nullptr));
        label_5->setText(QApplication::translate("MainWindow", "<html><head/><body><p><span style=\" text-decoration: underline;\">Shader courant</span></p></body></html>", nullptr));
        label->setText(QApplication::translate("MainWindow", "<html><head/><body><p><span style=\" text-decoration: underline;\">Calcule lumi\303\250re</span></p></body></html>", nullptr));
        drawMode->setText(QApplication::translate("MainWindow", "TextLabel", nullptr));
        shader->setText(QApplication::translate("MainWindow", "TextLabel", nullptr));
        lightMode->setText(QApplication::translate("MainWindow", "TextLabel", nullptr));
        lightPosLabel->setText(QApplication::translate("MainWindow", "<html><head/><body><p><span style=\" text-decoration: underline;\">Position vertical de la lumi\303\250re :</span></p></body></html>", nullptr));
        lightPosValue->setText(QApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-weight:600;\">45</span></p></body></html>", nullptr));
        sigmaLabel->setText(QApplication::translate("MainWindow", "<html><head/><body><p><span style=\" text-decoration: underline;\">Sigma (*10) : </span></p></body></html>", nullptr));
        sigmaValue->setText(QApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-weight:600;\">10</span></p></body></html>", nullptr));
        lightThresholdLabel->setText(QApplication::translate("MainWindow", "<html><head/><body><p><span style=\" text-decoration: underline;\">Limite d'angle de la lumi\303\250re :</span> (PI/) (*10):</p></body></html>", nullptr));
        lightThresholdValue->setText(QApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-weight:600;\">30</span></p></body></html>", nullptr));
        checkBox->setText(QApplication::translate("MainWindow", "CheckBox", nullptr));
        checkBox_2->setText(QApplication::translate("MainWindow", "CheckBox", nullptr));
        gaussBlurLabel->setText(QApplication::translate("MainWindow", "<html><head/><body><p><span style=\" text-decoration: underline;\">GaussBlur Facteur :</span></p></body></html>", nullptr));
        gaussBlurValue->setText(QApplication::translate("MainWindow", "TextLabel", nullptr));
        GaussBlurButton->setText(QApplication::translate("MainWindow", "Recompute height Map", nullptr));
        menuFile->setTitle(QApplication::translate("MainWindow", "Fichier", nullptr));
        menuAide->setTitle(QApplication::translate("MainWindow", "Aide", nullptr));
        menuSelection_Map->setTitle(QApplication::translate("MainWindow", "Selection Map", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
