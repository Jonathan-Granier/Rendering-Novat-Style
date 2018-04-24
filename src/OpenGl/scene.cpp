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

    initializeGenShader();
    initializeMaps(filepaths);
    majCurrentMap();
    initializeTexture();


    _loadedHeightMapGauss    = make_shared<HeightMapGauss>();
    _generatedHeightMapGauss = make_shared<HeightMapGauss>();
    initializeHeightMapGauss(_loadedHeightMapGauss,_loadedMaps->getHeightMap());
    initializeHeightMapGauss(_generatedHeightMapGauss,_generatedMaps->getHeightMap());



    _meshSphere = MeshLoader::vertexFromObj("models/sphere.obj");
}






void Scene::draw(shared_ptr<Shader> shader, vec3 lightPosition){

    _currentMaps->sendLightMapToShader(shader);
    _currentMaps->sendParallaxMap(shader);
    for(unsigned int i=0;i<_textures.size();i++){
        _textures[i]->sendToShader(shader);
    }



    mat4 modelMesh;
    shader->setMat4("modelMat",modelMesh);
    _currentMaps->drawMesh();
    mat4 modelSphere;
    modelSphere = glm::translate(modelSphere,lightPosition*_currentMaps->getMesh()->radius());
    modelSphere = glm::scale(modelSphere,vec3(_currentMaps->getMesh()->radius()/20.0,_currentMaps->getMesh()->radius()/20.0,_currentMaps->getMesh()->radius()/20.0));
    shader->setMat4("modelMat",modelSphere);
   _meshSphere->Draw();


    glActiveTexture(GL_TEXTURE0);
}

void Scene::drawOnlyMesh(){
    _currentMaps->drawMesh();
}

void Scene::drawHeightMap(shared_ptr<Shader> shader){
    _currentMaps->drawHeightMap(shader);
}

void Scene::drawNormalMap(shared_ptr<Shader> shader){           _currentMaps->drawNormalMap(shader); }
void Scene::drawSlantMap(shared_ptr<Shader> shader){            _currentMaps->drawSlantMap(shader);}
void Scene::drawCurvatureMap(shared_ptr<Shader> shader){        _currentMaps->drawCurvatureMap(shader);}
void Scene::drawCorrectCurvatureMap(shared_ptr<Shader> shader){ _currentMaps->drawCorrectCurvatureMap(shader);}
void Scene::drawLightMap(std::shared_ptr<Shader> shader){       _currentMaps->drawLightMap(shader); }
void Scene::drawParallaxMap(std::shared_ptr<Shader> shader){    _currentMaps->drawParallaxMap(shader);}


void Scene::drawAsciiTex(std::shared_ptr<Shader> shader)
{
    _asciiTex->sendToShader(shader);
}

void Scene::initializeGaussMap(){
    if(!_isInitializedGaussMap)
    {
        cout << "Compute Gauss Load Map ..." << endl;
        computeGaussBlur(_loadedMapsGauss,_loadedHeightMapGauss,_loadedMaps->getHeightMap());
        cout << "Compute Gauss Generate Map ..." << endl;
        computeGaussBlur(_generatedMapsGauss,_generatedHeightMapGauss,_generatedMaps->getHeightMap());
        _isComputeCurvatureMap = false;
        _isInitializedGaussMap = true;

    }
}



void Scene::computeCurvatureMap(){
    if(!_isComputeCurvatureMap)
    {
        _loadedMaps->generateSlantMap(_widthViewport,_heightViewport);
        _loadedMapsGauss->generateSlantMap(_widthViewport,_heightViewport);
        _generatedMaps->generateSlantMap(_widthViewport,_heightViewport);
        _generatedMapsGauss->generateSlantMap(_widthViewport,_heightViewport);

        _loadedMaps->generateCurvatureMap(_widthViewport,_heightViewport,_sigma);
        _loadedMapsGauss->generateCurvatureMap(_widthViewport,_heightViewport,_sigma);
        _generatedMaps->generateCurvatureMap(_widthViewport,_heightViewport,_sigma);
        _generatedMapsGauss->generateCurvatureMap(_widthViewport,_heightViewport,_sigma);

        _isComputeCurvatureMap = true;
    }
}




void Scene::computeLightMap(vec3 lightPosition, float lightYaw, float lightPitch){
    _currentMaps->generateLightMap(_widthViewport,_heightViewport,lightPosition,lightYaw,lightPitch,_lightThreshold,_lightSelector);
}

void Scene::computeParallaxMap(glm::vec3 lightPosition){
    _currentMaps->generateParallaxMap(_widthViewport,_heightViewport,lightPosition);
}



