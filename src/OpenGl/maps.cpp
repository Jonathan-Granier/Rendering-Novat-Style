#include "maps.h"
#include "meshloader.h"
#include <iostream>
using namespace std;

Maps::Maps(shared_ptr<GenShaders> shaders):
    _gaussBlurFactor(3),
    _lightThreshold(M_PI/3.0)
{
    _width = 1024;
    _height = 1024;
    initialize(shaders);
}



void Maps::create(int width, int height,float ymin, float ymax){
    _width = width;
    _height = height;
    _ymin = ymin;
    _ymax = ymax;
    resize();
    _isGenerate = false;
    _factorIsChange = true;

}
void Maps::create(shared_ptr<Texture> heightMap,int width, int height,float ymin, float ymax){
    _heightMap = heightMap;
    _width = width;
    _height = height;
    _ymin = ymin;
    _ymax = ymax;
    resize();
    _isGenerate = true;
    _factorIsChange = false;
}


/*
void Maps::setNormalMap(vector<float> data){
    _normalMap = make_shared<LoadTexture>("normalMap", data,GL_RGBA32F,GL_RGBA, _width,_height);;
}
*/
void Maps::generateHeightMap(int widthViewport,int heightViewport,std::shared_ptr<Texture> refHeightMap){
    if(!_isGenerate && _factorIsChange)
    {
        _gaussBlurHMap->startGenerate();
        _gaussBlurHMap->generatorShader()->setInt("halfsize",_gaussBlurFactor);
        _gaussBlurHMap->generatorShader()->setInt("direction",0);
        refHeightMap->sendToShader(_gaussBlurHMap->generatorShader(),"img");
        _gaussBlurHMap->generate(widthViewport,heightViewport);


        _gaussBlurVMap->startGenerate();
        _gaussBlurVMap->generatorShader()->setInt("halfsize",_gaussBlurFactor);
        _gaussBlurVMap->generatorShader()->setInt("direction",1);
        _gaussBlurHMap->sendToShader(_gaussBlurVMap->generatorShader(),"img");
        _gaussBlurVMap->generate(widthViewport,heightViewport);

        _heightMap = _gaussBlurVMap;
        _heightMap->setMeshOffset(refHeightMap->meshOffset());
        generateNormalMap(widthViewport,heightViewport);
        generateSlantMap(widthViewport,heightViewport);
        _isGenerate = true;
        _factorIsChange = false;
    }
}


void Maps::generateEditHeightMap(int widthViewport,int heightViewport,std::shared_ptr<Texture> previousHeightMap,bool firstMap){

    _editHeightMap->startGenerate();
    _editHeightMap->generatorShader()->setBool("firstMap",firstMap);
    _heightMap->sendToShader(_editHeightMap->generatorShader(),"currentHeightMap");
    if(!firstMap)
        previousHeightMap->sendToShader(_editHeightMap->generatorShader(),"previousHeightMap");
    _editHeightMap->generate(widthViewport,heightViewport);
}


void Maps::generateNormalMap(int widthViewport,int heightViewport){

    //_normalMap = MeshLoader::normalFromHeightMap(_heightMap->getDataRED(),_width,_height,_heightMap->meshOffset());
    _normalMap->startGenerate();
    _normalMap->generatorShader()->setVec2("resolution",_width,_height);
    _normalMap->generatorShader()->setFloat("offset",_heightMap->meshOffset());
    _editHeightMap->sendToShader(_normalMap->generatorShader());
    _normalMap->generate(widthViewport,heightViewport);
}




void Maps::generateSlantMap(int widthViewport,int heightViewport)
{
    _slantMap->startGenerate();
    _slantMap->generatorShader()->setVec2("resolution",_width,_height);
    _slantMap->generatorShader()->setFloat("offset",_heightMap->meshOffset());
    _heightMap->sendToShader(_slantMap->generatorShader());
    _normalMap->sendToShader(_slantMap->generatorShader());
    _slantMap->generate(widthViewport,heightViewport);
}
/*
void Maps::generateCurvatureMap(int widthViewport,int heightViewport, int sigma)
{
    _curvatureMap->startGenerate();
    _curvatureMap->generatorShader()->setFloat("sigma",sigma);
    _normalMap->sendToShader(_curvatureMap->generatorShader());
    _curvatureMap->generate(widthViewport,heightViewport);

    _correctCurvatureMap->startGenerate();
    _normalMap->sendToShader(_correctCurvatureMap->generatorShader());
    _curvatureMap->sendToShader(_correctCurvatureMap->generatorShader());
    _correctCurvatureMap->generate(widthViewport,heightViewport);
}
*/
void Maps::generateShadeLightMap(int widthViewport, int heightViewport, glm::vec3 lightPos, float pitch, float yaw, bool none)
{
    _shadeLightMap->startGenerate();
    _shadeLightMap->generatorShader()->setVec3("lightPosition",lightPos);
    _shadeLightMap->generatorShader()->setFloat("yaw",yaw);
    _shadeLightMap->generatorShader()->setFloat("pitch",pitch);
    _shadeLightMap->generatorShader()->setInt("lightSelector",0);
    _shadeLightMap->generatorShader()->setFloat("threshold",_lightThreshold);
    _shadeLightMap->generatorShader()->setBool("none",none);
    _slantMap->sendToShader(_shadeLightMap->generatorShader());
    //_correctCurvatureMap->sendToShader(_lightMap->generatorShader());
    _shadeLightMap->generate(widthViewport,heightViewport);
}

