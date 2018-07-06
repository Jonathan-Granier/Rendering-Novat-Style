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

    initializeGenShader();
    initializeTexture();
    initStackScale();

    _meshSphere = MeshLoader::vertexFromObj("../ressources/models/sphere.obj");
}



void Scene::createScene(const vector<string> &filepaths){
    cout << "Create New Scene" << endl;

    if(filepaths.empty()){

        cout << "generate heightMap ... " << endl;
        shared_ptr<Texture> heightMap = computeGenHeightMap();
        heightMap->setHeightMapOffset(1.0);
        initializeScale(heightMap);
    }
    else{
        cout << "Loading MNT from : " << endl;
        for(unsigned int i=0;i< filepaths.size() ; i++ ){
            cout << filepaths[i] << "..." << endl;
        }
        shared_ptr<Texture> heightMap = MeshLoader::textureFromMNT(filepaths);
        initializeScale(heightMap);
    }

    for(shared_ptr<ScaleManager> m : _scaleManagers){
        if(m->ID!=0)
            m->scale->create(_mountains->getWidth(),_mountains->getHeight(),_mountains->getYmin(),_mountains->getYmax());
    }

   _doReloadLaplacienPyramid = true;
}



void Scene::draw(shared_ptr<Shader> shader, vec3 lightDirection){


    _scaleManagers[_currentIndex]->scale->sendShadingMap(shader);
    _scaleManagers[_currentIndex]->scale->sendNormalMapToShader(shader);
    _scaleManagers[_currentIndex]->scale->sendShadeLightMapToShader(shader);
    _scaleManagers[_currentIndex]->scale->sendMergeShadowMap(shader);
    _scaleManagers[_currentIndex]->scale->sendHeightMapToShader(shader);
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


    mat4 modelMesh = mat4(1.0);
    shader->setMat4("modelMat",modelMesh);
    _mountains->draw();

    mat4 modelSphere = mat4(1.0);
    modelSphere = glm::translate(modelSphere,lightDirection*_mountains->getRadius());
    modelSphere = glm::scale(modelSphere,vec3(_mountains->getRadius()/20.0,_mountains->getRadius()/20.0,_mountains->getRadius()/20.0));
    shader->setMat4("modelMat",modelSphere);
    _meshSphere->draw();




    glActiveTexture(GL_TEXTURE0);
}


void Scene::drawHeightMap(shared_ptr<Shader> shader){               _scaleManagers[_currentIndex]->scale->drawHeightMap(shader);}
void Scene::drawEditHeightMap(shared_ptr<Shader> shader){           _scaleManagers[_currentIndex]->scale->drawEditHeightMap(shader);}
void Scene::drawNormalMap(shared_ptr<Shader> shader){               _scaleManagers[_currentIndex]->scale->drawNormalMap(shader); }
void Scene::drawSlantMap(shared_ptr<Shader> shader){                _scaleManagers[_currentIndex]->scale->drawSlantMap(shader);}
void Scene::drawShadeLightMap(std::shared_ptr<Shader> shader){      _scaleManagers[_currentIndex]->scale->drawShadeLightMap(shader); }
void Scene::drawShadowLightMap(std::shared_ptr<Shader> shader){     _scaleManagers[_currentIndex]->scale->drawShadowLightMap(shader); }
void Scene::drawShadowMap(std::shared_ptr<Shader> shader){          _scaleManagers[_currentIndex]->scale->drawShadowMap(shader);}
void Scene::drawMorphoErosionMap(std::shared_ptr<Shader> shader){   _scaleManagers[_currentIndex]->scale->drawMorphoErosionMap(shader);}
void Scene::drawMorphoDilationMap(std::shared_ptr<Shader> shader){  _scaleManagers[_currentIndex]->scale->drawMorphoDilationMap(shader);}
void Scene::drawMergeShadowMap(std::shared_ptr<Shader> shader){     _scaleManagers[_currentIndex]->scale->drawMergeShadowMap(shader);}
void Scene::drawShadingMap(std::shared_ptr<Shader> shader){         _scaleManagers[_currentIndex]->scale->drawShadingMap(shader);}

void Scene::drawAsciiTex(std::shared_ptr<Shader> shader)
{
    _asciiTex->sendToShader(shader);
}




