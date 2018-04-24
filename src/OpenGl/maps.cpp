#include "maps.h"
#include "meshloader.h"
#include <iostream>
using namespace std;

Maps::Maps(shared_ptr<GenShaders> shaders, shared_ptr<Texture> heightMap, string name)
{
    _heightMap = heightMap;
    _width = heightMap->getWidth();
    _height = heightMap->getHeight();
    _name = name;
    initialize(shaders);
    initializeDataMaps();
}




Maps::Maps(shared_ptr<GenShaders> shaders, int width, int height,string name)
{
     _width = width;
     _height = height;
     _name = name;
    initialize(shaders);
}

void Maps::printName(){
    cout << _name << endl;
}


void Maps::generateSlantMap(int widthViewport,int heightViewport)
{
    _slantMap->startGenerate();
    _slantMap->generatorShader()->setVec2("resolution",_mesh->getWidth(),_mesh->getHeight());
    _heightMap->sendToShader(_slantMap->generatorShader());
    _normalMap->sendToShader(_slantMap->generatorShader());
    _slantMap->generate(widthViewport,heightViewport);
}

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

void Maps::generateLightMap(int widthViewport,int heightViewport,glm::vec3 lightPos, float yaw, float pitch, float lightThreshold, int lightSelector)
{
    _lightMap->startGenerate();
    _lightMap->generatorShader()->setVec3("lightPosition",lightPos);
    _lightMap->generatorShader()->setFloat("yaw",yaw);
    _lightMap->generatorShader()->setFloat("pitch",pitch);
    _lightMap->generatorShader()->setInt("lightSelector",lightSelector);
    _lightMap->generatorShader()->setFloat("threshold",lightThreshold);
    _slantMap->sendToShader(_lightMap->generatorShader());
    _correctCurvatureMap->sendToShader(_lightMap->generatorShader());
    _lightMap->generate(widthViewport,heightViewport);
}

void Maps::generateParallaxMap(int widthViewport, int heightViewport,glm::vec3 lightPos)
{
    _parallaxMap->startGenerate();
    _parallaxMap->generatorShader()->setFloat("ymin",_mesh->getYmin());
    _parallaxMap->generatorShader()->setFloat("ymax",_mesh->getYmax());
    _parallaxMap->generatorShader()->setFloat("step",_heightMap->meshOffset());
    _parallaxMap->generatorShader()->setVec2("resolution",_mesh->getWidth(),_mesh->getHeight());
    _parallaxMap->generatorShader()->setVec3("lightPosition",lightPos);
    _heightMap->sendToShader(_parallaxMap->generatorShader());
    _lightMap->sendToShader(_parallaxMap->generatorShader());
    _parallaxMap->generate(widthViewport,heightViewport);
}

void Maps::drawHeightMap(shared_ptr<Shader> shader){
    shader->setFloat("ymin",_mesh->getYmin());
    shader->setFloat("ymax",_mesh->getYmax());
    _heightMap->draw(shader);
}

void Maps::drawNormalMap(shared_ptr<Shader> shader){            _normalMap->draw(shader); }
void Maps::drawSlantMap(shared_ptr<Shader> shader){             _slantMap->draw(shader);}
void Maps::drawCurvatureMap(shared_ptr<Shader> shader){         _curvatureMap->draw(shader);}
void Maps::drawCorrectCurvatureMap(shared_ptr<Shader> shader){  _correctCurvatureMap->draw(shader);}
void Maps::drawLightMap(shared_ptr<Shader> shader){             _lightMap->draw(shader);}
void Maps::drawParallaxMap(std::shared_ptr<Shader> shader){     _parallaxMap->draw(shader);}

void Maps::drawMesh()
{
    _mesh->Draw();
}

void Maps::sendHeightMapToShader(std::shared_ptr<Shader> shader){           _heightMap->sendToShader(shader); }
void Maps::sendNormalMapToShader(std::shared_ptr<Shader> shader){           _normalMap->sendToShader(shader); }
void Maps::sendSlantMapToShader(std::shared_ptr<Shader> shader){            _slantMap->sendToShader(shader); }
void Maps::sendCurvatureMapToShader(std::shared_ptr<Shader> shader){        _curvatureMap->sendToShader(shader);}
void Maps::sendCorrecCurvatureMapToShader(std::shared_ptr<Shader> shader){  _correctCurvatureMap->sendToShader(shader);}
void Maps::sendLightMapToShader(std::shared_ptr<Shader> shader){            _lightMap->sendToShader(shader);}
void Maps::sendParallaxMap(std::shared_ptr<Shader> shader){                 _parallaxMap->sendToShader(shader);}



void Maps::setHeightMap(std::shared_ptr<Texture> heightMap)
{
    _heightMap = heightMap;
    _width = heightMap->getWidth();
    _height = heightMap->getHeight();
    resize();
    initializeDataMaps();
}



shared_ptr<Texture> Maps::getHeightMap(){
    return _heightMap;
}

std::shared_ptr<Mesh> Maps::getMesh() const
{
    return _mesh;
}

/************************************************
 *              Private Functions               *
 ************************************************/


void Maps::initialize(shared_ptr<GenShaders> shaders)
{
    _slantMap = make_shared<GeneratedTexture>("slantMap",_width,_height,shaders->slantShader);
    _curvatureMap = make_shared<GeneratedTexture>("curvatureMap",_width,_height,shaders->curvatureShader);
    _correctCurvatureMap = make_shared<GeneratedTexture>("curvatureMap",_width,_height,shaders->correctCurvatureShader);
    _lightMap     = make_shared<GeneratedTexture>("lightMap",    _width,_height,shaders->generateLightShader);
    _parallaxMap  = make_shared<GeneratedTexture>("parallaxMap",_width,_height,shaders->parallaxShader);
    _slantMap->initialize();
    _curvatureMap->initialize();
    _correctCurvatureMap->initialize();
    _lightMap->initialize();
    _parallaxMap->initialize();
}

void Maps::initializeDataMaps(){
   _mesh = MeshLoader::vertexFromHeightMap(_heightMap->getDataRED(),_width,_height,_heightMap->meshOffset());

    vector<float> dataNormalMap = _mesh->getNormalMapZUp();
    _normalMap    = make_shared<LoadTexture>("normalMap", dataNormalMap,GL_RGBA32F,GL_RGBA, _width,_height);
}

void Maps::resize()
{
    _slantMap->resize(_width,_height);
    _curvatureMap->resize(_width,_height);
    _correctCurvatureMap->resize(_width,_height);
    _lightMap->resize(_width,_height);
    _parallaxMap->resize(_width,_height);
}
