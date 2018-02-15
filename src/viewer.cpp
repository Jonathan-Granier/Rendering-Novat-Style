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

    vertexLoader vL;
    _vertices = vL.vertexFromHardCode();

    initShaders();

    _model = new Model(Model::NONE,"");
    //initTextures();
    //initBuffers();
    //_mesh = Mesh(_vertices,_indices,_textures);
    //_mesh.setupMesh();

    show();
}

Viewer::~Viewer() {
  //deleteBuffers();
  glfwTerminate();
}


void Viewer::initShaders()
{
    _shader.initialize("shaders/vertexshader.vert", "shaders/fragmentshader.frag");
}



void Viewer::initTextures(){

    int width, height, nrChannels;
    unsigned char *data;

    Texture texture1,texture2;
    texture1.type="texture_normal";
    texture2.type="texture_normal";

    glGenTextures(1, &texture1.id);
    glBindTexture(GL_TEXTURE_2D, texture1.id);
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




    glGenTextures(1, &texture2.id);
    glBindTexture(GL_TEXTURE_2D, texture2.id);
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

    _textures.push_back(texture1);
    _textures.push_back(texture2);

  /*  _shader.use();
    glUniform1i(glGetUniformLocation(_shader._ID, "texture_normal1"), 0);
    glUniform1i(glGetUniformLocation(_shader._ID, "texture_normal2"), 1);
*/

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


    _shader.use();

    glm::mat4 model;
    glm::mat4 view;
    glm::mat4 projection;
    model = glm::rotate(model, glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f));
    view  = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
    projection = glm::perspective(glm::radians(45.0f), (float)_SCR_WIDTH / (float)_SCR_HEIGHT, 0.1f, 100.0f);
    _shader.setMat4("model",model);
    _shader.setMat4("view",view);
    _shader.setMat4("projection",projection);

    //_model->draw(_shader);

    for(unsigned int i = 0; i < 10; i++)
    {
      glm::mat4 model;
      model = glm::translate(model, _cubePositions[i]);
      float angle = 20.0f * i;
      model = glm::rotate(model, (float)glfwGetTime()*glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
      _shader.setMat4("model", model);

      _model->draw(_shader);
    }



    _shader.disable();

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

