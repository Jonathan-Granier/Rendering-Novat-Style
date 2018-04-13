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
    _curvatureMapIsComputed(false),
    _lightSelector(0),
    _typeMeshUsed(typeMesh),
    _widthViewport(widthViewport),
    _heightViewport(heightViewport)

{
    MeshLoader ml;

    loadingWithLog(ml,filepaths);

    initialize();

    _meshSphere = ml.vertexFromObj("models/sphere.obj");

    _curvatureMap = make_shared<GeneratedTexture>("curvatureMap",_currentMesh->getWidth(),_currentMesh->getHeight(),
                                                  "shaders/curvature.vert","shaders/curvature.frag");

    _lightMap = make_shared<GeneratedTexture>("lightMap",_currentMesh->getWidth(),_currentMesh->getHeight(),
                                                  "shaders/generatelight.vert","shaders/generatelight.frag");

    _gaussBlur = make_shared<GeneratedTexture>("gaussBlur",_currentMesh->getWidth(),_currentMesh->getHeight(),
                                               "shaders/gaussBlur.vert","shaders/gaussBlur.frag");

    _curvatureMap->initialize();
    _lightMap->initialize();
    _gaussBlur->initialize();


    LoadTexture texture1("container", "textures/container.jpg");
    LoadTexture texture2("awesomeface", "textures/awesomeface.png");
    LoadTexture texture3("neige_ombre", "textures/dégradé_neige_ombre.png");
    LoadTexture texture4("degrade_debug", "textures/dégradé_debug.png");
    LoadTexture texture5("flat_color_debug", "textures/flat_color.png");

    _textures.push_back(texture1);
    _textures.push_back(texture2);
    _textures.push_back(texture3);
    _textures.push_back(texture4);
    _textures.push_back(texture5);


}






void Scene::draw(shared_ptr<Shader> shader, vec3 lightPosition){

    _lightMap->sendToShader(shader);

    for(unsigned int i=0;i<_textures.size();i++){
        _textures[i].sendToShader(shader);
    }

    mat4 modelMesh;

    shader->setMat4("modelMat",modelMesh);
    _currentMesh->Draw();
   // _meshPlane->Draw();
    mat4 modelSphere;
    modelSphere = glm::translate(modelSphere,lightPosition*_currentMesh->radius());
    modelSphere = glm::scale(modelSphere,vec3(_currentMesh->radius()/20.0,_currentMesh->radius()/20.0,_currentMesh->radius()/20.0));
    shader->setMat4("modelMat",modelSphere);
   _meshSphere->Draw();
    // always good practice to set everything back to defaults once configured.
    glActiveTexture(GL_TEXTURE0);
}

void Scene::drawOnlyMesh(){
    _currentMesh->Draw();
}

void Scene::drawHeightMap(shared_ptr<Shader> shader){

    if(_heightMap != NULL){
        shader->setInt("ymin",_currentMesh->getYmin());
        shader->setInt("ymax",_currentMesh->getYmax());
        _heightMap->draw(shader);
    }
}

void Scene::drawNormalMap(shared_ptr<Shader> shader){
    if(_normalMap != NULL){
        _normalMap->draw(shader);

    }
}

void Scene::drawCurvatureMap(shared_ptr<Shader> shader){
    if(_curvatureMap != NULL){
        _curvatureMap->draw(shader);

    }
}

void Scene::drawGaussBlur(shared_ptr<Shader> shader){
    if(_gaussBlur != NULL){
        _gaussBlur->draw(shader);
    }
}

void Scene::drawLightMap(std::shared_ptr<Shader> shader){
    if(_lightMap != NULL){
        _lightMap->draw(shader);

    }
}

void Scene::computeCurvatureMap(){
    if(!_curvatureMapIsComputed){

        _curvatureMap->startGenerate();
        _curvatureMap->generatorShader()->setFloat("sigma",_sigma);
        _normalMap->sendToShader(_curvatureMap->generatorShader());
        _curvatureMap->generate(_widthViewport,_heightViewport,0,0);
        _curvatureMapIsComputed = true;
    }
}



void Scene::computeLightMap(vec3 lightPosition, float lightYaw, float lightPitch){
    _lightMap->startGenerate();
    _lightMap->generatorShader()->setVec3("lightPosition",lightPosition);
    _lightMap->generatorShader()->setFloat("yaw",lightYaw);
    _lightMap->generatorShader()->setFloat("pitch",lightPitch);
    _lightMap->generatorShader()->setInt("lightSelector",_lightSelector);
    _lightMap->generatorShader()->setFloat("threshold",_lightThreshold);
    _curvatureMap->sendToShader(_lightMap->generatorShader());
    _lightMap->generate(_widthViewport,_heightViewport);
}


void Scene::reloadGenerateTexturesShader(){
    _curvatureMap->reloadShader();
    _lightMap->reloadShader();

    _curvatureMapIsComputed = false;

}









void Scene::switchTypeMeshUsed(){
    switch(_typeMeshUsed){
        case LOADED:
            _typeMeshUsed = GENERATED;



            break;
        case GENERATED:
            _typeMeshUsed = LOADED;
            break;
    }
    initialize();
    _curvatureMap->resize(_currentMesh->getWidth(),_currentMesh->getHeight());
    _lightMap->resize(_currentMesh->getWidth(),_currentMesh->getHeight());
    _gaussBlur->resize(_currentMesh->getWidth(),_currentMesh->getHeight());
}



vec3 Scene::center() const
{
    return _currentMesh->center();
}


float Scene::radius() const
{
    return _currentMesh->radius();
}



float Scene::getSigma() const
{
    return _sigma;
}

void Scene::setSigma(float sigma)
{
    _sigma = sigma;
    _curvatureMapIsComputed = false;
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






void Scene::initialize(){
    switch(_typeMeshUsed){
    case LOADED:    _currentMesh = _loadedMesh;    break;
    case GENERATED: _currentMesh = _generatedMesh; break;
    }
    _curvatureMapIsComputed = false;
    getMapFromMNT();


}



void Scene::getMapFromMNT(){
    vector<float> dataHeightMap = _currentMesh->getReverseHeightMap();
    _heightMap = make_shared<LoadTexture>("heightMap", dataHeightMap,GL_R32F,GL_RED,_currentMesh->getWidth(),_currentMesh->getHeight());
    vector<float> dataNormalMap = _currentMesh->getReverseNormalMap();
    _normalMap = make_shared<LoadTexture>("normalMap", dataNormalMap,GL_RGBA32F,GL_RGBA,_currentMesh->getWidth(),_currentMesh->getHeight());
}





void Scene::loadingWithLog(MeshLoader ml, const vector<string> &filepaths){
    cout << "Loading MNT from : " << endl;
    for(unsigned int i=0;i< filepaths.size() ; i++ ){
        cout << filepaths[i] << "..." << endl;
    }
    _loadedMesh = ml.vertexFromMNT(filepaths);
    _loadedMesh->printInfo();


    cout << "Generate mesh ..." << endl;
    _generatedMesh = computeMeshFromGenHeightMap(ml);
    _generatedMesh->printInfo();

}

shared_ptr<Mesh> Scene::computeMeshFromGenHeightMap(MeshLoader ml){

    int width = 200, height = 200;

    HeightMap heightMap = HeightMap("heightMapGen", width,height);
    heightMap.initialize();
    heightMap.startGenerate();
    vector<float> data = heightMap.generate(_widthViewport,_heightViewport);


    return ml.vertexFromHeightMap(data,width,height);
}


