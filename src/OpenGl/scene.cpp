#include "scene.h"

#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include "vertex.h"
#include "iostream"
#include "heightmap.h"

using namespace std;
using namespace glm;

Scene::Scene(int widthViewport,int heightViewport) :
    _currentIndex(0),
    _typeShading(0),
    _doShadow(false),
    _shadeSelector(0),
    _widthViewport(widthViewport),
    _heightViewport(heightViewport)
{
    _reloadEditHeightMap = true;
    initializeGenShader();
    initializeTexture();
    //initializeGenMaps();
    initStackMaps();
    _typeMerge = NONE;

    _meshSphere = MeshLoader::vertexFromObj("models/sphere.obj");
}



void Scene::createScene(const vector<string> &filepaths){
    cout << "Create New Scene" << endl;

    if(filepaths.empty()){

        cout << "Generate heightMap ... " << endl;
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



void Scene::draw(shared_ptr<Shader> shader, vec3 lightPosition){


    //cout << "I Draw id :" << _currentIndex << endl;
    //printMapsManagers();
    _mapsManagers[_currentIndex]->maps->sendShadingMap(shader);
    _mapsManagers[_currentIndex]->maps->sendNormalMapToShader(shader);
    _mapsManagers[_currentIndex]->maps->sendShadeLightMapToShader(shader);
    _mapsManagers[_currentIndex]->maps->sendParallaxMap(shader);

    for(unsigned int i=0;i<_textures.size();i++){
        _textures[i]->sendToShader(shader);
    }


    shader->setInt("typeShading",_typeShading);
    shader->setBool("doShadow",_doShadow);
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
void Scene::drawEditHeightMap(shared_ptr<Shader> shader){       _mapsManagers[_currentIndex]->maps->drawEditHeightMap(shader);}
void Scene::drawNormalMap(shared_ptr<Shader> shader){           _mapsManagers[_currentIndex]->maps->drawNormalMap(shader); }
void Scene::drawSlantMap(shared_ptr<Shader> shader){            _mapsManagers[_currentIndex]->maps->drawSlantMap(shader);}
void Scene::drawShadeLightMap(std::shared_ptr<Shader> shader){  _mapsManagers[_currentIndex]->maps->drawShadeLightMap(shader); }
void Scene::drawShadowLightMap(std::shared_ptr<Shader> shader){ _mapsManagers[_currentIndex]->maps->drawShadowLightMap(shader); }
void Scene::drawParallaxMap(std::shared_ptr<Shader> shader){    _mapsManagers[_currentIndex]->maps->drawParallaxMap(shader);}
void Scene::drawShadingMap(std::shared_ptr<Shader> shader){     _mapsManagers[_currentIndex]->maps->drawShadingMap(shader);}


void Scene::drawAsciiTex(std::shared_ptr<Shader> shader)
{
    _asciiTex->sendToShader(shader);
}


void Scene::generateGaussHeightMap(){
    for(shared_ptr<MapsManager> m:_mapsManagers){
        if(m->ID != 0){
            m->maps->generateHeightMap(_widthViewport,_heightViewport,_mapsManagers[0]->maps->getHeightMap());
        }
    }
}


void Scene::generateEditHeightAndNormalMap(){


    bool firstMap = true;
    shared_ptr<Texture> previousHeightMap;
    if(_reloadEditHeightMap){
        cout << "I generate NormalMap " << endl;
        for(int i = _mapsManagers.size()-1; i >=0 ; i--){
            if(_mapsManagers[i]->enabled){
                _mapsManagers[i]->maps->generateEditHeightMap(_widthViewport,_heightViewport,previousHeightMap,firstMap);
                firstMap = false;
                _mapsManagers[i]->maps->generateNormalMap(_widthViewport,_heightViewport);
                previousHeightMap = _mapsManagers[i]->maps->getEditHeightMap();
            }
        }
        _reloadEditHeightMap = false;
    }

}


void Scene::generateSlantLightAndParalaxMaps(glm::mat4 mdvMat, glm::mat3 normalMat,glm::vec3 lightPos, float pitch, float yaw){

    bool firstMap = true;
    int i;
    std::shared_ptr<LightTextures> previousShadeLightMap;
    std::shared_ptr<LightTextures> previousShadowLightMap;
    std::shared_ptr<Texture>       previousShadingMap;

    bool none = false;
    bool doMergeLight = false;
    bool doMergeShade = false;


    switch(_typeMerge){
    case NONE:
        none = true;
        break;
    case LIGHT:
        doMergeLight = true;
        break;
    case SHADE:
        doMergeShade = true;
        break;
    }




    for(i=_mapsManagers.size()-1; i>=0;i--){
        if(_mapsManagers[i]->enabled){
            _mapsManagers[i]->maps->generateNormalMap(_widthViewport,_heightViewport);
            _mapsManagers[i]->maps->generateSlantMap(_widthViewport,_heightViewport);
            if(firstMap){
                _mapsManagers[i]->maps->generateShadeLightMap(_widthViewport,_heightViewport,lightPos,pitch,yaw,none);
                _mapsManagers[i]->maps->generateShadowLightMap(_widthViewport,_heightViewport,lightPos,pitch,yaw);
            }
            else{
                _mapsManagers[i]->maps->generateShadeLightMap(_widthViewport,_heightViewport,previousShadeLightMap,pitch,doMergeLight,none);
                _mapsManagers[i]->maps->generateShadowLightMap(_widthViewport,_heightViewport,previousShadowLightMap,pitch);
            }
            _mapsManagers[i]->maps->generateParallaxMap(_widthViewport,_heightViewport,lightPos);
            _mapsManagers[i]->maps->generateShadingMap(_widthViewport,_heightViewport,mdvMat,normalMat,lightPos,_typeShading,previousShadingMap,firstMap,doMergeShade,_shadeSelector);
            firstMap = false;
            previousShadeLightMap  = _mapsManagers[i]->maps->getShadeLightMap();
            previousShadowLightMap = _mapsManagers[i]->maps->getShadowLightMap();
            previousShadingMap     = _mapsManagers[i]->maps->getShadingMap();
        }
    }

}


void Scene::reloadGenerateTexturesShader(){
    _genShaders->editHeightMapShader->reload();
    _genShaders->normalMapShader->reload();
    _genShaders->slantShader->reload();
    _genShaders->curvatureShader->reload();
    _genShaders->correctCurvatureShader->reload();
    _genShaders->shadeLightShader->reload();
    _genShaders->shadowLightShader->reload();
    _genShaders->gaussBlurShader->reload();
    _genShaders->parallaxShader->reload();
    _genShaders->shadingShader->reload();
    _reloadEditHeightMap = true;
}





vec3 Scene::center() const
{
    return _mountains->center();
}


float Scene::radius() const
{
    return _mountains->radius();
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

void Scene::setTypeShading(int typeShading)
{
    _typeShading = typeShading;
}

void Scene::setDoShadow(bool doShadow)
{
    _doShadow = doShadow;
}





void Scene::setTypeMerge(int t){
    switch(t){
    case 0 : _typeMerge = NONE; break;
    case 1 : _typeMerge = LIGHT; break;
    case 2 : _typeMerge = SHADE; break;
    }

}

void Scene::setShadeSelector(int s){
    _shadeSelector = s;
}


/************************************************
 *              Private Functions               *
 ************************************************/




void Scene::initializeGenShader(){
    _genShaders = make_shared<GenShaders>();
    _genShaders->editHeightMapShader        = make_shared<Shader>("shaders/editheightmap.vert","shaders/editheightmap.frag");
    _genShaders->normalMapShader            = make_shared<Shader>("shaders/normalmap.vert","shaders/normalmap.frag");
    _genShaders->slantShader                = make_shared<Shader>("shaders/slant.vert","shaders/slant.frag");
    _genShaders->curvatureShader            = make_shared<Shader>("shaders/curvature.vert","shaders/curvature.frag");
    _genShaders->correctCurvatureShader     = make_shared<Shader>("shaders/correctcurvature.vert","shaders/correctcurvature.frag");
    _genShaders->shadeLightShader           = make_shared<Shader>("shaders/shadelight.vert","shaders/shadelight.frag");
    _genShaders->shadowLightShader          = make_shared<Shader>("shaders/shadowlight.vert","shaders/shadowlight.frag");
    _genShaders->gaussBlurShader            = make_shared<Shader>("shaders/gaussBlur.vert","shaders/gaussBlur.frag");
    _genShaders->parallaxShader             = make_shared<Shader>("shaders/parallax.vert","shaders/parallax.frag");
    _genShaders->shadingShader              = make_shared<Shader>("shaders/shading.vert","shaders/shading.frag");
}


void Scene::initializeMaps(std::shared_ptr<Texture> heightMap){

        _mountains = MeshLoader::vertexFromHeightMap(heightMap->getDataRED(),heightMap->getWidth(),heightMap->getHeight(),heightMap->meshOffset());

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
    vector<float> data = heightMap.generate(_widthViewport,_heightViewport);
    return make_shared<LoadTexture>("heightMap", data,GL_R32F,   GL_RED,1024 ,1024);
}



void Scene::initializeTexture(){
    shared_ptr<LoadTexture> texture1 = make_shared<LoadTexture>("container", "textures/container.jpg");
    shared_ptr<LoadTexture> texture2 = make_shared<LoadTexture>("awesomeface", "textures/awesomeface.png");
    shared_ptr<LoadTexture> texture3 = make_shared<LoadTexture>("neige_ombre", "textures/dégradé_neige_ombre.png");
    shared_ptr<LoadTexture> texture4 = make_shared<LoadTexture>("degrade_debug", "textures/dégradé_debug.png");
    shared_ptr<LoadTexture> texture5 = make_shared<LoadTexture>("flat_color_debug", "textures/flat_color.png");
    shared_ptr<LoadTexture> texture6 = make_shared<LoadTexture>("degrade_neige", "textures/degrade_neige.png");
    _asciiTex = make_shared<LoadTexture>("asciiTex","textures/ASCII_Debug.png");



    _textures.push_back(texture1);
    _textures.push_back(texture2);
    _textures.push_back(texture3);
    _textures.push_back(texture4);
    _textures.push_back(texture5);
    _textures.push_back(texture6);

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
        std::shared_ptr<Maps> m =  make_shared<Maps>(_genShaders);
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
