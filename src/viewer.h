#ifndef VIEWER_H
#define VIEWER_H

#include <iostream>
#include <unistd.h>

//#include <glad/glad.h>
//#include <GLFW/glfw3.h>

// GLEW lib: needs to be included first!!
#include <GL/glew.h>

// OpenGL library
#include <GL/gl.h>

// OpenGL Utility library
#include <GL/glu.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <vector>


#include <QGLFormat>
#include <QGLWidget>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QTimer>

#include "lib/stb_image.h"
#include "mesh.h"
#include "shader.h"
#include "camera.h"
#include "vertexLoader.h"
#include "model.h"

#include "camera_test.h"

class Viewer : public QGLWidget
{
public:
    Viewer(const QGLFormat &format=QGLFormat::defaultFormat());
    ~Viewer();

    virtual void paintGL();
    virtual void initializeGL();
    virtual void resizeGL(int width,int height);
    virtual void keyPressEvent(QKeyEvent *ke);
    virtual void mousePressEvent(QMouseEvent *me);
    virtual void mouseMoveEvent(QMouseEvent *me);


private:

    Shader      *_shader;
    Model       *_model;
    Camera      *_cam;
    Camera_TEST *_cam_TEST;

};

#endif // VIEWER_H
