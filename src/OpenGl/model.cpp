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
        break;
        case NONE:  _mesh = ml.cubeFromHardCode();
        break;
        default:    _mesh = ml.cubeFromHardCode();
        break;
    }
    _meshPlane = ml.planeFromHardCode();
   //  _meshSphere = ml.vertexFromObj("models/cube.obj");


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







void Model::draw(Shader *shader,vec3 lightPosition)
{

    for(unsigned int i=0;i<_textures.size();i++){
        _textures[i].draw(shader,i);
    }


  //  mat4 modelMesh;
  //  mat4 modelPlane;
  //  mat4 modelSphere;
  //  vec3 l = lightPosition;
   // modelSphere = translate(modelSphere,l);
   // modelSphere = scale(modelSphere,vec3(10.0f));

   // shader->setMat4("model",modelMesh);
    _mesh->Draw();
   // shader->setMat4("model",modelPlane);
    _meshPlane->Draw();
   // shader->setMat4("model",modelSphere);
   // _meshSphere->Draw();


    // always good practice to set everything back to defaults once configured.
    glActiveTexture(GL_TEXTURE0);
}


void Model::initShadowMap(){
    // configure depth map FBO
    // -----------------------

    glGenFramebuffers(1,&_depthMapFBO);
    // create depth texture

    unsigned int depthMap;
    glGenTextures(1,&depthMap);
    glBindTexture(GL_TEXTURE_2D,depthMap);
    glTexImage2D(GL_TEXTURE_2D,0,GL_DEPTH_COMPONENT,_SHADOW_WIDTH,_SHADOW_HEIGHT,0,GL_DEPTH_COMPONENT,GL_FLOAT,NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
    float borderColor[] = { 1.0, 1.0, 1.0, 1.0 };
    glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);

    // attach depth texture as FBO's depth buffer
    glBindFramebuffer(GL_FRAMEBUFFER,_depthMapFBO);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT,GL_TEXTURE_2D,depthMap,0);
    glDrawBuffer(GL_NONE);
    glReadBuffer(GL_NONE);
    glBindFramebuffer(GL_FRAMEBUFFER,0);


    Texture depthTex(depthMap,"depthMap");
    _textures.push_back(depthTex);
}

mat4 Model::RenderFromLight(vec3 lightPosition,Shader *shader,float width,float height){
    glm::mat4 lightProjection , lightView;
    float near_plane =1.0f, far_plane=7.5f;


    lightProjection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, near_plane, far_plane);
    lightView =  glm::lookAt(lightPosition, glm::vec3(0.0f), glm::vec3(0.0, 1.0, 0.0));
    _lightSpaceMatrix = lightProjection * lightView;
    // render scene from light's point of view
    shader->use();
    shader->setMat4("_lightSpaceMatrix",_lightSpaceMatrix);

    glViewport(0,0,_SHADOW_WIDTH,_SHADOW_HEIGHT);

    glGetIntegerv(GL_FRAMEBUFFER_BINDING, &_oldFBO);

    glBindFramebuffer(GL_FRAMEBUFFER,_depthMapFBO);
    glClear(GL_DEPTH_BUFFER_BIT);
    for(unsigned int i=0;i<_textures.size();i++){
        _textures[i].draw(shader,i);
    }
    _meshPlane->Draw();
    _mesh->Draw();

    glBindFramebuffer(GL_FRAMEBUFFER, _oldFBO);

    // reset viewport
    glViewport(0, 0, width, height);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    shader->disable();


    mat4 biasMatrix(
                0.5, 0.0, 0.0, 0.0,
                0.0, 0.5, 0.0, 0.0,
                0.0, 0.0, 0.5, 0.0,
                0.5, 0.5, 0.5, 1.0
            );

    _lightSpaceMatrix = biasMatrix*_lightSpaceMatrix;

    return _lightSpaceMatrix;
}


void Model::DebugShadowMap(Shader *shader){
    shader->next();
    shader->use();
    for(unsigned int i=0;i<_textures.size();i++){
        _textures[i].draw(shader,i);
    }

    renderQuad();
    shader->disable();
    shader->previous();
}

void Model::renderQuad(){
    unsigned int quadVAO = 0;
    unsigned int quadVBO;

    float quadVertices[] = {
           // positions        // texture Coords
           -1.0f,  1.0f, 0.0f, 0.0f, 1.0f,
           -1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
            1.0f,  1.0f, 0.0f, 1.0f, 1.0f,
            1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
       };
       // setup plane VAO
       glGenVertexArrays(1, &quadVAO);
       glGenBuffers(1, &quadVBO);
       glBindVertexArray(quadVAO);
       glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
       glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
       glEnableVertexAttribArray(0);
       glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
       glEnableVertexAttribArray(1);
       glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
       glBindVertexArray(quadVAO);
       glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
       glBindVertexArray(0);
}


float Model::radius() const
{
    return _mesh->radius();
}

vec3 Model::center() const
{
    return _mesh->center();
}


glm::mat4 Model::getLightSpaceMatrix() const
{
    return _lightSpaceMatrix;
}
