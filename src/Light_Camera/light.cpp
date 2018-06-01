#include "light.h"
#include <iostream>

#include <glm/gtx/vector_angle.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/string_cast.hpp>
using namespace glm;
using namespace std;
Light::Light(float yaw , float pitch)
{
    _yaw = yaw;
    _pitch = pitch;
    updatePosition();
}


void Light::startMoveAroundYAxe(glm::vec2 moussePos,float width,float height){
    _oldmoussePosition = centerAndNormalize(moussePos,width,height);
}

void Light::moveAroundYAxe(vec2 moussePos,float width,float height){
    moussePos = centerAndNormalize(moussePos,width,height);
    float theta= orientedAngle(_oldmoussePosition,moussePos);
    _yaw -= theta;
    //Modulo
    _yaw = _yaw - 2*M_PI*floor(_yaw/(2.0 * M_PI));


    _oldmoussePosition = moussePos;
    updatePosition();

}

void Light::moveAroundXZ(float theta)
{
    if(theta < M_PI/2.0f && theta >= 0.0f )
        _pitch = theta;

    updatePosition();

}


void Light::setFixePosition()
{
    _yaw = -M_PI/4.0f;
    _pitch = M_PI/4.0f;
    updatePosition();
}

void Light::setFixePosition(float yaw, float pitch){
    _yaw = yaw;
    _pitch = pitch;
    updatePosition();
}

glm::vec3 Light::position() const
{
    return _position;
}

float Light::yaw() const
{
    return _yaw;
}

float Light::pitch() const
{
    return _pitch;
}

/************************************************
 *              Private Functions               *
 ************************************************/

vec2 Light::centerAndNormalize(vec2 v,float width,float height){
    v.x -= width/2.0;
    v.y -= height/2.0;
    return normalize(v);
}





void Light::updatePosition(){
    _position.x = cos(_pitch) * cos(_yaw);
    _position.y = sin(_pitch);
    _position.z = cos(_pitch) * sin(_yaw);
    _position = normalize(_position);
}
