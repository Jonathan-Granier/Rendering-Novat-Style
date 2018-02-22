#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include <QMainWindow>
#include "viewer.h"


class MainWindow : public QMainWindow
{
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
private:
    Viewer *_viewer;
};

#endif // MAINWINDOW_H
