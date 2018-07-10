#include "viewer.h"
#include <iostream>


#include <QStringList>
#include <QString>
#include "OpenGl/meshloader.h"
/*
// TODO DELETE ET trouve une solution
#define GLM_ENABLE_EXPERIMENTAL
*/
#define GLM_ENABLE_EXPERIMENTAL
#include "glm/gtx/string_cast.hpp"


using namespace std;
using namespace glm;

Viewer::Viewer(QWidget *parent) :
    QOpenGLWidget(parent),
    _drawMode(CLASSICAL),
    _lightMode(false)
{



    QSurfaceFormat format;
    format.setVersion(4,4);
    format.setProfile(QSurfaceFormat::CoreProfile);
    format.setSamples(16); // //multisampling (antialiasing) -> add glEnable(GL_MULTISAMPLE); in initialization.
    format.setDepthBufferSize(24);
    this->setFormat(format);
    create();
    _filepaths.push_back("../ressources/models/Basic/Est.asc");// BDALTI_Alpe_d_huez.asc");
    _light  = make_shared<Light>();
    _needInitializeScene = true;
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
    glClearColor(0.345f, 0.647f, 0.827f, 1.0f); // Cyan
    //glClearColor(0.5f, 0.5f, 0.5f, 1.0f);     // Grey
    glEnable(GL_DEPTH_TEST);
    glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
    glViewport(0,0,width(),height());



    if(_needInitializeScene){ // I don't know why but i need to reInitialize the OpenGl context . I have probleme with meshLoader.
        _scene  = make_shared<Scene>(width(),height());
        _needInitializeScene = false;
    }

    loadScene();
    initShaders();



    emit initializeDone();


}

// Rendu loop
void Viewer::paintGL(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    _scene->generateLaplacienPyramid();
    _scene->generateIntermediateScale(_cam->mdvMatrix(),_cam->normalMatrix(),_light->getDirection(),_light->getPitch(),_light->getYaw());
    switch(_drawMode){

    case HEIGHTMAP:
        _drawTextureShader->use();
        initDrawTexture(0);
        _scene->drawHeightMap(_drawTextureShader);
        _drawTextureShader->disable();
        break;
    case EDITHEIGHTMAP:
        _drawTextureShader->use();
        initDrawTexture(1);
        _scene->drawEditHeightMap(_drawTextureShader);
        _drawTextureShader->disable();
        break;
    case NORMALMAP:
        _drawTextureShader->use();
        initDrawTexture(2);
        _scene->drawNormalMap(_drawTextureShader);
        _drawTextureShader->disable();
        break;

    case SLANTMAP:
        _drawTextureShader->use();
        initDrawTexture(3);
        _scene->drawSlantMap(_drawTextureShader);
        _drawTextureShader->disable();
        break;
    case SHADELIGHTMAP :
        _drawTextureShader->use();
        initDrawTexture(4);
        _scene->drawShadeLightMap(_drawTextureShader);
        _drawTextureShader->disable();
        break;
    case SHADOWLIGHTMAP :
        _drawTextureShader->use();
        initDrawTexture(5);
        _scene->drawShadowLightMap(_drawTextureShader);
        _drawTextureShader->disable();
        break;
    case SHADOW :
        _drawTextureShader->use();
        initDrawTexture(6);
        _scene->drawShadowMap(_drawTextureShader);
        _drawTextureShader->disable();
        break;
    case MORPHODILATION :
        _drawTextureShader->use();
        initDrawTexture(7);
        _scene->drawMorphoDilationMap(_drawTextureShader);
        _drawTextureShader->disable();
        break;
    case MORPHOEROSION :
        _drawTextureShader->use();
        initDrawTexture(8);
        _scene->drawMorphoErosionMap(_drawTextureShader);
        _drawTextureShader->disable();
        break;
    case MERGESHADOW :
        _drawTextureShader->use();
        initDrawTexture(9);
        _scene->drawMergeShadowMap(_drawTextureShader);
        _drawTextureShader->disable();
        break;
    case SHADING :
        _drawTextureShader->use();
        initDrawTexture(10);
        _scene->drawShadingMap(_drawTextureShader);
        _drawTextureShader->disable();
         break;
    case CLASSICAL:
        _meshShader->use();
        _meshShader->setMat4("mdvMat",_cam->mdvMatrix());
        _meshShader->setMat4("projMat",_cam->projMatrix());
        _meshShader->setMat3("normalMat",_cam->normalMatrix());
        _meshShader->setVec3("lightDirection",_light->getDirection());
        _meshShader->setVec3("cameraPosition",_cam->view());
        _scene->draw(_meshShader,_light->getDirection());
        _meshShader->disable();
        break;
    }
}

