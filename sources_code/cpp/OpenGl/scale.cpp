#include "scale.h"
#include "meshloader.h"
#include <iostream>
using namespace std;

Scale::Scale(shared_ptr<GenShaders> shaders, std::shared_ptr<ViewportSize> viewportSize):
    _gaussBlurFactor(3),
    _lightThreshold(M_PI/3.0)
{
    _width = 1024;
    _height = 1024;
    _viewportSize = viewportSize;
    initialize(shaders);
}



void Scale::create(int width, int height,float ymin, float ymax){
    _width = width;
    _height = height;
    _ymin = ymin;
    _ymax = ymax;
    _yminEdit = _ymin;
    _ymaxEdit = _ymax;
    resize();
}
void Scale::create(shared_ptr<Texture> heightMap,int width, int height,float ymin, float ymax){
    _heightMap = heightMap;
    _width = width;
    _height = height;
    _ymin = ymin;
    _ymax = ymax;
    _yminEdit = _ymin;
    _ymaxEdit = _ymax;
    resize();
}

void Scale::generateHeightMap(std::shared_ptr<Texture> refHeightMap){
    _gaussBlurHMap->startGenerate();
    _gaussBlurHMap->getGeneratorShader()->setInt("halfsize",_gaussBlurFactor);
    _gaussBlurHMap->getGeneratorShader()->setInt("direction",0);
    refHeightMap->sendToShader(_gaussBlurHMap->getGeneratorShader(),"img");
    _gaussBlurHMap->generate(_viewportSize->width,_viewportSize->height);

    _gaussBlurVMap->startGenerate();
    _gaussBlurVMap->getGeneratorShader()->setInt("halfsize",_gaussBlurFactor);
    _gaussBlurVMap->getGeneratorShader()->setInt("direction",1);
    _gaussBlurHMap->sendToShader(_gaussBlurVMap->getGeneratorShader(),"img");
    _gaussBlurVMap->generate(_viewportSize->width,_viewportSize->height);

    _heightMap = _gaussBlurVMap;
    _heightMap->setHeightMapOffset(refHeightMap->getHeightMapOffset());
}


void Scale::generateEditHeightMap(std::shared_ptr<Texture> nextHeightMap, bool lastMap){

    _editHeightMap->startGenerate();
    _editHeightMap->getGeneratorShader()->setBool("lastMap",lastMap);
    _heightMap->sendToShader(_editHeightMap->getGeneratorShader(),"currentHeightMap");
    if(!lastMap){
        nextHeightMap->sendToShader(_editHeightMap->getGeneratorShader(),"nextHeightMap");
        //Arbitrary , need to find a better solution (Without check all the values).
        _ymaxEdit = 1000;
        _yminEdit = -1000;

    }
    _editHeightMap->generate(_viewportSize->width,_viewportSize->height);
}


void Scale::generateNormalMap(){
    _normalMap->startGenerate();
    _normalMap->getGeneratorShader()->setVec2("resolution",_width,_height);
    _normalMap->getGeneratorShader()->setFloat("offset",_heightMap->getHeightMapOffset());
    _editHeightMap->sendToShader(_normalMap->getGeneratorShader());
    _normalMap->generate(_viewportSize->width,_viewportSize->height);
}




void Scale::generateSlantMap()
{
    _slantMap->startGenerate();
    _normalMap->sendToShader(_slantMap->getGeneratorShader());
    _slantMap->generate(_viewportSize->width,_viewportSize->height);
}

void Scale::generateShadeLightMap(glm::vec3 lightDir, float pitch, float yaw, bool doEdit)
{
    _shadeLightMap->startGenerate();
    _shadeLightMap->getGeneratorShader()->setVec3("lightDirection",lightDir);
    _shadeLightMap->getGeneratorShader()->setFloat("yaw",yaw);
    _shadeLightMap->getGeneratorShader()->setFloat("pitch",pitch);
    _shadeLightMap->getGeneratorShader()->setFloat("threshold",_lightThreshold);
    _shadeLightMap->getGeneratorShader()->setBool("doEdit",doEdit);
    _slantMap->sendToShader(_shadeLightMap->getGeneratorShader());
    _shadeLightMap->generate(_viewportSize->width,_viewportSize->height);
}

void Scale::generateShadowLightMap(glm::vec3 lightDir, float pitch, float yaw, bool doEdit)
{
    _shadowLightMap->startGenerate();
    _shadowLightMap->getGeneratorShader()->setVec3("lightDirection",lightDir);
    _shadowLightMap->getGeneratorShader()->setFloat("yaw",yaw);
    _shadowLightMap->getGeneratorShader()->setFloat("pitch",pitch);
    _shadowLightMap->getGeneratorShader()->setFloat("threshold",_lightThreshold);
    _shadowLightMap->getGeneratorShader()->setBool("doEdit",doEdit);
    _slantMap->sendToShader(_shadowLightMap->getGeneratorShader());
    _shadowLightMap->generate(_viewportSize->width,_viewportSize->height);
}

