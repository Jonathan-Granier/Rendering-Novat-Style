#include "light.h"
#include <iostream>

#include <glm/gtx/vector_angle.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/string_cast.hpp>
using namespace glm;
using namespace std;
Light::Light(vec3 position, bool mode) :
    _mode(mode),
    _position(position)
{
    _previousTheta = 45.0;
}

void Light::setFixePosition()
{
    _position =  vec3(10000.0, 14000.000000, -10000.0);
}

glm::vec3 Light::position() const
{
    return _position;
}



void Light::move(vec2 p,float width,float height)
{
    _position.x = (p[0]-(float)(width/2))/((float)(width/2));
    _position.y = (p[1]-(float)(height/2))/((float)(height/2));
    _position.z = 1.0f-std::max(fabs(_position[0]),fabs(_position[1]));
    _position = normalize(_position);
}


void Light::startMoveAroundYAxe(glm::vec2 moussePos,float width,float height){
    _oldmoussePosition = centerAndNormalize(moussePos,width,height);
}

void Light::moveAroundYAxe(vec2 moussePos,float width,float height){
    moussePos = centerAndNormalize(moussePos,width,height);



    float theta= orientedAngle(_oldmoussePosition,moussePos);


    vec3 axis(0.0,1.0,0.0);
    _position = rotate(_position,theta,axis);

    _oldmoussePosition = moussePos;
}

void Light::moveAroundXZ(float theta)
{
    if(theta > 89.0f)
        theta = 89.0f;
    if(theta < 0.0f)
        theta = 0.0f;
    cout << "theta = " << theta << endl;
    float diffTheta = theta - _previousTheta;
    if(diffTheta = 0)
    vec3 previousPosition = _position;
    vec3 axis(-_position.y,0.0,_position.x); // Move around the perpendicular of the projection vector position.
    _position = rotate(_position,glm::radians(diffTheta),axis);



    _previousTheta = theta;
}

vec2 Light::centerAndNormalize(vec2 v,float width,float height){
    v.x -= width/2.0;
    v.y -= height/2.0;
    return normalize(v);
}

