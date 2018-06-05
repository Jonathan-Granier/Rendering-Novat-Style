#include "viewer.h"
#include <iostream>


#include <QStringList>
#include <QString>
#include "src/OpenGl/meshloader.h"
/*
// TODO DELETE ET trouve une solution
#define GLM_ENABLE_EXPERIMENTAL

#include "glm/gtx/string_cast.hpp"
*/

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
    glClearColor(0.345f, 0.647f, 0.827f, 1.0f); //  Bleu denim
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
    case MORPHOEROSION :
        _drawTextureShader->use();
        initDrawTexture(9);
        _scene->drawMorphoErosionMap(_drawTextureShader);
        _drawTextureShader->disable();
        break;
    case MORPHODILATION :
        _drawTextureShader->use();
        initDrawTexture(10);
        _scene->drawMorphoDilationMap(_drawTextureShader);
        _drawTextureShader->disable();
        break;
    case MERGESHADOW :
        _drawTextureShader->use();
        initDrawTexture(11);
        _scene->drawMergeShadowMap(_drawTextureShader);
        _drawTextureShader->disable();
        break;
    case SHADING :
        _drawTextureShader->use();
        initDrawTexture(12);
        _scene->drawShadingMap(_drawTextureShader);
        _drawTextureShader->disable();
         break;
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
}    //_shadowMap = make_shared<ShadowMap>("depthMap",1024,1024);
//_shadowMap->initialize();

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
    _lightShaders->reload();
    //_shadowMap->reloadShader();
    _drawTextureShader->reload();
    _scene->reloadGenerateTexturesShader();
    cout << "Reload shader done " << endl;
    update();

}




void Viewer::printCamAndLight(){
   /* cout << "proj mat : " << glm::to_string(_cam->projMatrix()) << endl;
    cout << "mdv mat : " << glm::to_string(_cam->mdvMatrix()) << endl;
    cout << "normal mat : " << glm::to_string(_cam ->normalMatrix()) << endl;
    cout << " light's angles : yaw : " << _light->yaw() << " pitch : " << _light->pitch() << endl;
  */
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
        case HEIGHTMAP:       _drawMode = EDITHEIGHTMAP  ; break;
        case EDITHEIGHTMAP:   _drawMode = NORMALMAP      ; break;
        case NORMALMAP:       _drawMode = SLANTMAP       ; break;
        case SLANTMAP :       _drawMode = SHADELIGHTMAP  ; break;
        case SHADELIGHTMAP :  _drawMode = SHADEANGLESMAP ; break;
        case SHADEANGLESMAP:  _drawMode = SHADOWLIGHTMAP ; break;
        case SHADOWLIGHTMAP:  _drawMode = SHADOWANGLESMAP; break;
        case SHADOWANGLESMAP: _drawMode = PARALLAX       ; break;
        case PARALLAX :       _drawMode = MORPHOEROSION  ; break;
        case MORPHOEROSION :  _drawMode = MORPHODILATION ; break;
        case MORPHODILATION :  _drawMode = MERGESHADOW   ; break;
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
        case 5 :  _drawMode = SHADEANGLESMAP ; break;
        case 6 :  _drawMode = SHADOWLIGHTMAP ; break;
        case 7 :  _drawMode = SHADOWANGLESMAP; break;
        case 8 :  _drawMode = PARALLAX       ; break;
        case 9:  _drawMode = MORPHOEROSION  ; break;
        case 10:  _drawMode = MORPHODILATION ; break;
        case 11:  _drawMode = MERGESHADOW    ; break;
        case 12:  _drawMode = SHADING        ; break;
        case 13 :  _drawMode = CLASSICAL      ; break;
        default:  _drawMode = CLASSICAL      ; break;
    }
    update();
}

