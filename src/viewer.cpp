#include "viewer.h"
#include <iostream>


#include <QStringList>
#include <QString>

#include "meshloader.h"
#include "glm/gtx/string_cast.hpp"

using namespace std;
using namespace glm;
Viewer::Viewer(QWidget *parent) :
    QOpenGLWidget(parent),
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
  delete _light;

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
    glClearColor(0.082f, 0.376f, 0.741f, 1.0f); //  Bleu denim
    glEnable(GL_DEPTH_TEST);
    glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
    glViewport(0,0,width(),height());



    loadModel();
    _shader = new Shader("shaders/basic.vert", "shaders/basic.frag");
    _shader->add("shaders/toon1D.vert","shaders/toon1D.frag");
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
    _shader->setVec3("lightPosition",_light->position());

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
        _light->_mode = false;
        _cam->initRotation(p);
    } else if(me->button()==Qt::MidButton) {
        _light->_mode = false;
        _cam->initMoveZ(p);
    } else if(me->button()==Qt::RightButton) {
        _light->_mode = true;
        _light->move(p,(float)width(),(float)height());
    }
    update();
}
void Viewer::mouseMoveEvent(QMouseEvent *me){
    const vec2 p((float)me->x(),(float)(height()-me->y()));
    if(_light->_mode)
        _light->move(p,(float)width(),(float)height());
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




void Viewer::printCamAndLight(){
    cout << "proj mat : " << glm::to_string(_cam->projMatrix()) << endl;
    cout << "mdv mat : " << glm::to_string(_cam->mdvMatrix()) << endl;
    cout << "normal mat : " << glm::to_string(_cam ->normalMatrix()) << endl;
    cout << " light vec : " << glm::to_string(_light->position()) << endl;
}

void Viewer::fixeCamAndLight()
{
    _cam->setFixePosition();
    _light->setFixePosition();
    update();
}

void Viewer::nextShader()
{
    _shader->next();
    update();
}

void Viewer::previousShader()
{
    _shader->previous();
    update();
}


void Viewer::loadModel()
{

    MeshLoader ml(_progressInfo);
    _model = new Model(ml,_filepaths,_typeModel);
    _cam = new Camera(_model->radius(),_model->center());
    _cam->initialize(width(),height(),true);
    _light = new Light();


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




