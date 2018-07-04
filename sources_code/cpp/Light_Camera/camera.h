/**
*   \file camera.h
*   \author Romain Vergne
*   \version 1.0
*   \date 26/02/2018
*/


#ifndef CAMERA_H
#define CAMERA_H

#include "trackball.h"

// OpenGL Mathematics
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/matrix_inverse.hpp>
#include <glm/gtc/type_ptr.hpp>


#include <math.h>
/**
 * @brief Define a camera link to a trackball for move the model arround the trackball.
 *   Compute model-view matrix, projection matrix and normal matrix.
 *   ! The center must be (0,0,0) (BUG).
 */
class Camera {
 public:
  enum {NONE, ROTATE, MOVEXY, MOVEZ};
  static const int PERSP=0; /**< TODO: describe */
  static const int ORTHO=1; /**< TODO: describe */

  /**
   * @brief
   *
   * @param radius
   * @param center
   * @param mode
   */
  Camera(float radius=1,const glm::vec3 &center=glm::vec3(0,0,0),int mode=PERSP);

  /**
   * @brief
   *
   * @param w
   * @param h
   * @param replace
   */
  void initialize(int w,int h,bool replace=true);
  /**
   * @brief
   *
   * @param f
   */
  void setFovy(float f);
  /**
   * @brief
   *
   * @param m
   */
  void setMode(int m);

  /**
   * @brief
   *
   * @param p
   */
  inline void initRotation(const glm::vec2 &p);
  /**
   * @brief
   *
   * @param p
   */
  inline void initMoveXY(const glm::vec2 &p);
  /**
   * @brief
   *
   * @param p
   */
  inline void initMoveZ(const glm::vec2 &p);
  /**
   * @brief
   *
   * @param p
   */
  inline void move(const glm::vec2 &p);

  /**
   * @brief
   *
   * @return int
   */
  inline int w() const { return _w; } // width
  /**
   * @brief
   *
   * @return int
   */
  inline int h() const { return _h; } // height

  /**
   * @brief
   *
   * @return const glm::vec3
   */
  inline const glm::vec3 up()    const { return _up;  } // up vector
  /**
   * @brief
   *
   * @return const glm::vec3
   */
  inline const glm::vec3 right() const { return _right; } // right vector
  /**
   * @brief
   *
   * @return const glm::vec3
   */
  inline const glm::vec3 view()  const { return _view;    } // view vector

  /**
   * @brief
   *
   * @return float
   */
  inline float zmin()  const { return _zmin;  } // min distance to object
  /**
   * @brief
   *
   * @return float
   */
  inline float zmax()  const { return _zmax;  } // max distance to object
  /**
   * @brief
   *
   * @return float
   */
  inline float fovy()  const { return _f;     } // aspect ratio

  /**
   * @brief
   *
   * @return const glm::vec2
   */
  inline const glm::vec2 pt() const { return _p; } // current clicked point

  // access
  /**
   * @brief
   *
   * @return glm::mat4
   */
  inline glm::mat4 projMatrix() const {return _matp;}
  /**
   * @brief
   *
   * @return glm::mat4
   */
  inline glm::mat4 mdvMatrix () const {return _matm;}
  /**
   * @brief
   *
   * @return glm::mat3
   */
  inline glm::mat3 normalMatrix () const {return glm::mat3(glm::inverseTranspose(mdvMatrix()));}

  /**
   * @brief Set the camera to a hard code fixe point.
   */
  void setFixePosition();

  void setFixePosition2();
protected:
  /**
   * @brief
   *
   * @param p
   */
  inline void rotate(const glm::vec2 &p);
  /**
   * @brief
   *
   * @param p
   */
  inline void moveXY(const glm::vec2 &p);
  /**
   * @brief
   *
   * @param p
   */
  inline void moveZ(const glm::vec2 &p);

 private:
  /**
   * @brief
   *
   * @param m
   */
  inline void updateCamVectors  (const glm::mat4 &m);
  /**
   * @brief
   *
   * @param m
   */
  inline void updateCamDists    (const glm::mat4 &m);

