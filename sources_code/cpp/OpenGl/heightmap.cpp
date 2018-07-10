#include "heightmap.h"
#include <iostream>



using namespace std;



HeightMap::HeightMap(string name, const int &width, const int &height):
    GeneratedTexture(name,width,height,make_shared<Shader>("shaders/genheightmap.vert","shaders/genheightmap.frag"))
{
}

void HeightMap::initialize()
{

    glGenFramebuffers(1,&_fbo);
    glBindFramebuffer(GL_FRAMEBUFFER,_fbo);

    glGenTextures(1,&_id);
    glBindTexture(GL_TEXTURE_2D,_id);
    glTexImage2D(GL_TEXTURE_2D,0,GL_R32F,_width,_height,0,GL_RED,GL_FLOAT,0);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);



    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0,GL_TEXTURE_2D,_id,0);
    GLenum DrawBuffers = GL_COLOR_ATTACHMENT0;
    glDrawBuffer(DrawBuffers);



    if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE){
        cerr << "error in framebuffer of " << _name  << endl;
        cerr << glCheckFramebufferStatus(GL_FRAMEBUFFER) << endl;
    }
}





vector<float> HeightMap::generate(int widthViewport, int heightViewport)
{


    glGetIntegerv(GL_FRAMEBUFFER_BINDING, &_qtfbo); // Qt have only one framebuffer actif

    glBindFramebuffer(GL_FRAMEBUFFER,_fbo);
    glViewport(0,0,_width,_height);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    renderQuad();



    GLint numBytes = _width*_height;
    float pixels[numBytes];
    glReadPixels(0,0,_width,_height,GL_RED,GL_FLOAT,pixels);


    glBindFramebuffer(GL_FRAMEBUFFER, _qtfbo);
    _generatorShader->disable();

    glViewport(0,0,widthViewport,heightViewport);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    vector<float> dataVec;
    copy(&pixels[0],&pixels[_width*_height],back_inserter(dataVec));
    return dataVec;

}
