#ifndef TRACKBALL_H
#define TRACKBALL_H



#include <glm/glm.hpp>
#include "lib/glm_add.h"
#include <glm/gtc/quaternion.hpp>

using namespace glm;

class TrackBall {
 public:
  TrackBall();
  TrackBall(float radius, const vec2 &center);
  TrackBall(const TrackBall &t);

  inline TrackBall& operator = (const TrackBall &t);

  inline void beginTracking(const vec2 &pt);
  inline glm::quat track(const vec2 &pt);
  inline void setCenter(const vec2 &center);
  inline void setRadius(float radius);

 private:
  vec2 _startPos;
  vec3 _startSphPos;
  vec2 _center;
  float _radius;
};

inline TrackBall& TrackBall::operator = (const TrackBall &t) {
  _startPos    = t._startPos;
  _startSphPos = t._startSphPos;
  _center      = t._center;
  _radius      = t._radius;

  return *this;
}

inline void TrackBall::beginTracking(const vec2 &pt) {
  vec2 p = pt - _center;
  _startPos = p;
  _startSphPos = vec3(p.x, p.y, _radius);
}

inline glm::quat TrackBall::track(const vec2 &pt) {
  vec2 p = pt - _center;
  float angle = length(p-_startPos)*4/_radius;
  vec3 ptSph = vec3(p.x,p.y,_radius);
  //vec3 axis = normal(ptSph ^ _startSphPos);
  vec3 axis = normal(cross(ptSph,_startSphPos));

  if(hasNan(axis)  || hasInf(axis))
    return quat(1,0,0,0);

  return quat(axis.x,axis.y,axis.z,angle);
}

inline void TrackBall::setCenter(const vec2 &center) {
  _center = center;
}

inline void TrackBall::setRadius(float radius) {
  _radius = radius;
}





#endif // TRACKBALL_H

