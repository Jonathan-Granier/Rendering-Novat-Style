/**
*   \file camera.h
*   \author Romain Vergne
*   \version 1.0
*   \date 26/02/2018
*
*/




#ifndef TRACKBALL_H
#define TRACKBALL_H


#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

#include "lib/glm_add.h"

#include <iostream>
/**
 * @brief A sphere that can move around his center
 */
class TrackBall {
 public:
  TrackBall();
  /**
   * @brief
   *
   * @param radius
   * @param center
   */
  TrackBall(float radius, const glm::vec2 &center);
  /**
   * @brief
   *
   * @param t
   */
  TrackBall(const TrackBall &t);

  /**
   * @brief
   *
   * @param t
   * @return TrackBall &operator
   */
  inline TrackBall& operator = (const TrackBall &t);

  /**
   * @brief
   *
   * @param pt
   */
  inline void beginTracking(const glm::vec2 &pt);
  /**
   * @brief
   *
   * @param pt
   * @return glm::quat
   */
  inline glm::quat track(const glm::vec2 &pt);
  /**
   * @brief
   *
   * @param center
   */
  inline void setCenter(const glm::vec2 &center);
  /**
   * @brief
   *
   * @param radius
   */
  inline void setRadius(float radius);

 private:
  glm::vec2 _startPos; /**< TODO: describe */
  glm::vec3 _startSphPos; /**< TODO: describe */
  glm::vec2 _center; /**< TODO: describe */
  float _radius; /**< TODO: describe */
};

/**
 * @brief
 *
 * @param t
 * @return TrackBall &TrackBall::operator
 */
inline TrackBall& TrackBall::operator = (const TrackBall &t) {
  _startPos    = t._startPos;
  _startSphPos = t._startSphPos;
  _center      = t._center;
  _radius      = t._radius;

  return *this;
}

/**
 * @brief
 *
 * @param pt
 */
inline void TrackBall::beginTracking(const glm::vec2 &pt) {
  glm::vec2 p = pt - _center;
  _startPos = p;
  _startSphPos = glm::vec3(p.x, p.y, _radius);
}

/**
 * @brief
 *
 * @param pt
 * @return glm::quat
 */
inline glm::quat TrackBall::track(const glm::vec2 &pt) {
  glm::vec2 p = pt - _center;
  float angle = glm::length(p-_startPos)*4/_radius;
  glm::vec3 ptSph = glm::vec3(p.x,p.y,_radius);
  glm::vec3 axis = gml_add::normal(glm::cross(ptSph, _startSphPos));
  if(gml_add::hasNan(axis)  || gml_add::hasInf(axis))
    return glm::quat(1,0,0,0);


  float a,b,c,d,tmp;
  tmp = sin(angle/2);

  a = cos(angle/2);
  b=axis.x*tmp;
  c=axis.y*tmp;
  d=axis.z*tmp;
  return glm::quat(d,a,b,c);
}

/**
 * @brief
 *
 * @param center
 */
inline void TrackBall::setCenter(const glm::vec2 &center) {
  _center = center;
}

/**
 * @brief
 *
 * @param radius
 */
inline void TrackBall::setRadius(float radius) {
  _radius = radius;
}

#endif // TRACKBALL_H


