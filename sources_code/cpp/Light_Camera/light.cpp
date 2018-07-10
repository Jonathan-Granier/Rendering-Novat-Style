#include "light.h"
#include <iostream>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/vector_angle.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/string_cast.hpp>
using namespace glm;
using namespace std;
Light::Light(float yaw , float pitch)
{
    _yaw = yaw;
    _pitch = pitch;
    updateDirection();
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
    updateDirection();

}

void Light::moveAroundXZ(float theta)
{
    if(theta < M_PI/2.0f && theta >= 0.0f )
        _pitch = theta;

    updateDirection();

}


void Light::setFixeDirection()
{
    _yaw = 3.76215;
    _pitch = M_PI/4.0f;
    updateDirection();
}

void Light::setFixeDirection(float yaw, float pitch){
    _yaw = yaw;
    _pitch = pitch;
    updateDirection();
}

glm::vec3 Light::getDirection() const
{
    return _direction;
}

float Light::getYaw() const
{
    return _yaw;
}

float Light::getPitch() const
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





void Light::updateDirection(){
    _direction.x = cos(_pitch) * cos(_yaw);
    _direction.y = sin(_pitch);
    _direction.z = cos(_pitch) * sin(_yaw);
    _direction = normalize(_direction);
}
