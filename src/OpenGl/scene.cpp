#include "scene.h"

#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include "vertex.h"
#include "iostream"
#include "heightmap.h"

using namespace std;
using namespace glm;

Scene::Scene(const vector<string> &filepaths,int widthViewport,int heightViewport) :
     _currentIndex(0),
    _widthViewport(widthViewport),
    _heightViewport(heightViewport)
{

    initializeGenShader();
    initializeMaps(filepaths);

    //majCurrentMap();
    initializeTexture();
    initStackMaps();


/*

    _loadedHeightMapGauss    = make_shared<HeightMapGauss>();
    _generatedHeightMapGauss = make_shared<HeightMapGauss>();
    initializeHeightMapGauss(_loadedHeightMapGauss,_loadedMaps->getHeightMap());
    initializeHeightMapGauss(_generatedHeightMapGauss,_generatedMaps->getHeightMap());
*/


    _meshSphere = MeshLoader::vertexFromObj("models/sphere.obj");
}

/*
void Scene::recreateScene(const vector<string> &filepaths){
    initializeMaps(filepaths);
}
*/


void Scene::draw(shared_ptr<Shader> shader, vec3 lightPosition){


    //cout << "I Draw id :" << _currentIndex << endl;
    //printMapsManagers();
    _mapsManagers[_currentIndex]->maps->sendLightMapToShader(shader);
    _mapsManagers[_currentIndex]->maps->sendParallaxMap(shader);

    for(unsigned int i=0;i<_textures.size();i++){
        _textures[i]->sendToShader(shader);
    }



    mat4 modelMesh;
    shader->setMat4("modelMat",modelMesh);
    _mountains->draw();
    mat4 modelSphere;
    modelSphere = glm::translate(modelSphere,lightPosition*_mountains->radius());
    modelSphere = glm::scale(modelSphere,vec3(_mountains->radius()/20.0,_mountains->radius()/20.0,_mountains->radius()/20.0));
    shader->setMat4("modelMat",modelSphere);
   _meshSphere->draw();


    glActiveTexture(GL_TEXTURE0);
}

void Scene::drawOnlyMesh(){
    _mountains->draw();
}

void Scene::drawHeightMap(shared_ptr<Shader> shader){           _mapsManagers[_currentIndex]->maps->drawHeightMap(shader);}
void Scene::drawNormalMap(shared_ptr<Shader> shader){           _mapsManagers[_currentIndex]->maps->drawNormalMap(shader); }
void Scene::drawSlantMap(shared_ptr<Shader> shader){            _mapsManagers[_currentIndex]->maps->drawSlantMap(shader);}
//void Scene::drawCurvatureMap(shared_ptr<Shader> shader){        _currentMaps->drawCurvatureMap(shader);}
//void Scene::drawCorrectCurvatureMap(shared_ptr<Shader> shader){ _currentMaps->drawCorrectCurvatureMap(shader);}
void Scene::drawLightMap(std::shared_ptr<Shader> shader){       _mapsManagers[_currentIndex]->maps->drawLightMap(shader); }
void Scene::drawParallaxMap(std::shared_ptr<Shader> shader){    _mapsManagers[_currentIndex]->maps->drawParallaxMap(shader);}


void Scene::drawAsciiTex(std::shared_ptr<Shader> shader)
{
    _asciiTex->sendToShader(shader);
}
/*
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
*/
/*

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
generateHeightMap
*/
void Scene::generateGaussHeightMap(){
    for(shared_ptr<MapsManager> m:_mapsManagers){
        if(m->ID != 0){
            m->maps->generateHeightMap(_widthViewport,_heightViewport,_mapsManagers[0]->maps->getHeightMap());
        }
    }


}

