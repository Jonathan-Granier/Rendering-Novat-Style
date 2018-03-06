#include "model.h"

#include "glm/glm.hpp"
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
        break;
        case NONE:  _mesh = ml.vertexFromHardCode();
        break;
        default:    _mesh = ml.vertexFromHardCode();
        break;
    }


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

}

Model::~Model()
{
    delete _mesh;
}

void Model::draw(Shader *shader)
{

    for(unsigned int i=0;i<_textures.size();i++){
        _textures[i].draw(shader,i);
    }

    _mesh->Draw();

    // always good practice to set everything back to defaults once configured.
    glActiveTexture(GL_TEXTURE0);
}

float Model::radius() const
{
    return _mesh->radius();
}

vec3 Model::center() const
{
    return _mesh->center();
}


