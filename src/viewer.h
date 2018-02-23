#ifndef VIEWER_H
#define VIEWER_H


// GLEW lib: needs to be included first!!
#include <GL/glew.h>

// OpenGL library
#include <GL/gl.h>

// OpenGL Utility library
#include <GL/glu.h>





#include <iostream>
#include <unistd.h>





#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <vector>





#include <QOpenGLWidget>
#include <QColor>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QTime>
#include <QProgressBar>



#include "lib/stb_image.h"
#include "mesh.h"
#include "shader.h"
#include "camera.h"
#include "meshLoader.h"
#include "model.h"



class Viewer : public QOpenGLWidget
{

public:
    Viewer(QWidget *parent = 0);
    ~Viewer();

    virtual void paintGL();
    virtual void initializeGL();
    virtual void resizeGL(int width,int height);
    virtual void keyPressEvent(QKeyEvent *ke);
    virtual void mousePressEvent(QMouseEvent *me);
    virtual void mouseMoveEvent(QMouseEvent *me);


    bool loadModelFromFile(const QString &path);

private:

    Shader      *_shader;
    Model       *_model;
    Camera      *_cam;
    glm::vec3   _lightPosition;
    bool        _lightMode;
    std::string _path;
    Model::TYPE_FILE _typeModel;

    QTime _timer;
    QProgressBar _progressBar;

    double lastTime;
    int _nbFrames;

    void loadModel();
    void moveLight(glm::vec2 p);  
    void printFPS();
};

#endif // VIEWER_H
