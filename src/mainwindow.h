#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "viewer.h"
#include <QMainWindow>


class QAction;
class QMenu;




class MainWindow : public QMainWindow
{
public:
    explicit MainWindow();
    ~MainWindow();
/*
protected:
    void closeEvent(QCloseEvent *event) override;
*/
private slots:
    void open();
    void saveScreenshot();
    void help();
    void about();




private:





    Viewer *_viewer;
    QApplication *_application;

    void setupMenu();
};

#endif // MAINWINDOW_H
