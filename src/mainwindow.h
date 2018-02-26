/*
 *
 *
 *  The main window
*/







#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "viewer.h"
#include <QMainWindow>


class QAction;
class QMenu;


/**
 * @brief The MainWindow class with basic menu bar (load model, save a screenshot and quit the app).
 */
class MainWindow : public QMainWindow
{
public:
    explicit MainWindow();
    ~MainWindow();
protected:
    void closeEvent(QCloseEvent *event) override;





private slots:
    void open();
    void saveScreenshot();
    void help();
    void about();
    void showLoadingBar();
    void updateLoadingBar();
    void hideLoadingBar();
private:

    Viewer *_viewer;
    QApplication *_application;
    QProgressBar *_loadingBar;


    void setupMenu();
    void setupLoadingBar();
    void deleteLoadingBar();
};

#endif // MAINWINDOW_H
