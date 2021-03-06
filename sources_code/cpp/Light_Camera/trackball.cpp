/**
*   \file trackball.cpp
*   \author Romain Vergne
*   \version 1.0
*   \date 26/02/2018
*
*/



#include "trackball.h"

TrackBall::TrackBall()
: _startPos(),
  _startSphPos(),
  _center(glm::vec2(0.0f, 0.0f)),
  _radius(1) {
}

TrackBall::TrackBall(float radius, const glm::vec2 &center)
: _startPos(),
  _startSphPos(),
  _center(center),
  _radius(radius) {

}

TrackBall::TrackBall(const TrackBall &t)
: _startPos(t._startPos),
  _startSphPos(t._startSphPos),
  _center(t._center),
  _radius(t._radius) {

}
