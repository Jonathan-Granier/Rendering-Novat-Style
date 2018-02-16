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


    glfwSetWindowUserPointer(_window, this);
    glfwSetFramebufferSizeCallback(_window, framebuffer_size_callback); // Resize function


    initShaders();

    _model = new Model(Model::NONE,"");
    _cam = new Camera(_model->radius(),_model->center());
    _cam->initialize(_SCR_WIDTH,_SCR_HEIGHT,true);

    //initTextures();
    //initBuffers();
    //_mesh = Mesh(_vertices,_indices,_textures);
    //_mesh.setupMesh();

    show();
}

Viewer::~Viewer() {
  //deleteBuffers();
  delete _model;
  delete _cam;
  delete _shader;
  glfwTerminate();
}


void Viewer::initShaders()
{
    _shader = new Shader("shaders/vertexshader.vert", "shaders/fragmentshader.frag");
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


    _shader->use();
  //  glUniformMatrix4fv(glGetUniformLocation(id,"mdvMat"),1,GL_FALSE,&(_cam->mdvMatrix()[0][0]));
    _shader->setMat4("mdvMat",_cam->mdvMatrix());
    _shader->setMat4("projMat",_cam->projMatrix());
    _shader->setMat4("normalMat",_cam->normalMatrix());

    glm::mat4 model;
    glm::mat4 view;
    glm::mat4 projection;
    model = glm::rotate(model, glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f));
    view  = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
    projection = glm::perspective(glm::radians(45.0f), (float)_SCR_WIDTH / (float)_SCR_HEIGHT, 0.1f, 100.0f);
    _shader->setMat4("model",model);
    _shader->setMat4("view",view);
    _shader->setMat4("projection",projection);

    _model->draw(_shader);
/*
    for(unsigned int i = 0; i < 10; i++)
    {
      glm::mat4 model;
      model = glm::translate(model, _cubePositions[i]);
      float angle = 20.0f * i;
      model = glm::rotate(model, (float)glfwGetTime()*glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
      _shader->setMat4("model", model);

      _model->draw(_shader);
    }
*/


    _shader->disable();

    glfwPollEvents(); // Checks if any events are triggered
    glfwSwapBuffers(_window); // Double buffer

}






void Viewer::processInput()
{
    if(glfwGetKey(_window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(_window, true);
}

Camera *Viewer::cam() const
{
    return _cam;
}

// Hors classe

//TODO add _cam
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    void *data = glfwGetWindowUserPointer(window);
    Viewer *v = static_cast<Viewer *>(data);
    inputEventManager::framebuffer_size_callback(v->cam(),width,height);
}

void mouse_callback(GLFWwindow* window,double xpos, double ypos)
{
    void *data = glfwGetWindowUserPointer(window);
    Viewer *v = static_cast<Viewer *>(data);
    inputEventManager::framebuffer_size_callback(v->cam(),width,height);
}

void scroll_callback(GLFWwindow* window,double xoffset, double yoffset)
{
    void *data = glfwGetWindowUserPointer(window);
    Viewer *v = static_cast<Viewer *>(data);
    inputEventManager::framebuffer_size_callback(v->cam(),width,height);
}
