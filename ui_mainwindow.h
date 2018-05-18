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
    QLabel *currentMaps;
    QWidget *verticalLayoutWidget_2;
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout_4;
    QHBoxLayout *horizontalLayout_3;
    QLabel *lightPosLabel;
    QLabel *lightPosValue;
    QSpacerItem *horizontalSpacer_2;
    QSlider *lightSlider;
    QWidget *mainWidget;
    QSlider *drawModeSlider;
    QWidget *verticalLayoutWidget_4;
    QVBoxLayout *settingsLayout;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout_8;
    QPushButton *reloadButton;
    QPushButton *addButton;
    QGroupBox *groupBox;
    QWidget *horizontalLayoutWidget_2;
    QHBoxLayout *horizontalLayout_2;
    QRadioButton *typeShading0;
    QRadioButton *typeShading1;
    QRadioButton *typeShading2;
    QCheckBox *shadowCheckBox;
    QGroupBox *typeMergeBox;
    QWidget *horizontalLayoutWidget_3;
    QHBoxLayout *typeMergeLayout;
    QRadioButton *typeMerge0;
    QRadioButton *typeMerge1;
    QRadioButton *typeMerge2;
    QGroupBox *shadeSelectorGroupeBox;
    QWidget *horizontalLayoutWidget_4;
    QHBoxLayout *horizontalLayout_4;
    QRadioButton *shade0;
    QRadioButton *shade1;
    QRadioButton *shade2;
    QRadioButton *shade3;
    QMenuBar *menubar;
    QMenu *menuFile;
    QMenu *menuAide;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->setWindowModality(Qt::WindowModal);
        MainWindow->resize(1583, 1036);
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
        verticalLayoutWidget = new QWidget(centralwidget);
        verticalLayoutWidget->setObjectName(QStringLiteral("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(10, 840, 421, 131));
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

        currentMaps = new QLabel(verticalLayoutWidget);
        currentMaps->setObjectName(QStringLiteral("currentMaps"));

        horizontalLayout->addWidget(currentMaps);


        verticalLayout->addLayout(horizontalLayout);

        verticalLayoutWidget_2 = new QWidget(centralwidget);
        verticalLayoutWidget_2->setObjectName(QStringLiteral("verticalLayoutWidget_2"));
        verticalLayoutWidget_2->setGeometry(QRect(450, 830, 481, 51));
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


        verticalLayout_2->addLayout(verticalLayout_4);

        mainWidget = new QWidget(centralwidget);
        mainWidget->setObjectName(QStringLiteral("mainWidget"));
        mainWidget->setGeometry(QRect(10, 10, 1191, 781));
        drawModeSlider = new QSlider(centralwidget);
        drawModeSlider->setObjectName(QStringLiteral("drawModeSlider"));
        drawModeSlider->setGeometry(QRect(20, 800, 1171, 20));
        drawModeSlider->setMaximum(8);
        drawModeSlider->setOrientation(Qt::Horizontal);
        drawModeSlider->setTickPosition(QSlider::TicksBelow);
        verticalLayoutWidget_4 = new QWidget(centralwidget);
        verticalLayoutWidget_4->setObjectName(QStringLiteral("verticalLayoutWidget_4"));
        verticalLayoutWidget_4->setGeometry(QRect(1210, 20, 361, 121));
        settingsLayout = new QVBoxLayout(verticalLayoutWidget_4);
        settingsLayout->setObjectName(QStringLiteral("settingsLayout"));
        settingsLayout->setSizeConstraint(QLayout::SetMinimumSize);
        settingsLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayoutWidget = new QWidget(centralwidget);
        horizontalLayoutWidget->setObjectName(QStringLiteral("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(1370, 950, 201, 31));
        horizontalLayout_8 = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout_8->setObjectName(QStringLiteral("horizontalLayout_8"));
        horizontalLayout_8->setContentsMargins(0, 0, 0, 0);
        reloadButton = new QPushButton(horizontalLayoutWidget);
        reloadButton->setObjectName(QStringLiteral("reloadButton"));

        horizontalLayout_8->addWidget(reloadButton);

        addButton = new QPushButton(horizontalLayoutWidget);
        addButton->setObjectName(QStringLiteral("addButton"));

        horizontalLayout_8->addWidget(addButton);

        groupBox = new QGroupBox(centralwidget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(950, 830, 301, 51));
        groupBox->setCheckable(false);
        horizontalLayoutWidget_2 = new QWidget(groupBox);
        horizontalLayoutWidget_2->setObjectName(QStringLiteral("horizontalLayoutWidget_2"));
        horizontalLayoutWidget_2->setGeometry(QRect(0, 20, 296, 23));
        horizontalLayout_2 = new QHBoxLayout(horizontalLayoutWidget_2);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        typeShading0 = new QRadioButton(horizontalLayoutWidget_2);
        typeShading0->setObjectName(QStringLiteral("typeShading0"));
        typeShading0->setChecked(true);

        horizontalLayout_2->addWidget(typeShading0);

        typeShading1 = new QRadioButton(horizontalLayoutWidget_2);
        typeShading1->setObjectName(QStringLiteral("typeShading1"));

        horizontalLayout_2->addWidget(typeShading1);

        typeShading2 = new QRadioButton(horizontalLayoutWidget_2);
        typeShading2->setObjectName(QStringLiteral("typeShading2"));

        horizontalLayout_2->addWidget(typeShading2);

        shadowCheckBox = new QCheckBox(centralwidget);
        shadowCheckBox->setObjectName(QStringLiteral("shadowCheckBox"));
        shadowCheckBox->setGeometry(QRect(950, 960, 111, 21));
        typeMergeBox = new QGroupBox(centralwidget);
        typeMergeBox->setObjectName(QStringLiteral("typeMergeBox"));
        typeMergeBox->setGeometry(QRect(950, 900, 301, 51));
        typeMergeBox->setCheckable(false);
        horizontalLayoutWidget_3 = new QWidget(typeMergeBox);
        horizontalLayoutWidget_3->setObjectName(QStringLiteral("horizontalLayoutWidget_3"));
        horizontalLayoutWidget_3->setGeometry(QRect(0, 20, 296, 23));
        typeMergeLayout = new QHBoxLayout(horizontalLayoutWidget_3);
        typeMergeLayout->setObjectName(QStringLiteral("typeMergeLayout"));
        typeMergeLayout->setContentsMargins(0, 0, 0, 0);
        typeMerge0 = new QRadioButton(horizontalLayoutWidget_3);
        typeMerge0->setObjectName(QStringLiteral("typeMerge0"));
        typeMerge0->setChecked(true);

        typeMergeLayout->addWidget(typeMerge0);

        typeMerge1 = new QRadioButton(horizontalLayoutWidget_3);
        typeMerge1->setObjectName(QStringLiteral("typeMerge1"));

        typeMergeLayout->addWidget(typeMerge1);

        typeMerge2 = new QRadioButton(horizontalLayoutWidget_3);
        typeMerge2->setObjectName(QStringLiteral("typeMerge2"));

        typeMergeLayout->addWidget(typeMerge2);

        shadeSelectorGroupeBox = new QGroupBox(centralwidget);
        shadeSelectorGroupeBox->setObjectName(QStringLiteral("shadeSelectorGroupeBox"));
        shadeSelectorGroupeBox->setGeometry(QRect(460, 900, 421, 51));
        horizontalLayoutWidget_4 = new QWidget(shadeSelectorGroupeBox);
        horizontalLayoutWidget_4->setObjectName(QStringLiteral("horizontalLayoutWidget_4"));
        horizontalLayoutWidget_4->setGeometry(QRect(0, 20, 420, 23));
        horizontalLayout_4 = new QHBoxLayout(horizontalLayoutWidget_4);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        horizontalLayout_4->setContentsMargins(0, 0, 0, 0);
        shade0 = new QRadioButton(horizontalLayoutWidget_4);
        shade0->setObjectName(QStringLiteral("shade0"));
        shade0->setChecked(true);

        horizontalLayout_4->addWidget(shade0);

        shade1 = new QRadioButton(horizontalLayoutWidget_4);
        shade1->setObjectName(QStringLiteral("shade1"));

        horizontalLayout_4->addWidget(shade1);

        shade2 = new QRadioButton(horizontalLayoutWidget_4);
        shade2->setObjectName(QStringLiteral("shade2"));

        horizontalLayout_4->addWidget(shade2);

        shade3 = new QRadioButton(horizontalLayoutWidget_4);
        shade3->setObjectName(QStringLiteral("shade3"));

        horizontalLayout_4->addWidget(shade3);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 1583, 20));
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
        QObject::connect(lightSlider, SIGNAL(valueChanged(int)), lightPosValue, SLOT(setNum(int)));

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
        actionHeight_Map->setText(QApplication::translate("MainWindow", "Height Map", nullptr));
        actionNormal_Map->setText(QApplication::translate("MainWindow", "Normal Map", nullptr));
        actionCurvature_Map->setText(QApplication::translate("MainWindow", "Curvature Map", nullptr));
        actionLight_Map->setText(QApplication::translate("MainWindow", "Light Map", nullptr));
        generateModelAction->setText(QApplication::translate("MainWindow", "Generer un model", nullptr));
        informationTitle->setText(QApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:16pt; font-weight:600; text-decoration: underline;\">Shading :</span></p></body></html>", nullptr));
        label_6->setText(QApplication::translate("MainWindow", "<html><head/><body><p><span style=\" text-decoration: underline;\">Mode de dessin</span></p></body></html>", nullptr));
        label_5->setText(QApplication::translate("MainWindow", "<html><head/><body><p><span style=\" text-decoration: underline;\">Shader courant</span></p></body></html>", nullptr));
        label->setText(QApplication::translate("MainWindow", "<html><head/><body><p><span style=\" text-decoration: underline;\">Maps Courantes</span></p></body></html>", nullptr));
        drawMode->setText(QApplication::translate("MainWindow", "TextLabel", nullptr));
        shader->setText(QApplication::translate("MainWindow", "TextLabel", nullptr));
        currentMaps->setText(QApplication::translate("MainWindow", "TextLabel", nullptr));
        lightPosLabel->setText(QApplication::translate("MainWindow", "<html><head/><body><p><span style=\" text-decoration: underline;\">Position vertical de la lumi\303\250re :</span></p></body></html>", nullptr));
        lightPosValue->setText(QApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-weight:600;\">45</span></p></body></html>", nullptr));
        reloadButton->setText(QApplication::translate("MainWindow", "Recharger", nullptr));
        addButton->setText(QApplication::translate("MainWindow", "Ajouter", nullptr));
        groupBox->setTitle(QApplication::translate("MainWindow", "Type de lumi\303\250re", nullptr));
        typeShading0->setText(QApplication::translate("MainWindow", "max(l.n,0)", nullptr));
        typeShading1->setText(QApplication::translate("MainWindow", "l.n*0.5 + 0.5", nullptr));
        typeShading2->setText(QApplication::translate("MainWindow", "abs(l.n)", nullptr));
        shadowCheckBox->setText(QApplication::translate("MainWindow", "Ombre port\303\251e", nullptr));
        typeMergeBox->setTitle(QApplication::translate("MainWindow", "Type de fusion", nullptr));
        typeMerge0->setText(QApplication::translate("MainWindow", "Aucune", nullptr));
        typeMerge1->setText(QApplication::translate("MainWindow", "Lumi\303\250re", nullptr));
        typeMerge2->setText(QApplication::translate("MainWindow", "Ombrage", nullptr));
        shadeSelectorGroupeBox->setTitle(QApplication::translate("MainWindow", "Selection shading", nullptr));
        shade0->setText(QApplication::translate("MainWindow", "Flou", nullptr));
        shade1->setText(QApplication::translate("MainWindow", "Details", nullptr));
        shade2->setText(QApplication::translate("MainWindow", "Mix", nullptr));
        shade3->setText(QApplication::translate("MainWindow", "Custom", nullptr));
        menuFile->setTitle(QApplication::translate("MainWindow", "Fichier", nullptr));
        menuAide->setTitle(QApplication::translate("MainWindow", "Aide", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
