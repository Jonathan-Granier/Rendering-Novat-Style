/**
* @file texture.cpp
* @author Jonathan Granier
* @copyright  This code was writen for the research project
*             "Rendering panorama maps in the "atelier Novat" style.
*             Performed at Inria Grenoble Rhöne-Alpes, Maverick Team.
*             Univ.Grenoble Alpes, LJK, INRIA.
*             Under the supervision of : Joelle THOLLOT and Romain VERGNE.
*/
#include "texture.h"


#include <GL/glew.h>
// OpenGL library
#include <GL/gl.h>
// OpenGL Utility library
#include <GL/glu.h>



#include <iostream>
#include "lib/stb_image.h"

using namespace std;

Texture::Texture(std::string name): _name(name){}


void Texture::sendToShader(shared_ptr<Shader> shader)
{
    glActiveTexture(GL_TEXTURE0 + _id);
    shader->setInt(_name,_id);
    glBindTexture(GL_TEXTURE_2D, _id);
}



void Texture::sendToShader(shared_ptr<Shader> shader,string name)
{
    glActiveTexture(GL_TEXTURE0 + _id);
    shader->setInt(name,_id);
    glBindTexture(GL_TEXTURE_2D, _id);
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


    glActiveTexture(GL_TEXTURE0 + _id);
    glBindTexture(GL_TEXTURE_2D ,_id);
    glGetTexImage(GL_TEXTURE_2D,0,GL_RED,GL_FLOAT,pixels);


    vector<float> dataVec;

    for(int i = _height-1; i >=0; i--){
        for(int j =0; j< _width;j++){
            dataVec.push_back(pixels[i*_width+ j]);
        }
    }
    free(pixels);

    return dataVec;

}


int Texture::getHeightMapOffset() const
{
    return _heightMapOffset;
}

void Texture::setHeightMapOffset(int heightMapOffset)
{
    _heightMapOffset = heightMapOffset;
}

int Texture::getWidth() const
{
    return _width;
}

int Texture::getHeight() const
{
    return _height;
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
