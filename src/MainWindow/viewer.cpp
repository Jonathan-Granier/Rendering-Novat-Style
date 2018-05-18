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
    _drawMode(CLASSICAL)

{



    QSurfaceFormat format;
    format.setVersion(4,4);
    format.setProfile(QSurfaceFormat::CoreProfile);
    format.setSamples(16); // //multisampling (antialiasing) -> add glEnable(GL_MULTISAMPLE); in initialization.
    format.setDepthBufferSize(24);
    this->setFormat(format);
    create();
    _filepaths.push_back("models/BDALTI_Alpe_d_huez.asc");
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
    glClearColor(0.082f, 0.376f, 0.741f, 1.0f); //  Bleu denim
    glEnable(GL_DEPTH_TEST);
    glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
    glViewport(0,0,width(),height());



    //loadScene();
    if(_needInitializeScene){ // I don't know why but i need to reInitialize the OpenGl context . I have probleme with meshLoader.
        _scene  = make_shared<Scene>(width(),height());
        _needInitializeScene = false;
    }

    loadScene();
    initShaders();
    _timer.start();



    emit initializeDone();


}

// Rendu loop
void Viewer::paintGL(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    _scene->generateGaussHeightMap();
    _scene->generateEditHeightAndNormalMap();
    _scene->generateSlantLightAndParalaxMaps(_cam->mdvMatrix(),_cam->mdvMatrix(),_light->position(),_light->pitch(),_light->yaw());
    switch(_drawMode){
    case CLASSICAL:


        _lightShaders->use();
        _lightShaders->setMat4("mdvMat",_cam->mdvMatrix());
        _lightShaders->setMat4("projMat",_cam->projMatrix());
        _lightShaders->setMat3("normalMat",_cam->mdvMatrix());
        _lightShaders->setVec3("lightPosition",_light->position());
        _lightShaders->setVec3("cameraPosition",_cam->view());
        _scene->draw(_lightShaders,_light->position());
        _lightShaders->disable();
        break;
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
    case SHADEANGLESMAP:
        _drawTextureShader->use();
        initDrawTexture(5);
        _scene->drawShadeLightMap(_drawTextureShader);
        _drawTextureShader->disable();
        break;
    case SHADOWLIGHTMAP :
        _drawTextureShader->use();
        initDrawTexture(6);
        _scene->drawShadowLightMap(_drawTextureShader);
        _drawTextureShader->disable();
        break;
    case SHADOWANGLESMAP:
        _drawTextureShader->use();
        initDrawTexture(7);
        _scene->drawShadowLightMap(_drawTextureShader);
        _drawTextureShader->disable();
        break;
    case PARALLAX :
        _drawTextureShader->use();
        initDrawTexture(8);
        _scene->drawParallaxMap(_drawTextureShader);
        _drawTextureShader->disable();
        break;
    case SHADING :
        _drawTextureShader->use();
        initDrawTexture(9);
        _scene->drawShadingMap(_drawTextureShader);
        _drawTextureShader->disable();
         break;
    }
}

void Viewer::resizeGL(int width,int height){
    _cam->initialize(width,height,false);
    glViewport(0,0,width,height);
    update();
}




