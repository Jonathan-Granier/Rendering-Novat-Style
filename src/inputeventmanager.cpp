#include "inputeventmanager.h"



void inputEventManager::framebuffer_size_callback(Camera *cam, int width, int height)
{
    cam->initialize(width,height,false);
    glViewport(0, 0, width, height);
}


void inputEventManager::mouse_callback(double xpos, double ypos){

}

void inputEventManager::scroll_callback(double xoffset, double yoffset){

}
