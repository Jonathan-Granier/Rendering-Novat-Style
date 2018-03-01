#include "viewer.h"
#include <iostream>


#include <QStringList>
#include <QString>

#include "meshloader.h"

using namespace std;
using namespace glm;
Viewer::Viewer(QWidget *parent) :
    QOpenGLWidget(parent),
    _lightPosition(vec3(0,0,1)),
    _lightMode(false),
    _typeModel(Model::NONE)
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
      cerr << "Warning: glewInit failed!" << endl;
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




void Viewer::mousePressEvent(QMouseEvent *me){
    const vec2 p((float)me->x(),(float)(height()-me->y()));
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
    const vec2 p((float)me->x(),(float)(height()-me->y()));
    if(_lightMode)
        moveLight(p);
    else
        _cam->move(p);

    update();
}

void Viewer::resetTheCameraPosition(){
    _cam->initialize(width(),height(),true);
    update();
}

void Viewer::reloadShader(){
    _shader->initialize();
    update();
}




void Viewer::loadModel()
{

    MeshLoader ml(_progressInfo);
    _model = new Model(ml,_filepaths,_typeModel);
    _cam = new Camera(_model->radius(),_model->center());
    _cam->initialize(width(),height(),true);


}

bool Viewer::loadModelFromFile(const QStringList &fileNames)
{

    if(_model){
        delete _model;
    }

    _filepaths.clear();


    QString ext_ref = fileNames.at(0).section('.',-1);
    //cout << "path : " << path.toStdString() << " ext : " << ext.toStdString() << endl;

    if(ext_ref.compare("obj")==0){
        _filepaths.push_back(fileNames.at(0).toStdString());
        _typeModel = Model::OBJ;
    }
    else if(ext_ref.compare("asc")==0){
        _filepaths.push_back(fileNames.at(0).toStdString());
        _typeModel = Model::MNT;
    }
    else{
        return false;
    }

    for(int i=1; i <fileNames.size();i++){
        QString ext = fileNames.at(i).section('.',-1);
        if(ext.compare(ext_ref)==0 && ext.compare("obj")!=0)
            _filepaths.push_back(fileNames.at(i).toStdString());
        else
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




void Viewer::moveLight(vec2 p)
{
    _lightPosition[0] = (p[0]-(float)(width()/2))/((float)(width()/2));
    _lightPosition[1] = (p[1]-(float)(height()/2))/((float)(height()/2));
    _lightPosition[2] = 1.0f-std::max(fabs(_lightPosition[0]),fabs(_lightPosition[1]));
    _lightPosition = normalize(_lightPosition);
}

