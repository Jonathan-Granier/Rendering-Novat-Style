#include "scene.h"

#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include "vertex.h"
#include "iostream"
#include "heightmap.h"

using namespace std;
using namespace glm;

Scene::Scene(const vector<string> &filepaths,TYPE_MESH typeMesh,int widthViewport,int heightViewport) :
    _sigma(1.0),
    _gaussBlurFactor(3),
    _lightSelector(0),
    _lightThreshold(M_PI/3.0),
    _typeMeshUsed(typeMesh),
    _widthViewport(widthViewport),
    _heightViewport(heightViewport),
    _isComputeCurvatureMap(false)

{

    _loadedMaps         = make_shared<MAPS>();
    _generatedMaps      = make_shared<MAPS>();
    _loadedMapsGauss    = make_shared<MAPS>();
    _generatedMapsGauss = make_shared<MAPS>();
    initializeGenShader();
    loadingWithLog(filepaths);

    InitGenTex(_loadedMaps);
    InitGenTex(_generatedMaps);
    InitGenTex(_loadedMapsGauss,_loadedMaps);
    InitGenTex(_generatedMapsGauss,_generatedMaps);

    initializeDataMaps(_loadedMaps,false);
    initializeDataMaps(_generatedMaps,false);


    majCurrentMap();

    _meshSphere = _meshLoader.vertexFromObj("models/sphere.obj");
/*
    _curvatureMap = make_shared<GeneratedTexture>("curvatureMap",_currentMesh->getWidth(),_currentMesh->getHeight(),
                                                  "shaders/curvature.vert","shaders/curvature.frag");

    _lightMap = make_shared<GeneratedTexture>("lightMap",_currentMesh->getWidth(),_currentMesh->getHeight(),
                                                  "shaders/generatelight.vert","shaders/generatelight.frag");

    _gaussBlurLoad = make_shared<GeneratedTexture>("gaussBlur",_loadedMesh->getWidth(),_loadedMesh->getHeight(),
                                               "shaders/gaussBlur.vert","shaders/gaussBlur.frag");
    _gaussBlurGen = make_shared<GeneratedTexture>("gaussBlur",_generatedMesh->getWidth(),_generatedMesh->getHeight(),
                                                  "shaders/gaussBlur.vert","shaders/gaussBlur.frag");





    _curvatureMap->initialize();
    _lightMap->initialize();
    _gaussBlurLoad->initialize();
    _gaussBlurGen->initialize();
*/

    shared_ptr<LoadTexture> texture1 = make_shared<LoadTexture>("container", "textures/container.jpg");
    shared_ptr<LoadTexture> texture2 = make_shared<LoadTexture>("awesomeface", "textures/awesomeface.png");
    shared_ptr<LoadTexture> texture3 = make_shared<LoadTexture>("neige_ombre", "textures/dégradé_neige_ombre.png");
    shared_ptr<LoadTexture> texture4 = make_shared<LoadTexture>("degrade_debug", "textures/dégradé_debug.png");
    shared_ptr<LoadTexture> texture5 = make_shared<LoadTexture>("flat_color_debug", "textures/flat_color.png");
    _asciiTex = make_shared<LoadTexture>("asciiTex","textures/ASCII_Debug.png");



    _textures.push_back(texture1);
    _textures.push_back(texture2);
    _textures.push_back(texture3);
    _textures.push_back(texture4);
    _textures.push_back(texture5);
   // computeGaussBlur();
}






void Scene::draw(shared_ptr<Shader> shader, vec3 lightPosition){

    _currentMaps->lightMap->sendToShader(shader);

    for(unsigned int i=0;i<_textures.size();i++){
        _textures[i]->sendToShader(shader);
    }

    mat4 modelMesh;
    shader->setMat4("modelMat",modelMesh);
    _currentMaps->mesh->Draw();
    mat4 modelSphere;
    modelSphere = glm::translate(modelSphere,lightPosition*_currentMaps->mesh->radius());
    modelSphere = glm::scale(modelSphere,vec3(_currentMaps->mesh->radius()/20.0,_currentMaps->mesh->radius()/20.0,_currentMaps->mesh->radius()/20.0));
    shader->setMat4("modelMat",modelSphere);
   _meshSphere->Draw();
    // always good practice to set everything back to defaults once configured.
    glActiveTexture(GL_TEXTURE0);
}

