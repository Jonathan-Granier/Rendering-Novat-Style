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
    _yminEdit = _ymin;
    _ymaxEdit = _ymax;
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
    _yminEdit = _ymin;
    _ymaxEdit = _ymax;
    resize();
    _isGenerate = true;
    _factorIsChange = false;
}

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
    if(!firstMap){
        previousHeightMap->sendToShader(_editHeightMap->generatorShader(),"previousHeightMap");
        _ymaxEdit = 1000;
        _yminEdit = -1000;
        //TODO arbitrary , need to find a better solution (Without check all the values).
    }
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

void Maps::generateShadeLightMap(int widthViewport, int heightViewport, glm::vec3 lightPos, float pitch, float yaw, bool doEdit)
{
    _shadeLightMap->startGenerate();
    _shadeLightMap->generatorShader()->setVec3("lightPosition",lightPos);
    _shadeLightMap->generatorShader()->setFloat("yaw",yaw);
    _shadeLightMap->generatorShader()->setFloat("pitch",pitch);
    _shadeLightMap->generatorShader()->setInt("lightSelector",0);
    _shadeLightMap->generatorShader()->setFloat("threshold",_lightThreshold);
    _shadeLightMap->generatorShader()->setBool("doEdit",doEdit);
    _slantMap->sendToShader(_shadeLightMap->generatorShader());
    _shadeLightMap->generate(widthViewport,heightViewport);
}

void Maps::generateShadowLightMap(int widthViewport, int heightViewport, glm::vec3 lightPos, float pitch, float yaw, bool doEdit)
{
    _shadowLightMap->startGenerate();
    _shadowLightMap->generatorShader()->setVec3("lightPosition",lightPos);
    _shadowLightMap->generatorShader()->setFloat("yaw",yaw);
    _shadowLightMap->generatorShader()->setFloat("pitch",pitch);
    _shadowLightMap->generatorShader()->setInt("lightSelector",0);
    _shadowLightMap->generatorShader()->setFloat("threshold",_lightThreshold);
    _shadowLightMap->generatorShader()->setBool("doEdit",doEdit);
    _slantMap->sendToShader(_shadowLightMap->generatorShader());
    _shadowLightMap->generate(widthViewport,heightViewport);
}

void Maps::generateParallaxMap(int widthViewport, int heightViewport,glm::vec3 lightPos)
{
    _parallaxMap->startGenerate();
    _parallaxMap->generatorShader()->setFloat("ymin",_yminEdit);
    _parallaxMap->generatorShader()->setFloat("ymax",_ymaxEdit);
    _parallaxMap->generatorShader()->setFloat("step",_heightMap->meshOffset());
    _parallaxMap->generatorShader()->setVec2("resolution",_width,_height);
    _parallaxMap->generatorShader()->setVec3("lightPosition",lightPos);
    _editHeightMap->sendToShader(_parallaxMap->generatorShader(),"heightMap");
    _shadowLightMap->sendToShader(_parallaxMap->generatorShader());
    _parallaxMap->generate(widthViewport,heightViewport);
}

void Maps::generateMorphoErosionMap(int widthViewport, int heightViewport,bool doMorpho)
{
    _morphoErosionMap->startGenerate();
    _morphoErosionMap->generatorShader()->setVec2("resolution",_width,_height);
    _morphoErosionMap->generatorShader()->setInt("operator",0);
    _morphoDilationMap->generatorShader()->setBool("doMorpho",doMorpho);
    _parallaxMap->sendToShader(_morphoErosionMap->generatorShader(),"shadowMap");
    _morphoErosionMap->generate(widthViewport,heightViewport);
}

void Maps::generateMorphoDilationMap(int widthViewport, int heightViewport, bool doMorpho)
{
    _morphoDilationMap->startGenerate();
    _morphoDilationMap->generatorShader()->setVec2("resolution",_width,_height);
    _morphoErosionMap->generatorShader()->setInt("operator",1);
    _morphoErosionMap->generatorShader()->setBool("doMorpho",doMorpho);
    _morphoErosionMap->sendToShader(_morphoDilationMap->generatorShader(),"shadowMap");
    _morphoDilationMap->generate(widthViewport,heightViewport);
}



void Maps::generateMergeShadowMap(int widthViewport, int heightViewport, std::shared_ptr<Texture> previousShadowMap, bool firstMap)
{
    _mergeShadowMap->startGenerate();
    _morphoDilationMap->sendToShader(_mergeShadowMap->generatorShader(),"currentShadowMap");
    _mergeShadowMap->generatorShader()->setBool("firstMap",firstMap);
    if(!firstMap)
        previousShadowMap->sendToShader(_mergeShadowMap->generatorShader(),"previousShadowMap");
    _mergeShadowMap->generate(widthViewport,heightViewport);
}

