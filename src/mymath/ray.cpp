#include "ray.hpp"

Ray::Ray(Vector3 origin, Vector3 direction) {
    this->o = origin;
    this->d = direction;
}

Ray::Ray(const Ray& other) {
    this->o = other.o;
    this->d = other.d;
}

Vector3 Ray::operator()(float t) {
    return o + t * d;
}
