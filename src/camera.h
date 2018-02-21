#ifndef CAMERA_H
#define CAMERA_H

#include "trackball.h"

// OpenGL Mathematics
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/matrix_inverse.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>

#include <math.h>

class Camera {
 public:
  enum {NONE, ROTATE, MOVEXY, MOVEZ};
  static const int PERSP=0;
  static const int ORTHO=1;

  Camera(float radius=1,const glm::vec3 &center=glm::vec3(0,0,0),int mode=PERSP);

  void initialize(int w,int h,bool replace=true);
  void setFovy(float f);
  void setMode(int m);

  inline void initRotation(const glm::vec2 &p);
  inline void initMoveXY(const glm::vec2 &p);
  inline void initMoveZ(const glm::vec2 &p);
  inline void move(const glm::vec2 &p);

  inline int w() const { return _w; } // width
  inline int h() const { return _h; } // height

  inline const glm::vec3 up()    const { return _view;  } // up vector
  inline const glm::vec3 right() const { return _right; } // right vector
  inline const glm::vec3 view()  const { return _up;    } // view vector

  inline float zmin()  const { return _zmin;  } // min distance to object
  inline float zmax()  const { return _zmax;  } // max distance to object
  inline float fovy()  const { return _f;     } // aspect ratio

  inline const glm::vec2 pt() const { return _p; } // current clicked point

  // access
  inline glm::mat4 projMatrix() const {return _matp;}
  inline glm::mat4 mdvMatrix () const {return _matm;}
  inline glm::mat3 normalMatrix () const {return glm::mat3(glm::inverseTranspose(mdvMatrix()));}

 protected:
  inline void rotate(const glm::vec2 &p);
  inline void moveXY(const glm::vec2 &p);
  inline void moveZ(const glm::vec2 &p);

 private:
  inline void updateCamVectors(const mat4 &m);
  inline void updateCamDists(const mat4 &m);

  int           _m; // moving mode
  int           _w; // width
  int           _h; // height
  glm::vec2     _p; // departure point when moving
  glm::vec3     _c; // center
  float         _r; // radius
  TrackBall     _t; // trackball
  float         _f; // fovy
  glm::ivec4    _v; // viewport
  int           _d; // mode (persp or ortho)

  glm::vec3     _up;
  glm::vec3     _right;
  glm::vec3     _view;
  float         _zmin;
  float         _zmax;
  glm::mat4     _matm;
  glm::mat4     _matp;
};

inline void Camera::initRotation(const glm::vec2 &p) {
  _m = ROTATE;
  _p = p;
  _t.beginTracking(_p);
}

inline void Camera::initMoveXY(const glm::vec2 &p) {
  _m = MOVEXY;
  _p = p;
}

inline void Camera::initMoveZ(const glm::vec2 &p) {
  _m = MOVEZ;
  _p = p;
}

inline void Camera::move(const glm::vec2 &p) {
  switch(_m) {
  case ROTATE: rotate(p); break;
  case MOVEXY: moveXY(p); break;
  case MOVEZ:  moveZ(p);  break;
  default: break;
  }
}

inline void Camera::rotate(const glm::vec2 &p) {
  glm::mat4 mo = _matm;

  // compute rotation matrix
  const glm::vec3 tr = vec3(mo[3][0],mo[3][1],mo[3][2]);
  const glm::mat4  t1 =  identityTranslateEq(-tr);
  const glm::mat4  t2 =  identityTranslateEq(tr);


  quat q = _t.track(p);
  const glm::mat4  mr = quatToMat4(q);

  _matm = t2*mr*t1*mo; // TODO test

  // update params
  _p = p;
  _t.beginTracking(_p);
  updateCamVectors(_matm);
  updateCamDists(_matm);
}

inline void Camera::moveXY(const glm::vec2 &p) {
  const float s = _r/300.0;

  // compute translation matrix
  _matm = translateEq(_matm,glm::vec3((p[0]-_p[0])*s,(p[1]-_p[1])*s,0.0f));

  // update params
  _p = p;
  updateCamDists(_matm);
}

inline void Camera::moveZ(const glm::vec2 &p) {
  const float s = _r/100.0;

  // compute translation matrix
  _matm = translateEq(_matm,glm::vec3(0.0f,0.0f,(_p[1]-p[1])*s));

  // update params
  _p = p;
  updateCamDists(_matm);
}

inline void Camera::updateCamVectors(const glm::mat4 &m) {
  _up    = glm::vec3(m[0][0],m[1][0],m[2][0]);
  _right = glm::vec3(m[0][1],m[1][1],m[2][1]);
  _view  = glm::vec3(m[0][2],m[1][2],m[2][2]);
}

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

