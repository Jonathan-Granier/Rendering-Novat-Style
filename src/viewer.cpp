#include "viewer.h"

Viewer::Viewer(const QGLFormat &format) :
    QGLWidget(format),
    _lightPosition(glm::vec3(0,0,1)),
    _lightMode(false)
{

}

Viewer::~Viewer() {
  //deleteBuffers();
  delete _model;
  delete _cam;
  delete _shader;

}


void Viewer::initializeGL(){

    makeCurrent();

    /*if (!gladLoadGL())
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        exit(0);
    }
    */

    // init and chack glew
    glewExperimental = GL_TRUE;

    if(glewInit()!=GLEW_OK) {
      std::cerr << "Warning: glewInit failed!" << std::endl;
    }






    // init OpenGL settings
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glEnable(GL_DEPTH_TEST);
    glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
    glViewport(0,0,width(),height());

    //_model = new Model(Model::NONE,"");
    _model = new Model(Model::OBJ,"Models/cube.obj");
    _cam = new Camera(_model->radius(),_model->center());
    _shader = new Shader("shaders/vertexshader.vert", "shaders/fragmentshader.frag");

    _cam->initialize(width(),height(),true);
}

void Viewer::paintGL(){

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    _shader->use();

    _shader->setMat4("mdvMat",_cam->mdvMatrix());
    _shader->setMat4("projMat",_cam->projMatrix());
    _shader->setMat3("normalMat",_cam->normalMatrix());
    _shader->setVec3("lightPosition",_lightPosition);

    _model->draw(_shader);

    _shader->disable();


}

void Viewer::resizeGL(int width,int height){
    _cam->initialize(width,height,false);
    glViewport(0,0,width,height);
    updateGL();
}



void Viewer::keyPressEvent(QKeyEvent *ke){

    // key i: init camera
    if(ke->key()==Qt::Key_I) {
      _cam->initialize(width(),height(),true);
    }
    //key r : reload shader
    if(ke->key()==Qt::Key_R){
       _shader->initialize();
    }
    updateGL();

}

void Viewer::mousePressEvent(QMouseEvent *me){
    const glm::vec2 p((float)me->x(),(float)(height()-me->y()));
    if(me->button()==Qt::LeftButton) {
        _lightMode = false;
        _cam->initRotation(p);
    } else if(me->button()==Qt::MidButton) {
        _lightMode = false;
        _cam->initMoveZ(p);
    } else if(me->button()==Qt::RightButton) {
        _lightMode = true;
        moveLight(p);
    }
    updateGL();
}
void Viewer::mouseMoveEvent(QMouseEvent *me){
    const glm::vec2 p((float)me->x(),(float)(height()-me->y()));
    if(_lightMode)
        moveLight(p);
    else
        _cam->move(p);

    updateGL();
}

void Viewer::moveLight(vec2 p)
{
    _lightPosition[0] = (p[0]-(float)(width()/2))/((float)(width()/2));
    _lightPosition[1] = (p[1]-(float)(height()/2))/((float)(height()/2));
    _lightPosition[2] = 1.0f-std::max(fabs(_lightPosition[0]),fabs(_lightPosition[1]));
    _lightPosition = glm::normalize(_lightPosition);
    std::cout << "I move the light : " << glm::to_string(_lightPosition) << std::endl;
}
