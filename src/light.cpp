#include "light.h"

using namespace glm;

Light::Light(vec3 position, bool mode) :
    _mode(mode),
    _position(position)
{

}

void Light::setFixePosition()
{
    _position = vec3(-0.877768, -0.459660, 0.135041);
}

glm::vec3 Light::position() const
{
    return _position;
}



void Light::move(vec2 p,float width,float height)
{
    _position.x = (p[0]-(float)(width/2))/((float)(width/2));
    _position.y = (p[1]-(float)(height/2))/((float)(height/2));
    _position.z = 1.0f-max(fabs(_position[0]),fabs(_position[1]));
    _position = normalize(_position);
}
