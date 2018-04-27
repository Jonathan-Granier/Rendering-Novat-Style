#include "generatedtexture.h"
#include <iostream>



using namespace std;


GeneratedTexture::GeneratedTexture(std::string name, const int &width, const int &height,
                                   std::shared_ptr<Shader> shader):
     Texture(name)
{
    _width = width;
    _height = height;
    _generatorShader = shader;
}



void GeneratedTexture::initialize()
{


    glGenFramebuffersEXT(1,&_FBO);
    glBindFramebuffer(GL_FRAMEBUFFER,_FBO);

    glGenTextures(1,&_ID);
    glBindTexture(GL_TEXTURE_2D,_ID);
    glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA32F,_width,_height,0,GL_RGBA,GL_FLOAT,0);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
   // float borderColor[] = { 1.0f, 1.0f, 1.0f, 1.0f };
   // glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);


    // attach depth texture as FBO's depth buffer


    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0,GL_TEXTURE_2D,_ID,0);
    GLenum DrawBuffers = GL_COLOR_ATTACHMENT0;
    glDrawBuffer(DrawBuffers);



    if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE){
        cerr << "error in framebuffer of " << _name  << endl;
        cerr << glCheckFramebufferStatus(GL_FRAMEBUFFER) << endl;
    }
}

void GeneratedTexture::startGenerate()
{
    _generatorShader->use();
}


void GeneratedTexture::generate(int widthViewport, int heightViewport)
{
    glGetIntegerv(GL_FRAMEBUFFER_BINDING, &_QTFBO); // In Qt we have only one framebuffer actif!
    glBindFramebuffer(GL_FRAMEBUFFER,_FBO);
    glViewport(0,0,_width,_height);



    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    renderQuad();

    glBindFramebuffer(GL_FRAMEBUFFER, _QTFBO);
    _generatorShader->disable();

    glViewport(0,0,widthViewport,heightViewport);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

}




void GeneratedTexture::resize(int width, int height){
    _width = width;
    _height = height;
    glBindTexture(GL_TEXTURE_2D,_ID);
    glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA32F,_width,_height,0,GL_RGBA,GL_FLOAT,0);

}



void GeneratedTexture::reloadShader()
{
    _generatorShader->reload();
}

std::shared_ptr<Shader> GeneratedTexture::generatorShader() const
{
    return _generatorShader;
}

