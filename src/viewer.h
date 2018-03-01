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

#include "shader.h"
#include "camera.h"
#include "model.h"
#include "progressinfo.h"

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

    /**
     * @brief A Shader pointer.
     */
    Shader      *_shader;
    /**
     * @brief A model pointer.
     */
    Model       *_model;
    /**
     * @brief A camera pointer
     */
    Camera      *_cam;
    /**
     * @brief the light position
     */
    glm::vec3   _lightPosition;
    /**
     * @brief For the mousse , true if we move the light , false otherwise.
     */
    bool        _lightMode;
    /**
     * @brief a vector of mesh file
     */
    std::vector<std::string> _filepaths;
    /**
     * @brief type of the _filepaths (OBJ,MNT or NONE).
     */
    Model::TYPE_FILE _typeModel;

    /**
     * @brief a Qt timer
     */
    QTime _timer;
    /**
     * @brief the progress of the meshloader
     */
    ProgressInfo *_progressInfo;

    /**
     * @brief load Model from _filepaths and of type _typeModel
     */
    void loadModel();
    /**
     * @brief Move the light
     * @param the new position of light.
     */
    void moveLight(glm::vec2 p);  
};

#endif // VIEWER_H
