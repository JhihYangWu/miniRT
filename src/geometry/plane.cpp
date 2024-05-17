#include "plane.hpp"

#define EPSILON 0.000001

Plane::Plane(Vector3 upperLeft, Vector3 lowerLeft, Vector3 lowerRight, Color c) {
    this->upperLeft = upperLeft;
    this->lowerLeft = lowerLeft;
    this->lowerRight = lowerRight;
    this->c = c;
    u = lowerRight - lowerLeft;
    v = upperLeft - lowerLeft;
    uDirLen = u.len();
    vDirLen = v.len();
    u.normalize();
    v.normalize();
    n = cross(u, v).normalize();
}

Plane::Plane(const Plane& other) {
    this->upperLeft = other.upperLeft;
    this->lowerLeft = other.lowerLeft;
    this->lowerRight = other.lowerRight;
    this->c = other.c;
    u = lowerRight - lowerLeft;
    v = upperLeft - lowerLeft;
    uDirLen = u.len();
    vDirLen = v.len();
    u.normalize();
    v.normalize();
    n = cross(u, v).normalize();
}

float Plane::intersect(Ray r) {
    // 1. intersects r with infinite plane first
    // let p0 be any point on the plane (such as lowerLeft)
    // eq1: n . p0 = n . x
    // eq2: x = o + t * d
    // n . p0 = n . (o + t * d)
    // n . p0 - n . o = n . (t * d)
    // n . p0 - n . o = t * n . d
    // t = (n . p0 - n . o) / (n . d)
    float t = (dot(n, lowerLeft) - dot(n, r.o)) / (dot(n, r.d) + EPSILON);
    if (t < 0.0f) return -1.0f; // plane is behind ray
    Vector3 hitPt = r(t);

    // 2. check if hitPt is inside plane
    Vector3 l = hitPt - lowerLeft;
    float alpha = dot(l, u) / uDirLen;
    float beta = dot(l, v) / vDirLen;
    if (alpha >= 0.0f && alpha <= 1.0f &&
        beta >= 0.0f && beta <= 1.0f) {
        // hitPt is inside plane
        return t;
    } else {
        // hitPt is outside plane
        return -1.0f;
    }
}
