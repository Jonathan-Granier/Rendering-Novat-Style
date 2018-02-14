#include "viewer.h"
#include <unistd.h>
Viewer::Viewer()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  //
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);          // Pour MAC OSX

    _window = glfwCreateWindow(_SCR_WIDTH, _SCR_HEIGHT, "Rendu-Style-Novat", NULL, NULL);
    if (_window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        exit(0);
    }
    glfwMakeContextCurrent(_window);


    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        exit(0);
    }

    glViewport(0, 0, _SCR_WIDTH, _SCR_HEIGHT);
    glfwSetFramebufferSizeCallback(_window, framebuffer_size_callback); // Resize function


    initShader();
    initBuffers();
    initTextures();
    show();
}

Viewer::~Viewer() {
  deleteBuffers();
  glfwTerminate();
}


void Viewer::initShader()
{
    _shader.initialize("shaders/vertexshader.vert", "shaders/fragmentshader.frag");
}
void Viewer::initBuffers()
{

    glGenVertexArrays(1, &_VAO);
    glGenBuffers(1, &_VBO);
    glGenBuffers(1, &_EBO);

    glBindVertexArray(_VAO);
    glBindBuffer(GL_ARRAY_BUFFER, _VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(_vertices), _vertices, GL_STATIC_DRAW); // Catapultage au CGU des vertices
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(_indices), _indices, GL_STATIC_DRAW); // Catapultage au CGU des indices


    //glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0); // Interpretation des données
    //glEnableVertexAttribArray(0);


    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // color attribute
    //glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    //glEnableVertexAttribArray(1);
    // texture coord attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0); // On ferme le VBO
    glBindVertexArray(0);   //On fermle le VAO

}

void Viewer::initTextures(){

    int width, height, nrChannels;
    unsigned char *data;

    glGenTextures(1, &_texture1);
    glBindTexture(GL_TEXTURE_2D, _texture1);
    // set the texture wrapping/filtering options (on the currently bound texture object)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load and generate the texture
    stbi_set_flip_vertically_on_load(true);
    data = stbi_load("textures/container.jpg", &width, &height, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture 1" << std::endl;
    }
    stbi_image_free(data);

    glGenTextures(1, &_texture2);
    glBindTexture(GL_TEXTURE_2D, _texture2);
    // set the texture wrapping/filtering options (on the currently bound texture object)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load and generate the texture
    data = stbi_load("textures/awesomeface.png", &width, &height, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture 2" << std::endl;
    }
    stbi_image_free(data);
    _shader.use();
    glUniform1i(glGetUniformLocation(_shader._ID, "texture1"), 0);
    glUniform1i(glGetUniformLocation(_shader._ID, "texture2"), 1);
}

void Viewer::deleteBuffers()
{
    glDeleteVertexArrays(1, &_VAO);
    glDeleteBuffers(1,&_EBO);
    glDeleteBuffers(1, &_VBO);

}
void Viewer::show()
{
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    glEnable(GL_DEPTH_TEST);
    while(!glfwWindowShouldClose(_window))
    {
        paintGL();
    }
}

 //Render Loop
void Viewer::paintGL()
{
    //Input
    processInput();

    //Rendering commands here
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // bind Texture
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, _texture1);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, _texture2);


    _shader.use();


    glm::mat4 view;
    glm::mat4 projection;
    //model = glm::rotate(model, (float)glfwGetTime() * glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f));
    view  = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
    projection = glm::perspective(glm::radians(45.0f), (float)_SCR_WIDTH / (float)_SCR_HEIGHT, 0.1f, 100.0f);
    //_shader.setMat4("model",model);
    _shader.setMat4("view",view);
    _shader.setMat4("projection",projection);


    glBindVertexArray(_VAO);
    for(unsigned int i = 0; i < 10; i++)
    {
      glm::mat4 model;
      model = glm::translate(model, _cubePositions[i]);
      float angle = 20.0f * i;
      model = glm::rotate(model, (float)glfwGetTime()*glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
      _shader.setMat4("model", model);

      glDrawArrays(GL_TRIANGLES, 0, 36);
    }


    glDrawArrays(GL_TRIANGLES,0,36);
    //glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    //glBindVertexArray(0);


    _shader.disable();
    // Check and call envents and swap the buffers
    glfwPollEvents(); // Checks if any events are triggered
    glfwSwapBuffers(_window); // Double buffer

}






void Viewer::processInput()
{
    if(glfwGetKey(_window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(_window, true);
}

// Hors classe
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

