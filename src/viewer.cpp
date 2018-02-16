#include "viewer.h"

Viewer::Viewer(const QGLFormat &format) :
    QGLWidget(format)
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
      cerr << "Warning: glewInit failed!" << endl;
    }






    // init OpenGL settings
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glEnable(GL_DEPTH_TEST);
    glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
    glViewport(0,0,width(),height());

    _model = new Model(Model::NONE,"");
    _cam = new Camera(_model->radius(),_model->center());
    _shader = new Shader("shaders/vertexshader.vert", "shaders/fragmentshader.frag");

    _cam->initialize(width(),height(),true);


    _cam_TEST = new Camera_TEST(_model->radius(),_model->center());
    _cam_TEST->initialize(width(),height(),true);
}

void Viewer::paintGL(){

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    _shader->use();

    _shader->setMat4("mdvMat",_cam->mdvMatrix());
    _shader->setMat4("projMat",_cam->projMatrix());
    _shader->setMat4("normalMat",_cam->normalMatrix());

    _model->draw(_shader);

    _shader->disable();


}

void Viewer::resizeGL(int width,int height){
    _cam->initialize(width,height,false);
    _cam_TEST->initialize(width,height,true);
    glViewport(0,0,width,height);
    updateGL();
}



void Viewer::keyPressEvent(QKeyEvent *ke){

    // key i: init camera
    if(ke->key()==Qt::Key_I) {
      _cam->initialize(width(),height(),true);
      _cam_TEST->initialize(width(),height(),true);
    }
    updateGL();
    // key r: reload shaders TODO
}

void Viewer::mousePressEvent(QMouseEvent *me){
    const glm::vec2 p((float)me->x(),(float)(height()-me->y()));
    if(me->button()==Qt::LeftButton) {
        _cam->initRotation(p);
        _cam_TEST->initRotation(p);
    } else if(me->button()==Qt::MidButton) {
        _cam->initMoveZ(p);
        _cam_TEST->initMoveZ(p);
    }
    updateGL();
}
void Viewer::mouseMoveEvent(QMouseEvent *me){
    const glm::vec2 p((float)me->x(),(float)(height()-me->y()));
    _cam->move(p);
    _cam_TEST->move(p);
    updateGL();
}
