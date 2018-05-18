#include "texture.h"


#include <GL/glew.h>
// OpenGL library
#include <GL/gl.h>
// OpenGL Utility library
#include <GL/glu.h>


#include "caller.h"


#include <iostream>
#include "lib/stb_image.h"

using namespace std;

Texture::Texture(std::string name): _name(name){}


void Texture::sendToShader(shared_ptr<Shader> shader)
{
    glActiveTexture(GL_TEXTURE0 + _ID);
    shader->setInt(_name,_ID);
    glBindTexture(GL_TEXTURE_2D, _ID);
}



void Texture::sendToShader(shared_ptr<Shader> shader,string name)
{
    glActiveTexture(GL_TEXTURE0 + _ID);
    shader->setInt(name,_ID);
    glBindTexture(GL_TEXTURE_2D, _ID);
}


void Texture::draw(std::shared_ptr<Shader> shader)
{
    sendToShader(shader);
    renderQuad();
}



vector<float> Texture::getDataRED(){
    GLint numBytes = _width*_height;
    float* pixels = (float*)malloc(sizeof(float)*numBytes);
    //glReadPixels(0,0,_width,_height,GL_RED,GL_FLOAT,pixels);


    glActiveTexture(GL_TEXTURE0 + _ID);
    glBindTexture(GL_TEXTURE_2D ,_ID);
    glGetTexImage(GL_TEXTURE_2D,0,GL_RED,GL_FLOAT,pixels);


    vector<float> dataVec;

    for(int i = _height-1; i >=0; i--){
        for(int j =0; j< _width;j++){
            //cout <<pixels[i*_width+ j] << "|";
            dataVec.push_back(pixels[i*_width+ j]);
        }
    }
    free(pixels);

    return dataVec;

}


void Texture::printValueRED(){

    GLint numBytes = _width*_height;
    float pixels[numBytes];

    glActiveTexture(GL_TEXTURE0 + _ID);
    glBindTexture(GL_TEXTURE_2D ,_ID);
    glGetTexImage(GL_TEXTURE_2D,0,GL_RED,GL_FLOAT,pixels);


    cout << _name << endl;
    for(int i = _height-1; i >=0; i--){
        for(int j =0; j< _width;j++){
            cout <<pixels[i*_width+ j] << "|";
            //dataVec.push_back(pixels[i*_width+ j]);
        }
        cout << endl;
    }
}


int Texture::meshOffset() const
{
    return _meshOffset;
}

void Texture::setMeshOffset(int meshOffset)
{
    _meshOffset = meshOffset;
}

int Texture::getWidth() const
{
    return _width;
}

int Texture::getHeight() const
{
    return _height;
}

std::string Texture::getName() const
{
    return _name;
}

unsigned int Texture::getID() const
{
    return _ID;
}

/************************************************
 *              Private Functions               *
 ************************************************/

void Texture::renderQuad()
{
    unsigned int quadVAO = 0;
    unsigned int quadVBO;
    
    
    float  quadVertices[] = {
        // positions        // texture Coords
         -1.0f,  1.0f, 0.0f, 0.0f, 1.0f,
         -1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
          1.0f,  1.0f, 0.0f, 1.0f, 1.0f,
          1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
       };


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
