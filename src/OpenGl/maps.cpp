#include "maps.h"
#include "meshloader.h"
#include <iostream>
using namespace std;

Maps::Maps(shared_ptr<GenShaders> shaders, shared_ptr<Texture> heightMap, float ymin, float ymax):
    _gaussBlurFactor(3),
    _lightThreshold(M_PI/3.0)
{
    _heightMap = heightMap;
    _width = heightMap->getWidth();
    _height = heightMap->getHeight();
    _ymin = ymin;
    _ymax = ymax;

    initialize(shaders);
}




Maps::Maps(shared_ptr<GenShaders> shaders, int width, int height,float ymin, float ymax):
    _gaussBlurFactor(3),
    _lightThreshold(M_PI/3.0)
{
    _width = width;
    _height = height;
    _ymin = ymin;
    _ymax = ymax;
    _isGenerate = false;
    _factorIsChange = true;
    initialize(shaders);
}



void Maps::setNormalMap(vector<float> data){
    _normalMap = make_shared<LoadTexture>("normalMap", data,GL_RGBA32F,GL_RGBA, _width,_height);;
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
        generateNormalMap();
        generateSlantMap(widthViewport,heightViewport);
        _isGenerate = true;
        _factorIsChange = false;
    }
}


void Maps::generateSlantMap(int widthViewport,int heightViewport)
{
    _slantMap->startGenerate();
    _slantMap->generatorShader()->setVec2("resolution",_width,_height);
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
void Maps::generateLightMap(int widthViewport, int heightViewport, glm::vec3 lightPos, float pitch, float yaw)
{
    _lightMap->startGenerate();
    _lightMap->generatorShader()->setVec3("lightPosition",lightPos);
    _lightMap->generatorShader()->setFloat("yaw",yaw);
    _lightMap->generatorShader()->setFloat("pitch",pitch);
    _lightMap->generatorShader()->setInt("lightSelector",0);
    _lightMap->generatorShader()->setFloat("threshold",_lightThreshold);
    _slantMap->sendToShader(_lightMap->generatorShader());
    //_correctCurvatureMap->sendToShader(_lightMap->generatorShader());
    _lightMap->generate(widthViewport,heightViewport);
}

void Maps::generateLightMap(int widthViewport, int heightViewport, std::shared_ptr<Texture> previousLightMap,float pitch)
{
    _lightMap->startGenerate();
    //_lightMap->generatorShader()->setVec3("lightPosition",lightPos);
    _lightMap->generatorShader()->setFloat("pitch",pitch);
    _lightMap->generatorShader()->setInt("lightSelector",1);
    _lightMap->generatorShader()->setFloat("threshold",_lightThreshold);
    previousLightMap->sendToShader(_lightMap->generatorShader());
    _slantMap->sendToShader(_lightMap->generatorShader());
    //_correctCurvatureMap->sendToShader(_lightMap->generatorShader());
    _lightMap->generate(widthViewport,heightViewport);
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
    _lightMap->sendToShader(_parallaxMap->generatorShader());
    _parallaxMap->generate(widthViewport,heightViewport);
}

void Maps::drawHeightMap(shared_ptr<Shader> shader){
    shader->setFloat("ymin",_ymin);
    shader->setFloat("ymax",_ymax);
    _heightMap->draw(shader);
}

void Maps::drawNormalMap(shared_ptr<Shader> shader){            _normalMap->draw(shader); }
void Maps::drawSlantMap(shared_ptr<Shader> shader){             _slantMap->draw(shader);}
//void Maps::drawCurvatureMap(shared_ptr<Shader> shader){         _curvatureMap->draw(shader);}
//void Maps::drawCorrectCurvatureMap(shared_ptr<Shader> shader){  _correctCurvatureMap->draw(shader);}
void Maps::drawLightMap(shared_ptr<Shader> shader){             _lightMap->draw(shader);}
void Maps::drawParallaxMap(std::shared_ptr<Shader> shader){     _parallaxMap->draw(shader);}
/*
void Maps::drawMesh()
{
    _mesh->Draw();
}
*/
/*
void Maps::sendHeightMapToShader(std::shared_ptr<Shader> shader){           _heightMap->sendToShader(shader); }
void Maps::sendNormalMapToShader(std::shared_ptr<Shader> shader){           _normalMap->sendToShader(shader); }
void Maps::sendSlantMapToShader(std::shared_ptr<Shader> shader){            _slantMap->sendToShader(shader); }
*/
//void Maps::sendCurvatureMapToShader(std::shared_ptr<Shader> shader){        _curvatureMap->sendToShader(shader);}
//void Maps::sendCorrecCurvatureMapToShader(std::shared_ptr<Shader> shader){  _correctCurvatureMap->sendToShader(shader);}
void Maps::sendLightMapToShader(std::shared_ptr<Shader> shader){            _lightMap->sendToShader(shader);}
void Maps::sendParallaxMap(std::shared_ptr<Shader> shader){                 _parallaxMap->sendToShader(shader);}


/*
void Maps::setHeightMap(std::shared_ptr<Texture> heightMap)
{
    _heightMap = heightMap;
    _width = heightMap->getWidth();
    _height = heightMap->getHeight();
    resize();
    initializeDataMaps();
}
*/


shared_ptr<Texture> Maps::getHeightMap(){
    return _heightMap;
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

std::shared_ptr<GeneratedTexture> Maps::getLightMap() const
{
    return _lightMap;
}
/*
std::shared_ptr<Mesh> Maps::getMesh() const
{
    return _mesh;
}
*/
/************************************************
 *              Private Functions               *
 ************************************************/


void Maps::initialize(shared_ptr<GenShaders> shaders)
{
    _gaussBlurVMap = make_shared<GeneratedTexture>("heightMap",_width,_height,shaders->gaussBlurShader);
    _gaussBlurHMap = make_shared<GeneratedTexture>("heightMap",_width,_height,shaders->gaussBlurShader);

    _slantMap = make_shared<GeneratedTexture>("slantMap",_width,_height,shaders->slantShader);
    //_curvatureMap = make_shared<GeneratedTexture>("curvatureMap",_width,_height,shaders->curvatureShader);
    //_correctCurvatureMap = make_shared<GeneratedTexture>("curvatureMap",_width,_height,shaders->correctCurvatureShader);
    _lightMap     = make_shared<LightTextures>("lightMap",_width,_height,shaders->generateLightShader);
    _parallaxMap  = make_shared<GeneratedTexture>("parallaxMap",_width,_height,shaders->parallaxShader);

    _gaussBlurVMap->initialize();
    _gaussBlurHMap->initialize();

    _slantMap->initialize();
    //_curvatureMap->initialize();
    //_correctCurvatureMap->initialize();
    _lightMap->initialize();
    _parallaxMap->initialize();
}



void Maps::generateNormalMap(){
   //_mesh = MeshLoader::vertexFromHeightMap(_heightMap->getDataRED(),_width,_height,_heightMap->meshOffset());
    _normalMap = MeshLoader::normalFromHeightMap(_heightMap->getDataRED(),_width,_height,_heightMap->meshOffset());
    /*
    vector<float> dataNormalMap = //_mesh->getNormalMapZUp();
    _normalMap    = make_shared<LoadTexture>("normalMap", dataNormalMap,GL_RGBA32F,GL_RGBA, _width,_height);
    */
}


/*
void Maps::resize()
{
    _gaussBlurVMap->resize(_width,_height);
    _gaussBlurHMap->resize(_width,_height);
    _slantMap->resize(_width,_height);
    //_curvatureMap->resize(_width,_height);
    //_correctCurvatureMap->resize(_width,_height);
    _lightMap->resize(_width,_height);
    _parallaxMap->resize(_width,_height);
}
*/
