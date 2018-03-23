#include "model.h"

#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include "vertex.h"
#include "iostream"



using namespace std;
using namespace glm;

Model::Model(MeshLoader ml, const vector<string> &filepaths,TYPE_FILE typeFile)
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
    //_meshPlane = ml.planeFromHardCode();
    //_meshSphere = ml.vertexFromObj("models/cube.obj");

/*
    Texture texture1("textures/container.jpg","container");
    Texture texture2("textures/awesomeface.png","awesomeface");
    Texture texture3("textures/dégradé_neige_ombre.png","neige_ombre");
    Texture texture4("textures/dégradé_debug.png","degrade_debug");
    Texture texture5("textures/flat_color.png","flat_color_debug");

    _textures.push_back(texture1);
    _textures.push_back(texture2);
    _textures.push_back(texture3);
    _textures.push_back(texture4);
    _textures.push_back(texture5);

*/
}

Model::~Model()
{
    delete _mesh;
}

void Model::draw(Shader *shader)
{

    for(unsigned int i=0;i<_textures.size();i++){
        _textures[i].draw(shader);
    }
    _mesh->Draw();
    //_meshPlane->Draw();
    // always good practice to set everything back to defaults once configured.
    glActiveTexture(GL_TEXTURE0);
}

void Model::drawOnlyMesh()
{
    //_meshPlane->Draw();
    _mesh->Draw();

}

void Model::drawHeightMap(Shader *shader){

    shader->setInt("ymin",_mesh->getYmin());
    shader->setInt("ymax",_mesh->getYmax());
    if(_heightMap != NULL){
        _heightMap->print(shader);
    }
}

void Model::drawNormalMap(Shader *shader){
    if(_normalMap != NULL){
        _normalMap->print(shader);
    }
}

float Model::radius() const
{
    return _mesh->radius();
}

vec3 Model::center() const
{
    return _mesh->center();
}


void Model::getMapFromMNT(){
    vector<float> dataHeightMap = _mesh->getHeightMap();
    _heightMap = new Texture(dataHeightMap,GL_R32F,GL_RED,_mesh->getWidth(),_mesh->getHeight(),"heightMap");
    vector<float> dataNormalMap = _mesh->getNormalMap();
    _normalMap = new Texture(dataNormalMap,GL_RGB,GL_RGB,_mesh->getWidth(),_mesh->getHeight(),"normalMap");

}


