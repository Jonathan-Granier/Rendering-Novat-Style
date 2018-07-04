#include "scene.h"

#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include "vertex.h"
#include "iostream"
#include "heightmap.h"

using namespace std;
using namespace glm;

Scene::Scene(int widthViewport,int heightViewport) :
    _plainColor(vec4(1.0,1.0,1.0,1.0)),
    _waterColor(vec4(0.694,0.78,0.902,1.0)),
    _currentIndex(0),
    _doShadow(false),
    _doEditShadeLightDir(true),
    _doEditShadowLightDir(true),
    _doShadowMorpo(true),
    _doDefaultShading(false),
    _shadeSelector(3),
    _colorSelector(0),
    _pitchLightShadow(M_PI/4.0)


{
    _viewportSize = make_shared<ViewportSize>();
    _viewportSize->width = widthViewport;
    _viewportSize->height = heightViewport;

    _reloadEditHeightMap = true;
    initializeGenShader();
    initializeTexture();
    //InitializeGenMaps();
    initStackMaps();

    _meshSphere = MeshLoader::vertexFromObj("../models/sphere.obj");
}



void Scene::createScene(const vector<string> &filepaths){
    cout << "Create New Scene" << endl;

    if(filepaths.empty()){

        cout << "generate heightMap ... " << endl;
        shared_ptr<Texture> heightMap = computeGenHeightMap();
        heightMap->setMeshOffset(1.0);
        initializeMaps(heightMap);
    }
    else{
        cout << "Loading MNT from : " << endl;
        for(unsigned int i=0;i< filepaths.size() ; i++ ){
            cout << filepaths[i] << "..." << endl;
        }
        shared_ptr<Texture> heightMap = MeshLoader::textureFromMNT(filepaths);
        initializeMaps(heightMap);
    }





    for(shared_ptr<MapsManager> m : _mapsManagers){
        if(m->ID!=0)
            m->maps->create(_mountains->getWidth(),_mountains->getHeight(),_mountains->getYmin(),_mountains->getYmax());
    }

   _reloadEditHeightMap = true;
}



void Scene::draw(shared_ptr<Shader> shader, vec3 lightDirection){


    _mapsManagers[_currentIndex]->maps->sendShadingMap(shader);
    _mapsManagers[_currentIndex]->maps->sendNormalMapToShader(shader);
    _mapsManagers[_currentIndex]->maps->sendShadeLightMapToShader(shader);
    _mapsManagers[_currentIndex]->maps->sendMergeShadowMap(shader);
    _mapsManagers[_currentIndex]->maps->sendHeightMapToShader(shader);
    shader->setFloat("ymax",_mountains->getYmax());
    shader->setFloat("ymin",_mountains->getYmin());



    _colorMapTex->sendToShader(shader);
    _celShadingTex->sendToShader(shader);
    shader->setVec4("plainColor",_plainColor);
    shader->setVec4("waterColor",_waterColor);
    shader->setInt("colorSelector",_colorSelector);


    shader->setBool("doShadow",_doShadow);
    shader->setBool("doDefaultShading",_doDefaultShading);
    shader->setVec3("lightDirection",lightDirection);


    mat4 modelMesh;
    shader->setMat4("modelMat",modelMesh);
    _mountains->draw();
    mat4 modelSphere;
    modelSphere = glm::translate(modelSphere,lightDirection*_mountains->getRadius());
    modelSphere = glm::scale(modelSphere,vec3(_mountains->getRadius()/20.0,_mountains->getRadius()/20.0,_mountains->getRadius()/20.0));
    shader->setMat4("modelMat",modelSphere);
    _meshSphere->draw();




    glActiveTexture(GL_TEXTURE0);
}

void Scene::drawOnlyMesh(){
    _mountains->draw();
}

void Scene::drawHeightMap(shared_ptr<Shader> shader){               _mapsManagers[_currentIndex]->maps->drawHeightMap(shader);}
void Scene::drawEditHeightMap(shared_ptr<Shader> shader){           _mapsManagers[_currentIndex]->maps->drawEditHeightMap(shader);}
void Scene::drawNormalMap(shared_ptr<Shader> shader){               _mapsManagers[_currentIndex]->maps->drawNormalMap(shader); }
void Scene::drawSlantMap(shared_ptr<Shader> shader){                _mapsManagers[_currentIndex]->maps->drawSlantMap(shader);}
void Scene::drawShadeLightMap(std::shared_ptr<Shader> shader){      _mapsManagers[_currentIndex]->maps->drawShadeLightMap(shader); }
void Scene::drawShadowLightMap(std::shared_ptr<Shader> shader){     _mapsManagers[_currentIndex]->maps->drawShadowLightMap(shader); }
void Scene::drawShadowMap(std::shared_ptr<Shader> shader){          _mapsManagers[_currentIndex]->maps->drawShadowMap(shader);}
void Scene::drawMorphoErosionMap(std::shared_ptr<Shader> shader){   _mapsManagers[_currentIndex]->maps->drawMorphoErosionMap(shader);}
void Scene::drawMorphoDilationMap(std::shared_ptr<Shader> shader){  _mapsManagers[_currentIndex]->maps->drawMorphoDilationMap(shader);}
void Scene::drawMergeShadowMap(std::shared_ptr<Shader> shader){     _mapsManagers[_currentIndex]->maps->drawMergeShadowMap(shader);}
void Scene::drawShadingMap(std::shared_ptr<Shader> shader){         _mapsManagers[_currentIndex]->maps->drawShadingMap(shader);}

