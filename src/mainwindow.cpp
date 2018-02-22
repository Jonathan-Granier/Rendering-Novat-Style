#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    _viewer = new Viewer();
    _viewer->show();
}

MainWindow::~MainWindow()
{
     delete _viewer;
}
