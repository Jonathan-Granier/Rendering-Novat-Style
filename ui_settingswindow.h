/********************************************************************************
** Form generated from reading UI file 'settingswindow.ui'
**
** Created by: Qt User Interface Compiler version 5.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETTINGSWINDOW_H
#define UI_SETTINGSWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SettingsWindow
{
public:
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QPushButton *reloadButton;
    QPushButton *addButton;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *centralLayout;

    void setupUi(QWidget *SettingsWindow)
    {
        if (SettingsWindow->objectName().isEmpty())
            SettingsWindow->setObjectName(QStringLiteral("SettingsWindow"));
        SettingsWindow->resize(600, 1000);
        SettingsWindow->setMinimumSize(QSize(600, 1000));
        SettingsWindow->setMaximumSize(QSize(600, 1000));
        SettingsWindow->setBaseSize(QSize(600, 500));
        QIcon icon;
        icon.addFile(QStringLiteral("../../../../../images/RSN.ico"), QSize(), QIcon::Normal, QIcon::Off);
        SettingsWindow->setWindowIcon(icon);
        horizontalLayoutWidget = new QWidget(SettingsWindow);
        horizontalLayoutWidget->setObjectName(QStringLiteral("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(390, 960, 201, 31));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        reloadButton = new QPushButton(horizontalLayoutWidget);
        reloadButton->setObjectName(QStringLiteral("reloadButton"));

        horizontalLayout->addWidget(reloadButton);

        addButton = new QPushButton(horizontalLayoutWidget);
        addButton->setObjectName(QStringLiteral("addButton"));

        horizontalLayout->addWidget(addButton);

        verticalLayoutWidget = new QWidget(SettingsWindow);
        verticalLayoutWidget->setObjectName(QStringLiteral("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(30, 20, 531, 71));
        centralLayout = new QVBoxLayout(verticalLayoutWidget);
        centralLayout->setObjectName(QStringLiteral("centralLayout"));
        centralLayout->setSizeConstraint(QLayout::SetMinimumSize);
        centralLayout->setContentsMargins(0, 0, 0, 0);

        retranslateUi(SettingsWindow);

        QMetaObject::connectSlotsByName(SettingsWindow);
    } // setupUi

    void retranslateUi(QWidget *SettingsWindow)
    {
        SettingsWindow->setWindowTitle(QApplication::translate("SettingsWindow", "Option multi Echelle", nullptr));
#ifndef QT_NO_TOOLTIP
        SettingsWindow->setToolTip(QApplication::translate("SettingsWindow", "<html><head/><body><p><br/></p></body></html>", nullptr));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_ACCESSIBILITY
        SettingsWindow->setAccessibleName(QString());
#endif // QT_NO_ACCESSIBILITY
        reloadButton->setText(QApplication::translate("SettingsWindow", "Recharger", nullptr));
        addButton->setText(QApplication::translate("SettingsWindow", "Ajouter", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SettingsWindow: public Ui_SettingsWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETTINGSWINDOW_H
