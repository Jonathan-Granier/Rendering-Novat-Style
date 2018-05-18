#include "lighttextures.h"
#include <iostream>

using namespace std;

LightTextures::LightTextures(std::string namelightMap, std::string nameAngleMap, const int &width, const int &height, std::shared_ptr<Shader> shader):
    GeneratedTexture(namelightMap,width,height,shader)
{
    nameAnglesMap = nameAngleMap;
}



void LightTextures::initialize()
{

    glGenFramebuffers(1,&_FBO);
    glBindFramebuffer(GL_FRAMEBUFFER,_FBO);

    // Texture 1 :
    glGenTextures(1,&_ID);
    glBindTexture(GL_TEXTURE_2D,_ID);
    glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA32F,_width,_height,0,GL_RGBA,GL_FLOAT,0);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
   // float borderColor[] = { 1.0f, 1.0f, 1.0f, 1.0f };
   // glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);





    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0,GL_TEXTURE_2D,_ID,0);

    // Texture 2 :
/**/
    glGenTextures(1,&_ID_Angles);
    glBindTexture(GL_TEXTURE_2D,_ID_Angles);
    glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA32F,_width,_height,0,GL_RGBA,GL_FLOAT,0);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
   // float borderColor[] = { 1.0f, 1.0f, 1.0f, 1.0f };
   // glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);

    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1,GL_TEXTURE_2D,_ID_Angles,0);

    /*


    GLenum DrawBuffers = GL_COLOR_ATTACHMENT0;
    glDrawBuffer(DrawBuffers);

    /**/



    if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE){
        cerr << "error in framebuffer of " << _name  << endl;
        cerr << glCheckFramebufferStatus(GL_FRAMEBUFFER) << endl;
    }
}



void LightTextures::generate(int widthViewport, int heightViewport)
{
    glGetIntegerv(GL_FRAMEBUFFER_BINDING, &_QTFBO); // In Qt we have only one framebuffer actif!
    glBindFramebuffer(GL_FRAMEBUFFER,_FBO);
    glViewport(0,0,_width,_height);
    GLenum DrawBuffers[2] = {GL_COLOR_ATTACHMENT0,GL_COLOR_ATTACHMENT1};
    glDrawBuffers(2,DrawBuffers);



    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    renderQuad();

    glBindFramebuffer(GL_FRAMEBUFFER, _QTFBO);
    _generatorShader->disable();
    glViewport(0,0,widthViewport,heightViewport);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

}

void LightTextures::sendToShader(shared_ptr<Shader> shader)
{



    glActiveTexture(GL_TEXTURE0 + _ID);
    shader->setInt(_name,_ID);
    glBindTexture(GL_TEXTURE_2D, _ID);

    glActiveTexture(GL_TEXTURE0 + _ID_Angles);
    shader->setInt(nameAnglesMap,_ID_Angles);
    glBindTexture(GL_TEXTURE_2D, _ID_Angles);

}

void LightTextures::draw(std::shared_ptr<Shader> shader)
{

    sendToShader(shader);
    renderQuad();
}


void LightTextures::resize(int width, int height){
    _width = width;
    _height = height;
    glBindTexture(GL_TEXTURE_2D,_ID);
    glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA32F,_width,_height,0,GL_RGBA,GL_FLOAT,0);
    glBindTexture(GL_TEXTURE_2D,_ID_Angles);
    glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA32F,_width,_height,0,GL_RGBA,GL_FLOAT,0);


}


unsigned int LightTextures::ID_Angles() const
{
    return _ID_Angles;
}