void Viewer::previousDrawMode(){
    switch(_drawMode){
        case HEIGHTMAP:         _drawMode = CLASSICAL      ; break;
        case EDITHEIGHTMAP:     _drawMode = HEIGHTMAP      ; break;
        case NORMALMAP:         _drawMode = EDITHEIGHTMAP  ; break;
        case SLANTMAP :         _drawMode = NORMALMAP      ; break;
        case SHADELIGHTMAP :    _drawMode = SLANTMAP       ; break;
        case SHADEANGLESMAP:    _drawMode = SHADELIGHTMAP  ; break;
        case SHADOWLIGHTMAP:    _drawMode = SHADEANGLESMAP ; break;
        case SHADOWANGLESMAP:   _drawMode = SHADOWLIGHTMAP ; break;
        case PARALLAX :         _drawMode = SHADOWANGLESMAP; break;
        case MORPHOEROSION :    _drawMode = PARALLAX       ; break;
        case MORPHODILATION :   _drawMode = MORPHOEROSION  ; break;
        case MERGESHADOW :      _drawMode = MORPHODILATION ; break;
        case SHADING :          _drawMode = MERGESHADOW    ; break;
        case CLASSICAL:         _drawMode = SHADING        ; break;
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
void Viewer::selectCurrentMaps(int id){
    _scene->selectCurrentMaps(id);
    update();
}
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
        case MORPHOEROSION :
            stringDrawMode = "Morpho Erosion Map";
        break;
        case MORPHODILATION :
            stringDrawMode = "Morpho Dilation Map";
        break;
        case MERGESHADOW :
            stringDrawMode = "Merge Shadow Map";
        break;
        case SHADING :
            stringDrawMode = "Shading Map";
        break;
        case CLASSICAL:
            stringDrawMode = "World";
        break;
    }
    return stringDrawMode;
}



string Viewer::getCurrentShader()
{

    return _lightShaders->name();
}



void Viewer::setGaussBlurFactor(unsigned int id, float g)
{
    _scene->setGaussBlurFactor(id,g);
    update();
}

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



void Viewer::setShadeSelector(int s){
    _scene->setShadeSelector(s);
    update();
}
// TODO Armoniser les noms

void Viewer::shadowEnabled(int b)
{
    _scene->setDoShadow(b);
    update();
}

void Viewer::shadowEnabledMorpho(int b)
{
    _scene->setDoShadowMorpo(b);
    update();
}

void Viewer::shadowEnabledLightDir(int b)
{
    _scene->setDoEditShadowLightDir(b);
    update();
}

void Viewer::shadeEnabledLightDir(int b)
{
    _scene->setDoEditShadeLightDir(b);
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



void Viewer::makeATest(int numTest){
    // Compute light :
    // Normal
    // Normal + ombre porté
    // Normal + color
    // Normal + color + ombre porté
    setShadeSelector(3);
    setColorSelector(0);
    shadowEnabled(false);

    takeScreenShot(QString("screenshots/NovatRDV/%1_high_ourMethode.png").arg(numTest));
    shadowEnabled(true);
    takeScreenShot(QString("screenshots/NovatRDV/%1_high_ourMethode_portée.png").arg(numTest));
    setColorSelector(1);
    takeScreenShot(QString("screenshots/NovatRDV/%1_high_ourMethode_portée_color_1.png").arg(numTest));
    setColorSelector(2);
    takeScreenShot(QString("screenshots/NovatRDV/%1_high_ourMethode_portée_color_2.png").arg(numTest));
    setColorSelector(3);
    takeScreenShot(QString("screenshots/NovatRDV/%1_high_ourMethode_portée_color_3.png").arg(numTest));
    // Lambercien

    nextShader();
    setColorSelector(0);
    shadowEnabled(false);
    shadowEnabledLightDir(false);
    takeScreenShot(QString("screenshots/NovatRDV/%1_high_lambercien.png").arg(numTest));
    shadowEnabled(true);
    takeScreenShot(QString("screenshots/NovatRDV/%1_high_lambercien_portée.png").arg(numTest));
    setColorSelector(1);
    takeScreenShot(QString("screenshots/NovatRDV/%1_high_lambercien_portée_color_1.png").arg(numTest));
    setColorSelector(2);
    takeScreenShot(QString("screenshots/NovatRDV/%1_high_lambercien_portée_color_2.png").arg(numTest));
    setColorSelector(3);
    takeScreenShot(QString("screenshots/NovatRDV/%1_high_lambercien_portée_color_3.png").arg(numTest));
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


void Viewer::takeScreenShot(QString name){

    update();
    QImage screenshot = grabFramebuffer();
    screenshot.save(name);
    cout << "screenshot save at " << name.toStdString() << endl;

}