void Viewer::resizeGL(int width,int height){
    //_cam->initialize(width,height,false);
    //glViewport(0,0,width,height);
    update();
}




void Viewer::mousePressEvent(QMouseEvent *me){
    _moussePos = vec2((float)me->x(),(float)(height()-me->y()));
    if(me->button()==Qt::LeftButton) {
        _lightMode = false;
        _cam->initRotation(_moussePos);
    } else if(me->button()==Qt::MidButton) {
        _lightMode = false;
        _cam->initMoveZ(_moussePos);
    } else if(me->button()==Qt::RightButton) {
        _lightMode = true;
        _light->startMoveAroundYAxe(_moussePos,width(),height());
    }
    update();
}

void Viewer::mouseMoveEvent(QMouseEvent *me){

   _moussePos = vec2((float)me->x(),(float)(height()-me->y()));


    if(_lightMode)
        _light->moveAroundYAxe(_moussePos,width(),height());
    else
        _cam->move(_moussePos);

    update();
}

void Viewer::setHeightLight(float angle)
{
    _light->moveAroundXZ(glm::radians(angle));
    update();
}

void Viewer::setPitchShadowLight(float p)
{
    _scene->setPitchLightShadow(glm::radians(p));
    update();
}




void Viewer::resetTheCameraPosition(){
    _cam->initialize(width(),height(),true);
    _light = make_shared<Light>();
    update();
}

void Viewer::reloadShader(){
    _meshShader->reload();
    //_shadowMap->reloadShader();
    _drawTextureShader->reload();
    _scene->reloadGenerateTexturesShader();
    cout << "reload shader done " << endl;
    update();

}




void Viewer::printCamAndLight(){
    cout << "proj mat : " << glm::to_string(_cam->projMatrix()) << endl;
    cout << "mdv mat : " << glm::to_string(_cam->mdvMatrix()) << endl;
    cout << "normal mat : " << glm::to_string(_cam ->normalMatrix()) << endl;
    cout << " light's angles : yaw : " << _light->getYaw() << " pitch : " << _light->getPitch() << endl;

}

void Viewer::fixeCamAndLight()
{
    _cam->setFixePosition();
    _light->setFixeDirection();
    update();
}



void Viewer::nextDrawMode(){
    switch(_drawMode){
        case HEIGHTMAP:       _drawMode = EDITHEIGHTMAP  ; break;
        case EDITHEIGHTMAP:   _drawMode = NORMALMAP      ; break;
        case NORMALMAP:       _drawMode = SLANTMAP       ; break;
        case SLANTMAP :       _drawMode = SHADELIGHTMAP  ; break;
        case SHADELIGHTMAP :  _drawMode = SHADOWLIGHTMAP ; break;
        case SHADOWLIGHTMAP:  _drawMode = SHADOW         ; break;
        case SHADOW :         _drawMode = MORPHODILATION ; break;
        case MORPHODILATION : _drawMode = MORPHOEROSION  ; break;
        case MORPHOEROSION :  _drawMode = MERGESHADOW    ; break;
        case MERGESHADOW :    _drawMode = SHADING        ; break;
        case SHADING :        _drawMode = CLASSICAL      ; break;
        case CLASSICAL:       _drawMode = HEIGHTMAP      ; break;
    }
    update();
}

