#ifndef TrackBall_TEST_H
#define TrackBall_TEST_H

#include "lib/vec2.h"
#include "lib/vec3.h"
#include "lib/quat.h"

#include <iostream>

class TrackBall_TEST {
 public:
  TrackBall_TEST();
  TrackBall_TEST(float radius, const Vec2f &center);
  TrackBall_TEST(const TrackBall_TEST &t);

  inline TrackBall_TEST& operator = (const TrackBall_TEST &t);

  inline void beginTracking(const Vec2f &pt);
  inline Quatf track(const Vec2f &pt);
  inline void setCenter(const Vec2f &center);
  inline void setRadius(float radius);

 private:
  Vec2f _startPos;
  Vec3f _startSphPos;
  Vec2f _center;
  float _radius;
};

inline TrackBall_TEST& TrackBall_TEST::operator = (const TrackBall_TEST &t) {
  _startPos    = t._startPos;
  _startSphPos = t._startSphPos;
  _center      = t._center;
  _radius      = t._radius;

  return *this;
}

inline void TrackBall_TEST::beginTracking(const Vec2f &pt) {
  Vec2f p = pt - _center;
  _startPos = p;
  _startSphPos = Vec3f(p.x(), p.y(), _radius);
}

inline Quatf TrackBall_TEST::track(const Vec2f &pt) {
  Vec2f p = pt - _center;
  float angle = (p-_startPos).length()*4/_radius;
  Vec3f ptSph = Vec3f(p.x(),p.y(),_radius);
  Vec3f axis = (ptSph ^ _startSphPos).normal();


//  std::cout << "TEST VEC: ( " << axis.x() << " , " << axis.y() << " , " << axis.z() << " ) | " << angle << std::endl;

  if(axis.hasNan()  || axis.hasInf())
    return Quatf(1,0,0,0);
 // std::cout << "TEST HERE" << std::endl;
    Quatf q = Quatf(axis,angle);
 //   std::cout << "TEST QUAD: ( " << q[0] << " , " << q[1] << " , " << q[2] << " , " << q[3] << " )"  << std::endl;

  return q;
}

inline void TrackBall_TEST::setCenter(const Vec2f &center) {
  _center = center;
}

inline void TrackBall_TEST::setRadius(float radius) {
  _radius = radius;
}

#endif // TrackBall_TEST_H

