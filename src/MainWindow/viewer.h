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


#include <QOpenGLWidget>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QTime>


#include "src/OpenGl/shader.h"
#include "src/OpenGl/progressinfo.h"
#include "src/OpenGl/model.h"
#include "src/Light_Camera/camera.h"
#include "src/Light_Camera/light.h"

/**
 * @brief The Open GL widget , init openGL, setup a model, a camera, a light and shaders and draw it.
 */
class Viewer : public QOpenGLWidget
{

public:
    /**
     * @brief Classic QWidget constructor, set up a QSurfaceFormat.
     * @param parent the QWidget parent of Viewer.
     */
    Viewer(QWidget *parent = 0);
    ~Viewer();

    /**
     * @brief Main loop of rendering.
     */
    virtual void paintGL();
    /**
     * @brief initialize openGl and the different element of viewer (model, camera, shader).
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


    /**
     * @brief Reset the camera postion.
     */
    void resetTheCameraPosition();
    /**
     * @brief Reload the shader.
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

    /**
     * @brief check and copy a stack file in _filepaths.
     * @param fileNames a stack of path file.
     * @return return true if the fileNames are correct (.obj or .asc).
     */
    bool loadModelFromFile(const QStringList &fileNames);


    /**
     * @brief get _progressInfo.
     * @return the state of the progress of the meshLoader.
     */
    ProgressInfo *progressInfo() const;





private:


    Shader      *_shader;   /** < A Shader pointer. */
    Model       *_model;    /** < A Model pointer.  */
    Camera      *_cam;      /** < A Camera pointer. */
    Light       *_light; /** < A Light pointer      */
    bool        _lightMode;
    std::vector<std::string> _filepaths; /** < A vector of mesh file.*/
    Model::TYPE_FILE _typeModel; /** < Type of the _filepaths (OBJ,MNT or NONE)..*/
    QTime _timer; /** < A Qt timer.*/
    ProgressInfo *_progressInfo; /** < The progress of the meshloader. */


    /**
     * @brief load Model from _filepaths and of type _typeModel
     */
    void loadModel();

};

#endif // VIEWER_H