void Maps::generateShadingMap(int widthViewport, int heightViewport, glm::mat4 mdvMat, glm::mat3 normalMat, glm::vec3 lightPosition, shared_ptr<Texture> previousShadingMap,bool firstMap, int shadeSelector)
{
    _shadingMap->startGenerate();
    _shadingMap->generatorShader()->setMat4("mdvMat",mdvMat);
    _shadingMap->generatorShader()->setMat3("normalMat",normalMat);
    _shadingMap->generatorShader()->setVec3("lightPosition",lightPosition);
    _shadingMap->generatorShader()->setBool("firstMap",firstMap);
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
    shader->setFloat("ymin",_yminEdit);
    shader->setFloat("ymax",_ymaxEdit);
    _editHeightMap->draw(shader);
}

void Maps::drawNormalMap(shared_ptr<Shader> shader){             _normalMap->draw(shader); }
void Maps::drawSlantMap(shared_ptr<Shader> shader){              _slantMap->draw(shader);}
void Maps::drawShadeLightMap(shared_ptr<Shader> shader){         _shadeLightMap->draw(shader);}
void Maps::drawShadowLightMap(shared_ptr<Shader> shader){        _shadowLightMap->draw(shader);}
void Maps::drawParallaxMap(std::shared_ptr<Shader> shader){      _parallaxMap->draw(shader);}
void Maps::drawMorphoErosionMap(std::shared_ptr<Shader> shader){ _morphoErosionMap->draw(shader);}
void Maps::drawMorphoDilationMap(std::shared_ptr<Shader> shader){_morphoDilationMap->draw(shader);}
void Maps::drawMergeShadowMap(std::shared_ptr<Shader> shader){   _mergeShadowMap->draw(shader);}
void Maps::drawShadingMap(std::shared_ptr<Shader> shader){       _shadingMap->draw(shader);}





void Maps::sendEditHeightMapToShader(std::shared_ptr<Shader> shader){       _editHeightMap->sendToShader(shader) ;}
void Maps::sendNormalMapToShader(std::shared_ptr<Shader> shader){           _normalMap->sendToShader(shader)     ;}
void Maps::sendShadeLightMapToShader(std::shared_ptr<Shader> shader){       _shadeLightMap->sendToShader(shader) ;}
void Maps::sendShadowLightMapToShader(std::shared_ptr<Shader> shader){      _shadowLightMap->sendToShader(shader);}
void Maps::sendParallaxMap(std::shared_ptr<Shader> shader){                 _parallaxMap->sendToShader(shader)   ;}

void Maps::sendMorphoErosionMap(std::shared_ptr<Shader> shader){            _morphoErosionMap->sendToShader(shader);}
void Maps::sendMorphoDilationMap(std::shared_ptr<Shader> shader){           _morphoDilationMap->sendToShader(shader);}
void Maps::sendMergeShadowMap(std::shared_ptr<Shader> shader){              _mergeShadowMap->sendToShader(shader);}
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
std::shared_ptr<GeneratedTexture> Maps::getShadeLightMap() const
{
    return _shadeLightMap;
}

std::shared_ptr<GeneratedTexture> Maps::getShadowLightMap() const
{
    return _shadowLightMap;
}

std::shared_ptr<GeneratedTexture> Maps::getShadingMap() const
{
    return _shadingMap;
}

std::shared_ptr<GeneratedTexture> Maps::getMorphoDilationMap() const
{
    return _morphoDilationMap;
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
    _shadeLightMap      = make_shared<GeneratedTexture>("shadeLightMap",_width,_height,shaders->shadeLightShader);
    _shadowLightMap     = make_shared<GeneratedTexture>("shadowLightMap",_width,_height,shaders->shadowLightShader);
    _parallaxMap        = make_shared<GeneratedTexture>("parallaxMap",_width,_height,shaders->parallaxShader);
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
    _parallaxMap->initialize();
    _morphoErosionMap->initialize();
    _morphoDilationMap->initialize();
    _mergeShadowMap->initialize();
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
    _morphoErosionMap->resize(_width,_height);
    _morphoDilationMap->resize(_width,_height);
    _mergeShadowMap->resize(_width,_height);
    _shadingMap->resize(_width,_height);

}