void Scene::generateSlantLightAndParalaxMaps(glm::vec3 lightPos, float pitch, float yaw){

    bool firstMap = true;

    std::shared_ptr<GeneratedTexture> previousLightMap;
    for(int i=_mapsManagers.size()-1; i>=0;i--){
        if(_mapsManagers[i]->enabled){
            _mapsManagers[i]->maps->generateSlantMap(_widthViewport,_heightViewport);
            if(firstMap){
                _mapsManagers[i]->maps->generateLightMap(_widthViewport,_heightViewport,lightPos,pitch,yaw);
                firstMap = false;
            }
            else{
                _mapsManagers[i]->maps->generateLightMap(_widthViewport,_heightViewport,previousLightMap,pitch);
            }
            _mapsManagers[i]->maps->generateParallaxMap(_widthViewport,_heightViewport,lightPos);
            previousLightMap  = _mapsManagers[i]->maps->getLightMap();
        }
    }
}




/*

void Scene::computeLightMap(vec3 lightPosition, float lightYaw, float lightPitch){
    _currentMaps->generateLightMap(_widthViewport,_heightViewport,lightPosition,lightYaw,lightPitch,_lightThreshold,_lightSelector);
}

void Scene::computeParallaxMap(glm::vec3 lightPosition){
    _currentMaps->generateParallaxMap(_widthViewport,_heightViewport,lightPosition);
}

*/

void Scene::reloadGenerateTexturesShader(){
    _genShaders->slantShader->reload();
    _genShaders->curvatureShader->reload();
    _genShaders->correctCurvatureShader->reload();
    _genShaders->generateLightShader->reload();
    _genShaders->gaussBlurShader->reload();
    _genShaders->parallaxShader->reload();
    //_isComputeCurvatureMap = false;

}


/*
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
*/




vec3 Scene::center() const
{
    return _mountains->center();
}


float Scene::radius() const
{
    return _mountains->radius();
}


/*
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
*/

void Scene::nextMaps(){


    unsigned int i = _currentIndex;
    do{
        i = (i+1 )% _mapsManagers.size();
    }while(!_mapsManagers[i]->enabled && _currentIndex != i);

    if(_currentIndex == i)
        cerr << "One or less maps are enabled ! " << endl;
    _currentIndex = i;
}

void Scene::previousMaps(){
    int i;
    do{
        i = (_mapsManagers.size() + i-1 )% _mapsManagers.size();
    }while(!_mapsManagers[i]->enabled && (int)_currentIndex != i);

    if((int)_currentIndex == i)
        cerr << "One or less maps are enabled ! " << endl;
    _currentIndex = i;
}

void Scene::setLightThreshold(unsigned int id, float t)
{
    findFromID(id)->maps->setLightThreshold(t);
}
/*
int Scene::getGaussBlurFactor() const
{
    return _gaussBlurFactor;
}
*/
void Scene::setGaussBlurFactor(unsigned int id ,int g)
{
    findFromID(id)->maps->setGaussBlurFactor(g);
}

void Scene::setEnabledMaps(unsigned int id, bool enabled){
    findFromID(id)->enabled = enabled;
}

void Scene::reloadGaussHeightMap()
{
    for(shared_ptr<MapsManager> m : _mapsManagers){
        if(m->ID != 0){
            m->maps->reloadHeightMap();
        }
    }
}

void Scene::addGaussMaps(unsigned int id)
{
    if(id == 0){
        cerr << "Can't add a new GaussMaps with id = 0" << endl;
        return;
    }
    //cout << "I ADD GAUSS MAPS : " << id << endl;



    std::shared_ptr<Maps> maps = getMapsFromSupply();
    if(maps!=nullptr){
        std::shared_ptr<MapsManager> mapsManager = make_shared<MapsManager>();
        mapsManager->maps = maps;
        mapsManager->enabled = false;
        mapsManager->ID = id;
        _mapsManagers.push_back(mapsManager);
    }


     //cout << "I END ADD GAUSS MAPS : " << id << endl;
}

