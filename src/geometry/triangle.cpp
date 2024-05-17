#include "triangle.hpp"

#define EPSILON 0.000001

Triangle::Triangle(Vector3 p0, Vector3 p1, Vector3 p2, Color c) {
    A = p0;
    B = p1;
    C = p2;
    this->c = c;
    edge1 = B - A;
    edge2 = C - A;
    n = cross(edge1, edge2).normalize();
}

Triangle::Triangle(const Triangle& other) {
    A = other.A;
    B = other.B;
    C = other.C;
    c = other.c;
    edge1 = B - A;
    edge2 = C - A;
    n = cross(edge1, edge2).normalize();
}

float Triangle::intersect(Ray r) {
    // refer to Fast, Minimum Storage Ray Triangle Intersection 1997 paper
    // Möller–Trumbore intersection algorithm
    Vector3 pVec = cross(r.d, edge2);
    float det = dot(pVec, edge1);
    if (det > -EPSILON && det < EPSILON) return -1.0f;
    float invDet = 1.0f / det;
    Vector3 tVec = r.o - A;
    float u = dot(pVec, tVec) * invDet; // not divided by det yet
    if (u < 0.0f || u > 1.0f) return -1.0f; // missed triangle
    Vector3 qVec = cross(tVec, edge1);
    float v = dot(qVec, r.d) * invDet; // not divided by det yet
    if (v < 0.0f || u + v > 1.0f) return -1.0f; // missed triangle

    // hit triangle
    float t = dot(qVec, edge2) * invDet; // time of intersection
    return t;
}
