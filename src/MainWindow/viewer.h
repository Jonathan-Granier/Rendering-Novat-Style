#ifndef VIEWER_H
#define VIEWER_H


// GLEW lib: needs to be included first!!
#include <GL/glew.h>

// OpenGL library
#include <GL/gl.h>

// OpenGL Utility library
#include <GL/glu.h>


//#include <unistd.h>
#include <glm/glm.hpp>
#include <vector>
#include <memory>

#include <QOpenGLWidget>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QTime>


#include "src/OpenGl/shader.h"
#include "src/OpenGl/scene.h"
#include "src/OpenGl/shadowmap.h"


#include "src/Light_Camera/camera.h"
#include "src/Light_Camera/light.h"


/**
 * @brief The Open GL widget , init openGL, setup a Scene, a camera, a light and shaders and draw it.
 */
class Viewer : public QOpenGLWidget
{
    Q_OBJECT
public:

    enum DRAWMODE{  CLASSICAL,  /*!< Mode for draw the Scene with the camera and the ligth */
                    SHADOWMAP,  /*!< Mode for draw only the shadow map of the Scene        */
                    HEIGHTMAP,  /*!< Mode for draw the height map of the current mesh      */
                    NORMALMAP,  /*!< Mode for draw the normal map of the current mesh      */
                    CURVATURE,  /*!< Mode for draw the curvature map of the current mesh   */
                    LIGHTMAP    /*!< Mode for draw the light map of the current mesh       */
                 };



    /**
     * @brief Classic QWidget constructor, set up a QSurfaceFormat.
     * @param parent the QWidget parent of Viewer.
     */
    Viewer(QWidget *parent = 0);

    /**
     * @brief Main loop of rendering.
     */
    virtual void paintGL();
    /**
     * @brief initialize openGl and the different element of viewer (Scene, camera, shader).
     */
    virtual void initializeGL();
    /**
     * @brief Resize the widget.
     * @param width : the new width of the widget.
     * @param height : the new height of the widget.
     */
    virtual void resizeGL(int width,int height);


    /**
     * @brief Intercepts the imput of the mousse and do something depeding on the pressed key.
     * @details - Left button : move the camera.
     *          - Mid button : zoom the camera.
     *          - Right button : move the light.
     * @param me the button pressed.
     */
    virtual void mousePressEvent(QMouseEvent *me);

    /**
     * @brief Intercepts the movements of the mouss when a button is pressed and do something depeding the button pressed.
     * @details -Left and Mid button : move the camera.
     *          -Right button : move the light.
     * @param me the button pressed.
     */
    virtual void mouseMoveEvent(QMouseEvent *me);



    void setHeightLight(float theta);
    float getHeightLight();
    /**
     * @brief Reset the camera postion.
     */
    void resetTheCameraPosition();
    /**
     * @brief Read and compile all shaders.
     */
    void reloadShader();

    /**
     * @brief Print the camera and light data
     */
    void printCamAndLight();

    /**
     * @brief Fixe the camera and the light to hard code positions.
     */
    void fixeCamAndLight();

    /**
     * @brief Switch to the next shader.
     * @return The current name of the shader.
     */
    std::string nextShader();

    /**
     * @brief Switch to the previous shader.
     * @return The currant name of the shader.
     */
    std::string previousShader();


    void previousDrawMode();
    void nextDrawMode();

    /**
     * @brief check and copy a stack file in _filepaths.
     * @param fileNames a stack of path file.
     * @return return true if the fileNames are correct (.obj or .asc).
     */
    bool loadSceneFromFile(const QStringList &fileNames);

    void switchScene();


    std::string getCurrentDrawMode();
    std::string getCurrentShader();

    float getSigma() const;
    void setSigma(float sigma);

    void nextLight();
    void previousLight();
    int getLightSelector() const;


signals :
    void initializeDone();

private:


    std::shared_ptr<Shader>     _lightShaders;           /** < Shaders for compute the light. */
    std::shared_ptr<Shader>     _drawTextureShader;
    std::shared_ptr<ShadowMap>  _shadowMap;

    std::shared_ptr<Scene>      _scene;            /** < A Scene pointer.  */
    std::shared_ptr<Camera>     _cam;              /** < A Camera pointer. */
    std::shared_ptr<Light>      _light;            /** < A Light pointer      */


    bool        _lightMode;
    DRAWMODE    _drawMode;

    std::vector<std::string> _filepaths;           /** < A vector of mesh file.*/
    QTime _timer;                                  /** < A Qt timer.*/



    /**
     * @brief load Scene from _filepaths and of type _typeMesh
     */
    void loadScene();

    void initShaders();
};

#endif // VIEWER_H
