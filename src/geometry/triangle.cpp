#include "triangle.hpp"

#define EPSILON 0.00000001

Triangle::Triangle(Vector3 p0, Vector3 p1, Vector3 p2) {
    A = p0;
    B = p1;
    C = p2;
    Vector3 AC = C - A;
    Vector3 CB = B - C;
    Vector3 BA = A - B;
    BC = C - B;
    CA = A - C;
    AB = B - A;
    n = cross(BC, BA).normalize();
    vA = AC - proj(AC, BC);
    vB = BA - proj(BA, CA);
    vC = CB - proj(CB, AB);
}

Triangle::Triangle(const Triangle& other) {
    A = other.A;
    B = other.B;
    C = other.C;
    Vector3 AC = C - A;
    Vector3 CB = B - C;
    Vector3 BA = A - B;
    BC = C - B;
    CA = A - C;
    AB = B - A;
    n = cross(BC, BA).normalize();
    vA = AC - proj(AC, BC);
    vB = BA - proj(BA, CA);
    vC = CB - proj(CB, AB);
}

float Triangle::intersect(Ray r) {
    // 1. intersects r with the triangle plane first
    // eq1: n . p0 = n . x
    // eq2: x = o + t * d
    // n . p0 = n . (o + t * d)
    // n . p0 - n . o = n . (t * d)
    // n . p0 - n . o = t * n . d
    // t = (n . p0 - n . o) / (n . d)
    float t = (dot(n, A) - dot(n, r.o)) / (dot(n, r.d) + EPSILON);
    if (t < 0.0f) return -1.0f; // triangle is behind ray
    Vector3 hitPt = r(t);

    // 2. and then checks if it is in the triangle
    // Math for Game Developers - Ray Triangle Intersection https://www.youtube.com/watch?v=EZXz-uPyCyA
    Vector3 AI = hitPt - A;
    Vector3 BI = hitPt - B;
    Vector3 CI = hitPt - C;
    float alpha = 1 - dot(vA, AI) / (dot(vA, AB) + EPSILON);
    if (alpha < 0.0f || alpha > 1.0f) return -1.0f;
    float beta = 1 - dot(vB, BI) / (dot(vB, BC) + EPSILON);
    if (beta < 0.0f || beta > 1.0f) return -1.0f;
    float gamma = 1 - dot(vC, CI) / (dot(vC, CA) + EPSILON);
    if (gamma < 0.0f || gamma > 1.0f) return -1.0f;

    return t;
}

Vector3 Triangle::getNormal() {
    return n;
}
