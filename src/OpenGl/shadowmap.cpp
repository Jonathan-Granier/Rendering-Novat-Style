#include "shadowmap.h"
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

using namespace std;
using namespace glm;

ShadowMap::ShadowMap(string name, const int &width, const int &height):
    GeneratedTexture(name,width,height,"shaders/shadowmap.vert","shaders/shadowmap.frag")
{
    _reverseQuad = false;
}
void ShadowMap::initialize()
{
    // configure depth map FBO
    // -----------------------

    glGenFramebuffers(1,&_FBO);
    glBindFramebuffer(GL_FRAMEBUFFER,_FBO);
    // create depth texture

    glGenTextures(1,&_ID);
    glBindTexture(GL_TEXTURE_2D,_ID);
    glTexImage2D(GL_TEXTURE_2D,0,GL_DEPTH_COMPONENT16,_width,_height,0,GL_DEPTH_COMPONENT,GL_FLOAT,0);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
    float borderColor[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);


    // attach depth texture as FBO's depth buffer


    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT,GL_TEXTURE_2D,_ID,0);
    glDrawBuffer(GL_NONE);
    //glReadBuffer(GL_NONE);
    //glBindFramebuffer(GL_FRAMEBUFFER,0);

   // glBindFramebuffer(GL_FRAMEBUFFER, _oldFBO);

    if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE){
        cerr << "ERROR IN FRAMBUFFER OF SHADOW MAP" << endl;
        cerr << glCheckFramebufferStatus(GL_FRAMEBUFFER) << endl;
    }


 //   _shadowMap = make_shared<Texture>(depthMap,name,_SHADOW_WIDTH,_SHADOW_HEIGHT);

}

glm::mat4 ShadowMap::generate(std::shared_ptr<Scene> scene, glm::vec3 lightPosition, float widthViewport, float heightViewPort)
{
    glCullFace(GL_FRONT); //TODO TEST
    glm::mat4 lightProjection , lightView;
    float near_plane =1.0f;

    float radius = scene->radius();
    lightProjection = glm::ortho(-radius, radius, -radius, radius, near_plane, radius*10);
    lightView =  glm::lookAt(lightPosition, glm::vec3(0.0f), glm::vec3(0.0, 1.0, 0.0));
    _lightSpaceMatrix = lightProjection * lightView;


    // render scene from light's point of view
    _generatorShader->setMat4("lightSpaceMatrix",_lightSpaceMatrix);

    glViewport(0,0,_width,_height);

    glGetIntegerv(GL_FRAMEBUFFER_BINDING, &_QTFBO); // In Qt we have only one framebuffer actif!

    glBindFramebuffer(GL_FRAMEBUFFER,_FBO);
    glClear(GL_DEPTH_BUFFER_BIT);



    scene->drawOnlyMesh();

    //glBindFramebuffer(GL_FRAMEBUFFER,0);
    glBindFramebuffer(GL_FRAMEBUFFER, _QTFBO);

    // reset viewport
    glViewport(0, 0, widthViewport, heightViewPort);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    _generatorShader->disable();

    glCullFace(GL_BACK);

    return _lightSpaceMatrix;
}



glm::mat4 ShadowMap::lightSpaceMatrix() const
{
    return _lightSpaceMatrix;
}