void Maps::generateShadeLightMap(int widthViewport, int heightViewport, std::shared_ptr<LightTextures> previousShadeLightMap,float pitch, bool doMerge, bool none)
{
    _shadeLightMap->startGenerate();
    _shadeLightMap->generatorShader()->setFloat("pitch",pitch);
    _shadeLightMap->generatorShader()->setInt("lightSelector",1);
    _shadeLightMap->generatorShader()->setFloat("threshold",_lightThreshold);
    _shadeLightMap->generatorShader()->setBool("doMerge",doMerge);
    _shadeLightMap->generatorShader()->setBool("none",none);
    previousShadeLightMap->sendToShader(_shadeLightMap->generatorShader());
    _slantMap->sendToShader(_shadeLightMap->generatorShader());
    //_correctCurvatureMap->sendToShader(_lightMap->generatorShader());
    _shadeLightMap->generate(widthViewport,heightViewport);
}

void Maps::generateShadowLightMap(int widthViewport, int heightViewport, glm::vec3 lightPos, float pitch, float yaw)
{
    _shadowLightMap->startGenerate();
    _shadowLightMap->generatorShader()->setVec3("lightPosition",lightPos);
    _shadowLightMap->generatorShader()->setFloat("yaw",yaw);
    _shadowLightMap->generatorShader()->setFloat("pitch",pitch);
    _shadowLightMap->generatorShader()->setInt("lightSelector",0);
    _shadowLightMap->generatorShader()->setFloat("threshold",_lightThreshold);
    _slantMap->sendToShader(_shadowLightMap->generatorShader());
    //_correctCurvatureMap->sendToShader(_lightMap->generatorShader());
    _shadowLightMap->generate(widthViewport,heightViewport);
}

void Maps::generateShadowLightMap(int widthViewport, int heightViewport, std::shared_ptr<LightTextures> previousShadowLightMap,float pitch)
{
    _shadowLightMap->startGenerate();
    _shadowLightMap->generatorShader()->setFloat("pitch",pitch);
    _shadowLightMap->generatorShader()->setInt("lightSelector",1);
    _shadowLightMap->generatorShader()->setFloat("threshold",_lightThreshold);
    previousShadowLightMap->sendToShader(_shadowLightMap->generatorShader());
    _slantMap->sendToShader(_shadowLightMap->generatorShader());
    //_correctCurvatureMap->sendToShader(_lightMap->generatorShader());
    _shadowLightMap->generate(widthViewport,heightViewport);
}


void Maps::generateParallaxMap(int widthViewport, int heightViewport,glm::vec3 lightPos)
{
    _parallaxMap->startGenerate();
    _parallaxMap->generatorShader()->setFloat("ymin",_ymin);
    _parallaxMap->generatorShader()->setFloat("ymax",_ymax);
    _parallaxMap->generatorShader()->setFloat("step",_heightMap->meshOffset());
    _parallaxMap->generatorShader()->setVec2("resolution",_width,_height);
    _parallaxMap->generatorShader()->setVec3("lightPosition",lightPos);
    _heightMap->sendToShader(_parallaxMap->generatorShader());
    _shadowLightMap->sendToShader(_parallaxMap->generatorShader());
    _parallaxMap->generate(widthViewport,heightViewport);
}

void Maps::generateShadingMap(int widthViewport, int heightViewport, glm::mat4 mdvMat, glm::mat3 normalMat, glm::vec3 lightPosition, int typeShading, shared_ptr<Texture> previousShadingMap,bool firstMap, bool doMerge, int shadeSelector)
{
    _shadingMap->startGenerate();
    _shadingMap->generatorShader()->setMat4("mdvMat",mdvMat);
    _shadingMap->generatorShader()->setMat3("normalMat",normalMat);
    _shadingMap->generatorShader()->setVec3("lightPosition",lightPosition);
    _shadingMap->generatorShader()->setInt("typeShading",typeShading);
    _shadingMap->generatorShader()->setBool("firstMap",firstMap);
    _shadingMap->generatorShader()->setBool("doMerge",doMerge);
    _shadingMap->generatorShader()->setInt("shadeSelector",shadeSelector);
    _normalMap->sendToShader(_shadingMap->generatorShader());
    _shadeLightMap->sendToShader(_shadingMap->generatorShader());
    if(!firstMap)
        previousShadingMap->sendToShader(_shadingMap->generatorShader());
    _shadingMap->generate(widthViewport,heightViewport);
}

void Maps::drawHeightMap(shared_ptr<Shader> shader){
    shader->setFloat("ymin",_ymin);
    shader->setFloat("ymax",_ymax);
    _heightMap->draw(shader);
}
//TODO , max et min
void Maps::drawEditHeightMap(shared_ptr<Shader> shader){
    shader->setFloat("ymin",_ymin-_ymax);
    shader->setFloat("ymax",_ymax-_ymin);
    _editHeightMap->draw(shader);
}

