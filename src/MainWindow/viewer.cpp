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
    _drawMode(CLASSICAL),
    _typeMesh(Scene::MNT)

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



    loadScene();
    _shader = make_shared<Shader>("shaders/debug.vert", "shaders/debug.frag");
    _shader->add("shaders/phong.vert", "shaders/phong.frag");
    _shader->add("shaders/phongspec.vert", "shaders/phongspec.frag");
    _shader->add("shaders/toon1D.vert","shaders/toon1D.frag");

    _shaderDrawTexture = make_shared<Shader>("shaders/drawtexture.vert","shaders/drawtexture.frag");

    _timer.start();

}

// Rendu loop
void Viewer::paintGL(){


    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


    switch(_drawMode){
    case CLASSICAL:
             _shadowMap->startGenerate();
             _shadowMap->generate(_Scene,_light->position(),width(),height());
             _shader->use();
             _shader->setMat4("mdvMat",_cam->mdvMatrix());
             _shader->setMat4("projMat",_cam->projMatrix());
             _shader->setMat3("normalMat",_cam->normalMatrix());
             _shader->setVec3("lightPosition",_light->position());
             _shader->setVec3("cameraPosition",_cam->view());
             _shader->setMat4("ligthSpaceMat",_shadowMap->lightSpaceMatrix());
             _shadowMap->sendToShader(_shader);
             _Scene->draw(_shader,_light->position());
             _shader->disable();_shaderDrawTexture->setInt("selectTexture",1);
        break;
    case SHADOWMAP:
             _shadowMap->startGenerate();
             _shadowMap->generate(_Scene,_light->position(),width(),height());
             _shaderDrawTexture->use();
             _shaderDrawTexture->setInt("selectTexture",0);
             _shadowMap->draw(_shaderDrawTexture);
             _shaderDrawTexture->disable();
        break;

    case HEIGHTMAP:
        _shaderDrawTexture->use();
        _shaderDrawTexture->setInt("selectTexture",2);
        _Scene->drawHeightMap(_shaderDrawTexture);
        _shaderDrawTexture->disable();
        break;
    case NORMALMAP:
        _shaderDrawTexture->use();
        _shaderDrawTexture->setInt("selectTexture",1);
        _Scene->drawNormalMap(_shaderDrawTexture);
        _shaderDrawTexture->disable();
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
    _light = make_shared<Light>(vec3(0.0,3*_Scene->radius(),3*_Scene->radius()));
    update();
}

void Viewer::reloadShader(){
    _shader->reload();
    //_shaderDepthMap->reload();
    _shadowMap->reloadShader();
    _shaderDrawTexture->reload();
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

void Viewer::loadScene()
{


    MeshLoader ml(_progressInfo);

    _Scene  = make_shared<Scene>(ml,_filepaths,_typeMesh);
    _cam    = make_shared<Camera>(_Scene->radius(),_Scene->center());
    _cam->initialize(width(),height(),true);
    _light  = make_shared<Light>(vec3(0.0,_Scene->radius(),3.0*_Scene->radius()));
    _shadowMap = make_shared<ShadowMap>("depthMap",1024,1024);
    _shadowMap->initialize();
            //_Scene = new Scene();
    //_cam = new Camera();
    //_cam->initialize(width(),height(),true);
    //_light = new Light(vec3(0.0,3*_Scene->radius(),3*_Scene->radius()));
    //_light = new Light(vec3(5, 20, 20));

    //_shadowMap = new ShadowMap("depthMap");


    //_Scene->initShadowMap();
}

bool Viewer::loadSceneFromFile(const QStringList &fileNames)
{



    _filepaths.clear();


    QString ext_ref = fileNames.at(0).section('.',-1);
    //cout << "path : " << path.toStdString() << " ext : " << ext.toStdString() << endl;

    if(ext_ref.compare("obj")==0){
        _filepaths.push_back(fileNames.at(0).toStdString());
        _typeMesh = Scene::OBJ;
    }
    else if(ext_ref.compare("asc")==0){
        _filepaths.push_back(fileNames.at(0).toStdString());
        _typeMesh = Scene::MNT;
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