void Scale::generateShadowMap()
{
    _shadowMap->startGenerate();
    _shadowMap->getGeneratorShader()->setFloat("ymin",_yminEdit);
    _shadowMap->getGeneratorShader()->setFloat("ymax",_ymaxEdit);
    _shadowMap->getGeneratorShader()->setFloat("step",_heightMap->getHeightMapOffset());
    _shadowMap->getGeneratorShader()->setVec2("resolution",_width,_height);
    _editHeightMap->sendToShader(_shadowMap->getGeneratorShader(),"heightMap");
    _shadowLightMap->sendToShader(_shadowMap->getGeneratorShader());
    _shadowMap->generate(_viewportSize->width,_viewportSize->height);
}


void Scale::generateMorphoDilationMap(bool doMorpho)
{
    _morphoDilationMap->startGenerate();
    _morphoDilationMap->getGeneratorShader()->setInt("operator",1);
    _morphoDilationMap->getGeneratorShader()->setBool("doMorpho",doMorpho);
    _shadowMap->sendToShader(_morphoDilationMap->getGeneratorShader(),"shadowMap");
    _morphoDilationMap->generate(_viewportSize->width,_viewportSize->height);
}


void Scale::generateMorphoErosionMap(bool doMorpho)
{
    _morphoErosionMap->startGenerate();
    _morphoErosionMap->getGeneratorShader()->setInt("operator",0);
    _morphoErosionMap->getGeneratorShader()->setBool("doMorpho",doMorpho);
    _morphoDilationMap->sendToShader(_morphoErosionMap->getGeneratorShader(),"shadowMap");
    _morphoErosionMap->generate(_viewportSize->width,_viewportSize->height);
}




void Scale::generateMergeShadowMap(std::shared_ptr<Texture> previousShadowMap, bool lastMap)
{
    _mergeShadowMap->startGenerate();
    _morphoErosionMap->sendToShader(_mergeShadowMap->getGeneratorShader(),"currentShadowMap");
    _mergeShadowMap->getGeneratorShader()->setBool("firstMap",lastMap);
    if(!lastMap)
        previousShadowMap->sendToShader(_mergeShadowMap->getGeneratorShader(),"previousShadowMap");
    _mergeShadowMap->generate(_viewportSize->width,_viewportSize->height);
}

void Scale::generateShadingMap(glm::mat4 mdvMat, glm::mat3 normalMat, shared_ptr<Texture> previousShadingMap, bool firstMap, int shadeSelector)
{
    _shadingMap->startGenerate();
    _shadingMap->getGeneratorShader()->setMat4("mdvMat",mdvMat);
    _shadingMap->getGeneratorShader()->setMat3("normalMat",normalMat);
    _shadingMap->getGeneratorShader()->setBool("firstMap",firstMap);
    _shadingMap->getGeneratorShader()->setInt("shadeSelector",shadeSelector);
    _normalMap->sendToShader(_shadingMap->getGeneratorShader());
    _shadeLightMap->sendToShader(_shadingMap->getGeneratorShader());
    if(!firstMap)
        previousShadingMap->sendToShader(_shadingMap->getGeneratorShader());
    _shadingMap->generate(_viewportSize->width,_viewportSize->height);
}

void Scale::drawHeightMap(shared_ptr<Shader> shader){
    shader->setFloat("ymin",_ymin);
    shader->setFloat("ymax",_ymax);
    _heightMap->draw(shader);
}

void Scale::drawEditHeightMap(shared_ptr<Shader> shader){
    shader->setFloat("ymin",_yminEdit);
    shader->setFloat("ymax",_ymaxEdit);
    _editHeightMap->draw(shader);
}

void Scale::drawNormalMap(shared_ptr<Shader> shader){             _normalMap->draw(shader); }
void Scale::drawSlantMap(shared_ptr<Shader> shader){              _slantMap->draw(shader);}
void Scale::drawShadeLightMap(shared_ptr<Shader> shader){         _shadeLightMap->draw(shader);}
void Scale::drawShadowLightMap(shared_ptr<Shader> shader){        _shadowLightMap->draw(shader);}
void Scale::drawShadowMap(std::shared_ptr<Shader> shader){        _shadowMap->draw(shader);}
void Scale::drawMorphoDilationMap(std::shared_ptr<Shader> shader){_morphoDilationMap->draw(shader);}
void Scale::drawMorphoErosionMap(std::shared_ptr<Shader> shader){ _morphoErosionMap->draw(shader);}
void Scale::drawMergeShadowMap(std::shared_ptr<Shader> shader){   _mergeShadowMap->draw(shader);}
void Scale::drawShadingMap(std::shared_ptr<Shader> shader){       _shadingMap->draw(shader);}