void Maps::drawNormalMap(shared_ptr<Shader> shader){            _normalMap->draw(shader); }
void Maps::drawSlantMap(shared_ptr<Shader> shader){             _slantMap->draw(shader);}
void Maps::drawShadeLightMap(shared_ptr<Shader> shader){        _shadeLightMap->draw(shader);}
void Maps::drawShadowLightMap(shared_ptr<Shader> shader){       _shadowLightMap->draw(shader);}
void Maps::drawParallaxMap(std::shared_ptr<Shader> shader){     _parallaxMap->draw(shader);}
void Maps::drawShadingMap(std::shared_ptr<Shader> shader){      _shadingMap->draw(shader);}




void Maps::sendEditHeightMapToShader(std::shared_ptr<Shader> shader){       _editHeightMap->sendToShader(shader) ;}
void Maps::sendNormalMapToShader(std::shared_ptr<Shader> shader){           _normalMap->sendToShader(shader)     ;}
void Maps::sendShadeLightMapToShader(std::shared_ptr<Shader> shader){       _shadeLightMap->sendToShader(shader) ;}
void Maps::sendShadowLightMapToShader(std::shared_ptr<Shader> shader){      _shadowLightMap->sendToShader(shader);}
void Maps::sendParallaxMap(std::shared_ptr<Shader> shader){                 _parallaxMap->sendToShader(shader)   ;}
void Maps::sendShadingMap(std::shared_ptr<Shader> shader){                  _shadingMap->sendToShader(shader)    ;}




float Maps::getLightThreshold() const
{
    return _lightThreshold;
}
void Maps::setLightThreshold(float t)
{

    if(t < _MINLIGHTRESHOLD)
        _lightThreshold = 0;
    if(t > _MAXLIGHTTRESHOLD)
        _lightThreshold = _MAXLIGHTTRESHOLD;
    else
        _lightThreshold = t;
}

float Maps::getGaussBlurFactor() const
{
    return _gaussBlurFactor;
}

void Maps::setGaussBlurFactor(float g)
{
    if(g <= 0)
        _gaussBlurFactor = 0;
    else
        _gaussBlurFactor = g;
    _factorIsChange = true;
}

void Maps::reloadHeightMap()
{
    _isGenerate = false;
}

int Maps::getWidth() const
{
    return _width;
}

int Maps::getHeight() const
{
    return _height;
}



shared_ptr<Texture> Maps::getHeightMap(){
    return _heightMap;
}

std::shared_ptr<GeneratedTexture> Maps::getEditHeightMap() const
{
    return _editHeightMap;
}
std::shared_ptr<LightTextures> Maps::getShadeLightMap() const
{
    return _shadeLightMap;
}

std::shared_ptr<LightTextures> Maps::getShadowLightMap() const
{
    return _shadowLightMap;
}

std::shared_ptr<GeneratedTexture> Maps::getShadingMap() const
{
    return _shadingMap;
}

/************************************************
 *              Private Functions               *
 ************************************************/


void Maps::initialize(shared_ptr<GenShaders> shaders)
{

    _gaussBlurVMap      = make_shared<GeneratedTexture>("heightMap",_width,_height,shaders->gaussBlurShader);
    _gaussBlurHMap      = make_shared<GeneratedTexture>("heightMap",_width,_height,shaders->gaussBlurShader);
    _editHeightMap      = make_shared<GeneratedTexture>("editHeightMap",_width,_height,shaders->editHeightMapShader);
    _normalMap          = make_shared<GeneratedTexture>("normalMap",_width,_height,shaders->normalMapShader);
    _slantMap           = make_shared<GeneratedTexture>("slantMap",_width,_height,shaders->slantShader);
    _shadeLightMap      = make_shared<LightTextures>("shadeLightMap","shadeAnglesMap",_width,_height,shaders->shadeLightShader);
    _shadowLightMap     = make_shared<LightTextures>("shadowLightMap","shadowAnglesMap",_width,_height,shaders->shadowLightShader);
    _parallaxMap        = make_shared<GeneratedTexture>("parallaxMap",_width,_height,shaders->parallaxShader);
    _shadingMap         = make_shared<GeneratedTexture>("shadingMap",_width,_height,shaders->shadingShader);

    _gaussBlurVMap->initialize();
    _gaussBlurHMap->initialize();
    _editHeightMap->initialize();
    _normalMap->initialize();
    _slantMap->initialize();
    _shadeLightMap->initialize();
    _shadowLightMap->initialize();
    _parallaxMap->initialize();
    _shadingMap->initialize();
}





void Maps::resize()
{
    _gaussBlurVMap->resize(_width,_height);
    _gaussBlurHMap->resize(_width,_height);
    _editHeightMap->resize(_width,_height);
    _normalMap->resize(_width,_height);
    _slantMap->resize(_width,_height);
    _shadeLightMap->resize(_width,_height);
    _shadowLightMap->resize(_width,_height);
    _parallaxMap->resize(_width,_height);
    _shadingMap->resize(_width,_height);
}

