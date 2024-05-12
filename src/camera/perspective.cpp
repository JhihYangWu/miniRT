#include "perspective.hpp"
#include <math.h>

PerspectiveCam::PerspectiveCam(Vector3 loc, Vector3 lookAt, float fovY) {
    this->loc = loc;
    up = Vector3(0, 1, 0);
    imgPlaneDist = 1 / tan(fovY * (M_PI / 180) / 2);
    w = (loc - lookAt).normalize();
    u = cross(up, w).normalize();
    v = cross(w, u).normalize();
}

Ray PerspectiveCam::generateRay(float x, float y) {
    Vector3 dir = u * x + v * y + -w * imgPlaneDist;
    return Ray(loc, dir);
}