void Scene::drawOnlyMesh(){
    _currentMaps->mesh->Draw();
}

void Scene::drawHeightMap(shared_ptr<Shader> shader){

    shader->setFloat("ymin",_currentMaps->mesh->getYmin());
    shader->setFloat("ymax",_currentMaps->mesh->getYmax());
    switch(_typeMeshUsed){
        case LOADED:
        case GENERATED:
            _currentMaps->heightMap->draw(shader);
            break;
        case GAUSSLOADED:
        case GAUSSGENERATED:
            _currentMaps->gaussMap->draw(shader);
            break;
    }


}

void Scene::drawNormalMap(shared_ptr<Shader> shader){
    if(_currentMaps->normalMap != NULL){
        _currentMaps->normalMap->draw(shader);

    }
}

void Scene::drawCurvatureMap(shared_ptr<Shader> shader){
    if(_currentMaps->curvatureMap != NULL){
        _currentMaps->curvatureMap->draw(shader);

    }
}

void Scene::drawCorrectCurvatureMap(shared_ptr<Shader> shader){
    if(_currentMaps->correctCurvatureMap != NULL){
        _currentMaps->correctCurvatureMap->draw(shader);

    }
}

void Scene::drawLightMap(std::shared_ptr<Shader> shader){
    if(_currentMaps->lightMap != NULL){
        _currentMaps->lightMap->draw(shader);

    }
}

void Scene::drawAsciiTex(std::shared_ptr<Shader> shader)
{
    _asciiTex->sendToShader(shader);
}

void Scene::initializeGaussMap(){
    if(!_isInitializedGaussMap)
    {
        computeGaussBlur(_loadedMapsGauss,_loadedMaps);
        computeGaussBlur(_generatedMapsGauss,_generatedMaps);
        _isComputeCurvatureMap = false;
        _isInitializedGaussMap = true;
    }
}


void Scene::computeCurvatureMap(){
    if(!_isComputeCurvatureMap)
    {
        computeCurvatureMap(_loadedMaps);
        computeCurvatureMap(_generatedMaps);
        computeCurvatureMap(_loadedMapsGauss);
        computeCurvatureMap(_generatedMapsGauss);
        _isComputeCurvatureMap = true;
    }
}


void Scene::computeLightMap(vec3 lightPosition, float lightYaw, float lightPitch){
    _currentMaps->lightMap->startGenerate();
    _currentMaps->lightMap->generatorShader()->setVec3("lightPosition",lightPosition);
    _currentMaps->lightMap->generatorShader()->setFloat("yaw",lightYaw);
    _currentMaps->lightMap->generatorShader()->setFloat("pitch",lightPitch);
    _currentMaps->lightMap->generatorShader()->setInt("lightSelector",_lightSelector);
    _currentMaps->lightMap->generatorShader()->setFloat("threshold",_lightThreshold);
    _currentMaps->correctCurvatureMap->sendToShader(_currentMaps->lightMap->generatorShader());
    _currentMaps->lightMap->generate(_widthViewport,_heightViewport);
}


void Scene::reloadGenerateTexturesShader(){
    _curvatureShader->reload();
    _correctCurvatureShader->reload();
    _generateLightShader->reload();
    _gaussBlurShader->reload();
    _isComputeCurvatureMap = false;

}



void Scene::switchTypeMeshUsed(){
    switch(_typeMeshUsed){
        case LOADED:
            _typeMeshUsed = GAUSSLOADED;
            break;
        case GAUSSLOADED:
            _typeMeshUsed = GENERATED;
            break;
        case GENERATED:
            _typeMeshUsed = GAUSSGENERATED;
            break;
        case GAUSSGENERATED:
            _typeMeshUsed = LOADED;
            break;
    }
    majCurrentMap();
}