void Scene::reloadGenerateTexturesShader(){
    _genShaders->slantShader->reload();
    _genShaders->curvatureShader->reload();
    _genShaders->correctCurvatureShader->reload();
    _genShaders->generateLightShader->reload();
    _genShaders->gaussBlurShader->reload();
    _genShaders->parallaxShader->reload();
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
    return _currentMaps->getMesh()->center();
}


float Scene::radius() const
{
    return _currentMaps->getMesh()->radius();
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








/************************************************
 *              Private Functions               *
 ************************************************/




void Scene::initializeGenShader(){
    _genShaders = make_shared<GenShaders>();
    _genShaders->slantShader                = make_shared<Shader>("shaders/slant.vert","shaders/slant.frag");
    _genShaders->curvatureShader            = make_shared<Shader>("shaders/curvature.vert","shaders/curvature.frag");
    _genShaders->correctCurvatureShader     = make_shared<Shader>("shaders/correctcurvature.vert","shaders/correctcurvature.frag");
    _genShaders->generateLightShader        = make_shared<Shader>("shaders/generatelight.vert","shaders/generatelight.frag");
    _genShaders->gaussBlurShader            = make_shared<Shader>("shaders/gaussBlur.vert","shaders/gaussBlur.frag");
    _genShaders->parallaxShader             = make_shared<Shader>("shaders/parallax.vert","shaders/parallax.frag");
}


void Scene::initializeMaps(const vector<string> &filepaths){
    cout << "Loading MNT from : " << endl;
    for(unsigned int i=0;i< filepaths.size() ; i++ ){
        cout << filepaths[i] << "..." << endl;
    }
    shared_ptr<Texture> heightMapL = MeshLoader::textureFromMNT(filepaths);
    _loadedMaps = make_shared<Maps>(_genShaders,heightMapL,"loadedMaps");

    cout << "Generate heightMap ..." << endl;
    shared_ptr<Texture> heightMapG = computeGenHeightMap();
    heightMapG->setMeshOffset(1.0);
    _generatedMaps = make_shared<Maps>(_genShaders,heightMapG,"generated Maps");


    _loadedMapsGauss = make_shared<Maps>(_genShaders,heightMapL->getWidth(),heightMapL->getHeight(),"Loaded Gauss Maps");
    _generatedMapsGauss = make_shared<Maps>(_genShaders,heightMapG->getWidth(),heightMapG->getHeight(),"Generated Gauss Maps");


}


void Scene::initializeTexture(){
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

}




void Scene::initializeHeightMapGauss(shared_ptr<HeightMapGauss> gauss, shared_ptr<Texture> refHeightMap){

    gauss->gaussMap = make_shared<GeneratedTexture>(_HEIGHTMAPNAME,refHeightMap->getWidth(),refHeightMap->getHeight(),_genShaders->gaussBlurShader);
    gauss->interGaussMap = make_shared<GeneratedTexture>("interGaussMap",refHeightMap->getWidth(),refHeightMap->getHeight(),_genShaders->gaussBlurShader);

    gauss->gaussMap->initialize();
    gauss->interGaussMap->initialize();

    gauss->gaussMap->setMeshOffset(refHeightMap->meshOffset());

}

shared_ptr<Texture> Scene::computeGenHeightMap(){
    HeightMap heightMap = HeightMap(_HEIGHTMAPNAME, _WIDTHGENTEX,_HEIGHTGENTEX);
    heightMap.initialize();
    heightMap.startGenerate();
    vector<float> data = heightMap.generate(_widthViewport,_heightViewport);
    return make_shared<LoadTexture>(_HEIGHTMAPNAME, data,GL_R32F,   GL_RED, _WIDTHGENTEX,_HEIGHTGENTEX);
}






void Scene::computeGaussBlur(shared_ptr<Maps> gaussMaps, shared_ptr<HeightMapGauss> gaussHeightMap,shared_ptr<Texture> refHeightMap){

    gaussHeightMap->interGaussMap->startGenerate();
    gaussHeightMap->interGaussMap->generatorShader()->setInt("halfsize",_gaussBlurFactor);
    gaussHeightMap->interGaussMap->generatorShader()->setInt("direction",0);
    refHeightMap->sendToShader(gaussHeightMap->interGaussMap->generatorShader(),"img");
    gaussHeightMap->interGaussMap->generate(_widthViewport,_heightViewport);


    gaussHeightMap->gaussMap->startGenerate();
    gaussHeightMap->gaussMap->generatorShader()->setInt("halfsize",_gaussBlurFactor);
    gaussHeightMap->gaussMap->generatorShader()->setInt("direction",1);
    gaussHeightMap->interGaussMap->sendToShader(gaussHeightMap->gaussMap->generatorShader(),"img");
    gaussHeightMap->gaussMap->generate(_widthViewport,_heightViewport);

    gaussMaps->setHeightMap(gaussHeightMap->gaussMap);

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