void Scene::drawAsciiTex(std::shared_ptr<Shader> shader)
{
    _asciiTex->sendToShader(shader);
}


void Scene::generateGaussHeightMap(){
    bool firstMap = true;
    unsigned int previousI = 0;
    for(unsigned int i = 0; i < _mapsManagers.size(); i++)
    {
        if(_mapsManagers[i]->enabled){
            if(!firstMap)
                _mapsManagers[i]->maps->generateHeightMap(_mapsManagers[previousI]->maps->getHeightMap());
            previousI = i;
            firstMap = false;
        }
    }

}


void Scene::generateEditHeightAndNormalMap(){


    bool lastMap = true;
    shared_ptr<Texture> nextHeightMap;
    if(_reloadEditHeightMap){
        for(int i = _mapsManagers.size()-1; i >=0 ; i--){
            if(_mapsManagers[i]->enabled){
                _mapsManagers[i]->maps->generateEditHeightMap(nextHeightMap,lastMap);
                lastMap = false;
                _mapsManagers[i]->maps->generateNormalMap();
                nextHeightMap = _mapsManagers[i]->maps->getHeightMap();
            }
        }
        _reloadEditHeightMap = false;
    }

}


void Scene::generateSlantLightAndParalaxMaps(glm::mat4 mdvMat, glm::mat3 normalMat,glm::vec3 lightPos, float pitch, float yaw){

    bool firstMap = true;
    int i;
    std::shared_ptr<Texture>       previousShadingMap;
    std::shared_ptr<Texture>       previousShadowMap;


    for(i=_mapsManagers.size()-1; i >= 0 ;i--){
        if(_mapsManagers[i]->enabled){
            _mapsManagers[i]->maps->generateNormalMap();
            _mapsManagers[i]->maps->generateSlantMap();

            _mapsManagers[i]->maps->generateShadeLightMap(lightPos,pitch,yaw,_doEditShadeLightDir);
            _mapsManagers[i]->maps->generateShadowLightMap(lightPos,_pitchLightShadow,yaw,_doEditShadowLightDir);
            if(_doShadow){
                _mapsManagers[i]->maps->generateShadowMap();
                _mapsManagers[i]->maps->generateMorphoDilationMap(_doShadowMorpo);
                _mapsManagers[i]->maps->generateMorphoErosionMap(_doShadowMorpo);
                _mapsManagers[i]->maps->generateMergeShadowMap(previousShadowMap,firstMap);
                previousShadowMap      = _mapsManagers[i]->maps->getMorphoErosionMap();
            }
            _mapsManagers[i]->maps->generateShadingMap(mdvMat,normalMat,previousShadingMap,firstMap,_shadeSelector);
            firstMap = false;
            previousShadingMap     = _mapsManagers[i]->maps->getShadingMap();
        }
    }

}


void Scene::reloadGenerateTexturesShader(){
    _genShaders->editHeightMapShader->reload();
    _genShaders->normalMapShader->reload();
    _genShaders->slantShader->reload();
    _genShaders->shadeLightShader->reload();
    _genShaders->shadowLightShader->reload();
    _genShaders->gaussBlurShader->reload();
    _genShaders->shadowShader->reload();
    _genShaders->morphoShader->reload();
    _genShaders->mergeShadowShader->reload();
    _genShaders->shadingShader->reload();
    _reloadEditHeightMap = true;
}





vec3 Scene::getCenter() const
{
    return _mountains->getCenter();
}


float Scene::getRadius() const
{
    return _mountains->getRadius();
}

// TODO Voir le lien entre Id et index si il est constant et adapter le code en fonction (plus de fonction supprimé)
void Scene::selectCurrentMaps(int id)
{
    if(_mapsManagers[id]->enabled)
        _currentIndex = id;
}



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
    _reloadEditHeightMap = true;
}

void Scene::reloadGaussHeightMap()
{
    for(shared_ptr<MapsManager> m : _mapsManagers){
        if(m->ID != 0){
            m->maps->reloadHeightMap();
        }
    }
    _reloadEditHeightMap = true;
}

void Scene::addGaussMaps(unsigned int id, bool enabled)
{
    if(id == 0){
        cerr << "Can't add a new GaussMaps with id = 0" << endl;
        return;
    }

    std::shared_ptr<Maps> maps = getMapsFromSupply();
    if(maps!=nullptr){
        maps->create(_mountains->getWidth(),_mountains->getHeight(),_mountains->getYmin(),_mountains->getYmax());
        std::shared_ptr<MapsManager> mapsManager = make_shared<MapsManager>();
        mapsManager->maps = maps;
        mapsManager->enabled = enabled;
        mapsManager->ID = id;
        _mapsManagers.push_back(mapsManager);
    }

    _reloadEditHeightMap = true;
}

