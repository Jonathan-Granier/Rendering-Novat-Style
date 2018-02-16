#ifndef INPUTEVENTMANAGER_H
#define INPUTEVENTMANAGER_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "camera.h"

class inputEventManager
{
public:
    static void framebuffer_size_callback(Camera *cam, int width, int height);
    static void mouse_callback(double xpos, double ypos);
    static void scroll_callback(double xoffset, double yoffset);
};

#endif // INPUTEVENTMANAGER_H
