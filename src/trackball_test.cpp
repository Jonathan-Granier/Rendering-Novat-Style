#include "trackball_test.h"


TrackBall_TEST::TrackBall_TEST()
: _startPos(),
  _startSphPos(),
  _center(Vec2f(0, 0)),
  _radius(1) {
}

TrackBall_TEST::TrackBall_TEST(float radius, const Vec2f &center)
: _startPos(),
  _startSphPos(),
  _center(center),
  _radius(radius) {

}

TrackBall_TEST::TrackBall_TEST(const TrackBall_TEST &t)
: _startPos(t._startPos),
  _startSphPos(t._startSphPos),
  _center(t._center),
  _radius(t._radius) {

}
