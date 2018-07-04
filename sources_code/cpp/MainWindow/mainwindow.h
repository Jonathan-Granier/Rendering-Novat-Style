/*
 *
 *
 *  The main window
*/







#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "viewer.h"
#include <QMainWindow>
#include <QGroupBox>
#include <memory>
#include "ui_mainwindow.h"

class QAction;
class QMenu;


/**
 * @brief The MainWindow class with basic menu bar (load model, save a screenshot and quit the app) and the central widget is a openGl widget.
 */
class MainWindow : public QMainWindow, private Ui::MainWindow
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
     * @details R : reload all shaders,
     *          I : init the camera,
     *          P : print the camera and light position,
     *          D : fixe the camera and the light to hard code positions,
     *          Q : Switch to the previous shader,
     *          S : Switch to the next shader,
     *          W : Switch to the previous draw mode,
     *          X : Switch to the previous draw mode.
     * @param event
     */
    void closeEvent(QCloseEvent *event) override;

    void keyPressEvent(QKeyEvent *ke) override;






private slots:
    /**
     * @brief open a file and call _viewer.loadModelFromFile.
     */
    void open();

    void generateModel();
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

    void updateLightPosition(int angle);
    void updateShadowLightPosition(int angle);
    //void updateSigma(int sigma);
    //void updateLightThreshold(int t);
    //void updateGaussBlurFactor(int g);
    void reloadHeightMaps();
    void setupInformationPanelSlot();
    void updateDrawMode(int d);
    void addNewPanel();


    void setShadowEnabled(int b);
    void setShadowEnabledMorpho(int b);
    void setShadowEnabledLightDir(int b);
    void setShadowUpdateLightPosition(int angle);



    void setShadeEnabledLightDir(int b);
    void setShadeUpdateLightPosition(int angle);

    void setDoDefaultShading(int b);

    QColor selectColor(QColor currentColor);
    QString loadTexture();

private:


    Ui::MainWindow *ui;



    //SettingsWindow *_settingsWindow;
    /**
     * @brief the central openGl widget
     */
    std::unique_ptr<Viewer> _viewer;
    /**
     * @brief The application widget : only use for quitEvent
     */
    QApplication *_application;
    /**
     * @brief the actual progress of the loading objects (Mesh and Textures).
     */

    unsigned int _id;

    QButtonGroup* _currentMapsSelector;


    void setupMenu();
    void setupControlePanel();
    void setupShadeSettings();
    void setupShadowSettings();
    void setupColorSettings();
    void setupButtons();

    void refreshInformationPanel();
    QGroupBox *createNewPanel(int id, bool firstPanel);

};

#endif // MAINWINDOW_H
