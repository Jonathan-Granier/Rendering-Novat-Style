#include "texture.h"

#include <GL/glew.h>
// OpenGL library
#include <GL/gl.h>
// OpenGL Utility library
#include <GL/glu.h>

#include <iostream>
#include "lib/stb_image.h"

using namespace std;


Texture::Texture(std::string name): _name(name), _reverseQuad(true){}


void Texture::sendToShader(shared_ptr<Shader> shader)
{
    glActiveTexture(GL_TEXTURE0 + _ID);
    shader->setInt(_name,_ID);
    glBindTexture(GL_TEXTURE_2D, _ID);
}


void Texture::draw(std::shared_ptr<Shader> shader)
{
    sendToShader(shader);
    renderQuad();
}


void Texture::renderQuad()
{
    unsigned int quadVAO = 0;
    unsigned int quadVBO;

    float x = (float)_width/(float)_height;

    glGenVertexArrays(1, &quadVAO);
    glGenBuffers(1, &quadVBO);
    glBindVertexArray(quadVAO);
    glBindBuffer(GL_ARRAY_BUFFER, quadVBO);


    if(_reverseQuad)
    {
      float  quadVertices[] = {
           // positions        // texture Coords
           -x,  1.0f, 0.0f, 0.0f, 0.0f,
           -x, -1.0f, 0.0f, 0.0f, 1.0f,
            x,  1.0f, 0.0f, 1.0f, 0.0f,
            x, -1.0f, 0.0f, 1.0f, 1.0f,
         };
      glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
    }
    else{
      float  quadVertices[] = {
           // positions        // texture Coords
           -x,  1.0f, 0.0f, 0.0f, 1.0f,
           -x, -1.0f, 0.0f, 0.0f, 0.0f,
            x,  1.0f, 0.0f, 1.0f, 1.0f,
            x, -1.0f, 0.0f, 1.0f, 0.0f,
         };
      glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
    }
   // setup plane VAO


   glEnableVertexAttribArray(0);
   glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
   glEnableVertexAttribArray(1);
   glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
   glBindVertexArray(quadVAO);
   glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
   glBindVertexArray(0);
}