void Viewer::setDrawMode(int d)
{
    switch(d){

        case 0 :  _drawMode = HEIGHTMAP      ; break;
        case 1 :  _drawMode = EDITHEIGHTMAP  ; break;
        case 2 :  _drawMode = NORMALMAP      ; break;
        case 3 :  _drawMode = SLANTMAP       ; break;
        case 4 :  _drawMode = SHADELIGHTMAP  ; break;
        case 5 :  _drawMode = SHADOWLIGHTMAP ; break;
        case 6 :  _drawMode = SHADOW         ; break;
        case 7:   _drawMode = MORPHODILATION ; break;
        case 8:   _drawMode = MORPHOEROSION  ; break;
        case 9:   _drawMode = MERGESHADOW    ; break;
        case 10:  _drawMode = SHADING        ; break;
        case 11:  _drawMode = CLASSICAL      ; break;
        default:  _drawMode = CLASSICAL      ; break;
    }
    update();
}

void Viewer::previousDrawMode(){
    switch(_drawMode){
        case HEIGHTMAP:         _drawMode = CLASSICAL       ; break;
        case EDITHEIGHTMAP:     _drawMode = HEIGHTMAP       ; break;
        case NORMALMAP:         _drawMode = EDITHEIGHTMAP   ; break;
        case SLANTMAP :         _drawMode = NORMALMAP       ; break;
        case SHADELIGHTMAP :    _drawMode = SLANTMAP        ; break;
        case SHADOWLIGHTMAP:    _drawMode = SHADELIGHTMAP   ; break;
        case SHADOW :           _drawMode = SHADOWLIGHTMAP  ; break;
        case MORPHODILATION :   _drawMode = SHADOW          ; break;
        case MORPHOEROSION :    _drawMode = MORPHODILATION  ; break;
        case MERGESHADOW :      _drawMode = MORPHOEROSION   ; break;
        case SHADING :          _drawMode = MERGESHADOW     ; break;
        case CLASSICAL:         _drawMode = SHADING         ; break;
    }
    update();
}

void Viewer::selectCurrentScale(int id){
    _scene->selectCurrentScale(id);
    update();
}


bool Viewer::loadSceneFromFile(const QStringList &fileNames)
{
    _filepaths.clear();


    QString ext_ref = fileNames.at(0).section('.',-1);

    if(ext_ref.compare("asc")==0){
        _filepaths.push_back(fileNames.at(0).toStdString());
    }
    else{
        return false;
    }

    for(int i=1; i <fileNames.size();i++){
        QString ext = fileNames.at(i).section('.',-1);
        if(ext.compare(ext_ref)==0)
            _filepaths.push_back(fileNames.at(i).toStdString());
        else
            return false;
    }


    initializeGL();
    //loadScene();
    update();
    return true;
}


void Viewer::generateScene(){
    _filepaths.clear();
    initializeGL();
    update();
}


string Viewer::getCurrentDrawMode()
{
    string stringdrawMode;
    switch(_drawMode){
        case HEIGHTMAP:
            stringdrawMode = "Height Map";
        break;
        case EDITHEIGHTMAP:
            stringdrawMode = "Edit Height Map";
        break;
        case NORMALMAP:
            stringdrawMode = "Normal Map";
        break;
        case SLANTMAP:
            stringdrawMode = "Slant Map";
        break;
        case SHADELIGHTMAP :
            stringdrawMode = "Shade Light Map";
        break;
        case SHADOWLIGHTMAP :
            stringdrawMode = "Shadow Light Map";
        break;
        case SHADOW :
            stringdrawMode = "Shadow Map";
        break;
        case MORPHODILATION :
            stringdrawMode = "Morpho Dilation Map";
        break;
        case MORPHOEROSION :
            stringdrawMode = "Morpho Erosion Map";
        break;

        case MERGESHADOW :
            stringdrawMode = "Merge Shadow Map";
        break;
        case SHADING :
            stringdrawMode = "Shading Map";
        break;
        case CLASSICAL:
            stringdrawMode = "World";
        break;
    }
    return stringdrawMode;
}


