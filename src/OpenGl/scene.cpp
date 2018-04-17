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
    _lightSelector(0),
    _typeMeshUsed(typeMesh),
    _widthViewport(widthViewport),
    _heightViewport(heightViewport)

{

    _loadedMaps         = make_shared<MAPS>();
    _generatedMaps      = make_shared<MAPS>();
    _loadedMapsGauss    = make_shared<MAPS>();
    _generatedMapsGauss = make_shared<MAPS>();


    initializeGenShader();
    loadingWithLog(filepaths);
    initializeMaps(_loadedMaps);
    initializeMaps(_generatedMaps);
   /* computeGaussBlur(_loadedMaps,_loadedMapsGauss);
    computeGaussBlur(_generatedMaps,_generatedMapsGauss);
    initializeMaps(_loadedMapsGauss);
    initializeMaps(_generatedMapsGauss);
  vector<float>data = _loadedMapsGauss->heightMap->getDataRED();

*/

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
*/



    /*
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

    if(_currentMaps->heightMap != NULL){
        shader->setFloat("ymin",_currentMaps->mesh->getYmin());
        shader->setFloat("ymax",_currentMaps->mesh->getYmax());
        _currentMaps->heightMap->draw(shader);
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
/*
void Scene::drawGaussBlur(shared_ptr<Shader> shader){
    if(_gaussBlur != NULL){
        _gaussBlur->draw(shader);
    }
}
*/
void Scene::drawLightMap(std::shared_ptr<Shader> shader){
    if(_currentMaps->lightMap != NULL){
        _currentMaps->lightMap->draw(shader);

    }
}

void Scene::drawAsciiTex(std::shared_ptr<Shader> shader)
{
    _asciiTex->sendToShader(shader);
}

/*
void Scene::computeGaussBlur(){
    cout << "GB 1" << endl;
    _loadedMesh = computeGaussBlur(_loadedMesh,_gaussBlurLoad);
    cout << "GB 2" << endl;
    _generatedMesh = computeGaussBlur(_generatedMesh,_gaussBlurGen);
    cout << "GB 3" << endl;
    initialize();

}
*/




void Scene::computeLightMap(vec3 lightPosition, float lightYaw, float lightPitch){
    _currentMaps->lightMap->startGenerate();
    _currentMaps->lightMap->generatorShader()->setVec3("lightPosition",lightPosition);
    _currentMaps->lightMap->generatorShader()->setFloat("yaw",lightYaw);
    _currentMaps->lightMap->generatorShader()->setFloat("pitch",lightPitch);
    _currentMaps->lightMap->generatorShader()->setInt("lightSelector",_lightSelector);
    _currentMaps->lightMap->generatorShader()->setFloat("threshold",_lightThreshold);
    _currentMaps->curvatureMap->sendToShader(_currentMaps->lightMap->generatorShader());
    _currentMaps->lightMap->generate(_widthViewport,_heightViewport);
}


void Scene::reloadGenerateTexturesShader(){
    _curvatureShader->reload();
    _generateLightShader->reload();
    _gaussBlurShader->reload();

    computeCurvatureMap(_loadedMaps);
    computeCurvatureMap(_generatedMaps);
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
    computeCurvatureMap(_loadedMaps);
    computeCurvatureMap(_generatedMaps);
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





void Scene::majCurrentMap()
{
    switch(_typeMeshUsed){
        case LOADED:            _currentMaps = _loadedMaps;         break;
        case GAUSSLOADED :      _currentMaps = _loadedMapsGauss;    break;
        case GENERATED :        _currentMaps = _generatedMaps;      break;
        case GAUSSGENERATED :   _currentMaps = _generatedMapsGauss; break;
    }
}


/*
void Scene::initialize(){
    switch(_typeMeshUsed){
    case LOADED:    _currentMesh = _loadedMesh;    break;
    case GENERATED: _currentMesh = _generatedMesh; break;
    }
    _curvatureMapIsComputed = false;
    getMapFromMNT();
}
*/

/*
void Scene::getMapFromMNT(){
    vector<float> dataHeightMap = _currentMesh->getReverseHeightMap();
    _heightMap = make_shared<LoadTexture>("heightMap", dataHeightMap,GL_R32F,GL_RED,_currentMesh->getWidth(),_currentMesh->getHeight());
    vector<float> dataNormalMap = _currentMesh->getReverseNormalMap();
    _normalMap = make_shared<LoadTexture>("normalMap", dataNormalMap,GL_RGBA32F,GL_RGBA,_currentMesh->getWidth(),_currentMesh->getHeight());
}
*/




void Scene::loadingWithLog(const vector<string> &filepaths){
    cout << "Loading MNT from : " << endl;
    for(unsigned int i=0;i< filepaths.size() ; i++ ){
        cout << filepaths[i] << "..." << endl;
    }

    _loadedMaps->heightMap = _meshLoader.textureFromMNT(filepaths);
    _generatedMaps->heightMap = computeMeshFromGenHeightMap();
    _generatedMaps->heightMap->setMeshOffset(1.0);

/*    _loadedMaps->mesh = _meshLoader.vertexFromMNT(filepaths);
    _loadedMaps->mesh->printInfo();


    cout << "Generate mesh ..." << endl;
    _generatedMaps->mesh = computeMeshFromGenHeightMap( );
    _generatedMaps->mesh->printInfo();
*/
}

shared_ptr<LoadTexture> Scene::computeMeshFromGenHeightMap(){

    int width = 200, height = 200;

    HeightMap heightMap = HeightMap("heightMapGen", width,height);
    heightMap.initialize();
    heightMap.startGenerate();
    vector<float> data = heightMap.generate(_widthViewport,_heightViewport);
    return make_shared<LoadTexture>("heightMap", data,GL_R32F,   GL_RED, width,height);
}




void Scene::initializeGenShader(){
    _curvatureShader     = make_shared<Shader>("shaders/curvature.vert","shaders/curvature.frag");
    _generateLightShader = make_shared<Shader>("shaders/generatelight.vert","shaders/generatelight.frag");
    _gaussBlurShader     = make_shared<Shader>("shaders/gaussBlur.vert","shaders/gaussBlur.frag");
}



void Scene::initializeMaps(shared_ptr<MAPS> maps){
    //Get HeightMap
    // Generated Mesh
    // Get   Normal
    // init Curvature
    // init Light

    //vector<float> dataHeightMap = maps->mesh->getReverseHeightMap();

    //maps->heightMap    = make_shared<LoadTexture>("heightMap", dataHeightMap,GL_R32F,   GL_RED,  maps->mesh->getWidth(),maps->mesh->getHeight());
    maps->mesh = _meshLoader.vertexFromHeightMap(maps->heightMap->getDataRED(),maps->heightMap->getWidth(),maps->heightMap->getHeight(),maps->heightMap->meshOffset());

    vector<float> dataNormalMap = maps->mesh->getReverseNormalMap();
    maps->normalMap    = make_shared<LoadTexture>("normalMap", dataNormalMap,GL_RGBA32F,GL_RGBA, maps->mesh->getWidth(),maps->mesh->getHeight());
    maps->curvatureMap = make_shared<GeneratedTexture>("curvatureMap",maps->mesh->getWidth(),maps->mesh->getHeight(),_curvatureShader);
    maps->lightMap     = make_shared<GeneratedTexture>("lightMap",    maps->mesh->getWidth(),maps->mesh->getHeight(),_generateLightShader);
    maps->curvatureMap->initialize();
    maps->lightMap->initialize();
    computeCurvatureMap(maps);
}

void Scene::computeCurvatureMap(shared_ptr<MAPS> maps){


    maps->curvatureMap->startGenerate();
    maps->curvatureMap->generatorShader()->setFloat("sigma",_sigma);
    maps->normalMap->sendToShader(maps->curvatureMap->generatorShader());
    maps->curvatureMap->generate(_widthViewport,_heightViewport);
}


void Scene::computeGaussBlur(shared_ptr<MAPS> ref, shared_ptr<MAPS> gauss){




    shared_ptr<GeneratedTexture>gaussHeightMap = make_shared<GeneratedTexture>("heightMap",ref->heightMap->getWidth(),ref->heightMap->getHeight(),_gaussBlurShader);
    gaussHeightMap->setMeshOffset(ref->heightMap->meshOffset());
    gaussHeightMap->initialize();


    gaussHeightMap->startGenerate();
    gaussHeightMap->generatorShader()->setInt("halfsize",3);
    gaussHeightMap->generatorShader()->setInt("direction",0);
    ref->heightMap->sendToShader(gaussHeightMap->generatorShader(),"img");
    gaussHeightMap->generate(_widthViewport,_heightViewport);
/*
    gaussHeightMap->startGenerate();
    gaussHeightMap->generatorShader()->setInt("halfsize",3);
    gaussHeightMap->generatorShader()->setInt("direction",1);
    gaussHeightMap->sendToShader(gaussHeightMap->generatorShader(),"img");
    gaussHeightMap->generate(_widthViewport,_heightViewport);
*/

    vector<float> data = gaussHeightMap->getDataRED();

    for(int i =0; i< data.size();i++){
        cout << data[i]<< endl;
    }

    gauss->heightMap = gaussHeightMap;

}
/*
void Scene::initializeGaussMap(){

}
*/