unsigned int Scene::getCurrentMapsIndex() const
{
    return _currentIndex;
}



void Scene::setDoShadow(bool doShadow)
{
    _doShadow = doShadow;
}







void Scene::setShadeSelector(int s){
    _shadeSelector = s;
}

void Scene::setPitchLightShadow(float pitchLightShadow)
{
    _pitchLightShadow = pitchLightShadow;
}

void Scene::setDoEditShadeLightDir(bool doEditShadeLightDir)
{
    _doEditShadeLightDir = doEditShadeLightDir;
}

void Scene::setDoEditShadowLightDir(bool doEditShadowLightDir)
{
    _doEditShadowLightDir = doEditShadowLightDir;
}

void Scene::setDoShadowMorpo(bool doShadowMorpo)
{
    _doShadowMorpo = doShadowMorpo;
}

void Scene::setPlainColor(const glm::vec4 &plainColor)
{
    _plainColor = plainColor;
}

glm::vec4 Scene::getPlainColor() const
{
    return _plainColor;
}


void Scene::setWaterColor(const glm::vec4 &waterColor)
{
    _waterColor = waterColor;

}


glm::vec4 Scene::getWaterColor() const
{
    return _waterColor;
}




void Scene::loadColorMapTex(std::string filepaths){
    _colorMapTex    = make_shared<LoadTexture>("colorMapTex",filepaths);

}

void Scene::loadCelShadingTex(std::string filepaths){
    _celShadingTex  = make_shared<LoadTexture>("celShadingTex",filepaths);
}

void Scene::setColorSelector(int colorSelector)
{
    _colorSelector = colorSelector;
}

void Scene::setDoDefaultShading(bool doDefaultShading)
{
    _doDefaultShading = doDefaultShading;
}


/************************************************
 *              Private Functions               *
 ************************************************/




void Scene::initializeGenShader(){
    _genShaders = make_shared<GenShaders>();
    _genShaders->editHeightMapShader        = make_shared<Shader>("../shaders/editheightmap.vert","../shaders/editheightmap.frag");
    _genShaders->normalMapShader            = make_shared<Shader>("../shaders/normalmap.vert","../shaders/normalmap.frag");
    _genShaders->slantShader                = make_shared<Shader>("../shaders/slant.vert","../shaders/slant.frag");
    _genShaders->shadeLightShader           = make_shared<Shader>("../shaders/shadelight.vert","../shaders/shadelight.frag");
    _genShaders->shadowLightShader          = make_shared<Shader>("../shaders/shadowlight.vert","../shaders/shadowlight.frag");
    _genShaders->gaussBlurShader            = make_shared<Shader>("../shaders/gaussBlur.vert","../shaders/gaussBlur.frag");
    _genShaders->shadowShader               = make_shared<Shader>("../shaders/shadowmap.vert","../shaders/shadowmap.frag");
    _genShaders->morphoShader               = make_shared<Shader>("../shaders/morpho.vert","../shaders/morpho.frag");
    _genShaders->mergeShadowShader          = make_shared<Shader>("../shaders/mergeshadow.vert","../shaders/mergeshadow.frag");
    _genShaders->shadingShader              = make_shared<Shader>("../shaders/shading.vert","../shaders/shading.frag");
}


void Scene::initializeMaps(std::shared_ptr<Texture> heightMap){

        _mountains = MeshLoader::vertexFromHeightMap(heightMap->getDataRED(),heightMap->getWidth(),heightMap->getHeight(),heightMap->getMeshOffset());
       // _mountains->printNormal();
        shared_ptr<MapsManager> mapsManager = make_shared<MapsManager>();
        mapsManager->maps = getMapsFromSupply();
        mapsManager->maps->create(heightMap,heightMap->getWidth(),heightMap->getHeight(),_mountains->getYmin(),_mountains->getYmax());
        mapsManager->ID = 0;
        mapsManager->enabled = true;
        if(_mapsManagers.empty())
            _mapsManagers.push_back(mapsManager);
        else
            _mapsManagers[0] = mapsManager;
}




shared_ptr<Texture> Scene::computeGenHeightMap(){
    HeightMap heightMap = HeightMap("heightMap",1024,1024);
    heightMap.initialize();
    heightMap.startGenerate();
    vector<float> data = heightMap.generate(_viewportSize->width,_viewportSize->height);
    return make_shared<LoadTexture>("heightMap", data,GL_R32F,   GL_RED,1024 ,1024);
}



void Scene::initializeTexture(){
    _asciiTex       = make_shared<LoadTexture>("asciiTex","../textures/ASCII_Debug.png");
    _celShadingTex  = make_shared<LoadTexture>("celShadingTex","../textures/cel_shading.png");
    _colorMapTex    = make_shared<LoadTexture>("colorMapTex","../textures/novat_moyenne_altitude.png");
}





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
        std::shared_ptr<Maps> m =  make_shared<Maps>(_genShaders,_viewportSize);
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
