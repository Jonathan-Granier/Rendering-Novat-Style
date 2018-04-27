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
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SettingsWindow
{
public:

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
    } // retranslateUi

};

namespace Ui {
    class SettingsWindow: public Ui_SettingsWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETTINGSWINDOW_H