vec3 Scene::center() const
{
    return _currentMaps->mesh->center();
}


float Scene::radius() const
{
    return _currentMaps->mesh->radius();
}



float Scene::getSigma() const
{
    return _sigma;
}

void Scene::setSigma(float sigma)
{
    _sigma = sigma;
    _isComputeCurvatureMap = false;
}



void Scene::previousLight()
{
     _lightSelector = (_lightSelector-1 + _MAXLIGHTSELECTOR) %_MAXLIGHTSELECTOR;
}

void Scene::nextLight()
{
    _lightSelector = (_lightSelector+1) % _MAXLIGHTSELECTOR;
}

int Scene::getLightSelector() const
{
    return _lightSelector;
}

float Scene::getLightThreshold() const
{
    return _lightThreshold;
}

void Scene::setLightThreshold(float lightThreshold)
{
    if(lightThreshold < _MINLIGHTRESHOLD)
        _lightThreshold = 0;
    if(lightThreshold > _MAXLIGHTSELECTOR)
        _lightThreshold = _MAXLIGHTSELECTOR;
    else
        _lightThreshold = lightThreshold;
}

int Scene::getGaussBlurFactor() const
{
    return _gaussBlurFactor;
}

void Scene::setGaussBlurFactor(int gaussBlurFactor)
{
    _gaussBlurFactor = gaussBlurFactor;
}

void Scene::reloadGaussHeightMap()
{
    _isInitializedGaussMap = false;
}





void Scene::majCurrentMap()
{
    switch(_typeMeshUsed){
    case LOADED:            _currentMaps = _loadedMaps;         break;
    case GAUSSLOADED :      _currentMaps = _loadedMapsGauss;    break;
        case GENERATED :        _currentMaps = _generatedMaps;      break;
        case GAUSSGENERATED :   _currentMaps = _generatedMapsGauss; break;
    }
}






void Scene::loadingWithLog(const vector<string> &filepaths){
    cout << "Loading MNT from : " << endl;
    for(unsigned int i=0;i< filepaths.size() ; i++ ){
        cout << filepaths[i] << "..." << endl;
    }

    _loadedMaps->heightMap = _meshLoader.textureFromMNT(filepaths);
    _generatedMaps->heightMap = computeMeshFromGenHeightMap();
    _generatedMaps->heightMap->setMeshOffset(1.0);

}

shared_ptr<LoadTexture> Scene::computeMeshFromGenHeightMap(){

    int width =1024, height = 1024;

    HeightMap heightMap = HeightMap("heightMapGen", width,height);
    heightMap.initialize();
    heightMap.startGenerate();
    vector<float> data = heightMap.generate(_widthViewport,_heightViewport);
    return make_shared<LoadTexture>("heightMap", data,GL_R32F,   GL_RED, width,height);
}


void Scene::computeCurvatureMap(shared_ptr<MAPS> maps){


    maps->curvatureMap->startGenerate();
    maps->curvatureMap->generatorShader()->setFloat("sigma",_sigma);
    maps->normalMap->sendToShader(maps->curvatureMap->generatorShader());
    maps->curvatureMap->generate(_widthViewport,_heightViewport);

    maps->correctCurvatureMap->startGenerate();
    maps->normalMap->sendToShader(maps->correctCurvatureMap->generatorShader());
    maps->curvatureMap->sendToShader(maps->correctCurvatureMap->generatorShader());
    maps->correctCurvatureMap->generate(_widthViewport,_heightViewport);

}


void Scene::initializeGenShader(){
    _curvatureShader            = make_shared<Shader>("shaders/curvature.vert","shaders/curvature.frag");
    _correctCurvatureShader  = make_shared<Shader>("shaders/correctcurvature.vert","shaders/correctcurvature.frag");
    _generateLightShader        = make_shared<Shader>("shaders/generatelight.vert","shaders/generatelight.frag");
    _gaussBlurShader            = make_shared<Shader>("shaders/gaussBlur.vert","shaders/gaussBlur.frag");
}