void Scene::generateLaplacienPyramid(){
    if(_doReloadLaplacienPyramid){

        // The gauss Blur
        bool firstMap = true;
        unsigned int previousI = 0;
        for(unsigned int i = 0; i < _scaleManagers.size(); i++)
        {
            if(_scaleManagers[i]->enabled){
                if(!firstMap)
                    _scaleManagers[i]->scale->generateHeightMap(_scaleManagers[previousI]->scale->getHeightMap());
                previousI = i;
                firstMap = false;
            }
        }
        // The difference
        bool lastMap = true;
        shared_ptr<Texture> nextHeightMap;
        for(int i = _scaleManagers.size()-1; i >=0 ; i--){
            if(_scaleManagers[i]->enabled){
                _scaleManagers[i]->scale->generateEditHeightMap(nextHeightMap,lastMap);
                lastMap = false;
                _scaleManagers[i]->scale->generateNormalMap();
                _scaleManagers[i]->scale->generateSlantMap();
                nextHeightMap = _scaleManagers[i]->scale->getHeightMap();
            }
        }
        _doReloadLaplacienPyramid = false;

    }
}

void Scene::generateIntermediateScale(glm::mat4 mdvMat, glm::mat3 normalMat,glm::vec3 lightDir, float pitch, float yaw){

    bool firstMap = true;
    int i;
    std::shared_ptr<Texture>       previousShadingMap;
    std::shared_ptr<Texture>       previousShadowMap;


    for(i=_scaleManagers.size()-1; i >= 0 ;i--){
        if(_scaleManagers[i]->enabled){

            _scaleManagers[i]->scale->generateShadeLightMap(lightDir,pitch,yaw,_doEditShadeLightDir);
            _scaleManagers[i]->scale->generateShadowLightMap(lightDir,_pitchLightShadow,yaw,_doEditShadowLightDir);
            if(_doShadow){
                _scaleManagers[i]->scale->generateShadowMap();
                _scaleManagers[i]->scale->generateMorphoDilationMap(_doShadowMorpo);
                _scaleManagers[i]->scale->generateMorphoErosionMap(_doShadowMorpo);
                _scaleManagers[i]->scale->generateMergeShadowMap(previousShadowMap,firstMap);
                previousShadowMap      = _scaleManagers[i]->scale->getMorphoErosionMap();
            }
            _scaleManagers[i]->scale->generateShadingMap(mdvMat,normalMat,previousShadingMap,firstMap,_shadeSelector);
            firstMap = false;
            previousShadingMap     = _scaleManagers[i]->scale->getShadingMap();
        }
    }

}

void Scene::addScale(unsigned int id, bool enabled)
{
    if(id == 0){
        cerr << "Can't add a new GaussScale with id = 0" << endl;
        return;
    }

    std::shared_ptr<Scale> scale = getScaleFromSupply();
    if(scale!=nullptr){
        scale->create(_mountains->getWidth(),_mountains->getHeight(),_mountains->getYmin(),_mountains->getYmax());
        std::shared_ptr<ScaleManager> scaleManager = make_shared<ScaleManager>();
        scaleManager->scale = scale;
        scaleManager->enabled = enabled;
        scaleManager->ID = id;
        _scaleManagers.push_back(scaleManager);
    }

    _doReloadLaplacienPyramid = true;
}


void Scene::reloadLaplacienPyramid()
{
    _doReloadLaplacienPyramid = true;
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
    _doReloadLaplacienPyramid = true;
}



void Scene::loadColorMapTex(std::string filepaths){
    _colorMapTex    = make_shared<LoadTexture>("colorMapTex",filepaths);

}

void Scene::loadCelShadingTex(std::string filepaths){
    _celShadingTex  = make_shared<LoadTexture>("celShadingTex",filepaths);
}



vec3 Scene::getCenter() const
{
    return _mountains->getCenter();
}


float Scene::getRadius() const
{
    return _mountains->getRadius();
}


void Scene::selectCurrentScale(int id)
{
    if(_scaleManagers[id]->enabled)
        _currentIndex = id;
}

unsigned int Scene::getCurrentScaleIndex() const
{
    return _currentIndex;
}


void Scene::setLightThreshold(unsigned int id, float t)
{
    findFromID(id)->scale->setLightThreshold(t);
}

void Scene::setGaussBlurFactor(unsigned int id ,int g)
{
    findFromID(id)->scale->setGaussBlurFactor(g);
}