void Scale::sendHeightMapToShader(std::shared_ptr<Shader> shader){           _heightMap->sendToShader(shader)        ;}
void Scale::sendEditHeightMapToShader(std::shared_ptr<Shader> shader){       _editHeightMap->sendToShader(shader)    ;}
void Scale::sendNormalMapToShader(std::shared_ptr<Shader> shader){           _normalMap->sendToShader(shader)        ;}
void Scale::sendSlantMapToShader(std::shared_ptr<Shader> shader){            _slantMap->sendToShader(shader)         ;}
void Scale::sendShadeLightMapToShader(std::shared_ptr<Shader> shader){       _shadeLightMap->sendToShader(shader)    ;}
void Scale::sendShadowLightMapToShader(std::shared_ptr<Shader> shader){      _shadowLightMap->sendToShader(shader)   ;}
void Scale::sendShadowMap(std::shared_ptr<Shader> shader){                   _shadowMap->sendToShader(shader)      ;}
void Scale::sendMorphoDilationMap(std::shared_ptr<Shader> shader){           _morphoDilationMap->sendToShader(shader);}
void Scale::sendMorphoErosionMap(std::shared_ptr<Shader> shader){            _morphoErosionMap->sendToShader(shader) ;}
void Scale::sendMergeShadowMap(std::shared_ptr<Shader> shader){              _mergeShadowMap->sendToShader(shader)   ;}
void Scale::sendShadingMap(std::shared_ptr<Shader> shader){                  _shadingMap->sendToShader(shader)       ;}


void Scale::setLightThreshold(float t)
{

    if(t < _MINLIGHTRESHOLD)
        _lightThreshold = _MINLIGHTRESHOLD;
    if(t > _MAXLIGHTTRESHOLD)
        _lightThreshold = _MAXLIGHTTRESHOLD;
    else
        _lightThreshold = t;
}

void Scale::setGaussBlurFactor(int g)
{
    if(g <= 0)
        _gaussBlurFactor = 0;
    else
        _gaussBlurFactor = g;
}


int Scale::getWidth() const
{
    return _width;
}

int Scale::getHeight() const
{
    return _height;
}



shared_ptr<Texture> Scale::getHeightMap(){
    return _heightMap;
}


std::shared_ptr<Texture> Scale::getShadingMap() const
{
    return _shadingMap;
}



std::shared_ptr<Texture> Scale::getMorphoErosionMap() const
{
    return _morphoErosionMap;
}

/************************************************
 *              Private Functions               *
 ************************************************/


void Scale::initialize(shared_ptr<GenShaders> shaders)
{

    _gaussBlurVMap      = make_shared<GeneratedTexture>("heightMap",_width,_height,shaders->gaussBlurShader);
    _gaussBlurHMap      = make_shared<GeneratedTexture>("heightMap",_width,_height,shaders->gaussBlurShader);
    _editHeightMap      = make_shared<GeneratedTexture>("editHeightMap",_width,_height,shaders->editHeightMapShader);
    _normalMap          = make_shared<GeneratedTexture>("normalMap",_width,_height,shaders->normalMapShader);
    _slantMap           = make_shared<GeneratedTexture>("slantMap",_width,_height,shaders->slantShader);
    _shadeLightMap      = make_shared<GeneratedTexture>("shadeLightMap",_width,_height,shaders->shadeLightShader);
    _shadowLightMap     = make_shared<GeneratedTexture>("shadowLightMap",_width,_height,shaders->shadowLightShader);
    _shadowMap          = make_shared<GeneratedTexture>("shadowMap",_width,_height,shaders->shadowShader);
    _morphoErosionMap   = make_shared<GeneratedTexture>("morphoErosionMap",_width,_height,shaders->morphoShader);
    _morphoDilationMap  = make_shared<GeneratedTexture>("morphoDilationMap",_width,_height,shaders->morphoShader);
    _mergeShadowMap     = make_shared<GeneratedTexture>("mergeShadowMap",_width,_height,shaders->mergeShadowShader);
    _shadingMap         = make_shared<GeneratedTexture>("shadingMap",_width,_height,shaders->shadingShader);

    _gaussBlurVMap->initialize();
    _gaussBlurHMap->initialize();
    _editHeightMap->initialize();
    _normalMap->initialize();
    _slantMap->initialize();
    _shadeLightMap->initialize();
    _shadowLightMap->initialize();
    _shadowMap->initialize();
    _morphoErosionMap->initialize();
    _morphoDilationMap->initialize();
    _mergeShadowMap->initialize();
    _shadingMap->initialize();
}





void Scale::resize()
{
    _gaussBlurVMap->resize(_width,_height);
    _gaussBlurHMap->resize(_width,_height);
    _editHeightMap->resize(_width,_height);
    _normalMap->resize(_width,_height);
    _slantMap->resize(_width,_height);
    _shadeLightMap->resize(_width,_height);
    _shadowLightMap->resize(_width,_height);
    _shadowMap->resize(_width,_height);
    _morphoErosionMap->resize(_width,_height);
    _morphoDilationMap->resize(_width,_height);
    _mergeShadowMap->resize(_width,_height);
    _shadingMap->resize(_width,_height);

}