unsigned int Scene::getCurrentMapsIndex() const
{
    return _currentIndex;
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
    shared_ptr<Texture> heightMap = MeshLoader::textureFromMNT(filepaths);
    _mountains = MeshLoader::vertexFromHeightMap(heightMap->getDataRED(),heightMap->getWidth(),heightMap->getHeight(),heightMap->meshOffset());

    shared_ptr<MapsManager> mapsManager = make_shared<MapsManager>();

    mapsManager->maps = make_shared<Maps>(_genShaders,heightMap,_mountains->getYmin(),_mountains->getYmax());
    mapsManager->ID = 0;
    mapsManager->enabled = true;
/*
    cout << "Generate heightMap ..." << endl;
    shared_ptr<Texture> heightMapG = computeGenHeightMap();
    heightMapG->setMeshOffset(1.0);
    _generatedMaps = make_shared<Maps>(_genShaders,heightMapG);


    _loadedMapsGauss = make_shared<Maps>(_genShaders,heightMapL->getWidth(),heightMapL->getHeight());
    _generatedMapsGauss = make_shared<Maps>(_genShaders,heightMapG->getWidth(),heightMapG->getHeight());
*/
    _mountains = MeshLoader::vertexFromHeightMap(heightMap->getDataRED(),heightMap->getWidth(),heightMap->getHeight(),heightMap->meshOffset());
    mapsManager->maps->setNormalMap(_mountains->getNormalMapZUp());
    _mapsManagers.push_back(mapsManager);
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



/*
void Scene::initializeHeightMapGauss(shared_ptr<HeightMapGauss> gauss, shared_ptr<Texture> refHeightMap){

    gauss->gaussMap = make_shared<GeneratedTexture>(_HEIGHTMAPNAME,refHeightMap->getWidth(),refHeightMap->getHeight(),_genShaders->gaussBlurShader);
    gauss->interGaussMap = make_shared<GeneratedTexture>("interGaussMap",refHeightMap->getWidth(),refHeightMap->getHeight(),_genShaders->gaussBlurShader);

    gauss->gaussMap->initialize();
    gauss->interGaussMap->initialize();

    gauss->gaussMap->setMeshOffset(refHeightMap->meshOffset());

}
*/
/*
shared_ptr<Texture> Scene::computeGenHeightMap(){
    HeightMap heightMap = HeightMap(_HEIGHTMAPNAME, _WIDTHGENTEX,_HEIGHTGENTEX);
    heightMap.initialize();
    heightMap.startGenerate();
    vector<float> data = heightMap.generate(_widthViewport,_heightViewport);
    return make_shared<LoadTexture>(_HEIGHTMAPNAME, data,GL_R32F,   GL_RED, _WIDTHGENTEX,_HEIGHTGENTEX);
}

*/



/*
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

}*/
/*
void Scene::majCurrentMap()
{
    switch(_typeMeshUsed){
        case LOADED:            _currentMaps = _loadedMaps;         break;
        case GAUSSLOADED :      _currentMaps = _loadedMapsGauss;    break;
        case GENERATED :        _currentMaps = _generatedMaps;      break;
        case GAUSSGENERATED :   _currentMaps = _generatedMapsGauss; break;
    }
}
*/


std::shared_ptr<Scene::MapsManager> Scene::findFromID(unsigned int id){

    for(shared_ptr<MapsManager> m : _mapsManagers){
        if(m->ID == id){
            return m;
        }
    }
    cerr << "ERROR in findFromID , unknow ID: " << id << endl;
    return nullptr;
}

void Scene::printMapsManagers(){
    cout <<" Maps Managers :" << endl;
    for(shared_ptr<MapsManager> m : _mapsManagers){
        cout << "ID : " << m->ID << " enabled : " << m->enabled << endl;
    }
}


void Scene::initStackMaps(){
    for(int i=0 ; i < 10 ; i++){
        std::shared_ptr<Maps> m =  make_shared<Maps>(_genShaders,_mountains->getWidth(),_mountains->getHeight(),_mountains->getYmin(),_mountains->getYmax());
        _supplyMaps.push_back(m);
    }
}

std::shared_ptr<Maps> Scene::getMapsFromSupply(){
    if(_supplyMaps.size()<=0){
        cerr << "No Maps anymore, the supply maps is empty" << endl;
        return nullptr;
    }
    std::shared_ptr<Maps> m = _supplyMaps.back();
    _supplyMaps.pop_back();
    return m;
}