void Viewer::mousePressEvent(QMouseEvent *me){




    //cout << width() << " " << height() << endl;
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

float Viewer::getHeightLight()
{
    return glm::degrees(_light->yaw());
}

void Viewer::resetTheCameraPosition(){
    _cam->initialize(width(),height(),true);
    _light = make_shared<Light>();
    update();
}

void Viewer::reloadShader(){
    _lightShaders->reload();
    //_shadowMap->reloadShader();
    _drawTextureShader->reload();
    _scene->reloadGenerateTexturesShader();

    update();

}




void Viewer::printCamAndLight(){
    cout << "proj mat : " << glm::to_string(_cam->projMatrix()) << endl;
    cout << "mdv mat : " << glm::to_string(_cam->mdvMatrix()) << endl;
    cout << "normal mat : " << glm::to_string(_cam ->normalMatrix()) << endl;
    cout << " light's angles : yaw : " << _light->yaw() << " pitch : " << _light->pitch() << endl;
}

void Viewer::fixeCamAndLight()
{
    _cam->setFixePosition();
    _light->setFixePosition();
    update();
}

string Viewer::nextShader()
{
    _lightShaders->next();
    update();
    return _lightShaders->name();
}

string Viewer::previousShader()
{
    _lightShaders->previous();
    update();
    return _lightShaders->name();
}


void Viewer::nextDrawMode(){
    switch(_drawMode){
        case CLASSICAL:       _drawMode = HEIGHTMAP      ; break;
        case HEIGHTMAP:       _drawMode = EDITHEIGHTMAP  ; break;
        case EDITHEIGHTMAP:   _drawMode = NORMALMAP      ; break;
        case NORMALMAP:       _drawMode = SLANTMAP       ; break;
        case SLANTMAP :       _drawMode = SHADELIGHTMAP  ; break;
        case SHADELIGHTMAP :  _drawMode = SHADEANGLESMAP ; break;
        case SHADEANGLESMAP:  _drawMode = SHADOWLIGHTMAP ; break;
        case SHADOWLIGHTMAP:  _drawMode = SHADOWANGLESMAP; break;
        case SHADOWANGLESMAP: _drawMode = PARALLAX       ; break;
        case PARALLAX :       _drawMode = SHADING        ; break;
        case SHADING :        _drawMode = CLASSICAL      ; break;
    }


    update();
}

void Viewer::setDrawMode(int d)
{
    switch(d){
        case 0 :  _drawMode = CLASSICAL      ; break;
        case 1 :  _drawMode = HEIGHTMAP      ; break;
        case 2 :  _drawMode = EDITHEIGHTMAP  ; break;
        case 3 :  _drawMode = NORMALMAP      ; break;
        case 4 :  _drawMode = SLANTMAP       ; break;
        case 5 :  _drawMode = SHADELIGHTMAP  ; break;
        case 6 :  _drawMode = SHADEANGLESMAP ; break;
        case 7 :  _drawMode = SHADOWLIGHTMAP ; break;
        case 8 :  _drawMode = SHADOWANGLESMAP; break;
        case 9 :  _drawMode = PARALLAX       ; break;
        case 10:  _drawMode = SHADING        ; break;
        default: _drawMode = CLASSICAL       ; break;
    }
    update();
}

void Viewer::previousDrawMode(){
    switch(_drawMode){
        case CLASSICAL:         _drawMode = SHADING        ; break;
        case HEIGHTMAP:         _drawMode = CLASSICAL      ; break;
        case EDITHEIGHTMAP:     _drawMode = HEIGHTMAP      ; break;
        case NORMALMAP:         _drawMode = EDITHEIGHTMAP  ; break;
        case SLANTMAP :         _drawMode = NORMALMAP      ; break;
        case SHADELIGHTMAP :    _drawMode = SLANTMAP       ; break;
        case SHADEANGLESMAP:    _drawMode = SHADELIGHTMAP  ; break;
        case SHADOWLIGHTMAP:    _drawMode = SHADEANGLESMAP ; break;
        case SHADOWANGLESMAP:   _drawMode = SHADOWLIGHTMAP ; break;
        case PARALLAX :         _drawMode = SHADOWANGLESMAP; break;
        case SHADING :          _drawMode = PARALLAX       ; break;
    }
    update();
}



/*
void Viewer::switchScene(){
    _scene->nextMaps();
    //_scene->switchTypeMeshUsed();
    //_cam    = make_shared<Camera>(_scene->radius(),_scene->center());
    //_cam->initialize(width(),height(),true);
    update();
}
*/
void Viewer::nextMaps(){
    _scene->nextMaps();
    update();
}

void Viewer::previousMaps(){
    _scene->previousMaps();
    update();
}



bool Viewer::loadSceneFromFile(const QStringList &fileNames)
{



    _filepaths.clear();


    QString ext_ref = fileNames.at(0).section('.',-1);
    //cout << "path : " << path.toStdString() << " ext : " << ext.toStdString() << endl;

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
    string stringDrawMode;
    switch(_drawMode){
        case CLASSICAL:
            stringDrawMode = "World";
        break;
        case HEIGHTMAP:
        stringDrawMode = "Height Map";
        break;
        case EDITHEIGHTMAP:
        stringDrawMode = "Edit Height Map";
        break;
        case NORMALMAP:
        stringDrawMode = "Normal Map";
        break;
        case SLANTMAP:
        stringDrawMode = "Slant Map";
            break;

        case SHADELIGHTMAP :
        stringDrawMode = "Shade Light Map";
        break;
        case SHADEANGLESMAP:
        stringDrawMode = "Shade Angles Map";
        break;
        case SHADOWLIGHTMAP :
        stringDrawMode = "Shadow Light Map";
        break;
        case SHADOWANGLESMAP:
        stringDrawMode = "Shadow Angles Map";
        break;
        case PARALLAX :
        stringDrawMode = "Parallax Map";
        break;
        case SHADING :
        stringDrawMode = "Shading Map";
        break;
    }
    return stringDrawMode;
}



string Viewer::getCurrentShader()
{

    return _lightShaders->name();
}

/*
float Viewer::getSigma() const
{
    return _scene->getSigma();
}

void Viewer::setSigma(float sigma)
{
    _scene->setSigma(sigma);
    update();
}

void Viewer::nextLight()
{
    _scene->nextLight();
    update();
}

void Viewer::previousLight()
{
    _scene->previousLight();
    update();
}

int Viewer::getLightSelector() const
{
    return _scene->getLightSelector();
}

float Viewer::getLightThreshold()
{
    return _scene->getLightSelector();
}

void Viewer::setLightThreshold(float lightThreshold)
{
    _scene->setLightThreshold(lightThreshold);
    update();
}

void Viewer::setGaussBlurFactor(int f){
    _scene->setGaussBlurFactor(f);
}

int Viewer::getGaussBlurFactor(){
    return _scene->getGaussBlurFactor();
}
*/
//TODO
void Viewer::setGaussBlurFactor(unsigned int id, float g)
{
    _scene->setGaussBlurFactor(id,g);
    //cout << " Set Gauss blur factor with id = " << id << " and sigma = " << sigma << endl;
    update();
}
//TODO
void Viewer::setLightThreshold(unsigned int id, float t)
{
    _scene->setLightThreshold(id,t);
    update();
}


void Viewer::setEnabledMaps(unsigned int id,bool enabled){
    _scene->setEnabledMaps(id,enabled);
    update();
}

void Viewer::reloadGaussHeightMap(){
    _scene->reloadGaussHeightMap();
    update();
}


void Viewer::addGaussMaps(unsigned int id){
    _scene->addGaussMaps(id);
    update();
}


int Viewer::getCurrentMapsIndex() const {
    return _scene->getCurrentMapsIndex();
}

void Viewer::setTypeShading(int t){
    _scene->setTypeShading(t);
    update();
}


void Viewer::setShadeSelector(int s){
    _scene->setShadeSelector(s);
    update();
}

void Viewer::setDoShadow(bool s){
    _scene->setDoShadow(s);
    update();
}

void Viewer::setTypeMerge(int t)
{
    _scene->setTypeMerge(t);
    update();
}

void Viewer::makeATest(int numTest){
    // Set camera
    _cam->setFixePosition2();
    // Set light
    //North
    _light->setFixePosition(2.47764,0.785498);
    makeTestForOneOrientation(numTest,"North");
    _light->setFixePosition(3.79852,0.785498);
    makeTestForOneOrientation(numTest,"East");
    _light->setFixePosition(5.56718,0.785498);
    makeTestForOneOrientation(numTest,"South");
    _light->setFixePosition(0.807116,0.785498);
    makeTestForOneOrientation(numTest,"West");




}


/************************************************
 *              Private Functions               *
 ************************************************/
void Viewer::loadScene()
{
    _scene->createScene(_filepaths);
    _cam    = make_shared<Camera>(_scene->radius(),_scene->center());
    _cam->initialize(width(),height(),true);
    //_shadowMap = make_shared<ShadowMap>("depthMap",1024,1024);
    //_shadowMap->initialize();


}

void Viewer::initShaders(){
    _lightShaders = make_shared<Shader>("shaders/debug.vert", "shaders/debug.frag");
    _lightShaders->add("shaders/computelight.vert", "shaders/computelight.frag");
    _lightShaders->add("shaders/phong.vert", "shaders/phong.frag");
    _lightShaders->add("shaders/phongspec.vert", "shaders/phongspec.frag");
    _lightShaders->add("shaders/toon1D.vert","shaders/toon1D.frag");

    _drawTextureShader = make_shared<Shader>("shaders/drawtexture.vert","shaders/drawtexture.frag");

}

void Viewer::initDrawTexture(int numTex){
    _drawTextureShader->setInt("selectTexture",numTex);
    _drawTextureShader->setVec2("moussePos",_moussePos);
    _scene->drawAsciiTex(_drawTextureShader);
}


void Viewer::makeTestForOneOrientation(int numEssai,QString orientation){


    // Set phong
    _lightShaders->setShader(2);
    _scene->setTypeShading(0);
    update();
    QImage screenshot1 = grabFramebuffer();
    screenshot1.save(QString("screenshots/Essai_%1_phong_%2_0.png").arg(numEssai).arg(orientation));

    _scene->setTypeShading(1);
    update();
    QImage screenshot2 = grabFramebuffer();
    screenshot2.save(QString("screenshots/Essai_%1_phong_%2_1.png").arg(numEssai).arg(orientation));

    // set computelight
     _lightShaders->setShader(1);
     update();
     QImage screenshot3 = grabFramebuffer();
     screenshot3.save(QString("screenshots/Essai_%1_slint_%2_1.png").arg(numEssai).arg(orientation));

     _scene->setTypeShading(0);
     update();
     QImage screenshot4 = grabFramebuffer();
     screenshot4.save(QString("screenshots/Essai_%1_slint_%2_0.png").arg(numEssai).arg(orientation));


}
