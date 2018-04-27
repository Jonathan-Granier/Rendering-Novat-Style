#ifndef SETTINGSWINDOW_H
#define SETTINGSWINDOW_H

#include <QWindow>
#include <QWidget>
#include <memory>
#include "viewer.h"
#include "ui_settingswindow.h"
#include <QSignalMapper>
#include <QGroupBox>
/*
class SettingsWindow : public QWidget
{
    Q_OBJECT
public:
    explicit SettingsWindow();
    ~SettingsWindow();



protected :
    void closeEvent(QCloseEvent *event);
private slots:
    void addPanel();
    void reload();


private :
    Ui::SettingsWindow *ui;


    void setButtons();
    QGroupBox *creatNewPanel(int id);

    int _ID;

};
*/
#endif // SETTINGSWINDOW_H