  int           _m; /**< moving mode */
  int           _w; /**< width */
  int           _h; /**< height */
  glm::vec2     _p; /**< departure point when moving  */
  glm::vec3     _c; /**< center */
  float         _r; /**< radius */
  TrackBall     _t; /**< trackball */
  float         _f; /**< fovy */
  glm::ivec4    _v; /**< viewport */
  int           _d; /**< mode (persp or ortho) */

  glm::vec3     _up; /**< TODO: describe */
  glm::vec3     _right; /**< TODO: describe */
  glm::vec3     _view; /**< TODO: describe */
  float         _zmin; /**< TODO: describe */
  float         _zmax; /**< TODO: describe */
  glm::mat4     _matm; /**< TODO: describe */
  glm::mat4     _matp; /**< TODO: describe */
};

/**
 * @brief
 *
 * @param p
 */
inline void Camera::initRotation(const glm::vec2 &p) {
  _m = ROTATE;
  _p = p;
  _t.beginTracking(_p);
}

/**
 * @brief
 *
 * @param p
 */
inline void Camera::initMoveXY(const glm::vec2 &p) {
  _m = MOVEXY;
  _p = p;
}

/**
 * @brief
 *
 * @param p
 */
inline void Camera::initMoveZ(const glm::vec2 &p) {
  _m = MOVEZ;
  _p = p;
}

/**
 * @brief
 *
 * @param p
 */
inline void Camera::move(const glm::vec2 &p) {
  switch(_m) {
  case ROTATE: rotate(p); break;
  case MOVEXY: moveXY(p); break;
  case MOVEZ:  moveZ(p);  break;
  default: break;
  }
}

/**
 * @brief
 *
 * @param p
 */
inline void Camera::rotate(const glm::vec2 &p) {
  glm::mat4 mo = _matm;

  // compute rotation matrix
  const glm::vec3 tr = glm::vec3(mo[3][0],mo[3][1],mo[3][2]);
  const glm::mat4 t1 = gml_add::identityTranslateEq(-tr);
  const glm::mat4 t2 = gml_add::identityTranslateEq(tr);


  glm::quat q = _t.track(p);
  const glm::mat4  mr = gml_add::quatToMat4(q);

  _matm = t2*mr*t1*mo; // TODO test

  // update params
  _p = p;
  _t.beginTracking(_p);
  updateCamVectors(_matm);
  updateCamDists(_matm);
}

/**
 * @brief
 *
 * @param p
 */
inline void Camera::moveXY(const glm::vec2 &p) {
  const float s = _r/300.0;

  // compute translation matrix
  _matm = gml_add::translateEq(_matm,glm::vec3((p[0]-_p[0])*s,(p[1]-_p[1])*s,0.0f));

  // update params
  _p = p;
  updateCamDists(_matm);
}

/**
 * @brief
 *
 * @param p
 */
inline void Camera::moveZ(const glm::vec2 &p) {
  const float s = _r/100.0;

  // compute translation matrix
  _matm = gml_add::translateEq(_matm,glm::vec3(0.0f,0.0f,(_p[1]-p[1])*s));

  // update params
  _p = p;
  updateCamDists(_matm);
}

/**
 * @brief
 *
 * @param m
 */
inline void Camera::updateCamVectors(const glm::mat4 &m) {
  _up    = glm::vec3(m[0][0],m[1][0],m[2][0]);
  _right = glm::vec3(m[0][1],m[1][1],m[2][1]);
  _view  = glm::vec3(m[0][2],m[1][2],m[2][2]);
}

/**
 * @brief
 *
 * @param m
 */
inline void Camera::updateCamDists(const glm::mat4 &m) {
  const float fact = 1.0f;
  const float eps = 0.0f;
  const glm::vec4 ca  = m*glm::vec4(_c[0],_c[1],_c[2],1.0);
  const float d = glm::length(glm::vec3(ca[0],ca[1],ca[2]));

  _zmin = d-fact*_r;
  _zmin = _zmin<=eps ? eps : _zmin;
  _zmax = _zmin + fact*_r;
}

#endif // CAMERA_H

