#include "viewer.h"
#include <iostream>


#include <QStringList>
#include <QString>

#include "src/OpenGl/meshloader.h"
#include "glm/gtx/string_cast.hpp"

using namespace std;
using namespace glm;
Viewer::Viewer(QWidget *parent) :
    QOpenGLWidget(parent),
    _lightMode(false),
    _drawMode(HEIGHTMAP),
    _typeModel(Model::MNT)

{

    QSurfaceFormat format;
    format.setVersion(4,4);
    format.setProfile(QSurfaceFormat::CoreProfile);
    format.setSamples(16); // //multisampling (antialiasing) -> add glEnable(GL_MULTISAMPLE); in initialization.
    format.setDepthBufferSize(24);
    this->setFormat(format);

    _progressInfo = new ProgressInfo();
    _filepaths.push_back("models/MNT_basic.asc");
}

Viewer::~Viewer() {


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
    _shader = make_shared<Shader>("shaders/debug.vert", "shaders/debug.frag");
    _shader->add("shaders/phong.vert", "shaders/phong.frag");
    _shader->add("shaders/phongspec.vert", "shaders/phongspec.frag");
    _shader->add("shaders/toon1D.vert","shaders/toon1D.frag");

  //  _shaderDepthMap = new Shader("shaders/shadowmap.vert", "shaders/shadowmap.frag");
  //  _shaderDepthMap->add("shaders/shadowmapdebug.vert", "shaders/shadowmapdebug.frag");

    _shaderHeightMap = make_shared<Shader>("shaders/heightmap.vert","shaders/heightmap.frag");
    _shaderNormalMap = make_shared<Shader>("shaders/normalmap.vert","shaders/normalmap.frag");

    _timer.start();

}

// Rendu loop
void Viewer::paintGL(){


    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


    switch(_drawMode){
    case CLASSICAL:
             _shadowMap->RenderFromLight(_model,_light->position(),width(),height());
             _shader->use();
             _shader->setMat4("mdvMat",_cam->mdvMatrix());
             _shader->setMat4("projMat",_cam->projMatrix());
             _shader->setMat3("normalMat",_cam->normalMatrix());
             _shader->setVec3("lightPosition",_light->position());
             _shader->setVec3("cameraPosition",_cam->view());
             _shader->setMat4("ligthSpaceMat",_shadowMap->lightSpaceMatrix());
             _shadowMap->draw(_shader);
             _model->draw(_shader);
             _shader->disable();
        break;
    case SHADOWMAP:
             _shadowMap->RenderFromLight(_model,_light->position(),width(),height());
             _shadowMap->DebugShadowMap();
        break;

    case HEIGHTMAP:
        _shaderHeightMap->use();
        _model->drawHeightMap(_shaderHeightMap);
        _shaderHeightMap->disable();
        break;
    case NORMALMAP:
        _shaderNormalMap->use();
        _model->drawNormalMap(_shaderNormalMap);
        _shaderNormalMap->disable();
        break;
    }
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
        _light->startMoveAroundYAxe(p,width(),height());
        //_light->moveAroundYAxe(p);
        //_light->move(p,(float)width(),(float)height());
    }
    update();
}
void Viewer::mouseMoveEvent(QMouseEvent *me){
    const vec2 p((float)me->x(),(float)(height()-me->y()));


    if(_lightMode)
        //_light->move(p,(float)width(),(float)height());
        _light->moveAroundYAxe(p,width(),height());
    else
        _cam->move(p);

    update();
}

void Viewer::resetTheCameraPosition(){
    _cam->initialize(width(),height(),true);
    _light = make_shared<Light>(vec3(0.0,3*_model->radius(),3*_model->radius()));
    update();
}

void Viewer::reloadShader(){
    _shader->reload();
    //_shaderDepthMap->reload();
    _shadowMap->reloadShader();
    _shaderHeightMap->reload();
    _shaderNormalMap->reload();
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

string Viewer::nextShader()
{
    _shader->next();
    update();
    return _shader->name();
}

string Viewer::previousShader()
{
    _shader->previous();
    update();
    return _shader->name();
}


void Viewer::nextDrawMode(){
    switch(_drawMode){
        case CLASSICAL: _drawMode = SHADOWMAP; break;
        case SHADOWMAP: _drawMode = HEIGHTMAP; break;
        case HEIGHTMAP: _drawMode = NORMALMAP; break;
        case NORMALMAP: _drawMode = CLASSICAL; break;
    }


    update();
}

void Viewer::previousDrawMode(){
    switch(_drawMode){
        case CLASSICAL: _drawMode = NORMALMAP; break;
        case SHADOWMAP: _drawMode = CLASSICAL; break;
        case HEIGHTMAP: _drawMode = SHADOWMAP; break;
        case NORMALMAP: _drawMode = HEIGHTMAP; break;
    }
    update();
}

void Viewer::loadModel()
{


    MeshLoader ml(_progressInfo);

    _model  = make_shared<Model>(ml,_filepaths,_typeModel);
    _cam    = make_shared<Camera>(_model->radius(),_model->center());
    _cam->initialize(width(),height(),true);
    _light  = make_shared<Light>(vec3(0.0,3*_model->radius(),3*_model->radius()));
    _shadowMap = make_shared<ShadowMap>("depthMap");
            //_model = new Model();
    //_cam = new Camera();
    //_cam->initialize(width(),height(),true);
    //_light = new Light(vec3(0.0,3*_model->radius(),3*_model->radius()));
    //_light = new Light(vec3(5, 20, 20));

    //_shadowMap = new ShadowMap("depthMap");


    //_model->initShadowMap();
}

bool Viewer::loadModelFromFile(const QStringList &fileNames)
{



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