void Scene::initializeDataMaps(shared_ptr<MAPS> maps,bool isGauss){

    shared_ptr<Texture> heightMap;
    if(isGauss)
        heightMap = maps->gaussMap;
    else
        heightMap = maps->heightMap;

    maps->mesh = _meshLoader.vertexFromHeightMap(heightMap->getDataRED(),heightMap->getWidth(),heightMap->getHeight(),heightMap->meshOffset());

    vector<float> dataNormalMap = maps->mesh->getReverseNormalMap();
    maps->normalMap    = make_shared<LoadTexture>("normalMap", dataNormalMap,GL_RGBA32F,GL_RGBA, maps->mesh->getWidth(),maps->mesh->getHeight());
}



void Scene::computeGaussBlur( shared_ptr<MAPS> gauss,shared_ptr<MAPS> ref){

    gauss->interGaussMap->startGenerate();
    gauss->interGaussMap->generatorShader()->setInt("halfsize",_gaussBlurFactor);
    gauss->interGaussMap->generatorShader()->setInt("direction",0);
    ref->heightMap->sendToShader(gauss->interGaussMap->generatorShader(),"img");
    gauss->interGaussMap->generate(_widthViewport,_heightViewport);


    gauss->gaussMap->startGenerate();
    gauss->gaussMap->generatorShader()->setInt("halfsize",_gaussBlurFactor);
    gauss->gaussMap->generatorShader()->setInt("direction",1);
    gauss->interGaussMap->sendToShader(gauss->gaussMap->generatorShader(),"img");
    gauss->gaussMap->generate(_widthViewport,_heightViewport);


    initializeDataMaps(gauss,true);


}


void Scene::InitGenTex(shared_ptr<MAPS> maps){
    maps->curvatureMap = make_shared<GeneratedTexture>("curvatureMap",maps->heightMap->getWidth(),maps->heightMap->getHeight(),_curvatureShader);
    maps->correctCurvatureMap = make_shared<GeneratedTexture>("curvatureMap",maps->heightMap->getWidth(),maps->heightMap->getHeight(),_correctCurvatureShader);
    maps->lightMap     = make_shared<GeneratedTexture>("lightMap",    maps->heightMap->getWidth(),maps->heightMap->getHeight(),_generateLightShader);
    maps->curvatureMap->initialize();
    maps->correctCurvatureMap->initialize();
    maps->lightMap->initialize();
}

void Scene::InitGenTex(shared_ptr<MAPS> maps, shared_ptr<MAPS> ref){
    maps->gaussMap = make_shared<GeneratedTexture>("gaussMap",ref->heightMap->getWidth(),ref->heightMap->getHeight(),_gaussBlurShader);
    maps->interGaussMap = make_shared<GeneratedTexture>("interGaussMap",ref->heightMap->getWidth(),ref->heightMap->getHeight(),_gaussBlurShader);
    maps->curvatureMap = make_shared<GeneratedTexture>("curvatureMap",ref->heightMap->getWidth(),ref->heightMap->getHeight(),_curvatureShader);
    maps->correctCurvatureMap = make_shared<GeneratedTexture>("curvatureMap",ref->heightMap->getWidth(),ref->heightMap->getHeight(),_correctCurvatureShader);
    maps->lightMap     = make_shared<GeneratedTexture>("lightMap",    ref->heightMap->getWidth(),ref->heightMap->getHeight(),_generateLightShader);

    maps->gaussMap->initialize();
    maps->interGaussMap->initialize();
    maps->curvatureMap->initialize();
    maps->correctCurvatureMap->initialize();
    maps->lightMap->initialize();

    maps->gaussMap->setMeshOffset(ref->heightMap->meshOffset());

}

