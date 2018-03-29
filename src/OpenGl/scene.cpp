#include "scene.h"

#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include "vertex.h"
#include "iostream"

#include "meshloader.h"


using namespace std;
using namespace glm;

Scene::Scene(const vector<string> &filepaths,TYPE_FILE typeFile)
{
    MeshLoader ml;
    switch (typeFile){
        case OBJ:   _mesh = ml.vertexFromObj(filepaths[0]);
        break;
        case MNT:   _mesh = ml.vertexFromMNT(filepaths);
                    getMapFromMNT();
        break;
        case NONE:  _mesh = ml.cubeFromHardCode();
        break;
        default:    _mesh = ml.cubeFromHardCode();
        break;
    }

    _meshPlane = ml.planeFromHardCode();
    _meshSphere = ml.vertexFromObj("models/sphere.obj");


    _curvatureMap = make_shared<GeneratedTexture>("curvatureMap",_mesh->getWidth(),_mesh->getHeight(),
                                                  "shaders/curvature.vert","shaders/curvature.frag");

    _lightMap = make_shared<GeneratedTexture>("lightMap",_mesh->getWidth(),_mesh->getHeight(),
                                                  "shaders/computelight.vert","shaders/computelight.frag");
    _curvatureMap->initialize();
    _lightMap->initialize();

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

Scene::~Scene()
{
    //delete _mesh;
}

void Scene::draw(shared_ptr<Shader> shader, vec3 lightPosition)
{

    _lightMap->sendToShader(shader);

    for(unsigned int i=0;i<_textures.size();i++){
        _textures[i].sendToShader(shader);
    }

    mat4 modelMesh;

    shader->setMat4("modelMat",modelMesh);
    _mesh->Draw();
   // _meshPlane->Draw();
    mat4 modelSphere;
    modelSphere = glm::translate(modelSphere,lightPosition/5.0f);
    modelSphere = glm::scale(modelSphere,vec3(_mesh->radius()/20.0,_mesh->radius()/20.0,_mesh->radius()/20.0));
    shader->setMat4("modelMat",modelSphere);
   _meshSphere->Draw();
    // always good practice to set everything back to defaults once configured.
    glActiveTexture(GL_TEXTURE0);
}

void Scene::drawOnlyMesh()
{
    _mesh->Draw();
}

void Scene::drawHeightMap(shared_ptr<Shader> shader){

    if(_heightMap != NULL){
        shader->setInt("ymin",_mesh->getYmin());
        shader->setInt("ymax",_mesh->getYmax());
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

void Scene::drawLightMap(std::shared_ptr<Shader> shader)
{
    if(_lightMap != NULL){
        _lightMap->draw(shader);

    }
}

void Scene::computeCurvatureMap(int widthViewport,int heightViewport)
{
    _curvatureMap->startGenerate();
    _normalMap->sendToShader(_curvatureMap->generatorShader());
    _curvatureMap->generate(widthViewport,heightViewport);
}

void Scene::computeLightMap(vec3 lightPosition, int widthViewport, int heightViewport)
{
    _lightMap->startGenerate();
    _lightMap->generatorShader()->setVec3("lightPosition",lightPosition);

    _curvatureMap->sendToShader(_lightMap->generatorShader());
    _lightMap->generate(widthViewport,heightViewport);
}


void Scene::reloadGenerateTexturesShader(){
    _curvatureMap->reloadShader();
    _lightMap->reloadShader();
}


float Scene::radius() const
{
    return _mesh->radius();
}

vec3 Scene::center() const
{
    return _mesh->center();
}


void Scene::getMapFromMNT(){
    vector<float> dataHeightMap = _mesh->getReverseHeightMap();
    _heightMap = make_shared<LoadTexture>("heightMap", dataHeightMap,GL_R32F,GL_RED,_mesh->getWidth(),_mesh->getHeight());
    vector<float> dataNormalMap = _mesh->getReverseNormalMap();
    _normalMap = make_shared<LoadTexture>("normalMap", dataNormalMap,GL_RGB,GL_RGB,_mesh->getWidth(),_mesh->getHeight());
}


