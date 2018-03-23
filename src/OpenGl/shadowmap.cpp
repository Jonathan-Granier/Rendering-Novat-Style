#include "shadowmap.h"
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

using namespace std;
using namespace glm;

ShadowMap::ShadowMap(string name)
{
    //Open the 2 shaders

    _generatorShader = make_shared<Shader>("shaders/shadowmap.vert", "shaders/shadowmap.frag");
    _debugShader = make_shared<Shader>("shaders/shadowmapdebug.vert", "shaders/shadowmapdebug.frag");

    initShadowMap(name);


}

void ShadowMap::initShadowMap(string name)
{
    // configure depth map FBO
    // -----------------------

    glGenFramebuffers(1,&_depthMapFBO);
    glBindFramebuffer(GL_FRAMEBUFFER,_depthMapFBO);
    // create depth texture

    unsigned int depthMap;
    glGenTextures(1,&depthMap);
    glBindTexture(GL_TEXTURE_2D,depthMap);
    glTexImage2D(GL_TEXTURE_2D,0,GL_DEPTH_COMPONENT16,_SHADOW_WIDTH,_SHADOW_HEIGHT,0,GL_DEPTH_COMPONENT,GL_FLOAT,0);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
    float borderColor[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);


    // attach depth texture as FBO's depth buffer


    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT,GL_TEXTURE_2D,depthMap,0);
    glDrawBuffer(GL_NONE);
    //glReadBuffer(GL_NONE);
    //glBindFramebuffer(GL_FRAMEBUFFER,0);

   // glBindFramebuffer(GL_FRAMEBUFFER, _oldFBO);

    if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE){
        cerr << "ERROR IN FRAMBUFFER OF SHADOW MAP" << endl;
    }


    _shadowMap = make_shared<Texture>(depthMap,name);

}

glm::mat4 ShadowMap::RenderFromLight(std::shared_ptr<Model> model, glm::vec3 lightPosition, float width, float height)
{
    glCullFace(GL_FRONT); //TODO TEST
    glm::mat4 lightProjection , lightView;
    float near_plane =1.0f, far_plane=7.5f;

    float radius = model->radius();
    lightProjection = glm::ortho(-radius, radius, -radius, radius, near_plane, radius*10);
    lightView =  glm::lookAt(lightPosition, glm::vec3(0.0f), glm::vec3(0.0, 1.0, 0.0));
    _lightSpaceMatrix = lightProjection * lightView;

    // render scene from light's point of view
    _generatorShader->use();
    _generatorShader->setMat4("lightSpaceMatrix",_lightSpaceMatrix);

    glViewport(0,0,_SHADOW_WIDTH,_SHADOW_HEIGHT);

    glGetIntegerv(GL_FRAMEBUFFER_BINDING, &_oldFBO); // In Qt we have only one framebuffer actif!

    glBindFramebuffer(GL_FRAMEBUFFER,_depthMapFBO);
    glClear(GL_DEPTH_BUFFER_BIT);



    model->drawOnlyMesh();

    //glBindFramebuffer(GL_FRAMEBUFFER,0);
    glBindFramebuffer(GL_FRAMEBUFFER, _oldFBO);

    // reset viewport
    glViewport(0, 0, width, height);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    _generatorShader->disable();

    glCullFace(GL_BACK);

    return _lightSpaceMatrix;
}



void ShadowMap::draw(std::shared_ptr<Shader> shader){
    _shadowMap->draw(shader);
}

void ShadowMap::reloadShader()
{
    _generatorShader->reload();
    _debugShader->reload();
}

glm::mat4 ShadowMap::lightSpaceMatrix() const
{
    return _lightSpaceMatrix;
}


void ShadowMap::DebugShadowMap()
{
    _debugShader->use();
    //Draw the texture
    _shadowMap->print(_debugShader);
    //renderQuad();

    _debugShader->disable();
}

void ShadowMap::renderQuad()
{
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
