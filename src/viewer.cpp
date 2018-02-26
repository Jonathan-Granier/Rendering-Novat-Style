#include "viewer.h"

Viewer::Viewer(QWidget *parent) :
    QOpenGLWidget(parent),
    _path(""),
    _typeModel(Model::NONE),
    _lightPosition(glm::vec3(0,0,1)),
    _lightMode(false)
{

    QSurfaceFormat format;
    format.setVersion(4,4);
    format.setProfile(QSurfaceFormat::CoreProfile);
    format.setSamples(16); // //multisampling (antialiasing) -> add glEnable(GL_MULTISAMPLE); in initialization.
    format.setDepthBufferSize(24);
    this->setFormat(format);

    _progressInfo = new ProgressInfo();
}

Viewer::~Viewer() {
  delete _model;
  delete _cam;
  delete _shader;
  delete _progressInfo;

}


void Viewer::initializeGL(){

    makeCurrent();

    // init and check glew

    glewExperimental = GL_TRUE;

    if(glewInit()!=GLEW_OK) {
      std::cerr << "Warning: glewInit failed!" << std::endl;
    }


    // init OpenGL settings
    glEnable(GL_MULTISAMPLE);
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glEnable(GL_DEPTH_TEST);
    glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
    glViewport(0,0,width(),height());



    loadModel();
    _shader = new Shader("shaders/vertexshader.vert", "shaders/fragmentshader.frag");
    _timer.start();

}

// Rendu loop
void Viewer::paintGL(){

    //printFPS();

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
    update();
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
    if(ke->key()==Qt::Key_F) {
     }
    update();

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
    update();
}
void Viewer::mouseMoveEvent(QMouseEvent *me){
    const glm::vec2 p((float)me->x(),(float)(height()-me->y()));
    if(_lightMode)
        moveLight(p);
    else
        _cam->move(p);

    update();
}

void Viewer::loadModel()
{

    MeshLoader ml(_progressInfo);
    _model = new Model(ml,_typeModel,_path);
    _cam = new Camera(_model->radius(),_model->center());
    _cam->initialize(width(),height(),true);


}

bool Viewer::loadModelFromFile(const QString &path)
{

    if(_model){
        delete _model;
    }
    QString ext = path.section('.',-1);

    std::cout << "path : " << path.toStdString() << " ext : " << ext.toStdString() << std::endl;

    if(ext.compare("obj")==0){
        std::cout << "OJB" << std::endl;
        _path = path.toStdString();
        _typeModel = Model::OBJ;
    }
    else if(ext.compare("asc")==0){
        std::cout << "MNT" << std::endl;
        _path = path.toStdString();
        _typeModel = Model::MNT;
    }
    else{
        return false;
    }
    initializeGL();
    update();
    return true;
}

ProgressInfo *Viewer::progressInfo() const
{
    return _progressInfo;
}




void Viewer::moveLight(glm::vec2 p)
{
    _lightPosition[0] = (p[0]-(float)(width()/2))/((float)(width()/2));
    _lightPosition[1] = (p[1]-(float)(height()/2))/((float)(height()/2));
    _lightPosition[2] = 1.0f-std::max(fabs(_lightPosition[0]),fabs(_lightPosition[1]));
    _lightPosition = glm::normalize(_lightPosition);
}

