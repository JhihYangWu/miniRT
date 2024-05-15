#include "sphere.hpp"

Sphere::Sphere(float radius, Vector3 loc, Color c) {
    this->radius = radius;
    this->loc = loc;
    this->c = c;
}

Sphere::Sphere(const Sphere& other) {
    this->radius = other.radius;
    this->loc = other.loc;
    this->c = other.c;
}

float Sphere::intersect(Ray r) {
    // eq1: x = o + t * d
    // eq2: (x - loc)^2 = radius^2
    // (o + t * d - loc)^2 = radius^2
    // ((o - loc) + t * d)^2 = radius^2
    // (o - loc)^2 + 2 * t * d * (o - loc) + t^2 * d^2 = radius^2
    // t^2 * (d^2) + t * (2 * d * (o - loc)) + ((o - loc)^2 - radius^2) = 0
    // A = d^2
    // B = 2 * d * (o - loc)
    // C = (o - loc)^2 - radius^2
    // discriminate = B^2 - 4AC
    // t = (-B +- sqrt(discriminate)) / 2A
    // discriminate > 0, 2 intersections
    // discriminate = 0, 1 intersection
    // discriminate < 0, missed sphere

    Vector3 oMinusLoc = r.o - loc;
    float A = dot(r.d, r.d);
    float B = dot(2 * r.d, oMinusLoc);
    float C = dot(oMinusLoc, oMinusLoc) - radius * radius;
    float discrim = B * B - 4 * A * C;
    if (discrim < 0.0f) return -1.0f; // missed sphere
    float t1 = (-B + sqrt(discrim)) / (2 * A);
    float t2 = (-B - sqrt(discrim)) / (2 * A);
    if (t1 > 0.0f && t2 > 0.0f) {
        return std::min(t1, t2);
    } else if (t1 > 0.0f) {
        return t1;
    } else if (t2 > 0.0f) {
        return t2;
    } else {
        // both behind camera
        return -1.0f;
    }
}

Vector3 Sphere::getNormal(Vector3 hitPt) {
    return (hitPt - loc).normalize();
}
