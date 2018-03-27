#include "generatedtexture.h"
#include <iostream>

using namespace std;
GeneratedTexture::GeneratedTexture(std::string name, const int &width, const int &height,
                                   const GLchar* genVertex, const GLchar* genFrag):
     Texture(name)
{
    _reverseQuad = true;
    _width = width;
    _height = height;
    _generatorShader = make_shared<Shader>(genVertex, genFrag);
}



void GeneratedTexture::initialize()
{
    // configure depth map FBO
    // -----------------------

    cout << "PROUT" << endl;

    glGenFramebuffers(1,&_FBO);
    glBindFramebuffer(GL_FRAMEBUFFER,_FBO);
    // create depth texture


    glGenTextures(1,&_ID);
    glBindTexture(GL_TEXTURE_2D,_ID);
    glTexImage2D(GL_TEXTURE_2D,0,GL_RGB32F,_width,_height,0,GL_RGB,GL_FLOAT,0);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
    float borderColor[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);


    // attach depth texture as FBO's depth buffer


    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0,GL_TEXTURE_2D,_ID,0);
    glDrawBuffer(GL_NONE);
    //glReadBuffer(GL_NONE);
    //glBindFramebuffer(GL_FRAMEBUFFER,0);

   // glBindFramebuffer(GL_FRAMEBUFFER, _oldFBO);

    if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE){
        cerr << "error in framebuffer of " << _name  << endl;
        cerr << glCheckFramebufferStatus(GL_FRAMEBUFFER) << endl;
    }

}

void GeneratedTexture::startGenerate()
{
    _generatorShader->use();
}


void GeneratedTexture::generate()
{
    glGetIntegerv(GL_FRAMEBUFFER_BINDING, &_QTFBO); // In Qt we have only one framebuffer actif!

    glBindFramebuffer(GL_FRAMEBUFFER,_FBO);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    renderQuad();

    glBindFramebuffer(GL_FRAMEBUFFER, _QTFBO);
    _generatorShader->disable();

}


void GeneratedTexture::reloadShader()
{
    _generatorShader->reload();
}

