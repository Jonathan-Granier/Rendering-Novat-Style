#include "scene.h"

#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include "vertex.h"
#include "iostream"



using namespace std;
using namespace glm;

Scene::Scene(MeshLoader ml, const vector<string> &filepaths,TYPE_FILE typeFile)
{

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
    _meshLightVector = ml.axisFromHardCode();
    _meshSphere = ml.vertexFromObj("models/sphere.obj");


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

    for(unsigned int i=0;i<_textures.size();i++){
        _textures[i].sendToShader(shader);
    }

    mat4 modelMesh;

    shader->setMat4("modelMat",modelMesh);
    _mesh->Draw();
    mat4 modelPlane;
    shader->setMat4("modelMat",modelPlane);
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
        shader->setInt("selectTexture",1);
        _normalMap->draw(shader);

    }
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
    vector<float> dataHeightMap = _mesh->getHeightMap();
    _heightMap = make_shared<LoadTexture>("heightMap", dataHeightMap,GL_R32F,GL_RED,_mesh->getWidth(),_mesh->getHeight());
    vector<float> dataNormalMap = _mesh->getNormalMap();
    _normalMap = make_shared<LoadTexture>("normalMap", dataNormalMap,GL_RGB,GL_RGB,_mesh->getWidth(),_mesh->getHeight());
}