void Viewer::setLightThreshold(unsigned int id, float t)
{
    _scene->setLightThreshold(id,t);
    update();
}


void Viewer::setGaussBlurFactor(unsigned int id, int g)
{
    _scene->setGaussBlurFactor(id,g);
    update();
}



void Viewer::setEnabledScale(unsigned int id,bool enabled){
    _scene->setEnabledScale(id,enabled);
    update();
}

void Viewer::reloadLaplacienPyramid(){
    _scene->reloadLaplacienPyramid();
    update();
}


void Viewer::addScale(unsigned int id){
    _scene->addScale(id);
    update();
}



void Viewer::setShadeSelector(int s){
    _scene->setShadeSelector(s);
    update();
}

void Viewer::setDoShadow(int b)
{
    _scene->setDoShadow(b);
    update();
}


void Viewer::setDoEditShadeLightDir(int b)
{
    _scene->setDoEditShadeLightDir(b);
    update();
}

void Viewer::setDoEditShadowLightDir(int b)
{
    _scene->setDoEditShadowLightDir(b);
    update();
}

void Viewer::setDoShadowMorpho(int b)
{
    _scene->setDoShadowMorpho(b);
    update();
}


void Viewer::setPlainColor(const QColor &plainColor)
{
    qreal r,g,b,a;
    plainColor.getRgbF(&r,&g,&b,&a);
    _scene->setPlainColor(vec4(r,g,b,a));
     update();
}

QColor Viewer::getPlainColor() const
{
    vec4 c = _scene->getPlainColor();
    QColor qc;
    qc.setRgbF(c.r,c.g,c.b,c.a);
    return qc;
}

void Viewer::setWaterColor(const QColor &waterColor)
{
    qreal r,g,b,a;
    waterColor.getRgbF(&r,&g,&b,&a);
    _scene->setWaterColor(vec4(r,g,b,a));
     update();
}

QColor Viewer::getWaterColor() const{
    vec4 c = _scene->getWaterColor();
    QColor qc;
    qc.setRgbF(c.r,c.g,c.b,c.a);
    return qc;
}

void Viewer::loadColorMapTex(QString filepaths){
    _scene->loadColorMapTex(filepaths.toStdString());
     update();
}

void Viewer::loadCelShadingTex(QString filepaths){
    _scene->loadCelShadingTex(filepaths.toStdString());
     update();
}




void Viewer::setColorSelector(int c)
{
    _scene->setColorSelector(c);
    update();
}


void Viewer::setDoDefaultShading(bool b)
{
   _scene->setDoDefaultShading(b);
   update();
}


/************************************************
 *              Private Functions               *
 ************************************************/
void Viewer::loadScene()
{
    _scene->createScene(_filepaths);
    _cam    = make_shared<Camera>(_scene->getRadius(),_scene->getCenter());
    _cam->initialize(width(),height(),true);

}

void Viewer::initShaders(){
    _meshShader = make_shared<Shader>("../sources_code/shaders/computelight.vert", "../sources_code/shaders/computelight.frag");
    _drawTextureShader = make_shared<Shader>("../sources_code/shaders/drawtexture.vert","../sources_code/shaders/drawtexture.frag");

}

void Viewer::initDrawTexture(int numTex){
    _drawTextureShader->setInt("selectTexture",numTex);
    _drawTextureShader->setVec2("moussePos",_moussePos);
    _scene->sendAsciiTexToShader(_drawTextureShader);
}
