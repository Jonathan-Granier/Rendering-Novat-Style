/*
 *
 *
 *  The main window
*/







#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "viewer.h"
#include <QMainWindow>
#include <QProgressBar>

class QAction;
class QMenu;


/**
 * @brief The MainWindow class with basic menu bar (load model, save a screenshot and quit the app) and the central widget is a openGl widget.
 */
class MainWindow : public QMainWindow
{
public:
    /**
     * @brief Set the different Widget.
     */
    explicit MainWindow();
    ~MainWindow();
protected:
    /**
     * @brief Intercepts the closeEvent and destroy all the variable of mainWindow.
     * @param event
     */
    void closeEvent(QCloseEvent *event) override;
    void keyPressEvent(QKeyEvent *ke);




private slots:
    /**
     * @brief open a file and call _viewer.loadModelFromFile.
     */
    void open();

    /**
     * @brief Save a screenshot of the actual _viewer.
     */
    void saveScreenshot();

    /**
     * @brief show the help window.
     */
    void help();

    /**
     * @brief show the about window.
     */
    void about();



    /**
     * @brief Show the loading bar
     * @bug problem with viewer
     */
    void showLoadingBar();
    /**
     * @brief Update the loading bar
     * @bug problem with viewer
     */
    void updateLoadingBar();
    /**
     * @brief Hide the loading bar
     * @bug problem with viewer
     */
    void hideLoadingBar();
private:


    /**
     * @brief the central openGl widget
     */
    Viewer *_viewer;
    /**
     * @brief The application widget : only use for quitEvent
     */
    QApplication *_application;
    /**
     * @brief the actual progress of the loading objects (Mesh and Textures).
     */
    QProgressBar *_loadingBar;

    /**
     * @brief Set up the menuBar and the different action
     */
    void setupMenu();
    /**
     * @brief Set up the loading bar
     */
    void setupLoadingBar();
    /**
     * @brief Delete the connections of the loading bar.
     */
    void deleteLoadingBar();
};

#endif // MAINWINDOW_H
