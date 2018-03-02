#include "camera.h"

Camera::Camera(float radius,const glm::vec3 &center,int mode)
  : _m(NONE),
    _w(0),
    _h(0),
    _p(0,0),
    _c(center),
    _r(radius),
    _t(),
    _f(45.0f),
    _d(mode),
    _up(0,0,0),
    _right(0,0,0),
    _view(0,0,0),
    _zmin(0),
    _zmax(0) {

}

void Camera::initialize(int w,int h,bool replace) {
  const float tmp1 = 100.0f;
  const float tmp2 = 3.0f;

  int wo2 = w/2;
  int ho2 = h/2;
  int rad = wo2<ho2 ? wo2 : ho2;

  // data initialization
  _m = NONE;
  _w = w;
  _h = h;
  _t = TrackBall(rad*2,glm::vec2(wo2,ho2));
  _f = 45.0f;

  // projection transformations
  if(_d==PERSP) {
    _matp = glm::perspective(_f,(float)_w/(float)_h,_r/tmp1,_r*tmp1);
  } else {
    _matp = glm::ortho((float)(-_w),(float)_w,(float)(-_h),(float)_h,0.0f,_r*100.0f);
  }

  if(!replace)
    return;

  // camera transformations
  _matm = glm::lookAt(glm::vec3(_c[0],_c[1],_c[2]-tmp2*_r),
                glm::vec3(_c[0],_c[1],_c[2]),
                glm::vec3(0.0,1.0,0.0));

  // update params
  updateCamVectors(_matm);
  updateCamDists(_matm);
}

void Camera::setFovy(float f) {
  _f = f;
  initialize(_w,_h,false);
}

void Camera::setMode(int m) {
  if(_d!=m) {
    _d = m;
    initialize(_w,_h,false);
  }
}


void Camera::setFixePosition(){
    _matp = glm::mat4(1.165184, 0.000000,  0.000000,   0.000000,
                      0.000000, 1.792591,  0.000000,   0.000000,
                      0.000000, 0.000000, -1.000000,  -1.000000,
                      0.000000, 0.000000, -361.554962, 0.000000);
    _matm = glm::mat4(0.908015, -0.011072, -0.418788, 0.000000,
                      0.045663,  0.996309,  0.072668, 0.000000,
                      0.416437, -0.085106,  0.905171, 0.000000,
                      -12.499985, 71.372101, -12304.133789, 1.000000);
}

