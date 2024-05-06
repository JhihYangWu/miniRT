#ifndef RAY_H
#define RAY_H

#include "vector3.hpp"

class Ray{
public:
    // constructors
    Ray(Vector3 origin, Vector3 direction);
    Ray(const Ray& other); // copy constructor

    // operators and methods
    Vector3 operator()(float t); // ray t time away

    // attributes
    Vector3 o; // origin
    Vector3 d; // direction, programmer is responsible for normalizing it
};

#endif
