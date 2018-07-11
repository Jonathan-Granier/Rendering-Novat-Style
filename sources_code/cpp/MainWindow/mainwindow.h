/**
* @file mainwindow.h
* @author Jonathan Granier
* @copyright  This code was writen for the research project
*             "Rendering panorama maps in the "atelier Novat" style.
*             Performed at Inria Grenoble Rhöne-Alpes, Maverick Team.
*             Univ.Grenoble Alpes, LJK, INRIA.
*             Under the supervision of : Joelle THOLLOT and Romain VERGNE.
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
 * @brief The MainWindow class is the controle center of the UI of the project. He have many buttons and a QOpenGLWidget.
 * The UI is generated with mainwindow.ui , a file generate by QTDesigner.
 */
class MainWindow : public QMainWindow, private Ui::MainWindow
{
public:
    /**
     * @brief Constructon, set the differents widgets.
     */
    explicit MainWindow();
    ~MainWindow();






protected:

    /**
    * Close the windows.
    */
    void closeEvent(QCloseEvent *event) override;

    /**
     * @brief Intercepts the closeEvent and destroy all the variable of mainWindow.
     * @details R : reload all shaders,
     *          I : init the camera,
     *          P : print the camera and light position,
     *          D : fixe the camera and the light to hard code positions,
     *          W : Switch to the previous draw mode,
     *          X : Switch to the next draw mode.
     *
     * @param ke    The key pressed
     */
    void keyPressEvent(QKeyEvent *ke) override;






private slots:
    /**
     * @brief Open files and load it.
     * @details See loadSceneFromFile function in viewer for more details.
     */
    void open();

    /**
    * @brief Generate a scene from the shader genheightmap.frag.
    * @details See generateScene function in viewer for more details.
    *
    */
    void generateScene();
    /**
     * @brief Save a screenshot of the actual QOpenGLWidget.
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
    * @brief Set the pitch of the global light
    *
    * @param theta      a angle in degree between 0 and 89.
    */
    void updateLightPosition(int angle);

    /**
    * @brief Set the picht of the light for the shadowLightMap.
    *
    * @param p          a angle in degree between 0 and 89.
    */
    void updateShadowLightPosition(int angle);

    /**
    * @brief Reload the laplacien pyramid.
    */
    void reloadLaplacienPyramid();

    /**
    * @brief call refreshInformationPanel function.
    */
    void setupInformationPanelSlot();

    /**
    * @brief update the draw mode
    * @details See viewer for more information.
    *
    * @param d      The draw mode number.
    */
    void updateDrawMode(int d);

    /**
    * @brief add a new scale and a new panel for controle this scale.
    * @details Increment _id
    */
    void addNewPanel();

    /**
    * @brief Enabled or disabled the shadow (compute and draw)
    * @param b       If 1, enabled the shadows, disabled otherwise.
    */
    void setShadowEnabled(int b);

    /**
    * @brief Set if the mathematical morphology on the shadow is done or not.
    * @param b       If 1, do the mathematical morphology, do nothing otherwise.
    */
    void setShadowEnabledMorpho(int b);

    /**
    * @brief Set if the light for compute the shadow is the global light or the oriented light.
    * @param b      If 1, oriented used, global light otherwise.
    */
    void setShadowEnabledLightDir(int b);



    /**
    * @brief Set if the light for compute the shade is the global light or the oriented light.
    * @param b      If 1, oriented used, global light otherwise.
    */
    void setShadeEnabledLightDir(int b);

    /**
    * @brief set if we compute ur shading methode or if we compute a classic lambertien with native normal and the global light.
    * @param b       If 1, classic lambertien, ur methode otherwise.
    */
    void setDoDefaultShading(int b);

    /**
    * @brief Open a QColor Dialog.
    * @return The color return by QColorDialog.
    */
    QColor selectColor(QColor currentColor);

    /**
    * @brief Select a texture to load.
    * @return The path of the texture file selected.
    */
    QString loadTexture();

private:

    /**
    * @brief The UI generate by QTDesigner.
    */
    Ui::MainWindow *ui;

    /**
     * @brief the central QOpenGLWidget
     */
    std::unique_ptr<Viewer> _viewer;
    /**
     * @brief The application widget : only use for quitEvent
     */
    QApplication *_application;

    /**
    * @brief The ID of the last scale add.
    */
    unsigned int _id;


    QButtonGroup* _currentScaleSelector;

    /**
    * @brief Do the connections between the menu bar and the functions
    */
    void setupMenu();

    /**
    * @brief Do the connections between the ControlePanel and the functions
    */
    void setupControlePanel();

    /**
    * @brief Do the connections between the shade settings and the functions
    */
    void setupShadeSettings();

    /**
    * @brief Do the connections between the shadow settings and the functions
    */
    void setupShadowSettings();

    /**
    * @brief Do the connections between the color settings and the functions
    */
    void setupColorSettings();

    /**
    * @brief Do the connections between the Multi-scale buttons and the functions
    */
    void setupButtons();

    /**
    * @brief Refresh the information on the controle Penel (Draw Mode)
    */
    void refreshInformationPanel();

    /**
    * @brief Create a new panel for controle a new scale.
    * @param id             The id of the new scale
    * @param firstPanel     If true don't show the slide bar for the sigma.
    */
    QGroupBox *createNewPanel(int id, bool firstPanel);

};

#endif // MAINWINDOW_H
