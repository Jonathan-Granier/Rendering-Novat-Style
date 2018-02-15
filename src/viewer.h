#ifndef VIEWER_H
#define VIEWER_H

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <vector>


#include "lib/stb_image.h"
#include "mesh.h"
#include "shader.h"
#include "camera.h"
#include "vertexLoader.h"
#include "model.h"



class Viewer
{
public:
    Viewer();
    ~Viewer();
private:
    void initShaders();
    void initTextures();
    void show();
    void paintGL();

    void processInput();


    GLFWwindow* _window;
    Shader _shader;

    vector<Texture> _textures;
    const unsigned int _SCR_WIDTH = 800;
    const unsigned int _SCR_HEIGHT = 600;
    //data

    std::vector<Vertex> _vertices;
    Model *_model;



    glm::vec3 _cubePositions[10] = {
      glm::vec3( 0.0f,  0.0f,  0.0f),
      glm::vec3( 2.0f,  5.0f, -15.0f),
      glm::vec3(-1.5f, -2.2f, -2.5f),
      glm::vec3(-3.8f, -2.0f, -12.3f),
      glm::vec3( 2.4f, -0.4f, -3.5f),
      glm::vec3(-1.7f,  3.0f, -7.5f),
      glm::vec3( 1.3f, -2.0f, -2.5f),
      glm::vec3( 1.5f,  2.0f, -2.5f),
      glm::vec3( 1.5f,  0.2f, -1.5f),
      glm::vec3(-1.3f,  1.0f, -1.5f)
    };


    std::vector<unsigned int> _indices = {  // note that we start from 0!
        0, 1, 3,   // first triangle
        1, 2, 3    // second triangle
    };

};

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

#endif // VIEWER_H
