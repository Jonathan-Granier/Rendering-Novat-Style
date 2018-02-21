#ifndef TRACKBALL_H
#define TRACKBALL_H


#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

#include "lib/glm_add.h"

#include <iostream>

class TrackBall {
 public:
  TrackBall();
  TrackBall(float radius, const glm::vec2 &center);
  TrackBall(const TrackBall &t);

  inline TrackBall& operator = (const TrackBall &t);

  inline void beginTracking(const glm::vec2 &pt);
  inline glm::quat track(const glm::vec2 &pt);
  inline void setCenter(const glm::vec2 &center);
  inline void setRadius(float radius);

 private:
  glm::vec2 _startPos;
  glm::vec3 _startSphPos;
  glm::vec2 _center;
  float _radius;
};

inline TrackBall& TrackBall::operator = (const TrackBall &t) {
  _startPos    = t._startPos;
  _startSphPos = t._startSphPos;
  _center      = t._center;
  _radius      = t._radius;

  return *this;
}

inline void TrackBall::beginTracking(const glm::vec2 &pt) {
  glm::vec2 p = pt - _center;
  _startPos = p;
  _startSphPos = glm::vec3(p.x, p.y, _radius);
}

inline glm::quat TrackBall::track(const glm::vec2 &pt) {
  glm::vec2 p = pt - _center;
  float angle = glm::length(p-_startPos)*4/_radius;
  glm::vec3 ptSph = glm::vec3(p.x,p.y,_radius);
  glm::vec3 axis = normal(glm::cross(ptSph, _startSphPos));

//  std::cout << "GLM VEC : ( " << axis.x << " , " << axis.y << " , " << axis.z << " ) | " << angle << std::endl;

  if(hasNan(axis)  || hasInf(axis))
    return quat(1,0,0,0);


  float a,b,c,d,tmp;
  tmp = sin(angle/2);

  a = cos(angle/2);
  b=axis.x*tmp;
  c=axis.y*tmp;
  d=axis.z*tmp;
  quat q = quat(d,a,b,c);
//  std::cout << "GLM QUAD: ( " << q[0] << " , " << q[1] << " , " << q[2] << " , " << q[3] << " )"  << std::endl;
  return q;
}

inline void TrackBall::setCenter(const glm::vec2 &center) {
  _center = center;
}

inline void TrackBall::setRadius(float radius) {
  _radius = radius;
}

#endif // TRACKBALL_H