void Scene::setEnabledScale(unsigned int id, bool enabled){
    findFromID(id)->enabled = enabled;
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
    _genShaders->editHeightMapShader        = make_shared<Shader>("../sources_code/shaders/editheightmap.vert","../sources_code/shaders/editheightmap.frag");
    _genShaders->normalMapShader            = make_shared<Shader>("../sources_code/shaders/normalmap.vert","../sources_code/shaders/normalmap.frag");
    _genShaders->slantShader                = make_shared<Shader>("../sources_code/shaders/slant.vert","../sources_code/shaders/slant.frag");
    _genShaders->shadeLightShader           = make_shared<Shader>("../sources_code/shaders/shadelight.vert","../sources_code/shaders/shadelight.frag");
    _genShaders->shadowLightShader          = make_shared<Shader>("../sources_code/shaders/shadowlight.vert","../sources_code/shaders/shadowlight.frag");
    _genShaders->gaussBlurShader            = make_shared<Shader>("../sources_code/shaders/gaussBlur.vert","../sources_code/shaders/gaussBlur.frag");
    _genShaders->shadowShader               = make_shared<Shader>("../sources_code/shaders/shadowmap.vert","../sources_code/shaders/shadowmap.frag");
    _genShaders->morphoShader               = make_shared<Shader>("../sources_code/shaders/morpho.vert","../sources_code/shaders/morpho.frag");
    _genShaders->mergeShadowShader          = make_shared<Shader>("../sources_code/shaders/mergeshadow.vert","../sources_code/shaders/mergeshadow.frag");
    _genShaders->shadingShader              = make_shared<Shader>("../sources_code/shaders/shading.vert","../sources_code/shaders/shading.frag");
}


void Scene::initializeScale(std::shared_ptr<Texture> heightMap){

        _mountains = MeshLoader::vertexFromHeightMap(heightMap->getDataRED(),heightMap->getWidth(),heightMap->getHeight(),heightMap->getHeightMapOffset());
       // _mountains->printNormal();
        shared_ptr<ScaleManager> scaleManager = make_shared<ScaleManager>();
        scaleManager->scale = getScaleFromSupply();
        scaleManager->scale->create(heightMap,heightMap->getWidth(),heightMap->getHeight(),_mountains->getYmin(),_mountains->getYmax());
        scaleManager->ID = 0;
        scaleManager->enabled = true;
        if(_scaleManagers.empty())
            _scaleManagers.push_back(scaleManager);
        else
            _scaleManagers[0] = scaleManager;
}




shared_ptr<Texture> Scene::computeGenHeightMap(){
    HeightMap heightMap = HeightMap("heightMap",1024,1024);
    heightMap.initialize();
    heightMap.startGenerate();
    vector<float> data = heightMap.generate(_viewportSize->width,_viewportSize->height);
    return make_shared<LoadTexture>("heightMap", data,GL_R32F,   GL_RED,1024 ,1024);
}



void Scene::initializeTexture(){
    _asciiTex       = make_shared<LoadTexture>("asciiTex","../ressources/textures/ASCII_Debug.png");
    _celShadingTex  = make_shared<LoadTexture>("celShadingTex","../ressources/textures/cel_shading.png");
    _colorMapTex    = make_shared<LoadTexture>("colorMapTex","../ressources/textures/novat_moyenne_altitude.png");
}





std::shared_ptr<Scene::ScaleManager> Scene::findFromID(unsigned int id){

    for(shared_ptr<ScaleManager> m : _scaleManagers){
        if(m->ID == id){
            return m;
        }
    }
    cerr << "ERROR in findFromID , unknow ID: " << id << endl;
    return nullptr;
}

void Scene::printScaleManagers(){
    cout <<" Scale Managers :" << endl;
    for(shared_ptr<ScaleManager> m : _scaleManagers){
        cout << "ID : " << m->ID << " enabled : " << m->enabled << endl;
    }
}


void Scene::initStackScale(){
    for(int i=0 ; i < 10 ; i++){
        std::shared_ptr<Scale> m =  make_shared<Scale>(_genShaders,_viewportSize);
        _supplyScale.push_back(m);
    }
}

std::shared_ptr<Scale> Scene::getScaleFromSupply(){
    if(_supplyScale.size()<=0){
        cerr << "No Scale anymore, the supply scale is empty" << endl;
        return nullptr;
    }
    std::shared_ptr<Scale> m = _supplyScale.back();
    _supplyScale.pop_back();
    return m;
}
